/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:01:00 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/06 18:37:11 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "scene.h"
# include "mlx.h"

# include <math.h>
# include <fcntl.h>

# define WIN_W 800
# define WIN_H 400
# define Q 113
# define W 119
# define A 97
# define S 115
# define D 100
# define SPACE 32
# define ESC 65307

typedef struct s_img_data {
	void	*img;
	char	*addr;
}	t_img_data;

typedef struct s_mlx_data {
	void		*mlx;
	void		*mlx_win;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_img_data	*img_st;
}	t_mlx_data;

// INIT
int		init_structure(t_mlx_data *mlx, t_img_data *img);
int		init_events(t_mlx_data *mlx);

// PARSING
int		parse(char *file_path, t_scene *scene);

// UTILS
void	my_mlx_pixel_put(t_mlx_data *mlx, int x, int y, int color);

// EVENTS
int		end_mlx_loop(t_mlx_data *mlx);
int		handle_keypress(int keycode, t_mlx_data *mlx);
int		handle_mouseclick(int button, int x, int y, t_mlx_data *mlx);

// EXIT
int		quit(t_mlx_data *mlx);

// DEBUG
int		debug_print_keycode(int keycode);
void	debug_aff_image(t_mlx_data *mlx);


#endif
