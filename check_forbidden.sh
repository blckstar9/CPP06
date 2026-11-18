#!/usr/bin/env bash

set -eu

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
TARGET_DIRS="$ROOT_DIR/ex00 $ROOT_DIR/ex01 $ROOT_DIR/ex02"
TMP_FILE="$(mktemp)"
FOUND=0

check_pattern() {
	local pattern="$1"
	local label="$2"
	local status

	if grep -R -nE \
		--include='*.cpp' \
		--include='*.hpp' \
		--include='*.h' \
		"$pattern" $TARGET_DIRS > "$TMP_FILE"; then
		echo "[KO] Forbidden pattern found: $label"
		cat "$TMP_FILE"
		FOUND=1
	else
		status=$?
		if [ "$status" -eq 1 ]; then
			echo "[OK] $label"
		else
			echo "[KO] grep error while scanning: $label"
			FOUND=1
		fi
	fi
}

check_pattern '\busing[[:space:]]+namespace\b' "using namespace"
check_pattern '\bfriend\b' "friend keyword"
check_pattern 'printf[[:space:]]*\(' "printf function"
check_pattern '(^|[^[:alnum:]_])(malloc|calloc|realloc|free)[[:space:]]*\(' "C alloc/free"
check_pattern '#[[:space:]]*include[[:space:]]*<algorithm>' "algorithm header"
check_pattern '#[[:space:]]*include[[:space:]]*<(vector|list|map|set|deque|stack|queue|unordered_map|unordered_set)>' "STL containers"
check_pattern 'typeinfo' "typeinfo header or symbol"
check_pattern '\btypeid\b' "typeid operator"

rm -f "$TMP_FILE"

if [ "$FOUND" -ne 0 ]; then
	echo "Forbidden scan failed."
	exit 1
fi

echo "Forbidden scan passed."
