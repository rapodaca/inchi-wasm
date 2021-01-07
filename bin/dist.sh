#!/bin/bash

mkdir -p dist

cp lib/wasi.esm.js dist
cp lib/molfile-to-inchi.js dist
cp build/molfile_to_inchi.wasm dist
cp web/index.html dist

sed -i "" -e "s/..\/build/\./g" ./dist/molfile-to-inchi.js
sed -i "" -e "s/..\/lib/\./g" ./dist/index.html