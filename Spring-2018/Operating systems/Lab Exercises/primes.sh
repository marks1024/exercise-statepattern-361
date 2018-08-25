##!/bin/bash
#echo "Prime numbers between 60000 and 63000:"
#number1=60000
#number2=63000
#
#until [ "$number1" = "$number2" ]
#do
#    flag=0
#    for (( i = 2; i <= "$(( $number1 / 2 ))"; i++ ))
#    do
#        tmp=$(( $number1 % i))
#        if [ $tmp -eq 0 ];
#        then
#            let "flag=1"
#            break
#        fi
#    done
#
#if [ $flag -eq 0 ]
#then
#    echo $number1
#fi
#let "number1 = $number1 + 1"
#done

#!/bin/bash

DIRNAME=$1
FILETYPE=$2
LOGFILE=$3

file "$DIRNAME"/* | fgrep "$FILETYPE" | tee $LOGFILE | wc -l

exit 0






