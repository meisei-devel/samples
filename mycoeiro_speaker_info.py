#@title 「Speaker_infoフォルダの作成」のために左の再生ボタンをおしてください
#%cd /content/
#!unzip /content/drive/MyDrive/MYCOEIROINK_WORK/downloads/dummy_speaker_info_2.zip

import glob
import uuid
import random
import shutil
import json
import os

speaker_info_contents = sorted(glob.glob('/content/drive/MyDrive/MYCOEIROINK_WORK/speaker_info/*'))
if len(speaker_info_contents) == 0:
  speaker_uuid = str(uuid.uuid1())
  speaker_id = random.randint(10001, 2147483647)

  shutil.move('/content/dummy_speaker_info/icons/<speaker_id>.png', f"/content/dummy_speaker_info/icons/{speaker_id}.png")
  shutil.move('/content/dummy_speaker_info/voice_samples/<speaker_id>_001.wav', f"/content/dummy_speaker_info/voice_samples/{speaker_id}_001.wav")
  shutil.move('/content/dummy_speaker_info/voice_samples/<speaker_id>_002.wav', f"/content/dummy_speaker_info/voice_samples/{speaker_id}_002.wav")
  shutil.move('/content/dummy_speaker_info/voice_samples/<speaker_id>_003.wav', f"/content/dummy_speaker_info/voice_samples/{speaker_id}_003.wav")
  shutil.move('/content/dummy_speaker_info/model/<speaker_id>', f"/content/dummy_speaker_info/model/{speaker_id}")

  metas = {
      "speakerName": "MYCOEIROINK",
      "speakerUuid": speaker_uuid,
      "styles": [
          {
              "styleName": "のーまる",
              "styleId": speaker_id
          }
      ]
  }

  with open('dummy_speaker_info/metas.json', mode='w', encoding='utf-8') as f:
    json.dump(metas, f, indent=4, ensure_ascii=False)

  os.makedirs('/content/drive/MyDrive/MYCOEIROINK_WORK/speaker_info', exist_ok=True)
  shutil.copytree('/content/dummy_speaker_info', f"/content/drive/MyDrive/MYCOEIROINK_WORK/speaker_info/{speaker_uuid}")
#!rm -rf dummy_speaker_info
