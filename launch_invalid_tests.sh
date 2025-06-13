#!/bin/bash

make re
make clean
./tests_alex/bash_validity.sh assets/scenes/invalid/*
