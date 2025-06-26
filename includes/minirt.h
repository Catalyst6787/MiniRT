#ifndef MINIRT_H
# define MINIRT_H

# define _USE_MATH_DEFINES

# include <sys/errno.h>
# include <stdbool.h>
# include <string.h>
# include <time.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <assert.h>

# include "libft.h"
# include "mlx.h"
# include "vec3.h"
# include "material.h"
# include "matrice.h"
# include "ray.h"
# include "sphere.h"
# include "object.h"
# include "scene.h"
# include "errors.h"
# include "render.h"
# include "keycodes.h"
# include "colors.h"
# include "test.h"
# include "debug.h"


# define SPACE_SET = " \t\n"

# define WIN_W 800
# define WIN_H 400
# define VIEWPORT_H 2.0
# define DEBUG_PIXEL_I 10
# define DEBUG_PIXEL_J 10
# define DEBUG 0

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define EPSILON 1.0E-5

# define FILE __FILE__
# define LINE __LINE__

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

int			init_mlx(t_minirt *minirt);
int			init_events(t_minirt *minirt);

/*                                 PARSING                                  */

void		parse_scene(t_minirt *minirt, char *file_path);
void		alloc_elements(t_minirt *minirt, t_scene *scene);

double		ato_buffer(char *ptr, int *cursor, int delim);

int			parse_ambiant_light(t_scene *scene, int *cursor);
int			parse_camera(t_scene *scene, int *cursor);
int			parse_light(t_scene *scene, int *cursor);
int			parse_sphere(t_scene *scene, t_sphere *sphere, int *cursor);
int			parse_plane(t_scene *scene, t_plane *plane, int *cursor);
int			parse_cylinder(t_scene *scene, t_cylinder *cylinder, int *cursor);

void		set_objects_transformation(t_scene *scene);
void		set_objects_material(t_scene *scene);

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


t_light		*new_light(t_vec3 pos, t_vec3 color);
t_ambient	*new_ambiant(t_vec3 color);
void			set_pixel_size(t_camera *camera);
t_camera	*new_camera(t_vec3 from, t_vec3 to, t_vec3 up, double fov);
t_camera	get_camera(int hsize, int vsize, double fov);

void		fill_intersection_table(t_minirt *minirt, t_render *render);

/*                                 RENDER                                  */

t_inter		get_inter(void);
t_light		get_light(t_vec3 pos, double brightness, t_vec3 color);
int			render_scene(t_minirt *minirt);
t_vec3		render_one_pixel_test(t_minirt *minirt, int x, int y);
t_vec3		get_lighting(t_comp comp);
int			free_render(t_render *render);
int			is_debug_pixel(int i, int j);
t_matrix	get_orientation_matrix(t_view view);

/*                             COLOR UTILS                                  */

t_vec3		color_int_multiplication(t_vec3 c0, int n);
t_vec3		color_color_multiplication(t_vec3 c1, t_vec3 c2);
int			color_to_int(t_vec3 color);
t_vec3		int_to_color(int int_color);

/* 								Material Utils						*/

t_material	get_material(void);
t_material	get_default_material(t_vec3 color, t_scene *scene);

/*                                 UTILS                                  */

void		my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color);
void		free_tab(char **arr);
void		free_and_null(void	**ptr);
void		print_err(char *file, int line, char *s);
int			get_max_int(int a, int b);
int			get_min_int(int a, int b);

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
void		print_scene_data(t_minirt *minirt);
void		print_scene_ok_message(void);
void		print_vec3(t_vec3 vec, char *vec_name);
void		print_ray(t_ray r);
void		print_render_data(t_render *render);
void		print_render_pixel(t_vec3	pixel_center,
				t_vec3	ray_direction,
				t_ray	ray,
				t_vec3	color);

/*                                 DOUBLE UTILS                            */

double		double_abs(double d);
int			double_isequal(double a, double b);

///				Transformation
void		set_sphere_transformation(t_sphere *s);
void		set_plane_transformation(t_plane *pl);
void		set_cylinder_tranformation(t_cylinder *cy);

// sort intersections
void	sort_inter(t_inter_list *inter_lst);
t_inter	*get_hit(t_inter_list *lst);
t_vec3	get_sphere_normal_at(const t_sphere *s, const t_vec3 world_point);
t_vec3	get_reflection(t_vec3 in, t_vec3 normal);
int		get_sphere_inter(const t_sphere *sphere,
			const t_ray ray, t_inter_list *list);
int		get_plane_inter(const t_plane *plane,
			const t_ray ray, t_inter_list *list);
t_comp	get_computations(t_scene *scene, t_inter *hit, t_ray r);
t_ray		ray_for_pixel(t_camera camera, double px, double py);

#endif
