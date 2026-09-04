const OPENAI_API_KEY = "取得済みのOpenAI API KEY";
const OPENAI_API_URL = "https://api.openai.com/v1/chat/completions";

function GPT3(prompt) {
  var payload = {
    model: "gpt-3.5-turbo",
    messages: [{role:"user", content:prompt}],
  };
  var options = {
    contentType: "application/json",
    headers: {Authorization: "Bearer " + OPENAI_API_KEY},
    payload: JSON.stringify(payload),
  };
  var response = JSON.parse(UrlFetchApp.fetch(OPENAI_API_URL, options).getContentText());
  return response.choices[0].message.content.trim();
}
