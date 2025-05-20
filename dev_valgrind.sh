make fclean
make re
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT assets/scenes/subject_example.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT assets/scenes/several_cylinders.rt
valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT assets/scenes/one_sphere.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT  assets/scenes/invalid/invalid_char.rt