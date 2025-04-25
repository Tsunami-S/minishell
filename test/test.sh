#!/bin/bash

TEST_FILE="./tester/all"
MINISHELL="./minishell"

echo "=== Minishell Leak Tester ==="

leaked_indices=()
index=0

# テストケース読み込み
while IFS= read -r line || [ -n "$line" ]; do
    echo "[$index] Running test: $line"

    # minishellでリークチェック実行 (definiteのみ表示)
    valgrind_output=$(echo -e "$line\nexit" | valgrind --leak-check=full --show-leak-kinds=definite --error-exitcode=42 $MINISHELL 2>&1)
    minishell_status=$?

    # リークチェック
    if [[ $minishell_status -eq 42 ]]; then
        echo "❌ Memory leak detected at test [$index]:"
        echo "$valgrind_output"
        leaked_indices+=("$index")
    fi

    echo "-------------------------------------"
    ((index++))
done < "$TEST_FILE"

# リークのあったテスト番号まとめて表示
if [ ${#leaked_indices[@]} -eq 0 ]; then
    echo "✅ No memory leaks detected in any test."
else
    echo "❌ Memory leaks detected in the following test(s):"
    echo "${leaked_indices[@]}"
fi
