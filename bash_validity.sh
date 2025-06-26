#!/bin/bash

i=1
n=$#

# printf "\n"

while [ $i -le $n ];
do
	printf "TEST $i\n\n\n"
	./miniRT ${!i}
	(( i++ ))
done

printf "Validity test done successfully for $n scenes\n\n"
