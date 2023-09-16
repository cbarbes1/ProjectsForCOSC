#!/bin/bash 
# This shell script implements a function to Display a right pointing array of a particular width onto the console using input verification

printStars()
{
        local t=$2
	local tailstr="*"
	star="*"

	for i in $(seq 1 `expr $1 - 1`); 
	do 
		tailstr="${tailstr}$star" 
	done

        local mid=`expr $t / 2`
        let mid++
        local midpoint=$mid
        stars="*"	
        for i in $(seq 1 `expr $t - 1`); 
        do
		if [ $i = $midpoint ]; then
			printf '%*s\n' `expr $1 + ${#stars}` "$stars$tailstr"
		else
			printf '%*s\n' `expr $1 + ${#stars}` "$stars"
		fi
		if [ $i -lt $midpoint ]; then
                        stars="${stars}$star$star"
                else
                        end=${#stars}
                        stars="${stars:0:`expr $end-2`}"       
                fi
        done
	printf '%*s\n' `expr $1 + ${#stars}` "*"
}
                
        
if [ -z $2 ]; then
        echo "no input"
        exit 1
elif [ $2 -gt 3 ]; then
        x=`expr $2 % 2`
        if [ $x = 1 ]; then
                printStars $1 $2
        fi
fi

exit 0

