import os
from openai import OpenAI
client = OpenAI()

file = client.files.create(
    file=open("my_company_rules.pdf", "rb"),
    purpose='assistants'
)

print(file)
