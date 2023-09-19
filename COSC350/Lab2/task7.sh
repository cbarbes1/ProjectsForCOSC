#!/bin/bash
# This shell script calculates the factorial of a number in this form n*(n-1)
#
#

# check to make sure the correct format was used
if [ $# < 1 ]; 
then
	echo "The Format for this script is ./task7.sh <numerical value>"
	exit 1
fi

# save the argument in a variable 
result=$1
# save the first factorial multiple
fact=`expr $1 - 1`

# while the factorial multiple is not 0
while [ $fact != 0 ]; do
	result=`expr $result \* $fact`
	let fact--
done

# print the result
echo $result

exit 0
