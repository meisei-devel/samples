import spacy
from spacy.training import Example
from spacy.tokens import DocBin

# サンプルデータセットの作成
train_data = [
    ("東京駅から大阪駅までの行き方を教えてください。", {"entities": [(0, 3, "DEPARTURE"), (5, 8, "DESTINATION")]}),
    ("渋谷駅から新宿駅への行き方を知りたいです。", {"entities": [(0, 3, "DEPARTURE"), (5, 8, "DESTINATION")]}),
    ("名古屋駅から京都駅までの最短ルートは？", {"entities": [(0, 4, "DEPARTURE"), (6, 8, "DESTINATION")]}),
    # さらに多くのデータを追加
]

# 日本語モデルのロード
nlp = spacy.blank("ja")

# NERパイプラインの追加
ner = nlp.add_pipe("ner")

# 新しいラベルの追加
for _, annotations in train_data:
    for ent in annotations.get("entities"):
        ner.add_label(ent[2])

# トレーニングデータの変換
def convert_data(data):
    db = DocBin()
    for text, annot in data:
        doc = nlp.make_doc(text)
        ents = []
        for start, end, label in annot["entities"]:
            span = doc.char_span(start, end, label=label)
            if span is not None:
                ents.append(span)
        doc.ents = ents
        db.add(doc)
    return db

# トレーニングデータの準備
train_db = convert_data(train_data)
train_db.to_disk("./train.spacy")

# トレーニングの実行
nlp.begin_training()
for itn in range(30):  # エポック数を増やしてみる
    losses = {}
    examples = []
    for text, annotations in train_data:
        doc = nlp.make_doc(text)
        example = Example.from_dict(doc, annotations)
        examples.append(example)
    nlp.update(examples, drop=0.35, losses=losses)
    print(f"Epoch {itn + 1} - Losses: {losses}")

# トレーニング済みモデルの保存
nlp.to_disk("./ner_model")

print("Model trained and saved.")
