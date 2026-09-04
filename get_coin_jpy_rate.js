async function main() {

const HTTPS = require('https');

function promiseRequest(url, options, postData) {
return new Promise(function (resolve, reject) {

	var req = HTTPS.request(url, options, (res) => {
		//console.log('statusCode:', res.statusCode);
		//console.log('headers:', res.headers);

		//200台以外はエラーとする場合
		//if(res.statusCode >= 300) {
		//	reject(new Error('res.statusCode >= 300'));
		//}

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

async function get_coin_jpy_rate(code) {

	var url = 'https://api.bitflyer.jp/v1/ticker?product_code=' + code;
	console.log(url);
	var json = null;
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
		json = await promiseRequest(url, options, postData);
		json = JSON.parse(json);
	}
	catch(err) {
		console.log(err.stack);
		json = null;
	}

	console.log(json);
	//console.log(json.ltp);

	return json != null ? json.ltp:0;
}

var coins = 1;

var coins_jpy = Math.floor(await get_coin_jpy_rate('BTC_JPY')) * coins;
console.log(coins + ' BTC は ' + coins_jpy + ' 円 です。');

coins_jpy = Math.floor(await get_coin_jpy_rate('ETH_JPY')) * coins;
console.log(coins + ' ETH は ' + coins_jpy + ' 円 です。');

} //async function main()

main();
