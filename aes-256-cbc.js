var crypto = require('crypto');

//現在日時をミリ秒単位で文字列化して返す
function get_time_string() {
	var date = new Date();
	return date.getFullYear() +
	('0' + (date.getMonth() + 1)).slice(-2) +
	('0' + date.getDate()).slice(-2) +
	('0' + date.getHours()).slice(-2) +
	('0' + date.getMinutes()).slice(-2) +
	('0' + date.getSeconds()).slice(-2) +
	('00' + date.getMilliseconds()).slice(-3);
}

//対象文字列
var target_string = 'あいうえおかきくけこ';
console.log('target_string=' + target_string);

//文字列キーの生成
var string_key = "KEY" + get_time_string();
console.log('string_key=' + string_key);

//バイナリキーの生成
var binary_key = crypto.randomBytes(16);
var binary_key_b64 = binary_key.toString('base64');
console.log('binary_key_b64=' + binary_key_b64);

//文字列キーをmd5化しバイナリキーと合わせてAES-256-CBC暗号化＆base64化
var md5 = crypto.createHash('md5');
var string_key_md5 = md5.update(string_key, 'binary').digest('hex');
console.log('string_key_md5=' + string_key_md5);
var cipher = crypto.createCipheriv('aes-256-cbc', string_key_md5, binary_key);
var encrypted = cipher.update(target_string, 'utf8', 'base64') + cipher.final('base64');
console.log('encrypted=' + encrypted);

//文字列キーとバイナリキーから暗号化文字列をAES-256-CBC復号化する
var decipher = crypto.createDecipheriv('aes-256-cbc', string_key_md5, Buffer.from(binary_key_b64, 'base64'));
var decrypted = decipher.update(encrypted, 'base64', 'utf8') + decipher.final('utf8');
console.log('decrypted=' + decrypted);
