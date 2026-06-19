#!/usr/bin/env bash

set -euo pipefail

# -----------------------------
# Configuration
# -----------------------------

APP="./build/app"
BUILD_DIR="./build"

# -----------------------------
# Input validation
# -----------------------------

if [[ $# -lt 2 ]]; then
    echo "Usage:"
    echo "  $0 <output_name> REGEX=\"<expression>\""
    echo ""
    echo "Example:"
    echo "  $0 demo REGEX=\"(a|b)*ab\""
    exit 1
fi

OUT_NAME="$1"
shift

# Parse REGEX=...
REGEX=""

for arg in "$@"; do
    case "$arg" in
        REGEX=*)
            REGEX="${arg#REGEX=}"
            ;;
    esac
done

if [[ -z "${REGEX}" ]]; then
    echo "Error: REGEX not provided."
    echo "Use: REGEX=\"your_regex\""
    exit 1
fi

# -----------------------------
# Paths
# -----------------------------

DOT_FILE="${BUILD_DIR}/${OUT_NAME}.dot"
PNG_FILE="${BUILD_DIR}/${OUT_NAME}.png"

# -----------------------------
# Ensure build dir exists
# -----------------------------

mkdir -p "$BUILD_DIR"

# -----------------------------
# Build if needed
# -----------------------------

if [[ ! -f "$APP" ]]; then
    echo "Building project..."
    make
fi

# -----------------------------
# Run regex → DOT
# -----------------------------

echo "Generating NFA DOT: $DOT_FILE"

"$APP" "$REGEX" "$DOT_FILE"

# -----------------------------
# DOT → PNG
# -----------------------------

echo "Generating PNG: $PNG_FILE"

dot -Tpng "$DOT_FILE" -o "$PNG_FILE"

echo "Done."
echo "DOT: $DOT_FILE"
echo "PNG: $PNG_FILE"