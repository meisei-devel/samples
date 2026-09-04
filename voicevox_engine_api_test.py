import requests
import json

URL = 'http://172.21.16.39:50021/'
TEXT = 'これはテストです。'
SPEAKER = 0
SAVED_FILE = './test.wav'

# make synthesis query

response = requests.post(URL + 'audio_query', params = {'text':TEXT, 'speaker':SPEAKER})
query_data = response.json()
print(query_data)

response = requests.post(URL + 'synthesis', params = {'speaker':SPEAKER, 'enable_interrogative_upspeak':'true'}, data = json.dumps(query_data))
print(response.status_code)
with open(SAVED_FILE, 'wb') as saved_file:
    saved_file.write(response.content)
