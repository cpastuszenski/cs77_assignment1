#!/bin/bash

function check_error {
    if [ "$?" -ne "0" ]; then
        echo "An error occurred!"
        exit 1
    fi
}

echo "test01: Ray-Sphere intersection"
./trace -s 1 scenes/test01.json
check_error

echo "test02: Ray-Triangle intersection"
./trace -s 1 scenes/test02.json
check_error

echo "test03: Shadow test"
./trace -s 1 scenes/test03.json
check_error

echo "test04: Reflection"
./trace -s 1 scenes/test04.json
check_error

echo "test05: Supersample"
./trace -s 9 scenes/test05.json
check_error

echo "test06: Large scene"
./trace -s 9 scenes/test06.json
check_error

echo "test07: Large scene with capped cylinder"
./trace -s 9 scenes/test07.json
check_error

echo "All completed successfully!"
