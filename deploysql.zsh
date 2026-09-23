# deploysql.zsh
# Upload the newest matching SQL file in ~/Downloads directly to a remote MySQL client over SSH.
# Environment-specific mappings live in ~/.config/deploysql/config.zsh and should not be committed.

deploysql() {
    local dir="$HOME/Downloads"
    local archive="$HOME/Desktop/deployed_sql"
    local config="$HOME/.config/deploysql/config.zsh"
    local file base target timestamp dest answer pattern

    if [[ ! -r "$config" ]]; then
        echo "設定ファイルがありません: $config"
        echo "deploysql_config.example.zsh を参考に作成してください。"
        return 1
    fi

    # shellcheck disable=SC1090
    source "$config"

    if [[ -z "$DEPLOYSQL_SSH_HOST" || ${#DEPLOYSQL_RULES[@]} -eq 0 ]]; then
        echo "deploysql の設定が不完全です: $config"
        return 1
    fi

    # Build find conditions from configured filename patterns.
    local -a find_args
    find_args=("$dir" -maxdepth 1 -type f '(')
    local first=1
    for pattern target in ${(kv)DEPLOYSQL_RULES}; do
        if (( ! first )); then
            find_args+=(-o)
        fi
        find_args+=(-name "$pattern")
        first=0
    done
    find_args+=(')' -print0)

    file=$(find "${find_args[@]}" | xargs -0 ls -t 2>/dev/null | head -1)

    if [[ -z "$file" ]]; then
        echo "投入対象のSQLがありません。"
        return 1
    fi

    base="${file:t}"
    target=""

    for pattern target_name in ${(kv)DEPLOYSQL_RULES}; do
        if [[ "$base" == ${~pattern} ]]; then
            target="$target_name"
            break
        fi
    done

    if [[ -z "$target" ]]; then
        echo "投入先を判定できません: $base"
        return 1
    fi

    echo
    echo "----------------------------------------"
    echo " SQL : $base"
    echo " DB  : $target"
    echo " HOST: $DEPLOYSQL_SSH_HOST"
    echo "----------------------------------------"
    echo

    read "answer?このSQLを投入しますか？ [y/N] "
    if [[ "$answer" != [yY] ]]; then
        echo "キャンセルしました。"
        return 0
    fi

    if ssh "$DEPLOYSQL_SSH_HOST" "mysql --defaults-group-suffix=-$target" < "$file"; then
        echo
        echo "DBへの投入に成功しました。"

        mkdir -p "$archive"
        timestamp=$(date '+%Y%m%d_%H%M%S')
        dest="$archive/${timestamp}_${base}"
        mv "$file" "$dest"

        echo "SQLを退避しました:"
        echo "$dest"
    else
        echo
        echo "ERROR: DBへの投入に失敗しました。"
        echo "SQLはDownloadsに残しています。"
        return 1
    fi
}
