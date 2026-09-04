const BIP39 = require('bip39');
const ECC = require('tiny-secp256k1')
const { BIP32Factory } = require('bip32');
const BIP32 = BIP32Factory(ECC);
const BITCOIN = require('bitcoinjs-lib');
const ETHERS = require('ethers');

//256BIT = 24 word phraseのニーモニックを生成
//すでに生成済みのニーモニックフレーズを所持している場合mnemonicにその文字列を入れればよい
console.log("COMMON 24 WORD MNEMONIC----");
var mnemonic = BIP39.generateMnemonic(256);
console.log("mnemonic: " + mnemonic);

//ビットコインテストネット(test3)のアドレス・鍵を生成
console.log("BITCOIN TESTNET3 ACCOUNT----");
var network = BITCOIN.networks.testnet;
var path = `m/49'/1'/0'/0`;
var seed = BIP39.mnemonicToSeedSync(mnemonic);
var root = BIP32.fromSeed(seed, network);
var account = root.derivePath(path);
var node = account.derive(0).derive(0);
var btcAddress = BITCOIN.payments.p2pkh({
  pubkey: node.publicKey,
  network: network,
}).address;
console.log('address: ' + btcAddress);
console.log("publicKey: " + node.publicKey.toString("hex"));
console.log("privateKey: " + node.privateKey.toString("hex"));
console.log("wif: " + node.toWIF());

//ビットコインメインネット(本物)のアドレス・鍵を生成
console.log("BITCOIN REAL MAINNET ACCOUNT----");
network = BITCOIN.networks.bitcoin;
path = `m/49'/0'/0'/0`;
seed = BIP39.mnemonicToSeedSync(mnemonic);
root = BIP32.fromSeed(seed, network);
account = root.derivePath(path);
node = account.derive(0).derive(0);
btcAddress = BITCOIN.payments.p2pkh({
  pubkey: node.publicKey,
  network: network,
}).address;
console.log('address: ' + btcAddress);
console.log("publicKey: " + node.publicKey.toString("hex"));
console.log("privateKey: " + node.privateKey.toString("hex"));
console.log("wif: " + node.toWIF());

//イーサリアムネットワークのアドレス・鍵を生成
//イーサリアムはテストもメインも全ネットワークでアドレス・鍵は共通である
console.log("ETHEREUM ALL NETWORK ACCOUNT----");
var wallet = ETHERS.Wallet.fromMnemonic(mnemonic);
console.log('address: ' + wallet.address);
console.log("publicKey: " + wallet.publicKey);
console.log("privateKey: " + wallet.privateKey);
console.log("wif: " + '');
console.log("mnemonic: " + wallet.mnemonic.phrase);
