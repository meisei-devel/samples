#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

import codecs
import cgi
import os
import sys
import io
import MeCab

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

def mecab_list(text):
    tagger = MeCab.Tagger("-Ochasen")
    tagger.parse('')
    node = tagger.parseToNode(text)
    word_class = []
    while node:
        word = node.surface
        wclass = node.feature.split(',')
        if wclass[0] != u'BOS/EOS':
            if wclass[6] == None:
                word_class.append((word, wclass[0], wclass[1], wclass[2], ""))
            else:
                word_class.append(
                    (word, wclass[0], wclass[1], wclass[2], wclass[6]))
        node = node.next
    return word_class

form = cgi.FieldStorage()
mecab_ta = form.getfirst('mecab_ta', '')

test = mecab_list(mecab_ta)

print("Content-Type: text/html; charset=UTF-8\r\n\r\n", end="")
for ttt in test:
    i = 0
    for tt in ttt:
        if i > 1:
            print(",", end="")
        print(tt, end="")
        if i == 0:
            print("　[")
        i += 1
    print("]<br>\n", end="")
