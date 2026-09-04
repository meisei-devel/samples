const fs = require("fs");
const { Configuration, OpenAIApi } = require("openai");
const configuration = new Configuration({
  apiKey: process.env.OPENAI_API_KEY,
});
const openai = new OpenAIApi(configuration);

(async () => {
	var response = await openai.createImageVariation(
		fs.createReadStream("ff10-512x512.png"),
		2,
		"512x512"
	);
	response.data.data.forEach(function (d) {
		console.log(d.url);
	});
})();
