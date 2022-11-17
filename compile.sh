#!/usr/bin/env bash

#Created by https://github.com/Toni500github
#Used for https://github.com/Toni500github/musical_donut

printf "\e[1;34mChecking libvlc headers... \n\n"
sleep 1

## check if you have installed libvlc-dev
function detect_libvlc() {
  if [[ ! -d /usr/include/vlc || ! -f /usr/include/vlc/vlc.h ]]; then
    printf "\e[1;31mPlease install libvlc-dev with your packages manager\n"
    exit  1
  else
    printf "\e[1;32mlibvlc headers are installed! \n"
    printf "compiling donut.c ... \n\n"
    sleep 1
  fi
}

## compile the donut.c file in the script directory
function compile() {
  if [[ ! -f $(dirname $0)/donut.c ]]; then
    printf "\e[1;31mdonut.c not found in this directory \n"
    exit 1
  else
    gcc donut.c -o donut.o -lm -lvlc -Wimplicit-function-declaration
  fi

## this will detect if donut.o is there after compiling
  if [[ ! -f $(dirname $0)/donut.o ]];then
    printf " \e[1;31mdonut.o not compiled successfully"
    exit 1
  else
    printf "\n\e[1;32mdonut.o compiled, now run ./donut.o \n"
    exit 0
  fi
}

## calls fuctions
detect_libvlc
compile
