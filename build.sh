#!/bin/bash

vendor/bin/premake5.exe gmake

if [ "$1" == "debug" ]; then
    echo "Performing debug build..."
    make all config=debug
    cd bin/Debug-windows/RelicApp
    ./RelicApp.exe
elif [ "$1" == "release" ]; then
    echo "Performing release build..."
    make all config=release
    cd bin/Release-windows/RelicApp
    ./RelicApp.exe    
elif [ "$1" == "dist" ]; then
    echo "Performing distribution release..."
    make all config=dist
    cd bin/Dist-windows/RelicApp
    ./RelicApp.exe
else
    echo "Invalid argument"
fi
