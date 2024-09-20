mkdir -p out
emcc ../push-box.c -o out/push-box.js -s EXPORTED_FUNCTIONS='["_push_box", "_malloc", "_free"]' -s EXPORTED_RUNTIME_METHODS='["cwrap", "getValue", "setValue"]'
mv out/push-box.js push-box.wasm.js
mv out/push-box.wasm push-box.wasm
rmdir out
