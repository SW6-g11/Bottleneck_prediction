#!/bin/sh
DIRECTORY="./build"
FILENAME="testing"
if [ ! -d "$DIRECTORY" ]; then
  mkdir $DIRECTORY
fi
rm $DIRECTORY/$FILENAME
cd $DIRECTORY
cmake ..
make
./testing