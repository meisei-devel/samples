import os
import sys
from linebot import LineBotApi
from linebot.models import TextSendMessage

str = ''
for line in sys.stdin:
   str += line

channel_access_token = "MY ACCESS TOKEN"
line_user_id = "MY USER ID"
 
line_bot_api = LineBotApi(channel_access_token)
 
def main():
    line_bot_api.push_message(line_user_id, TextSendMessage(text=str))
 
if __name__ == "__main__":
    main()
