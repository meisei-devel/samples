<?php

$html = file_get_contents('./sample_form_template.html');

$html = str_replace('$title$', 'たいとる', $html);
$html = str_replace('$body$', 'ぼでぃ', $html);

$textarea = "";
if(isset($_POST['textarea'])) {
	$textarea = htmlspecialchars_decode($_POST['textarea']);
}

$html = str_replace('$textarea$', htmlspecialchars($textarea), $html);

$content_length = strlen($html);

header('Content-Type: text/html; charset=UTF-8');
header('Content-Length: ' . $content_length);

echo $html;
