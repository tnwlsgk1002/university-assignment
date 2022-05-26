import sys
import numpy as np

from nets.multi_layer_net import MultiLayerNetExtended
from utils.util import load_config
from nets.data_loader import load_cifar10
from utils.logger import Logger

if __name__ == '__main__' :
    config = load_config('config/config.yaml')

    hidden_list     = config['network']['hidden_list']
    input_size      = config['network']['input_size']
    output_size     = config['network']['output_size']
    use_batchnorm   = config['network']['use_batchnorm']
    weight          = config['weight']['file']
    logfile         = config['test']['log_file']

    sys.stdout = Logger(logfile)
    
    x_train, y_train, x_test, y_test = load_cifar10('./data\\cifar_10_batches_bin')

    network = MultiLayerNetExtended(input_size=input_size, hidden_size_list=hidden_list,
                                    output_size=output_size,
                                    use_batchnorm=use_batchnorm, use_weights=True,
                                    weights=weight)
    
    print('==== test_size : ', x_test.shape[0])
    test_acc = network.accuracy(x_test, y_test)

    print('=============== Final Test Accuracy ===============')
    print('test acc : '+ str(test_acc))
