#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"

# include "mlx.h"
# include "vec3.h"
# include "ray.h"
# include "scene.h"
# include "errors.h"
# include <sys/errno.h>
# include <stdbool.h>
# include "debug.h"
# include <string.h>



# define BS 4096
# define SPACE_SET = " 	\n"

# define RED "\033[31m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define COLOR_RESET "\033[0m"

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

# define EPSILON 1.0E-5

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


typedef struct s_minirt
{
	t_mlx_data	*mlx;
	t_scene		*scene;
	t_render	*render;
}				t_minirt;


/*                                 INIT                                  */ 

int			init_structure(t_mlx_data *mlx, t_img_data *img);
int			init_events(t_mlx_data *mlx);

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
void		check_data_validity(t_minirt *minirt, t_scene *scene);
void		char_error_check(t_minirt *minirt,
							char c,
							const char *alpha_set,
							const char *sign_set);
void		single_elements_check(t_minirt *minirt, t_scene *scene);
void		count_elements(t_scene *scene);
void		check_characters_validity(t_minirt *minirt);

/*                                 RENDER                                  */ 

int			render_scene(t_minirt *minirt, t_mlx_data *mlx, t_scene *scene);
int			render_pixel(int i, int j, t_render	*render, t_minirt *minirt, t_sphere *sphere);
int			ray_color(const t_ray *r, t_vec3 *color, int is_debug_pixel, t_sphere *sphere);
int			free_render(t_render *render);
int			init_render(t_render *render);


/*                                 UTILS                                  */ 

void		my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color);
void		free_tab(char **arr);
void		free_and_null(void	**ptr);
int			get_color_as_int(t_vec3 *color);

/*                                 EVENTS                                  */ 

int			end_mlx_loop(t_mlx_data *mlx);
int			handle_keypress(int keycode, t_mlx_data *mlx);
int			handle_mouseclick(int button, int x, int y, t_mlx_data *mlx);

/*                                 EXIT                                  */ 

int			quit(t_minirt *minirt, char *str);

/*                                 DEBUG                                  */ 

int			debug_print_keycode(int keycode);
void		debug_aff_image(t_minirt *minirt);
void		debug_pixel(const t_ray *r);
void		print_scene_data(t_minirt *minirt);
void		print_scene_ok_message(void);

/*                                 SPHERE                                  */ 
int			hit_sphere(const t_sphere *sphere, const t_ray *ray);
t_sphere	*sphere_new_alloc(t_vec3 *pos, double diameter, t_vec3 *color);
void		free_sphere(t_sphere *sphere);


/*                                 RENDER UTILS                                  */

int			set_viewport_upper_left(t_render *render);
int			set_pixel00_loc(t_render *render);
int			set_pixel_center(t_vec3	*pixel_center,
			int i, int j, t_render	*render);
int			set_ray_direction(t_vec3 *ray_direction,
			t_render *render, t_vec3 *pixel_center);
int			is_debug_pixel(int i, int j);

/*                                 DOUBLE UTILS                                  */ 

double		double_abs(double d);
int			double_isequal(double a, double b);


#endif
