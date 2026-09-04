const { Configuration, OpenAIApi } = require("openai");
const configuration = new Configuration({
  apiKey: process.env.OPENAI_API_KEY,
});
const openai = new OpenAIApi(configuration);

(async () => {
	var response = await openai.retrieveModel('ada-similarity');
	console.dir(response.data, { depth: null });
})();

