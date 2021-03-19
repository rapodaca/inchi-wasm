mkdir -p build

if [[ "$OSTYPE" =~ ^darwin ]]; then
  PLATFORM="-D__APPLE__"
  PATH=/usr/local/opt/llvm/bin:$PATH
else
  PLATFORM=""
fi

clang \
  -dynamiclib \
  -Oz \
  -v \
  -DTARGET_API_LIB \
  ${PLATFORM} \
  -Isrc/molfile_to_inchi.h \
  -Iinchi/INCHI_BASE/src \
  inchi/INCHI_BASE/src/*.c \
  inchi/INCHI_API/libinchi/src/*.c \
  src/inchi_wasm.c \
  -o build/inchi_wasm.dylib