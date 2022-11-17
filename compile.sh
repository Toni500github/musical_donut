#!/usr/bin/env bash

#Created by https://github.com/Toni500github
#Used for https://github.com/Toni500github/musical_donut
DIR=$(dirname $0)

printf "\e[1;34mChecking libvlc headers... \n\n"
sleep 1

## if donut.o exists already, it will remove it
if [[ -f $DIR/donut.o ]]; then
  rm $DIR/donut.o
fi

## check if you have installed libvlc-dev
function detect_libvlc() {
  if [[ ! -d /usr/include/vlc || ! -f /usr/include/vlc/vlc.h ]]; then
    printf "\e[1;31mPlease install libvlc-dev with your packages manager\n"
    exit 1
  else
    printf "\e[1;32mlibvlc headers are installed! \n"
    printf "\e[1;34mcompiling donut.c ... \n\n \e[0m"
    sleep 1
  fi
}

## compile the donut.c file in the script directory
function compile() {
  if [[ ! -f $DIR/donut.c ]]; then
    printf "\e[1;31mdonut.c not found in this directory \n"
    exit 1
  else
    gcc -Wimplicit-function-declaration $DIR/donut.c -o $DIR/donut.o -lm -lvlc
  fi

## this will detect if donut.o is there after compiling
  if [[ ! -f $DIR/donut.o ]]; then
    printf " \e[1;31mdonut.o not compiled successfully \n"
    exit 1
  else
    printf "\e[1;34mdonut.o compiled, now run you can ./donut.o \nStarting donut.o ...\e[0m\n"
  fi
}

## calls fuctions
detect_libvlc
compile
chmod +x $DIR/donut.o && cd $DIR && ./donut.o
