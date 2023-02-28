#!/usr/bin/env bash

#Created by https://github.com/Toni500github
#Used for https://github.com/Toni500github/musical_donut
DIR=$(dirname $0)

printf "\e[1;34mChecking libvlc headers... \n\n"

## if donut exists already, it will remove it
function donut_exists {
if [[ -f $DIR/donut ]]; then
  printf "donut exists already, overwrite? "
  read yn
  case $yn in
    y|Y|ye|yeah|yes|YES|Yes|yep|Es|es|YeS)
    rm $DIR/donut
 ;;
    n|N|NO|no|nO|No|nope|NOPE|o|O)
    printf "\e[1;32mdonut will not be overwritten\n"
    exit 0
  esac
fi
}

## check if you are rumning android and Termux
function detect_termux {
arch=$(uname -o)
  if [[ $arch == Android ]] && [[ -d /data/data/com.termux/files/usr/bin/ ]]; then
    detect_libvlc_termux
    compile
  else
    detect_libvlc
    compile
  fi
}

## check if you have installed libvlc-dev
function detect_libvlc {
  if [[ ! -d /usr/include/vlc || ! -f /usr/include/vlc/vlc.h ]]; then
    printf "\e[1;31mPlease install libvlc-dev and vlc with your packages manager\n"
    exit 1
  else
    printf "\e[1;32mlibvlc headers are installed! \n"
    printf "\e[1;34mcompiling main.c ... \n\n"
  fi
}

## same thing with detect_libvlc but for termux
function detect_libvlc_termux {
  if [[ ! -d /data/data/com.termux/files/usr/include/vlc || ! -f /data/data/com.termux/files/usr/include/vlc/vlc.h ]]; then
    printf "\e[1;31mvlc not installed. \e[1;34mInstalling vlc...\n"
    pkg update
    pkg reinstall vlc
      if [[ ! -d /data/data/com.termux/files/usr/include/vlc || ! -f /data/data/com.termux/files/usr/include/vlc/vlc.h ]]; then
      printf "\e[1;31mcouldn't install vlc"
      exit 1

      else
	detect_libvlc_termux
      fi
  else
    printf "\n\e[1;32mlibvlc headers are installed! \n"
    printf "\e[1;34mcompiling main.c ... \n\n"
  fi
}

## compile the main.c file in the script directory
function compile {
  if [[ ! -f $DIR/main.c ]]; then
    printf "\e[1;main.c not found in this directory \n"
    exit 1
  else
    cc $DIR/main.c -o $DIR/donut -lm -lvlc
  fi

## this will detect if donut is there after compiling
  if [[ ! -f $DIR/donut ]]; then
    printf " \e[1;31mdonut not compiled successfully \n"
    exit 1
  else
    printf "\n\e[1;32mdonut compiled, now you can run ./donut \n\e[1;34mStarting donut...\e[0m\n"
  fi
}

## calls functions and execute donut
donut_exists
detect_termux
chmod +x $DIR/donut && cd $DIR && ./donut
