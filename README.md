# ARMv9-Sim

## Instructions to run the code

### Dependencies
- Make sure gcc is installed with GCC Version 12 and above for ARM v9 support.
```bash
gcc --version
gcc.exe (MinGW.org GCC-6.3.0-1) 6.3.0
Copyright (C) 2016 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### Run benchmarks
```bash
make run
```

## Multi Arch Setup
Ensure docker, docker buildx has been installed

### Build MultiArch Image

```bash
docker buildx build -t keshikash/bench --platform linux/amd64,linux/arm64 .
```

```bash
docker run keshikash/bench
```
