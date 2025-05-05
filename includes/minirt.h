/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:01:00 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/05 16:50:55 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"

# define WIN_W 1920
# define WIN_H 1080
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

void	my_mlx_pixel_put(t_mlx_data *mlx, int x, int y, int color);
int		end_mlx_loop(t_mlx_data *mlx);
int		quit(t_mlx_data *mlx);
int		debug_print_keycode(int keycode);
int		handle_keypress(int keycode, t_mlx_data *mlx);



#endif
