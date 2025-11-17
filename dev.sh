#!/bin/bash

scene=$1

RED='\033[0;31m'
BLUE='\033[0;34m'
RESET='\033[0m'

make bonus
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
	printf "${BLUE}11 : cylinder_debug.rt\n${RESET}"
	printf "${BLUE}12 : cylinder_debug_2.rt\n${RESET}"
	printf "${BLUE}13 : cylinder_debug_3.rt\n${RESET}"
	printf "${BLUE}14 : cylinder_turn_animation.rt\n${RESET}"
	printf "${BLUE}15 : sphere_animation.rt\n${RESET}"
	printf "${BLUE}16 : plane_debug_2.rt\n${RESET}"
	printf "${BLUE}17 : cone_debug.rt\n${RESET}"
	printf "${BLUE}18 : several_planes.rt\n${RESET}"
	printf "${BLUE}19 : snooker.rt\n${RESET}"
	exit 1
fi


if [ $scene == 1 ]; then
	./miniRT scenes_bonus/subject_example.rt
elif [ $scene == 2 ]; then
	./miniRT scenes_bonus/subject_disorder.rt
elif [ $scene == 3 ]; then
	./miniRT scenes_bonus/one_sphere.rt
elif [ $scene == 4 ]; then
	./miniRT scenes_bonus/several_cylinders.rt
elif [ $scene == 5 ]; then
	./miniRT scenes_bonus/scene_3spheres.rt
elif [ $scene == 6 ]; then
	./miniRT scenes_bonus/ten_spheres.rt
elif [ $scene == 7 ]; then
	./miniRT scenes_bonus/shadows.rt
elif [ $scene == 8 ]; then
	./miniRT scenes_bonus/shadows_2.rt
elif [ $scene == 9 ]; then
	./miniRT scenes_bonus/plane_debug.rt
elif [ $scene == 10 ]; then
	./miniRT scenes_bonus/plane_inter_shadow.rt
elif [ $scene == 11 ]; then
	./miniRT scenes_bonus/cylinder_debug.rt
elif [ $scene == 12 ]; then
	./miniRT scenes_bonus/cylinder_debug_2.rt
elif [ $scene == 13 ]; then
	./miniRT scenes_bonus/cylinder_debug_3.rt
elif [ $scene == 14 ]; then
	./miniRT scenes_bonus/cylinder_turn_animation.rt
elif [ $scene == 15 ]; then
	./miniRT scenes_bonus/sphere_animation.rt
elif [ $scene == 16 ]; then
	./miniRT scenes_bonus/plane_debug_2.rt
elif [ $scene == 17 ]; then
	./miniRT scenes_bonus/cone_debug.rt
elif [ $scene == 18 ]; then
	./miniRT scenes_bonus/several_planes.rt
elif [ $scene == 19 ]; then
	./miniRT scenes_bonus/snooker.rt
fi

