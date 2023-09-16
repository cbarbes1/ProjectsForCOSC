#!/bin/bash
# This shell script implements a function to Display a diamond of a particular width onto the console using input verification

echo "Please enter the Base size of the Diamond"
read base

# function to print the diamond out with the desired width
printStars()
{
	local t=$1
	local mid=`expr $t / 2`
	let mid++
	local midpoint=$mid
	star="*"
	stars="*"

	for i in $(seq 1 `expr $t - 1`); 
	do
		printf '%*s\n' $mid "$stars"	
		if [ $i -lt $midpoint ]; 
		then
			let mid++
			stars="${stars}$star$star"
		else
			end=${#stars}
			stars="${stars:0:`expr $end-2`}"
			let mid--	
		fi
	done
	printf '%*s\n' $midpoint "*"
}
		
	
if [ -z $base ]; then
	echo "no input"
	exit 1
elif [ $base -gt 3 ]; then
	x=`expr $base % 2`
	if [ $x = 1 ]; then
		printStars $base
	fi
fi

exit 0
