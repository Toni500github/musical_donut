# Crossplatform Musical Spinning Donut 3D

just some spinning 3D donut but with the option to choose which song you want to play in background

[Original Video with source code](https://www.youtube.com/watch?v=DEqXNfs_HhY)

# How to use/compile

### Linux/Termux
```bash
bash compile.sh
```
or
```bash
gcc donut.c -o donut.o -lvlc -lm
./donut.o
```
### Windows (MinGW-64) (you will need to setup the VLC library in your windows host)
```bash
gcc donut.c -o donut.exe -lvlc -lm
```
### MacOS
if you have one and compiled the donut, send pull request about how to compile for MacOS

# Know bugs
* No bugs 💯💯
