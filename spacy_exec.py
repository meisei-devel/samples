import spacy

# トレーニング済みモデルの読み込み
nlp = spacy.load("./ner_model")

# ユーザーの入力に対する出発地と目的地の抽出
def extract_entities(text):
    doc = nlp(text)
    departure = None
    destination = None
    for ent in doc.ents:
        if ent.label_ == "DEPARTURE":
            departure = ent.text
        elif ent.label_ == "DESTINATION":
            destination = ent.text
    return departure, destination

# テスト用の入力
user_input = "大久保駅から吉祥寺駅までの行き方を教えてください。"
departure, destination = extract_entities(user_input)
print(f"出発地: {departure}, 目的地: {destination}")
