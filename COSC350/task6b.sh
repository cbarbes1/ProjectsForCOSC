#!/bin/bash 
# This shell script implements a function to Display a diamond of a particular width onto the console using input verification
echo "Please enter the tail size of the tail"
read tail

echo "Please enter the Base size of the Diamond"
read base

printStars()
{
        local t=$2
	head -c $1 < /dev/zero | tr '\0' '\52' > tailstr 
        local mid=`expr $t / 2`
        let mid++
        local midpoint=$mid
        star="*"
        stars="*"	
        for i in $(seq 1 `expr $t - 1`); 
        do
		if [ $i = t ]; then
			stars="${stars}$tailstr"
		fi
                printf '%*s\n' $t "$stars"
		if [ $i -lt $midpoint ]; then
                        stars="${stars}$star$star"
                else
                        end=${#stars}
                        stars="${stars:0:`expr $end-2`}"       
                fi
        done
        printf '%*s\n' $t "*"
}
                
        
if [ -z $base ]; then
        echo "no input"
        exit 1
elif [ $base -gt 3 ]; then
        x=`expr $base % 2`
        if [ $x = 1 ]; then
                printStars $tail $base
        fi
fi

exit 0

