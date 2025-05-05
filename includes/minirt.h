/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:01:00 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/05 15:55:50 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"

# define WIN_W 1920
# define WIN_H 1080

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
int		end_mlx_loop(int keycode, t_mlx_data *mlx);
int		quit(t_mlx_data *mlx);

#endif
