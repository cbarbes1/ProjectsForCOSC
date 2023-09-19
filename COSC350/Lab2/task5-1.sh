#!/bin/sh

touch numbs

for i in $(seq 1 100);
do
	echo $i\\n>>numbs
done

exit 0
