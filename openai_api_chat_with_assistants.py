import os
import time
from openai import OpenAI

class Assistant:
	def __init__(self, assistant_id: str) -> None:
		self.client = OpenAI()
		self.assistant = self.client.beta.assistants.retrieve(assistant_id)
		self.thread = self.client.beta.threads.create()

	def send_message(self, message: str) -> str:
		print("user :", message)
		self.client.beta.threads.messages.create(
			thread_id=self.thread.id,
			role="user",
			content=message,
		)
		self.client.beta.threads.runs.create(
			thread_id=self.thread.id,
			assistant_id=self.assistant.id,
		)
		self._wait()
		self.show_message(num=1)

	def _wait(self) -> None:
		status = "queued"
		while status != "completed":
			time.sleep(0.5)
			run = self.client.beta.threads.runs.list(
				thread_id=self.thread.id,
			)
			for r in run:
				status = r.status
				break

	def show_message(self, num: int = 5) -> None:
		messages = self.client.beta.threads.messages.list(
			thread_id=self.thread.id,
		)
		messages_list = [message for message in messages]
		for message in (messages_list[:num]):
			print(message.role, ":", message.content[0].text.value)

if __name__ == "__main__":

	messages = [
		"まずおおまかに概要を教えてください。",
		"この会社はフレックスタイム制でしょうか？",
		"その場合、コアタイムはいつですか？",
	]

	print("Assistant API Test with GPT-3.5")
	assistant = Assistant("asst_111111112222222233333333") #GPT-3.5
	for message in messages:
		assistant.send_message(message)

	print("Assistant API Test with GPT-4")
	assistant = Assistant("asst_444444445555555566666666") #GPT-4
	for message in messages:
		assistant.send_message(message)
