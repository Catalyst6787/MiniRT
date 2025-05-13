/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:01:00 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/13 11:27:43 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"

# include "vec3.h"
# include "ray.h"
# include "sphere.h"
# include "scene.h"
# include "mlx.h"



# include <time.h>
# include <math.h>
# include <fcntl.h>

// DEBUG
# include <assert.h>

# define WIN_W 800
# define WIN_H 400
# define FOCAL_LEN 1.0
# define VIEWPORT_H 2.0
# define DEBUG_PIXEL_I 10
# define DEBUG_PIXEL_J 10
# define DEBUG 0

# define Q 113
# define W 119
# define A 97
# define S 115
# define D 100
# define SPACE 32
# define ESC 65307

typedef struct s_img_data
{
	void	*img;
	char	*addr;
}	t_img_data;

typedef struct s_mlx_data
{
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

// PARSING TYPES
int		parse_ambiant(char *line, t_scene *scene);
int		parse_camera(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);
int		parse_sphere(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);

// UTILS
void	my_mlx_pixel_put(t_mlx_data *mlx, int x, int y, int color);
void	free_tab(char **arr);
void	free_and_null(void	**ptr);
int		get_color_as_int(t_vec3 *color);

//FILE UTILS
int		check_file(char *file_path, int *fd);
int		get_file_contents(int fd, char **file_contents);

// EVENTS
int		end_mlx_loop(t_mlx_data *mlx);
int		handle_keypress(int keycode, t_mlx_data *mlx);
int		handle_mouseclick(int button, int x, int y, t_mlx_data *mlx);

// EXIT
int		quit(t_mlx_data *mlx);

// DEBUG
int		debug_print_keycode(int keycode);
void	debug_aff_image(t_mlx_data *mlx);

// RENDER
int		render_scene(t_mlx_data *mlx, t_scene *scene);
int		render_pixel(int i, int j, t_render	*render, t_mlx_data *mlx, t_sphere *sphere);
int		ray_color(const t_ray *r, t_vec3 *color, int is_debug_pixel, t_sphere *sphere);
int		free_render(t_render *render);
int		init_render(t_render *render);

// RENDER UTILS
int		set_viewport_upper_left(t_render *render);
int		set_pixel00_loc(t_render *render);
int		set_pixel_center(t_vec3	*pixel_center,
			int i, int j, t_render	*render);
int		set_ray_direction(t_vec3 *ray_direction,
			t_render *render, t_vec3 *pixel_center);
int		is_debug_pixel(int i, int j);


#endif
