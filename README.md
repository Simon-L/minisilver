# OpenSilver/eightohat flavours of TB-303 clone

> :warning: WIP! Put a limiter on the output! There are known bugs causing high volume!

![screenshot](./doc/Screenshot.png)

## Building

```bash
git clone --recursive https://github.com/Simon-L/eightohat
cmake -Bbuild
cmake --build build
# optionally cmake --build build --parallel 16
./build/bin/eightohat
```

License is GPL 3 or later