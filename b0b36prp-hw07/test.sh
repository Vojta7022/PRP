#!/usr/bin/env bash

make clean
make

echo -------------------------------------------------------------------
echo BASE
echo -------------------------------------------------------------------
for VAR in {1..4}; do
    echo ------------------------------------
    name="./data/man/pub0$VAR-m"
    pattern=(`cat "$name.in.pat"`)
    file_in="$name.in"
    file_out="$name.out"
    return_val=(`cat "$name.in.return"`)

    echo ./hw07-b0b36prp $pattern $file_in

    ./hw07-b0b36prp $pattern $file_in > tmp
    echo expected: $return_val got: $?
    diff -y $file_out tmp

    # this is actually the output of the diff
    # 0 == same, 1 == different, 2 == trouble
    diff_result=$?
    if [[ $diff_result = 0 ]]; then
        echo "DIFF: FILES ARE THE SAME"
    elif [[ $diff_result = 1 ]]; then
        echo "DIFF: FILES ARE DIFFERENT"
    elif [[ $diff_result = 2 ]]; then
        echo "DIFF: SOMETHING IS WRONG"
    fi
done


echo -------------------------------------------------------------------
echo OPTIONAL
echo -------------------------------------------------------------------
declare -a arr=("01-A" "02-B" "03-B" "04-B" "05-C")
for VAR in "${arr[@]}"; do
    echo ------------------------------------
    name="./data/opt/pub$VAR"
    pattern=(`cat "$name.in.pat"`)
    file_in="$name.in"
    file_out="$name.out"
    return_val=(`cat "$name.in.return"`)
    #echo "$pattern $file"

    if [[ ${VAR:3:1} = "B" ]]; then
        flags="-E"
    elif [[ ${VAR:3:1} = "C" ]]; then
        flags="--color=always"
    else
        flags=""
    fi
    echo ./hw07-b0b36prp $flags $pattern $file_in

    ./hw07-b0b36prp $flags $pattern $file_in > tmp
    echo expected: $return_val got: $?
    diff -y $file_out tmp

    # this is actually the output of the diff
    # 0 == same, 1 == different, 2 == trouble
    diff_result=$?
    if [[ $diff_result = 0 ]]; then
        echo "DIFF: FILES ARE THE SAME"
    elif [[ $diff_result = 1 ]]; then
        echo "DIFF: FILES ARE DIFFERENT"
    elif [[ $diff_result = 2 ]]; then
        echo "DIFF: SOMETHING IS WRONG"
    fi
done

