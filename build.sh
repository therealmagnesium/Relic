#!/bin/bash

if [ "$1" == "windows" ] || [ "$1" == "linux" ]; then
    vendor/"$1"/premake5 gmake
else
    echo "Invalid argument"
fi

if [ "$2" == "debug" ]; then
    echo "Performing debug build..."
    make all config=debug
    cd bin/Debug-windows/RelicApp
    ./RelicApp.exe
elif [ "$2" == "release" ]; then
    echo "Performing release build..."
    make all config=release
    cd bin/Release-windows/RelicApp
    ./RelicApp.exe    
elif [ "$2" == "dist" ]; then
    echo "Performing distribution release..."
    make all config=dist
    cd bin/Dist-windows/RelicApp
    ./RelicApp.exe
else
    echo "Invalid argument"
fi
