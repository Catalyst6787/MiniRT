make fclean
make re
valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT assets/scenes/subject_example.rt