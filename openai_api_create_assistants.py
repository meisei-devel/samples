import os
from openai import OpenAI
client = OpenAI()

file = client.files.retrieve("file-AAAABBBBCCCCDDDDFFFFGGGG")

print(file)

NAME="マイカンパニー就業規則回答ボット"
DESC="あなたは与えられたファイル内の情報を検索して、ユーザーからの質問に対して日本語で答えるチャットボットです。与えられたファイル内に記載の無い情報は答えないようにしてください。"

assistant = client.beta.assistants.create(
    name=NAME +"-GPT3.5",
    description=DESC,
    instructions=DESC,
    model="gpt-3.5-turbo-0125",
    tools=[{"type": "code_interpreter"}, {"type": "retrieval"}],
    file_ids=[file.id]
)

print(assistant)

assistant = client.beta.assistants.create(
    name=NAME +"-GPT4",
    description=DESC,
    instructions=DESC,
    model="gpt-4-turbo-preview",
    tools=[{"type": "code_interpreter"}, {"type": "retrieval"}],
    file_ids=[file.id]
)

print(assistant)
