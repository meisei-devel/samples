#@title 「モデルの作成のための環境構築2」のために左の再生ボタンをおしてください

import os
import glob
import shutil

pretrained_model_tag = 'model_2' #@param ["model_1", "model_2", "model_3"] {type: "string"}

espnet_wavs_dir = '/content/espnet/egs2/mycoe/tts1/downloads/wavs'
os.makedirs(espnet_wavs_dir, exist_ok=True)

wav_paths = sorted(glob.glob('/content/normalized_wavs/*.wav'))

for wav_path in wav_paths:
  shutil.copyfile(wav_path, espnet_wavs_dir + '/' + wav_path.split('/')[-1])

#%cd /content/
if pretrained_model_tag == 'model_1':
  shutil.unpack_archive('/content/drive/MyDrive/MYCOEIROINK_WORK/downloads/mycoe_pretrain_model.zip', '/content/')
if pretrained_model_tag == 'model_2':
  shutil.unpack_archive('/content/drive/MyDrive/MYCOEIROINK_WORK/downloads/mycoe_pretrain_model_2.zip', '/content/')
if pretrained_model_tag == 'model_3':
  shutil.unpack_archive('/content/drive/MyDrive/MYCOEIROINK_WORK/downloads/mycoe_pretrain_model_3.zip', '/content/')

shutil.copyfile('/content/mycoe_pretrain_model/100epoch.pth', '/content/espnet/egs2/mycoe/tts1/downloads/100epoch.pth')
shutil.copyfile('/content/mycoe_pretrain_model/tokens.txt', '/content/espnet/egs2/mycoe/tts1/downloads/tokens.txt')
shutil.copyfile('/content/corpus/transcripts_utf8.txt', '/content/espnet/egs2/mycoe/tts1/downloads/transcripts_utf8.txt')
