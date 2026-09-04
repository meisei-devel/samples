// 同期的にhttps通信するサンプル
const https = require('https');

function promiseRequest(url, options, postData) {
return new Promise(function (resolve, reject) {

	var req = https.request(url, options, (res) => {
		console.log('statusCode:', res.statusCode);
		console.log('headers:', res.headers);

		//200台以外はエラーとする場合
		if(res.statusCode >= 300) {
			reject(new Error('res.statusCode >= 300'));
		}

		var chunks = []; //チャンクレスポンスストック配列

		res.on('data', chunk => chunks.push(Buffer.from(chunk)))
		.on('end', () => { //チャンクレスポンスストリーム終了
			var buffer = Buffer.concat(chunks);
			resolve(buffer);
		});
	});

	req.on('error', (err) => {
		reject(err);
	});

	req.on('timeout', () => {
		req.abort();
		reject(new Error('request timed out'));
	});

	if(postData != null) {
		req.write(postData);
	}

	req.end();

});
}

async function main() {

	const url = 'https://www.yahoo.co.jp/';

	var options = {
		method: 'GET',
		timeout: 5000,
		//headers: {
			//'Content-Type': 'application/json',
		//},
	};

	//var postData = JSON.stringify({
	//	'limit' : 50
	//});
	var postData = null;

	try {
		const res = await promiseRequest(url, options, postData);
		//Promiseがresolveするとresがここに返る
		console.log(res.constructor.name); // =Buffer
		console.log(res.toString());
	}
	catch(err) { //Promiseがrejectするとerrがここに返る
		console.log(err.constructor.name); // =Error
		console.log(err.stack);
	}

}

main();
