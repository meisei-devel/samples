from PIL import Image
import numpy as np
import os, sys

input_dir = '/content/drive/MyDrive/Colab Notebooks/cifar-10-batches-py/data_batch_1'
output_dir = '/content/drive/MyDrive/Colab Notebooks/cifar-10-images-1'
label_file = '/content/drive/MyDrive/Colab Notebooks/cifar-10-batches-py/batches.meta'

def read_bin(path):
  import pickle
  with open(path, 'rb') as f:
    r = pickle.load(f, encoding='bytes')
  return r

# 保存先ディレクトリの作成とカテゴリディレクトリの作成
try:
  os.makedirs(output_dir)
except:
  pass
labels = read_bin(label_file)
if b"label_names" in labels:
  labels = read_bin(label_file)[b"label_names"]
else:
  labels = read_bin(label_file)[b"coarse_label_names"]
for i in labels:
  try:
    dir=os.path.join(output_dir, i.decode('utf-8'))
    os.makedirs(dir)
  except:
    pass

# 画像バイナリの読み込み
images = read_bin(input_dir)
files = images[b"filenames"]
if b"labels" in images:
  image_labels = images[b"labels"]
else:
  image_labels = images[b"coarse_labels"]
image_data = images[b"data"]

# 画像ファイルとして保存
for i,_ in enumerate(files):
  file = files[i]
  image_label = image_labels[i]
  image = image_data[i]
  path = os.path.join(os.path.join(output_dir, labels[image_label].decode('utf-8'), file.decode('utf-8')))
  out_image_1 = np.reshape(image, [3, 32, 32]).transpose(1,2,0)
  out_image_2 = Image.fromarray(out_image_1)
  with open(path, mode='wb') as o:
    out_image_2.save(o)
  print("saved: {}".format(path))
