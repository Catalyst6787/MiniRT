#ifndef MINIRT_H
# define MINIRT_H

// # ifndef __USE_MISC
// #  define __USE_MISC 1
// # endif

# include "libft.h"

# include "mlx.h"
# include "vec3.h"
# include "ray.h"
# include "scene.h"
# include "debug.h"
# include "errors.h"
# include "keycodes.h"
# include "colors.h"


# include <sys/errno.h>
# include <stdbool.h>
# include <string.h>
# include <time.h>

# include <math.h>
# include <fcntl.h>
# include <assert.h>

# define SPACE_SET = " 	\n"

# define WIN_W 800
# define WIN_H 400
// # define FOCAL_LEN 1.0
# define VIEWPORT_H 2.0
# define DEBUG_PIXEL_I 10
# define DEBUG_PIXEL_J 10
# define DEBUG 0

# define M_PI 3.14159265358979323846
# define EPSILON 1.0E-5


typedef struct s_render
{
	double	focal_length;
	double	viewport_height;
	double	viewport_width;
	t_vec3	camera_center;
	t_vec3	camera_dir;
	t_vec3	world_up;
	t_vec3	right;
	t_vec3	up;
	t_vec3	viewport_u;
	t_vec3	viewport_v;
	t_vec3	pixel_delta_u;
	t_vec3	pixel_delta_v;
	t_vec3	viewport_upper_left;
	t_vec3	pixel00_loc;
}	t_render;

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

typedef struct s_minirt
{
	t_mlx_data	*mlx;
	t_scene		*scene;
	t_render	*render;
}	t_minirt;

/*                                 INIT                                  */

int			init_mlx(t_minirt *minirt);
int			init_events(t_minirt *minirt);

/*                                 PARSING                                  */

void		parse_scene(t_minirt *minirt, char *file_path);
void		alloc_elements(t_minirt *minirt, t_scene *scene);

double		ato_buffer(char *ptr, int *cursor, int delim);

int			parse_ambiant_light(t_minirt *minirt, t_scene *scene, int *cursor);
int			parse_camera(t_minirt *minirt, t_scene *scene, int *cursor);
int			parse_light(t_minirt *minirt, t_scene *scene, int *cursor);
int			parse_sphere(t_minirt *minirt, t_scene *scene, t_sphere *sphere, int *cursor);
int			parse_plane(t_minirt *minirt, t_scene *scene, t_plane *plane, int *cursor);
int			parse_cylinder(t_minirt *minirt, t_scene *scene, t_cylinder *cylinder, int *cursor);

void		check_file_name(t_minirt *minirt, char *file_path);
void		check_file_not_empty(t_minirt *minirt);
void		check_data_validity(t_minirt *minirt, t_scene *scene);
void		char_error_check(t_minirt *minirt,
							char c,
							const char *alpha_set,
							const char *sign_set);
void		single_elements_check(t_minirt *minirt, t_scene *scene);
void		count_elements(t_scene *scene);
void		check_characters_validity(t_minirt *minirt);

/*                                 RENDER                                  */

int			render_scene(t_minirt *minirt);
int			render_pixel(int i, int j, t_render *render, t_minirt *minirt, t_sphere *sphere);
int			ray_color(const t_ray *r, t_vec3 *color, int is_debug_pixel, t_sphere *sphere);
int			free_render(t_render *render);
int			init_render(t_minirt *minirt);

int			set_viewport_upper_left(t_minirt *minirt);
int			set_pixel00_loc(t_minirt *minirt);
int			set_pixel_center(t_vec3	*pixel_center,
			int i, int j, t_render	*render);
int			set_ray_direction(t_vec3 *ray_direction,
			t_render *render, t_vec3 *pixel_center);
int			is_debug_pixel(int i, int j);

/*                                 UTILS                                  */

void		my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color);
void		free_tab(char **arr);
void		free_and_null(void	**ptr);
int			get_color_as_int(t_vec3 *color);

/*                                 EVENTS                                  */

int			end_mlx_loop(t_mlx_data *mlx);
int			handle_keypress(int keycode, t_minirt *minirt);
int			handle_mouseclick(int button, int x, int y, t_minirt *minirt);
void		event_print_debug(t_minirt *minirt);
void		print_camera_data(t_minirt *minirt);

/*                                 EXIT                                  */

int			quit(t_minirt *minirt, char *str);

/*                                 DEBUG                                  */

int			debug_print_keycode(int keycode);
void		debug_aff_image(t_minirt *minirt);
void		debug_pixel(const t_ray *r);
void		print_scene_data(t_minirt *minirt);
void		print_scene_ok_message(void);

/*                                 DOUBLE UTILS                                  */

double		double_abs(double d);
int			double_isequal(double a, double b);

/*									TESTS									*/

int			start_all_tests(void);


#endif
