import sys
import numpy as np
import matplotlib.pyplot as plt

from nets.multi_layer_net import MultiLayerNetExtended
from utils.util import shuffle_dataset, load_config
from nets.data_loader import load_cifar10
from utils.logger import Logger
from utils.trainer import Trainer

if __name__ == '__main__' :
    config = load_config('config/config.yaml')

    hidden_list     = config['network']['hidden_list']
    input_size      = config['network']['input_size']
    output_size     = config['network']['output_size']
    weight_init_std = config['network']['weight_init_std']
    use_batchnorm   = config['network']['use_batchnorm']
    use_dropout     = config['network']['use_dropout']
    weight_decay    = config['network']['weight_decay']

    validation_rate = config['train']['validation_rate']
    epochs          = config['train']['epochs']
    batch_size      = config['train']['batch_size']
    optimizer       = config['train']['optimizer']
    lr              = config['train']['learning_rate']
    verbose         = config['train']['verbose']
    logfile         = config['train']['log_file']

    weight          = config['weight']['file']

    sys.stdout = Logger(logfile)
    
    x_train, y_train, x_test, y_test = load_cifar10('./data\\cifar_10_batches_bin')

    # 훈련 데이터 뒤섞기
    x_train, y_train = shuffle_dataset(x_train, y_train)

    # 검증 데이터 분할
    validation_num = int(x_train.shape[0] * validation_rate)

    x_val = x_train[:validation_num]
    y_val = y_train[:validation_num]
    x_train = x_train[validation_num:]
    y_train = y_train[validation_num:]
                 
    network = MultiLayerNetExtended(input_size=input_size, hidden_size_list=hidden_list,
                                    output_size=output_size,
                                    weight_init_std=weight_init_std,
                                    use_batchnorm=use_batchnorm,
                                    weight_decay_lambda=weight_decay,
                                    use_dropout=use_dropout)
    
    trainer = Trainer(network, x_train, y_train, x_val, y_val, 
                      epochs=epochs, mini_batch_size=batch_size,
                      optimizer=optimizer, optimizer_param={'lr' : lr}, verbose=verbose)
    
    trainer.train()

    train_acc_list = trainer.train_acc_list
    val_acc_list = trainer.val_acc_list

    for idx in range(1, len(hidden_list) + 1) :
        network.params['BN'+str(idx)+'Mean'] = network.layers['BatchNorm'+str(idx)].running_mean
        network.params['BN'+str(idx)+'Var'] = network.layers['BatchNorm'+str(idx)].running_var

    np.save(weight, network.params)

    print('==== weight saved ====')

    # 그래프 그리기 =============
    markers = {'train' : 'o', 'val' : 's'}
    x = np.arange(len(train_acc_list))
    plt.plot(x, train_acc_list, marker='o', label='train', markevery=10)
    plt.plot(x, val_acc_list, marker='s', label='val', markevery=10)
    plt.xlabel('epochs')
    plt.ylabel('accuracy')
    plt.ylim(0, 1.0)
    plt.legend(loc = 'lower right')
    plt.savefig('results/train-val-result.png')