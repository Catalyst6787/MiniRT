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


#  define A 97
#  define C 99
#  define D 100
#  define E 101
#  define O 111
#  define Q 113
#  define R 114
#  define S 115
#  define W 119
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
#endif
