<?php

$html = file_get_contents('./sample_template.html');

$html = str_replace('$title$', 'たいとる', $html);
$html = str_replace('$body$', 'ぼでぃ', $html);

$content_length = strlen($html);

header('Content-Type: text/html; charset=UTF-8');
header('Content-Length: ' . $content_length);

echo $html;
