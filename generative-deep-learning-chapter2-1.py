#ライブラリ

import numpy as np
import tensorflow as tf
from tensorflow.keras.utils import to_categorical
from tensorflow.keras.datasets import cifar10
from tensorflow.keras.layers import Input, Flatten, Dense, Activation
from tensorflow.keras.models import Model
from tensorflow.keras.optimizers import Adam
import matplotlib.pyplot as plt

#データロード

NUM_CLASSES = 10

(x_train, y_train), (x_test, y_test) = cifar10.load_data()

x_train = x_train.astype('float32') / 255.0
x_test = x_test.astype('float32') / 255.0

y_train = to_categorical(y_train, NUM_CLASSES)
y_test = to_categorical(y_test, NUM_CLASSES)

data = np.random.randint(low=0, high=5, size=10)
print(data)
print(to_categorical(data))
print(to_categorical(data, 8))

#モデル定義・コンパイルをMirroredStrategy withブロック内で行い、以降のトレーニングをデュアルGPUで行う

with tf.distribute.MirroredStrategy(cross_device_ops=tf.distribute.HierarchicalCopyAllReduce()).scope():

	input_layer = Input(shape=(32, 32, 3))
	x = Flatten()(input_layer)
	x = Dense(units=200, activation='relu')(x)
	x = Dense(units=150, activation='relu')(x)

	output_layer = Dense(units=10, activation='softmax')(x)

	output_layer2 = Dense(units=200)(x)
	output_layer2 = Activation('relu')(output_layer2)
	model = Model(input_layer, output_layer)
	model.summary()

	opt = Adam(lr=0.0005)
	model.compile(loss='categorical_crossentropy', optimizer=opt, metrics=['accuracy'])

#トレーニング実行

model.fit(x_train,
          y_train,
          batch_size = 32,
          epochs = 10,
          shuffle = True)

model.evaluate(x_test, y_test, batch_size=32)

#予測インデックステスト

CLASSES = np.array(['AirPlane', 'Car','Bird','Cat', 'Deer','Dog','Flog','Horse','Ship','Truck'])
preds = model.predict(x_test)
preds_single = CLASSES[np.argmax(preds, axis= -1)]
actual_single = CLASSES[np.argmax(y_test, axis = -1)]

print(preds[0])
print(np.argmax(preds[0]))
print(preds_single[0])
print(actual_single[0])

#予測画像リスト表示テスト

n_to_show = 10
indices = np.random.choice(range(len(x_test)), n_to_show)
fig = plt.figure(figsize=(15, 3))
fig.subplots_adjust(hspace=0.4, wspace=0.4)

for i, idx in enumerate(indices):
  img = x_test[idx]
  ax = fig.add_subplot(1, n_to_show, i+1)
  ax.axis('off')
  ax.text(0.5, -0.35, 'pred = ' + str(preds_single[idx]), fontsize=10, ha='center', transform=ax.transAxes) 
  ax.text(0.5, -0.7, 'act = ' + str(actual_single[idx]), fontsize=10, ha='center', transform=ax.transAxes)
  ax.imshow(img)
