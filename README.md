# InChI-Wasm

Compiles a molfile to InChI function written in C and linked to the InChI C library to WebAssembly.

## Instructions

For an overview of the procedure, see [Compiling C to WebAssembly and Running It - without Emscripten](https://depth-first.com/articles/2019/10/16/compiling-c-to-webassembly-and-running-it-without-emscripten/).

To summarize:

1. Install LLVM on your platform. On macOS, that probably means installing through Homebrew.
2. Activate LLVM, if necessary. macOS users will need to append the LLVM `bin` path to the `PATH` environment variable. Something like `export PATH=/usr/local/opt/llvm/bin:$PATH` should work.
3. Verify that LLVM is working with `llc --version`. The output should include `wasm32` and `wasm64`.
4. Clone, compile, and install [wasi-libc](https://github.com/CraneStation/wasi-libc).
5. Copy the file [libclang_rt.builtins-wasm32.a](https://github.com/jedisct1/libclang_rt.builtins-wasm32.a) to your local LLVM `bin/wasi` directory.

From there, you can compile this project with:

```bash
cd inchi-wasm
bin/build.sh
```