#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname ${BASH_SOURCE[0]})" && pwd)"
TOP_DIR="${SCRIPT_DIR}/.."

cd ${TOP_DIR}

RESULT=0

for text_file in $(find . -type f \( -name "*.cpp" -or -name "*.h" -or -name "*.txt" -or -name "*.sh" -or -name "*.cmake" -or -name "*.inl" -or -name "*.hpp" \));
do
    if ! (enca $text_file -L russian | grep -q "7bit ASCII characters") ; then
        echo "File $text_file"
        enca $text_file -L russian
        RESULT=1
    fi 
done

if [[ $RESULT = 1 ]]; then
    echo "ERROR: Some files have content encoded differently  than 7bit ASCII."
    exit 1
fi

exit 0