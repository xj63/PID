mkdir -p out
emcc ../../pid.c ../../features/default.c ../push-box.c -o out/pid-push-box.js -s EXPORTED_FUNCTIONS='["_pid_new", "_pid_update", "_push_box", "_malloc", "_free"]' -s EXPORTED_RUNTIME_METHODS='["cwrap", "getValue", "setValue"]'
mv out/pid-push-box.js pid-push-box.wasm.js
mv out/pid-push-box.wasm pid-push-box.wasm
rmdir out
