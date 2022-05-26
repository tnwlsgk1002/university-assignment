#인공신경망 5
import numpy as np
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras.layers import Dense

class MyCallback(tf.keras.callbacks.Callback):
    def __init__(self):
        super().__init__()
        self.start_time = time.time()

    def on_epoch_end(self, epoch, logs=None):
        if time.time() - self.start_time > 300:
            self.model.stop_training = True

class ministModel(keras.Model):
    def __init__(self):
        super(ministModel, self).__init__()
        self.flatten = keras.layers.Flatten(input_shape=(28,28))
        self.dense1 = keras.layers.Dense(128, activation = 'sigmoid')
        self.dense2 = keras.layers.Dense(10, activation = 'softmax')

    def call(self, inputs):
        x = self.flatten(inputs)
        x = self.dense1(x)
        return self.dense2(x)

mnist = tf.keras.datasets.mnist
(x_train, y_train_origin), (x_test, y_test_origin) = mnist.load_data()
x_train, x_test = x_train / 255.0, x_test / 255.0           # 0과 1 사이의 값으로 변환
x_train = x_train.reshape((-1, 28, 28, 1))
x_test = x_test.reshape((-1, 28, 28, 1))

nb_classes = 10
y_train = keras.utils.to_categorical(y_train_origin, num_classes = nb_classes)  # one-hot encoding
y_test = keras.utils.to_categorical(y_test_origin, num_classes = nb_classes)    # one-hot encoding

print(x_train.shape)
print(y_train.shape)
print(y_test_origin)
print(y_test)   

model = ministModel()

model.compile(optimizer = keras.optimizers.SGD(learning_rate = 0.1), loss = 'categorical_crossentropy', metrics = ['categorical_accuracy'])
#model.compile(optimizer = keras.optimizers.Adam(learning_rate = 0.001), loss = 'categorical_crossentropy', metrics = ['categorical_accuracy'])
hist = model.fit(x_train, y_train, epochs=10000, batch_size=100, validation_data=(x_test, y_test), callbacks=[MyCallback()])
model.evaluate(x_test, y_test)

y_new = model.predict(x_test)
print(y_new)
y_label = tf.argmax(y_new, axis = 1)
print(y_label.numpy())

# 검증
total_count = len(y_label)
correct_count = 0
for i in range(len(y_label)):
    if y_label[i] == y_test_origin[i]:
        correct_count += 1
print("총 개수 :", total_count, "맞춘 개수 :", correct_count, "정확도 :", correct_count / total_count)

print(hist.history["val_categorical_accuracy"])
print(">>> 최대값 :", max(hist.history["val_categorical_accuracy"]))
