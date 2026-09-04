<?php date_default_timezone_set('Asia/Tokyo');

//標準入力からメールの中身を取り出して表示するサンプル
//添付ファイル保存機能つき

require_once 'Mail/mimeDecode.php';

//ヘッダ取得：$strにそのまま入る
function read_header_1(&$obj, &$key, &$str)
{
    $str = '';
    if (array_key_exists($key, $obj->headers)) {
        $str = $obj->headers[$key];
    }
    echo $key . ": " . $str . "\n";
}

//ヘッダ取得：$strにそのまま入る＋<>に囲まれた部分を$valに入れる
function read_header_2(&$obj, &$key, &$str, &$val)
{
    $str = '';
    $val = '';
    if (array_key_exists($key, $obj->headers)) {
        $str = $obj->headers[$key];
        $lpos = strpos($str, '<');
        $rpos = strpos($str, '>');
        if ($lpos !== false && $rpos !== false) {
            $lpos++;
            $val = substr($str, $lpos, $rpos - $lpos);
        } else {
            $val = $str;
        }
    }
    echo $key . ": " . $str . "\n";
    echo $key . ": " . $val . "\n";
}

//ヘッダ取得：$strにそのまま入る＋<>に囲まれた部分を$valに入れる（//で連結）
//上記2関数と異なり$valはグローバル扱いなので呼び側で初期化しておくこと
function read_header_3(&$obj, &$key, &$str, &$val)
{
    $str = '';
    if (array_key_exists($key, $obj->headers)) {
        $str = $obj->headers[$key];
        $ref = $str;
        if (strpos($ref, '<') !== false) {
            while (true) {
                $lpos = strpos($ref, '<');
                $rpos = strpos($ref, '>');
                if ($lpos === false || $rpos === false) {
                    break;
                }
                $lpos++;
                $sub = substr($ref, $lpos, $rpos - $lpos);
                if (strpos($val, $sub) === false) { //すでに連結済みの値はスキップ
                    $val .= '/' . $sub . '/';
                }
                $ref = substr($ref, $rpos + 1);
            }
        } elseif (strpos($val, $ref) === false) {
            $val .= '/' . $ref . '/';
        }
    }
    echo $key . ": " . $str . "\n";
    #	echo $key . ": " . $val . "\n";
}

//標準入力からメールの生データを読み込んでobjectに展開

//etc/aliasesなどから直接起動する場合カレントを適切な場所に移動すること
//chdir( "/home/hogeuser" );

$stdin = file_get_contents('php://stdin');
$decoder = new Mail_mimeDecode($stdin);

$params = []; //オプションをここで設定（コード変換をお任せ設定）
$params['include_bodies'] = true;
$params['decode_bodies']  = true;
$params['decode_headers'] = true;
$params['crlf'] = "\r\n";
//$params['input'] = $stdin;

$object = null;
try {
    $object = $decoder->decode($params);
//    $object = Mail_mimeDecode::decode($params);
} catch (Exception $e) {
    fputs(STDERR, $e->getMessage() . "\n");
    $object = null;
    exit(); //デコードエラー終了
}

//ダンプ （しない場合コメントアウトのこと）
var_dump($object);

//Date:
$date = $object->headers["date"];
$date_seq = strtotime($date);
$date_str = date('Y-m-d H:i:s', $date_seq);
echo "date: " . $date . "\n";
echo "date_seq: " . $date_seq . "\n";
echo "date_str: " . $date_str . "\n";

//From: To: Message-Id:
$key = 'from';
$str = '';
$val = '';
read_header_2($object, $key, $str, $val);
$key = 'to';
read_header_2($object, $key, $str, $val);
$key = 'message-id';
read_header_2($object, $key, $str, $val);
$msg_id = $val;

//References,In-Reply-Toは//で一気に連結する
$key = 'references';
$val = '';
read_header_3($object, $key, $str, $val);
$key = 'in-reply-to';
read_header_3($object, $key, $str, $val);
echo "references+in-reply-to: " . $val . "\n";

//Subject:
$key = 'subject';
read_header_1($object, $key, $str);

//本文テキストと思われるものを抽出してcontents_bodyに連結して入れる

$contents_body = "";

//シングルパートの場合
if (property_exists($object, 'body')) {
    $contents_body .= $object->body;
}

//マルチパートの場合
if (property_exists($object,'parts')) {
    $parts = $object->parts;
    $n = count($parts);
    for ($i = 0; $i < $n; $i++) { //マルチパート取得ループ
        $arval = $parts[$i];
        if (array_key_exists("content-type", $arval->headers)) {
            if (strpos($arval->headers["content-type"], "text/plain") !== false) {
                //echo $arval->headers["content-type"] . "\n";
                if (property_exists($arval, 'body')) {
                    //echo $arval->body;
                    $contents_body .= $arval->body;
                }
            }
        }
        if (array_key_exists("content-disposition", $arval->headers)) { //添付ファイル保存
            $dsp = $arval->headers["content-disposition"];
            $lpp = strpos($dsp, "filename=\"");
            if ($lpp !== false) {
                $lpp += 10;
                $sub = substr($dsp, $lpp);
                $rpp = strpos($sub, "\"");
                if ($rpp !== false) {
                    $sub = substr($sub, 0, $rpp);
                    echo "attachment-filename: " . $sub . "\n";
                    if (property_exists($arval, 'body')) {
                        file_put_contents($sub, $arval->body);
                    }
                }
            }
        }
    }
}

//特殊コード等の加工をする

if (strlen($contents_body) > 0) {
    $body_full = str_replace("\r\n", "\n", $contents_body); //改行コードの統一
    $body_full = str_replace("\t", "", $body_full); //タブは切る

    //ここで、PHP標準はUTF-8以外=JISをデコードしてくれないので、
    //一旦ファイルに落とし、外部コマンドnkfで判別変換して読み込み

    $fbtmp = "body_tmp.txt"; //$msg_id . ".txt";
    $fbout = "body_out.txt"; //$msg_id . ".txt";
    file_put_contents($fbtmp, $body_full);

    if (strcmp(exec("nkf -g " . $fbtmp), "ISO-2022-JP") == 0) { //JIS
        exec("nkf -J -w " . $fbtmp . " > " . $fbout); //UTF-8へ変換
        $body_full = file_get_contents($fbout); //読み込み
    }

    echo $body_full;
}
