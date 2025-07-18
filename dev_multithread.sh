make bonus
valgrind --tool=helgrind --log-file=./log/helgrind.log ./miniRT_bonus assets/scenes/subject_example.rt
# valgrind --tool=drd --log-file=./log/helgrind.log ./miniRT_bonus assets/scenes/subject_example.rt
# valgrind --leak-check=full --show-leak-kinds=all --log-file=./log/valgrind.log ./miniRT_bonus assets/scenes/subject_example.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT assets/scenes/several_cylinders.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT assets/scenes/one_sphere.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT assets/scenes/invalid/empty.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT  assets/scenes/invalid/invalid_char.rt