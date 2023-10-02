#!/bin/sh

rm numbs

for i in $(seq 1 100);
do
	echo $i >> numbs
done

exit 0
