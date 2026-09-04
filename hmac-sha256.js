var crypto = require('crypto');

var email = 'hogeuser@test12345.co.jp';
var password = 'hogepass123';

var encrypted = crypto.createHmac('SHA256', password).update(email).digest('hex');

console.log(encrypted);
