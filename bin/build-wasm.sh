#!/bin/bash

if [ -n "$WASI_LIBC_HOME" ]; then
  echo "Reading libc from $WASI_LIBC_HOME"
else
  echo "Set the libc location with 'export WASI_LIBC_HOME=path/to/wasi-libc'."
  exit 1
fi

mkdir -p build

if [[ "$OSTYPE" =~ ^darwin ]]; then
  PLATFORM="-D__APPLE__"
  PATH=/usr/local/opt/llvm/bin:$PATH
else
  PLATFORM=""
fi

clang \
  --target=wasm32-unknown-wasi \
  --sysroot ${WASI_LIBC_HOME} \
  -Oz \
  -v \
  -Wl,-import-memory \
  -Wl,-wrap,clock \
  -Wl,-export,malloc \
  -Wl,-export,molfile_to_inchi \
  -Wl,-export,inchi_to_inchikey \
  -Wl,-no-entry \
  -DTARGET_API_LIB \
  ${PLATFORM} \
  -Iinchi/INCHI_BASE/src \
  inchi/INCHI_BASE/src/*.c \
  inchi/INCHI_API/libinchi/src/*.c \
  src/inchi_wasm.c \
  -o build/inchi_wasm.wasm