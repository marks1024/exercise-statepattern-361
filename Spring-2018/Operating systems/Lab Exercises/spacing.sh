#!/bin/bash

filename="$1"
count=0

while read -r line
do

#single spacing
#    if [ "$line" != "" ]
#    then
        array[count]=$line
        let "count += 1"
#    fi

done < "$filename"
echo "${array[3]}"
echo "${array[@]}"

#double spacing

#echo -e ${array[0]}"\n\n" > "$filename"
#index=1
#
#while [ "$index" -lt "${#array[*]}" ]
#do
#    echo -e ${array[index]}"\n\n" >> "$filename"
#    let "index += 1"
#done

