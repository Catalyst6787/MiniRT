#!/bin/bash

scene=$1

RED='\033[0;31m'
RESET='\033[0m'

make fclean
make
printf "\n\n"

if [ $# == 0 ]; then
	# printf "${RED}Warning : no scene loaded (usage ./dev.sh <map_number>)\n${RESET}"
	printf "${RED}usage ./dev.sh <map_number>\n${RESET}"
	# ./miniRT assets/scenes/subject_example.rt
	exit 1
fi


if [ $scene == 1 ]; then
	./miniRT assets/scenes/subject_example.rt
elif [ $scene == 2 ]; then
	./miniRT assets/scenes/subject_disorder.rt
elif [ $scene == 3 ]; then
	./miniRT assets/scenes/one_sphere.rt
elif [ $scene == 4 ]; then
	./miniRT assets/scenes/several_cylinders.rt
elif [ $scene == 5 ]; then
	echo scene slot 5 is empty
elif [ $scene == 6 ]; then
	echo scene slot 6 is empty
elif [ $scene == 7 ]; then
	echo scene slot 7 is empty
elif [ $scene == 8 ]; then
	echo scene slot 8 is empty
fi

