const UNITS = require('cryptocurrency-unit-convert');

function gas_to_coin(coinname, gas) {
	var s = '';
	if(coinname.match(/BTC/)) {
		s = UNITS.convertBTC(gas + '', 'satoshi', 'btc');
	}
	else if(coinname.match(/ETH/)) {
		s = UNITS.convertETH(gas + '', 'wei', 'eth');
	}
	return s; //Number(s)だと大きいまたは小さい数が指数表記(1e-18のような)になってしまう
}

function coin_to_gas(coinname, coin) {
	var s = '';
	if(coinname.match(/BTC/)) {
		s = UNITS.convertBTC(coin + '', 'btc', 'satoshi');
	}
	else if(coinname.match(/ETH/)) {
		s = UNITS.convertETH(coin + '', 'eth', 'wei');
	}
	return s; //Number(s)だと大きいまたは小さい数が指数表記(1e-18のような)になってしまう
}

var gas = 1000000;
var coin_btc = gas_to_coin('BTC', gas);
var coin_eth = gas_to_coin('ETH', gas);

console.log(gas + ' SATOSHI は ' + coin_btc + ' BTC です。');
console.log(gas + ' WEI は ' + coin_eth + ' ETH です。');

console.log(coin_btc + ' BTC は ' + coin_to_gas('BTC', coin_btc) + ' SATOSHI です。');
console.log(coin_eth + ' ETH は ' + coin_to_gas('ETH', coin_eth) + ' WEI です。');
