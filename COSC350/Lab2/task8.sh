#!/bin/bash
# This program takes a number and prints the sum of its digits
#

# if the number of parameters is less than 1 error 1
if [ $# -lt 1 ]; then 
	echo "You need to pass one numberical argument"
	exit 1
fi

num=$1 # set the num
result=${num:0:1} # begin the result by placeing in the first digit
length=`expr ${#num} - 1` # grab the length

for i in $(seq 1 $length); 
do
	# add in the next digit
	result=`expr $result + ${num:$i:1}`
done

# print result
echo $result

exit 0

