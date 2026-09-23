# deploysql.zsh
# Downloads にある最新の technote_*.sql / estate_*.sql を
# SSH 経由で CORESERVER の MySQL に投入する。
#
# CORESERVER 側 ~/.my.cnf に以下のグループが必要:
#   [client-technote]
#   [client-estate]

function deploysql() {
    local dir="$HOME/Downloads"
    local archive="$HOME/Desktop/deployed_sql"
    local file base target timestamp dest answer

    # Downloads にある最新の対象 SQL を取得
    file=$(find "$dir" -maxdepth 1 -type f \
        \( -name 'technote_*.sql' -o -name 'estate_*.sql' \) \
        -print0 2>/dev/null | xargs -0 ls -t 2>/dev/null | head -1)

    if [[ -z "$file" ]]; then
        echo "投入対象のSQLがありません。"
        return 1
    fi

    base="${file:t}"

    # ファイル名から接続先を判定
    case "$base" in
        technote_*) target="technote" ;;
        estate_*)   target="estate" ;;
        *)
            echo "DBを判定できません: $base"
            return 1
            ;;
    esac

    echo
    echo "----------------------------------------"
    echo " SQL : $base"
    echo " DB  : $target"
    echo "----------------------------------------"
    echo

    read "answer?このSQLを投入しますか？ [y/N] "
    if [[ "$answer" != [yY] ]]; then
        echo "キャンセルしました。"
        return 0
    fi

    # SQL はサーバーへ保存せず、そのまま標準入力で MySQL へ渡す
    if ssh core "mysql --defaults-group-suffix=-$target" < "$file"; then
        echo
        echo "DBへの投入に成功しました。"

        mkdir -p "$archive" || return 1
        timestamp=$(date '+%Y%m%d_%H%M%S')
        dest="$archive/${timestamp}_${base}"

        if mv "$file" "$dest"; then
            echo "SQLを退避しました:"
            echo "$dest"
        else
            echo "WARNING: DB投入には成功しましたが、SQLの退避に失敗しました。"
            echo "再投入しないよう注意してください: $file"
            return 1
        fi
    else
        echo
        echo "ERROR: DBへの投入に失敗しました。"
        echo "SQLはDownloadsに残しています。"
        return 1
    fi
}
