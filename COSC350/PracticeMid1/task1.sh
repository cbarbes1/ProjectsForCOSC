#!/bin/bash

for file in *; 
do 
	case $file in 
		*.c ) gcc -o "Hello1" $file;;
		*.cpp ) g++ -o "Hello2" $file;;
		*.txt ) cat $file;;
		* ) echo "file is not c or c++ or test file";;
	esac
done
exit 0
