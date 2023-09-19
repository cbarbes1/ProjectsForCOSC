#!/bin/bash
# This shell script implements a function to Display a diamond of a particular width onto the console using input verification

# function to print the diamond out with the desired width
printStars()
{
	local t=$1
	local mid=`expr $t / 2` # number of chars in the first line
	let mid++ # increment to find actual value
	local midpoint=$mid # save the mid point
	star="*" # string to build the line
	stars="*" # actual output string
	
	# loop from 1 to the width - 1
	for i in $(seq 1 `expr $t - 1`); 
	do
		printf '%*s\n' $mid "$stars"	# print the actual line with mid number of chars on the line
		if [ $i -lt $midpoint ]; # if in the first sector 
		then
			let mid++
			stars="${stars}$star$star"
		else # second sector 
			end=${#stars}
			stars="${stars:0:`expr $end-2`}"
			let mid--	
		fi
	done
	printf '%*s\n' $midpoint "*"
}
		
# if no base dont continue
if [ -z $1 ]; then
	echo "no input"
	exit 1
elif [ $1 -gt 3 ]; then
	x=`expr $1 % 2`
	if [ $x = 1 ]; then
		printStars $1
	fi
fi

exit 0
