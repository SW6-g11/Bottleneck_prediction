#!/bin/sh
DIRECTORY="./build"
if [ ! -d "$DIRECTORY" ]; then
  mkdir $DIRECTORY
fi
cd $DIRECTORY
cmake ..
make
./Network_Simulator