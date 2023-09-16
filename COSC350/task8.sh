#!/bin/bash
# This program takes a number and prints the sum of its digits
#

if [ $# -lt 1 ]; then 
	echo "You need to pass one numberical argument"
	exit 1
fi

num=$1
result=${num:0:1}
length=${#num}

i=1
while [ $i -ne $length ]; 
do
	result=`expr $result + ${num:$i:1}`
	i=`expr $i + 1`
done

echo $result

exit 0

