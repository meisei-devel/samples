import os
import openai
openai.api_key = os.getenv("OPENAI_API_KEY")

response = openai.Model.list()

for d in response.data:
	print(d.id)

print('Total Models: ' + str(len(response.data)))
