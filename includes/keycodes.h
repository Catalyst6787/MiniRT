#ifndef KEYCODE_H
# define KEYCODE_H

# ifdef __linux__
#  define SPACE 32
#  define ESC 65307

#  define UP 65362
#  define DOWN 65364
#  define LEFT 65361
#  define RIGHT 65363

#  define PLUS 61
#  define MINUS 45

#  define PAV_UP 65431
#  define PAV_DOWN 65433
#  define PAV_LEFT 65430
#  define PAV_RIGHT 65432

#  define PAV_FRONT 65434
#  define PAV_BACK 65435

#  define PAV_PLUS 65451
#  define PAV_MINUS 65453
#  define PAV_MIDDLE 65437


#  define A 97
#  define B 98
#  define C 99
#  define D 100
#  define E 101
#  define F 102
#  define G 103
#  define H 104
#  define I 105
#  define J 106
#  define K 107
#  define L 108
#  define N 110
#  define O 111
#  define P 112
#  define Q 113
#  define R 114
#  define S 115
#  define U 117
#  define V 118
#  define W 119
#  define X 120
#  define Z 122
# endif

# ifdef __APPLE__

#  define SPACE 49
#  define ESC 53

#  define UP 126
#  define DOWN 125
#  define LEFT 123
#  define RIGHT 124

#  define PLUS 24
#  define MINUS 27

#  define PAV_UP 65431
#  define PAV_DOWN 65433
#  define PAV_LEFT 65430
#  define PAV_RIGHT 65432

#  define PAV_FRONT 65434
#  define PAV_BACK 65435

#  define PAV_PLUS 65451
#  define PAV_MINUS 65453
#  define PAV_MIDDLE 65437



#  define A 0
#  define C 99
#  define D 2
#  define E 14
#  define H 4
#  define I 34
#  define J 38
#  define K 40
#  define L 37
#  define O 31
#  define P 35
#  define Q 113
#  define R 15
#  define S 1
#  define U 32
#  define W 13
#  define X 7
#  define Z 6

# endif

# define COMMAND_HELP_1 "ASWDER : Cam position"
# define COMMAND_HELP_2 "Arrows : Cam direction"
# define COMMAND_HELP_3 "HJUKOP : Light"
# define COMMAND_HELP_4 "SPACE : Render"
# define COMMAND_HELP_5 "Pav Num arrows : change object position / direction"
# define COMMAND_HELP_6 "Pav Num 5 : change object move mode (dir / pos)"
# define COMMAND_HELP_7 "Pav Num +- : change object to move"
# define COMMAND_HELP_8 "C : print scene data"
# define COMMAND_HELP_9 "B : display commmand help"
# define COMMAND_HELP_10 "N : change onscreen string color"
# define COMMAND_HELP_11 "V : cylinder cap on / off"
# define COMMAND_HELP_12 "P : fun wth sphere shearing"
# define COMMAND_HELP_13 "L : fun wth cylinder rotation"




#endif
