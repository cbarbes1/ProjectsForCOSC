#!/bin/bash
# This shell script find a word in a requested file in the desired directory
#

# Ask the user for the directory
echo "Please enter the directory in which to find the file"
read nm_dir

# if the directory does not exit terminate with error message
if [ ! -d $nm_dir ]; then
	echo "Directory does not exist"
	exit 1
fi

# Ask the user for the name of the file
echo "Please enter the name of the file"
read fl_name

count=0 # set the count to 0
while [ $count -lt 2 -a ! -e $fl_name -a ! -r $fl_name ]; do # run the loop while less than 3 tries and not exist or readable
	echo "Try Again: "
	read fl_name
	let "count++"
done

if [ $count -gt 1 ]; then # if the count is greater than 1 than error occured
        # which error occured ?	
	if [ ! -e $fl_name ]; then 
		echo "File does not exist"
		exit 2
	elif [ ! -r $fl_name ]; then
        	echo "File is not readable"	
		exit 3
	fi
fi

# ask the user for the word
echo "Please enter the word to find in the file"
read word

# if the grep finds the word then print found
if grep -q $word $fl_name; then
	echo "$word" "FOUND!"
else 
	echo "$word" "NOT FOUND!"
	exit 4
fi

exit 0
