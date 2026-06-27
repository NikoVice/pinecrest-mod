#!/usr/bin/env bash
# ============================================================================
#  compile.sh - build the Pinecrest gamemode on Linux (server / VPS / CI)
# ----------------------------------------------------------------------------
#  Downloads a pinned Linux build of the pawn-lang compiler on first run,
#  then compiles gamemodes/main.pwn -> gamemodes/main.amx using the project's
#  include path (pawno/include).
#
#  Usage:
#    ./compile.sh                # compile gamemodes/main.pwn
#    ./compile.sh cameditor      # compile gamemodes/cameditor.pwn
#    ./compile.sh gamemodes/foo  # compile an explicit .pwn path
#
#  Requirements: bash, curl (or wget), tar, and 32-bit glibc
#  (already present on any host that runs the 32-bit samp03svr).
# ============================================================================
set -euo pipefail

# --- settings ---------------------------------------------------------------
PAWN_VERSION="3.10.4"   # matches pawno/VERSION.txt (community compiler)
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
COMPILER_DIR="${ROOT_DIR}/.compiler/pawnc-${PAWN_VERSION}-linux"
PAWNCC="${COMPILER_DIR}/bin/pawncc"
LIB_DIR="${COMPILER_DIR}/lib"
# Compiler options - kept identical to .gitlab-ci.yml so local and CI builds
# produce the same result:
#   -ipawno/include -igamemodes   include search paths
#   -;+                           require semicolons (the codebase relies on it)
PAWN_OPTS=(-i"${ROOT_DIR}/pawno/include" -i"${ROOT_DIR}/gamemodes" -\;+)

# --- pick the input file ----------------------------------------------------
INPUT="${1:-gamemodes/main}"
INPUT="${INPUT%.pwn}"                       # strip extension if given
case "$INPUT" in
    */*) SRC="${ROOT_DIR}/${INPUT}.pwn" ;;  # explicit path
    *)   SRC="${ROOT_DIR}/gamemodes/${INPUT}.pwn" ;;
esac
OUT="${SRC%.pwn}.amx"

if [[ ! -f "$SRC" ]]; then
    echo "ERROR: source not found: $SRC" >&2
    exit 1
fi

# --- ensure the compiler is present -----------------------------------------
fetch() {
    local url="$1" dst="$2"
    if command -v curl >/dev/null 2>&1; then
        curl -fSL --retry 4 --retry-delay 2 --max-time 120 "$url" -o "$dst"
    elif command -v wget >/dev/null 2>&1; then
        wget -q -O "$dst" "$url"
    else
        echo "ERROR: need curl or wget to download the compiler." >&2
        exit 1
    fi
}

if [[ ! -x "$PAWNCC" ]]; then
    echo ">> Pawn compiler ${PAWN_VERSION} not found, downloading..."
    mkdir -p "${ROOT_DIR}/.compiler"
    TARBALL="$(mktemp)"
    URL="https://github.com/pawn-lang/compiler/releases/download/v${PAWN_VERSION}/pawnc-${PAWN_VERSION}-linux.tar.gz"
    fetch "$URL" "$TARBALL"
    tar -xzf "$TARBALL" -C "${ROOT_DIR}/.compiler"
    rm -f "$TARBALL"
    chmod +x "$PAWNCC"
fi

# --- 32-bit runtime sanity check --------------------------------------------
# pawncc with no input exits non-zero, so detect the binary by its banner.
if ! LD_LIBRARY_PATH="$LIB_DIR" "$PAWNCC" 2>&1 | grep -q "Pawn compiler"; then
    echo "WARNING: pawncc failed to start. It is a 32-bit (i386) binary -" >&2
    echo "         install 32-bit glibc, e.g. on Debian/Ubuntu:" >&2
    echo "           sudo dpkg --add-architecture i386 && sudo apt-get update" >&2
    echo "           sudo apt-get install -y libc6:i386" >&2
fi

# --- compile ----------------------------------------------------------------
# Run from the repo root with -igamemodes so that include paths written as
# "logic/..." resolve exactly like in the GitLab CI build.
echo ">> Compiling: ${SRC#$ROOT_DIR/}"
echo ">> Output:    ${OUT#$ROOT_DIR/}"
set +e
( cd "$ROOT_DIR" && LD_LIBRARY_PATH="$LIB_DIR" "$PAWNCC" "$SRC" -o"$OUT" "${PAWN_OPTS[@]}" )
STATUS=$?
set -e

if [[ $STATUS -eq 0 && -f "$OUT" ]]; then
    echo ">> OK: built $(basename "$OUT") ($(stat -c%s "$OUT" 2>/dev/null || wc -c <"$OUT") bytes)"
else
    echo ">> Compilation finished with errors (exit $STATUS)." >&2
fi
exit $STATUS
