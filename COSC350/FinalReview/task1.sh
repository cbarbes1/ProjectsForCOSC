#!/bin/bash

# make sure that the script is given atleast the checker parameter
if [ $# -lt 1 ];
then
	exit 1;
fi

# if the user requests the print all sub directories script 
if [ $1 -eq 1 ];
then
	for i in *
	do
		if [ -d $i ];
		then
			ls $i
		fi
	done
	ls
# this segment implements funtion 2 of the script
elif [ $1 -eq 2 ];
then
	if [ $# -lt 2 ];
	then 
		exit 1;
	fi
	
	width=$2
	mid=`expr $width/2`
	let mid++
	temp=1
	for i in $(seq 1 $mid)
	do
		printf "%*s" $mid
		for j in $(seq 1 $temp)
		do
			printf "*"
		done
		echo
		temp=`expr $temp + 2`
		let mid--
	done
# this segment implement function 3 of the script which finds all reference to the word main in all files in the directory
elif [ $1 -eq 3 ];
then
	for file in *
	do
		if grep -q main $file
		then
			echo $file
		fi
	done
	grep "Smith" "Student.txt" | sort -k 4,4 > Smith.txt
# this segment sums all arguments if there is no script type given and the number of argument is greater than 1
else
	if [ $# -lt 1 ];
	then
		exit 1
	fi
	sum=0
	for i in $@;
	do
		sum=`expr $sum + $i`
	done
	echo $sum
fi


exit 0
