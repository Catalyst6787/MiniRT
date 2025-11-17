make bonus
valgrind --leak-check=full --show-leak-kinds=all --log-file=./log/valgrind.log ./miniRT scenes/subject_example.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT scenes/several_cylinders.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT scenes/one_sphere.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT scenes/invalid/empty.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT  scenes/invalid/invalid_char.rt