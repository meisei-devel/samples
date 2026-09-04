const { Configuration, OpenAIApi } = require("openai");
const configuration = new Configuration({
  apiKey: process.env.OPENAI_API_KEY,
});
const openai = new OpenAIApi(configuration);

(async () => {
	var prompt = '### 大阪と東京はどれくらい離れていますか？';
	var response = await openai.createCompletion({
		model: "text-davinci-003",
		prompt: prompt,
		temperature: 0.6,
		max_tokens: 1024,
		stop: ["###"],
	});
	console.log(response.data.choices);

	prompt += response.data.choices[0].text + '\n';
	prompt += '### 英語とドイツ語でお願いします。';
	response = await openai.createCompletion({
		model: "text-davinci-003",
		prompt: prompt,
		temperature: 0.6,
		max_tokens: 1024,
		stop: ["###"],
	});
	console.log(response.data.choices);

})();
