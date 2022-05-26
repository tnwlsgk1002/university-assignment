import os
import yaml
import numpy as np

def smooth_curve(x) :
    '''손실 함수의 그래프를 매끄럽게 하기 위해 사용'''
    window_len = 11
    s = np.r_[x[window_len-1:0:-1], x, x[-1:-window_len:-1]]
    w = np.kaiser(window_len, 2)
    y = np.convolve(w/w.sum(), s, mode='valid')
    return y[5:len(y)-5]

def shuffle_dataset(x, t) :
    '''데이터셋을 뒤섞는다.
    Parameter
    ---------
    x : 훈련 데이터
    t : 정답 테이블
    
    Returns
    ---------
    x, t : 뒤섞은 훈련 데이터와 정답 테이블
    '''
    permutation = np.random.permutation(x.shape[0])
    x = x[permutation, :] if x.ndim == 2 else x[permutation, :,:,:]
    t = t[permutation]

    return x, t

def conv_output_size(input_size, filter_size, stride=1, pad=0) :
    return (input_size + 2*pad - filter_size) / stride + 1

def im2col(input_data, filter_h, filter_w, stride=1, pad=0) :
    '''다수의 이미지를 입력받아 2차원 배열로 변환한다(평탄화).
    
    Parameters
    ----------
    input_data : 4차원 배열 형태의 입력 데이터(이미지 수, 채널 수, 높이, 너비)
    filter_h : 필터의 높이
    filter_w : 필터의 너비
    stride : 스트라이드
    pad : 패딩
    
    ----------
    
    '''
    pass


def load_config(config_name) :
    with open(config_name) as file :
        config = yaml.safe_load(file)
    return config

    