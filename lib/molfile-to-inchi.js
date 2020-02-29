import WASI from './wasi.esm.js';

const wasmPath = '../build/molfile_to_inchi.wasm';
const memory = new WebAssembly.Memory({ initial: 10 });

(async () => {
  const response = await fetch(wasmPath);
  const bytes = await response.arrayBuffer();
  const wasi = new WASI();
  const { instance } = await WebAssembly.instantiate(bytes, {
    env: { memory }, wasi_snapshot_preview1: wasi.wasiImport
  });
  const pMolfile = instance.exports.malloc(1024);
  const pOptions = instance.exports.malloc(1024);
  const pOutput = instance.exports.malloc(20480);

  window.molfileToInChI = (molfile) => {
    const inputView = new Uint8Array(memory.buffer);
    const encoder = new TextEncoder();
  
    inputView.set(encoder.encode(molfile), pMolfile);
    
    const result = instance.exports.molfile_to_inchi(
      pMolfile, pOptions, pOutput
    );

    const outputView = new Uint8Array(memory.buffer);
    const decoder = new TextDecoder();
    const output = decoder.decode(
      outputView.subarray(pOutput, outputView.indexOf(0, pOutput))
    );

    if (result < 0 || result > 1) {
      throw Error("inchi error: " + output);
    }

    return output;
  };

  window.dispatchEvent(new Event('InChIReady'));
})();