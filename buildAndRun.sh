#!/bin/sh
DIRECTORY="./build"
FILENAME="Network_Simulator"
if [ ! -d "$DIRECTORY" ]; then
  mkdir $DIRECTORY
fi
rm $DIRECTORY/$FILENAME
cd $DIRECTORY
cmake ..
make
./Network_Simulator
./testing