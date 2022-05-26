from typing import OrderedDict
from collections import OrderedDict
import numpy as np

from .layers import *
from utils.optimizer import *
from utils.util import *

class MultiLayerNetExtended:
    def __init__(self, input_size, hidden_size_list, output_size, weight_init_std=0.01, 
                 activation='relu', use_batchnorm=False, weight_decay_lambda=0, 
                 use_dropout=True, dropout_ratio=0.5, use_weights=False, weights=None):

        self.params = {}
        self.use_batchnorm = use_batchnorm
        self.weight_decay_lambda = weight_decay_lambda
        self.use_dropout = use_dropout
        self.hidden_layer_num = len(hidden_size_list) # 은닉층 개수
        
        if use_weights and weights is not None :
            self.params = np.load(weights, allow_pickle=True).item().copy()
            print("==== weights loaded ====")
        else :
            # 가중치 초기화
            all_size_list = [input_size] + hidden_size_list + [output_size]        
            for idx in range(1, len(all_size_list)):
                self.params['W' + str(idx)] = weight_init_std * np.random.randn(all_size_list[idx-1], all_size_list[idx])
                self.params['b' + str(idx)] = np.zeros(all_size_list[idx])        
            
        
        # 계층 생성
        activation_layer = {'sigmoid': Sigmoid, 'relu': Relu}
        self.layers = OrderedDict()

        for idx in range(1, self.hidden_layer_num+1):
            self.layers['Affine' + str(idx)] = Affine(self.params['W' + str(idx)],
                                                      self.params['b' + str(idx)])
            if self.use_batchnorm:
                self.params['gamma' + str(idx)] = np.ones(hidden_size_list[idx-1])
                self.params['beta' + str(idx)] = np.zeros(hidden_size_list[idx-1])
                self.layers['BatchNorm' + str(idx)] = BatchNormalization(self.params['gamma' + str(idx)], self.params['beta' + str(idx)])
                
            self.layers['Activation' + str(idx)] = activation_layer[activation]()
            
            if self.use_dropout:
                self.layers['Dropout' + str(idx)] = Dropout(dropout_ratio)
        
        idx = self.hidden_layer_num + 1
        self.layers['Affine' + str(idx)] = Affine(self.params['W' + str(idx)], 
                                                  self.params['b' + str(idx)])
        self.lastLayer = SoftmaxWithLoss()
        
        
    def predict(self, x, train_flg=False): # train_flg 추가
        for key, layer in self.layers.items(): # key와 layer 추출
            if "BatchNorm" in key or "Dropout" in key:  # 학습 및 추론 구별
                x = layer.forward(x, train_flg)
            else:
                x = layer.forward(x)
        return x

    def loss(self, x, t, train_flg=False):  # train_flg 추가
        y = self.predict(x, train_flg)      # train_flg 추가

        W1 = self.params['W1']
        W2 = self.params['W2']
        
        # 각 weight에 대해 합산
        weight_decay = 0
        for idx in range(1, self.hidden_layer_num + 2):
            W = self.params['W' + str(idx)]
            weight_decay += 0.5 * self.weight_decay_lambda * np.sum(W**2)       
        
        return self.lastLayer.forward(y, t) + weight_decay
    
    def accuracy(self, x, t):  
        y = self.predict(x)       
        y = np.argmax(y, axis=1)  
        
        accuracy = np.sum(y == t) / float(x.shape[0])  
        return accuracy
    
    def numerical_gradient(self, f, x):
        h = 1e-4 # 0.0001
        grad = np.zeros_like(x)
    
        it = np.nditer(x, flags=['multi_index'], op_flags=['readwrite'])
        while not it.finished:
            idx = it.multi_index
            tmp_val = x[idx]
            x[idx] = float(tmp_val) + h
            fxh1 = f(x) # f(x+h)

            x[idx] = tmp_val - h 
            fxh2 = f(x) # f(x-h)
            grad[idx] = (fxh1 - fxh2) / (2*h)

            x[idx] = tmp_val # 값 복원
            it.iternext()   
        
        return grad

    def gradient(self, x, t):
        self.loss(x, t, train_flg=True) # train_flg 추가
        
        dout = 1
        dout = self.lastLayer.backward(dout)
        
        layers = list(self.layers.values())
        layers.reverse()
        
        for layer in layers:
            dout = layer.backward(dout)
        
        grads = {}
        
        # 각 가중치에 대해 gradient 계산
        for idx in range(1, self.hidden_layer_num+2):
            grads['W' + str(idx)] = self.layers['Affine' + str(idx)].dW + self.weight_decay_lambda * self.params['W' + str(idx)]
            grads['b' + str(idx)] = self.layers['Affine' + str(idx)].db

            if self.use_batchnorm and idx != self.hidden_layer_num+1: 
                # 마지막 계층은 Batch Normalization 사용 안함
                grads['gamma' + str(idx)] = self.layers['BatchNorm' + str(idx)].dgamma
                grads['beta' + str(idx)] = self.layers['BatchNorm' + str(idx)].dbeta       
        
        return grads # dictionary 형
