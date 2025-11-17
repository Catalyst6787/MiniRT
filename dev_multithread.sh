make bonus
valgrind --tool=helgrind --log-file=./log/helgrind.log ./miniRT_bonus scenes_bonus/cone_debug.rt
# valgrind --tool=drd --log-file=./log/helgrind.log -s ./miniRT_bonus scenes/subject_example.rt
# valgrind --leak-check=full --show-leak-kinds=all --log-file=./log/valgrind.log ./miniRT_bonus scenes/subject_example.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT scenes/several_cylinders.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT scenes/one_sphere.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT scenes/invalid/empty.rt
# valgrind --leak-check=full --log-file=./log/valgrind.log ./miniRT  scenes/invalid/invalid_char.rt