const { Configuration, OpenAIApi } = require("openai");

const configuration = new Configuration({
  apiKey: process.env.OPENAI_API_KEY,
});
const openai = new OpenAIApi(configuration);

(async () => {
  const completion = await openai.createChatCompletion({
    model: "gpt-3.5-turbo",
    messages: [
        { role: "user", content: "When will the GPT-4 API be available?" }
    ],
  });
  console.log(completion.data.choices[0].message);

  const completion2 = await openai.createChatCompletion({
    model: "gpt-3.5-turbo",
    messages: [
        { role: "user", content: "When will the GPT-4 API be available?" },
        completion.data.choices[0].message,
        { role: "user", content: "日本語でお願いします。" }
    ],
  });
  console.log(completion2.data.choices[0].message);

})();
