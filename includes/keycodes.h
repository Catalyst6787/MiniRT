/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:56:46 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:56:46 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H



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

#  define L_BRACKET 91
#  define R_BRACKET 93

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

# define COMMAND_HELP_1 "ASWDER : Cam position"
# define COMMAND_HELP_2 "Arrows : Cam direction"
# define COMMAND_HELP_3 "SPACE : Render"
# define COMMAND_HELP_4 "Pav Num arrows : change object value"
# define COMMAND_HELP_5 "Pav Num 5 : change object mode (dir / pos / color / brightness)"
# define COMMAND_HELP_6 "Pav Num +- : change selected"
# define COMMAND_HELP_7 "C : print scene data"
# define COMMAND_HELP_8 "B : display commmand help"
# define COMMAND_HELP_9 "N : change onscreen string color"
# define COMMAND_HELP_10 "V : cylinder cap on / off"
# define COMMAND_HELP_11 "P : fun wth sphere shearing"
# define COMMAND_HELP_12 "L : fun wth cylinder rotation"

#endif
