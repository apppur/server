#!/bin/bash

Make()
{
  if [ "all" == "$1" ]
  then
    make clean
    make -j`cat /proc/cpuinfo | grep 'cpu cores' | wc -l`
    make test
  elif [ "clean" == "$1" ]
  then
    make clean
  elif [ "force" == "$1" ]
  then
    make clean
    make -j`cat /proc/cpuinfo | grep 'cpu cores' | wc -l`
    make test
  elif [ "normal" == "$1" ]
  then
    make -j`cat /proc/cpuinfo | grep 'cpu cores' | wc -l`
    #make test
  else
    make -j`cat /proc/cpuinfo | grep 'cpu cores' | wc -l`
  fi
}

if [ ! -d "build" ]
then
  echo "build file does not exist, we will make it."
  mkdir build
  cd build
  cmake ..
  #make -j`cat /proc/cpuinfo | grep 'cpu cores' | wc -l`
  Make
else
  cd build
  #echo `cat /proc/cpuinfo | grep 'cpu cores' | wc -l`
  #make -j`cat /proc/cpuinfo | grep 'cpu cores' | wc -l`
  Make
fi

