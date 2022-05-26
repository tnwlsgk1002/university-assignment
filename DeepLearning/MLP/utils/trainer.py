from .optimizer import *

class Trainer:
    def __init__(self, network, x_train, y_train, x_val, y_val,
                 epochs=20, mini_batch_size=100,
                 optimizer='SGD', optimizer_param={'lr':0.01}, verbose=True):
        self.network = network
        self.verbose = verbose
        self.x_train = x_train
        self.y_train = y_train
        self.x_val = x_val
        self.y_val = y_val
        self.epochs = epochs
        self.batch_size = mini_batch_size

        # optimzer
        optimizer_class_dict = {'sgd':SGD, 'momentum':Momentum, 
                                'adagrad':AdaGrad, 'rmsprpo':RMSprop, 'adam':Adam}
        self.optimizer = optimizer_class_dict[optimizer.lower()](**optimizer_param)
        
        self.train_size = x_train.shape[0]
        self.iter_per_epoch = max(self.train_size / mini_batch_size, 1)
        self.max_iter = int(epochs * self.iter_per_epoch)
        self.current_iter = 0
        self.current_epoch = 0
        
        self.train_loss_list = []
        self.train_acc_list = []
        self.val_acc_list = []

    def train_step(self):
        batch_mask = np.random.choice(self.train_size, self.batch_size)
        x_batch = self.x_train[batch_mask]
        y_batch = self.y_train[batch_mask]

        grads = self.network.gradient(x_batch, y_batch)
        self.optimizer.update(self.network.params, grads)
        
        loss = self.network.loss(x_batch, y_batch)
        self.train_loss_list.append(loss)
        
        #if self.verbose: 
        #    print("train loss:" + str(loss))
        
        if self.current_iter % self.iter_per_epoch == 0:
            self.current_epoch += 1
                            
            train_acc = self.network.accuracy(self.x_train, self.y_train)
            val_acc = self.network.accuracy(self.x_val, self.y_val)
            
            self.train_acc_list.append(train_acc)
            self.val_acc_list.append(val_acc)

            if self.verbose: 
                print("=== epoch:" + str(self.current_epoch) + ", train acc:" + str(train_acc) + ", val acc:" + str(val_acc) + " ===")

        self.current_iter += 1

    def train(self):
        for i in range(self.max_iter):
            self.train_step()

        val_acc = self.network.accuracy(self.x_val, self.y_val)

        if self.verbose:
            print("=============== Final Test Accuracy ===============")
            print("val acc:" + str(val_acc))