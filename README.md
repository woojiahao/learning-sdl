To compile on MacOS:

```bash
gcc main.c -I /usr/local/include/SDL3 -L /usr/local/lib -lSDL3 -Wl,-rpath,/usr/local/lib
```