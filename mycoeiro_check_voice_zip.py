#@title 「zip内の内容確認」のために左の再生ボタンをおしてください
import glob
import shutil
import os
import soundfile as sf

colab_workspace = '/content/tmp'

if os.path.exists(colab_workspace):
  shutil.rmtree(colab_workspace)
os.makedirs(colab_workspace, exist_ok=True)

zip_folder = '/content/drive/MyDrive/MYCOEIROINK_WORK/voices'
if len(glob.glob(zip_folder + '/*.zip')) == 0:
  raise Exception(f"zipが見つかりません。")
zip_path = glob.glob(zip_folder + '/*.zip')[0]
workspace_zip_path = colab_workspace + '/wavs.zip'
wavs_folder = colab_workspace + '/wavs'
shutil.copyfile(zip_path, workspace_zip_path)
shutil.unpack_archive(workspace_zip_path, wavs_folder)

wav_paths = sorted(glob.glob(wavs_folder + '/**/*.wav', recursive=True))
wav_names = [wav_path.split('/')[-1].replace('.wav', '') for wav_path in wav_paths]

#!git clone https://github.com/shirowanisan/coeiroink-corpus-manager.git
with open('/content/coeiroink-corpus-manager/marged-corpus.txt', encoding='utf-8') as f:
  text = f.readlines()
ita_corpus_keys = [s.split(':')[0] for s in text]
ita_corpus_values = [s.split(':')[-1] for s in text]
ita_corpus_dict = dict(zip(ita_corpus_keys, ita_corpus_values))

for wav_name in wav_names:
  if wav_name not in ita_corpus_keys:
    raise Exception(f"「{wav_name}」というwavファイルが含まれており、このファイル名はMYCOEIROINK対象のコーパスに含まれていません。")

if len(wav_names) < 10:
  raise Exception(f"wavファイルの数が「{len(wav_names)}」ですが、wavファイルは10以上必要です。")

incorrect_fs_flag = False
incorrect_fs_list = []
for wav_path in wav_paths:
  wav, original_fs = sf.read(wav_path)
  if len(wav.shape) == 2:
    raise Exception(f"「{wav_path.split('/')[-1]}」が、ステレオの可能性があります。モノラルにしてください。")
  if original_fs != 44100:
    incorrect_fs_list.append(wav_path.split('/')[-1])
    incorrect_fs_flag = True
if incorrect_fs_flag:
  print("WARNING: 44.1kHz以外の音声が含まれています。MYCOEでは44.1kHz以外の音声は44.1kHzに変換して利用されます。")
  print(incorrect_fs_list)

#@title 音声の開始終了の無音区間を自動で削除する場合は「ON」にしてください。（開始終了の無音区間がない方が、音声生成の速度が速くなる傾向にあります。）

trim_flag = 'ON' #@param ["ON", "OFF"] {type: "string"}

import librosa
from librosa.util import normalize

MAX_WAV_VALUE = 32768.0
sampling_fs = 44100

normalized_wavs_path = '/content/normalized_wavs'
if os.path.exists(normalized_wavs_path):
  shutil.rmtree(normalized_wavs_path)
os.makedirs(normalized_wavs_path, exist_ok=True)

text = ''
# wavのサンプリング周波数と音量の調整とテキストの作成
for wav_path in wav_paths:
  wav_name = wav_path.split('/')[-1].replace('.wav', '')
  text += wav_name + ':' + ita_corpus_dict[wav_name]
  wav, original_fs = sf.read(wav_path)
  if original_fs != sampling_fs:
    wav = librosa.resample(wav, orig_sr=original_fs, target_sr=sampling_fs)
  if trim_flag == "ON":
    wav = librosa.effects.trim(wav, top_db=30)[0]
  normalized_wav = normalize(wav) * 0.90
  sf.write(normalized_wavs_path + '/' + wav_path.split('/')[-1], normalized_wav, sampling_fs, 'PCM_16')

corpus_path = '/content/corpus'
if os.path.exists(corpus_path):
  shutil.rmtree(corpus_path)
os.makedirs(corpus_path, exist_ok=True)

with open('/content/corpus/transcripts_utf8.txt', 'w', encoding='UTF-8') as f:
  f.write(text)

print(f"今回の学習に使われる音声の数は全部で「{len(wav_paths)}」個となっています。ご確認ください。")
