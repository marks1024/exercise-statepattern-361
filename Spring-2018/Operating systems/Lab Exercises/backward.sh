#!/bin/bash
filename=$1
outfile="$2"
count=0
while read -r -n1 ch
do
    array[count]=$ch
    let "count += 1"
    #echo $line
    #echo -e $line"\n\n" >> "$outfile"

done < "$filename"
echo "${array[3]}"
echo "${array[@]}"

index="${#array[*]}"
let "index -= 1"
printf '%c' ${array[index]} > "$filename"
#echo -e ${array[index-1]} > "$filename"


while [ "$index" -gt 0 ]
do
    let "index -= 1"
    # echo -e ${array[index]} >> "$filename"
    printf '%c' ${array[index]} >> "$filename"

done
