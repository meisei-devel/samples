//PostgreSQL接続サンプル
async function main() {

const UTIL = require('util');

const PG = require('pg');

const POOL = new PG.Pool({ //接続パラメータを指定してPoolを生成する
	host: '127.0.0.1',
	port: 5432,
	database: 'testdb',
	user: 'testuser',
	password: 'testpass'
});

POOL.connect( async (err, client) => { //接続

	if (err) {
		console.log(err);
		return; //エラー終了
	}

	try {
		var query = "DROP TABLE IF EXISTS testtbl"; //既存テーブル消去
		console.log(query);
		var result = await client.query(query);

		query = "CREATE TABLE testtbl (key VARCHAR(512) PRIMARY KEY, value TEXT NOT NULL)"; //新規テーブル作成
		console.log(query);
		result = await client.query(query);

		query = "INSERT INTO testtbl (key, value) VALUES ('きー１', 'ばりゅー１')"; //データ投入
		console.log(query);
		result = await client.query(query);

		query = "INSERT INTO testtbl (key, value) VALUES ('きー２', 'ばりゅー２')"; //データ投入
		console.log(query);
		result = await client.query(query);

		query = UTIL.format("SELECT value FROM testtbl WHERE key = '%s'", 'きー２'); //２番目のデータを抽出
		console.log(query);
		result = await client.query(query);
		console.log(result.rows);		
		if(result.rows.length > 0) {
			console.log(result.rows[0].value);
		}
	}
	catch (err) {
		console.log(err.stack); //エラー
	}

	client.release(true); //これを忘れるとサーバにずっとコネクションが溜まる

});

} //async function main()

main();
