#!/bin/bash

scene=$1

RED='\033[0;31m'
BLUE='\033[0;34m'
RESET='\033[0m'

make
printf "\n"

if [ $# == 0 ]; then
	printf "${RED}usage ./dev.sh <map_number>\n\n${RESET}"
	printf "${BLUE}1 : subject_example.rt\n${RESET}"
	printf "${BLUE}2 : subject_disorder.rt.rt\n${RESET}"
	printf "${BLUE}3 : one_sphere.rt.rt\n${RESET}"
	printf "${BLUE}4 : several_cylinders.rt\n${RESET}"
	printf "${BLUE}5 : scene_3spheres.rt\n${RESET}"
	printf "${BLUE}6 : ten_spheres.rt\n${RESET}"
	printf "${BLUE}7 : shadows.rt\n${RESET}"
	printf "${BLUE}8 : shadows_2.rt\n${RESET}"
	printf "${BLUE}9 : plane_debug.rt\n${RESET}"
	printf "${BLUE}10 : plane_inter_shadow.rt\n${RESET}"

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
	./miniRT assets/scenes/scene_3spheres.rt
elif [ $scene == 6 ]; then
	./miniRT assets/scenes/ten_spheres.rt
elif [ $scene == 7 ]; then
	./miniRT assets/scenes/shadows.rt
elif [ $scene == 8 ]; then
	./miniRT assets/scenes/shadows_2.rt
elif [ $scene == 9 ]; then
	./miniRT assets/scenes/plane_debug.rt
elif [ $scene == 10 ]; then
	./miniRT assets/scenes/plane_inter_shadow.rt
elif [ $scene == 11 ]; then
	./miniRT assets/scenes/cylinder_debug.rt
fi

