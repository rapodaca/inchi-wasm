#!/bin/bash

mkdir -p dist

cp lib/wasi.esm.js dist
cp lib/inchi-wasm.js dist
cp build/inchi_wasm.wasm dist
cp web/index.html dist

sed -i "" -e "s/..\/build/\./g" ./dist/inchi-wasm.js
sed -i "" -e "s/..\/lib/\./g" ./dist/index.html