#!/usr/bin/env bash

cd ..

find . -type f \( -name "*.cpp" -or -name "*.h" -or -name "*.txt" -or -name "*.sh" -or -name "*.cmake" -or -name "*.inl" -or -name "*.hpp" \) -exec bash -c '

if ! (enca "{}" -L russian | grep -q "7bit ASCII characters") ; then
    echo "File '{}'"
    enca "{}" -L russian
fi 

' -- {} \;


