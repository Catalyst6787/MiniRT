#ifndef MINIRT_H
# define MINIRT_H

# define _USE_MATH_DEFINES

# include <sys/errno.h>
# include <stdbool.h>
# include <string.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <assert.h>
# include <unistd.h>
# include <dirent.h>
#include <sys/time.h>

# include "libft.h"
# include "mlx.h"
# include "vec3.h"
# include "material.h"
# include "matrice.h"
# include "ray.h"
# include "sphere.h"
# include "plane.h"
# include "cylinder.h"
# include "cone.h"
# include "object.h"
# include "scene.h"
# include "errors.h"
# include "render.h"
# include "keycodes.h"
# include "colors.h"
# include "debug.h"
# include "pthread.h"

# define SPACE_SET " \t\n"

// # define WIN_W 3840
// # define WIN_H 2160
# define WIN_W 1920
# define WIN_H 1080
// # define WIN_W 1280
// # define WIN_H 720

# define VIEWPORT_H 2.0
# define DEBUG_PIXEL_I 10
# define DEBUG_PIXEL_J 10
# define DEBUG 0

# define PIXEL_SIZE_MULT 10 // size of pixels, 1 is normal
# define NB_THREADS 16
# define MULTI_THREADING 1
# define GENERATE_SCENE 0

# define REFLECTION_MAX_DEPTH 10
# ifndef M_PI
#  define M_PI 3.14159265358979323846
#  define M_PI_2 1.57079632679489661923
# endif
# define EPSILON 1.0E-5

# define LINE __LINE__

typedef struct s_img_data
{
	void	*img;
	char	*addr;
}	t_img_data;

typedef enum e_move_mode
{
	pos,
	dir,
	size,
	red,
	green,
	blue
}				t_move_mode;

typedef struct s_parsing_helper
{
	int			l;
	int			s;
	int			p;
	int			cy;
	int			co;
}				t_parsing_helper;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*mlx_win;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_img_data	*img_st;
}	t_mlx_data;

typedef struct s_ui
{
	int			color_id;
	t_vec3		string_color;
	t_move_mode	move_mode;
	int			selected_object;
	char		*str_selected_object;
	char		*str_mode;
	bool		command_help;
}				t_ui;

typedef struct s_minirt
{
	t_mlx_data	*mlx;
	t_scene		*scene;
	t_render	*render;
	t_ui		*ui;
}				t_minirt;

////	Bonuses		////

typedef struct s_rand {
	int		nb_lights;
	int		nb_obj;
	double	lights_ratio[4];
	bool	is_plane;
}				t_rand;


typedef struct s_thread_data
{
	int				id;
	pthread_t		thread;
	t_minirt		*minirt;
	t_inter_list inter_list;
	t_inter_list shadow_list;
}				t_thread_data;

/*                                 INIT                                  */

int			init_mlx(t_minirt *minirt);
int			init_events(t_minirt *minirt);

/*                                 PARSING                                  */

void		parse_scene(t_minirt *minirt);
void		alloc_elements(t_minirt *minirt, t_scene *scene);

int			get_file_contents(int fd, char **file_contents);
void		set_scene_buffer(t_minirt *minirt);
double		ato_buffer(char *ptr, int *cursor, int delim);

void		parse_scene_elements(t_minirt *minirt, t_scene *scene);
int			parse_ambiant_light(t_minirt *minirt, t_scene *scene, int *cursor);
int			parse_camera(t_minirt *minirt, t_scene *scene, int *cursor);
int			parse_light(t_minirt *minirt,
				t_scene *scene,
				t_light *light,
				int *cursor);
int			parse_sphere(t_minirt *minirt,
				t_scene *scene, t_sphere *sphere, int *cursor);
int			parse_plane(t_minirt *minirt,
				t_scene *scene, t_plane *plane, int *cursor);
int			parse_cylinder(t_minirt *minirt,
				t_scene *scene, t_cylinder *cylinder, int *cursor);
int			parse_cone(t_minirt *minirt,
				t_scene *scene, t_cone *cone, int *cursor);

void		set_objects_transformation(t_scene *scene);
void		set_objects_material(t_scene *scene);

int			count_comas(char *buffer, int i);
int			count_spaces_in_line(char *buffer, int i);
void		check_file_name(t_minirt *minirt);
void		check_file_not_empty(t_minirt *minirt);
void		check_data_validity(t_minirt *minirt, t_scene *scene);
void		char_error_check(t_minirt *minirt,
				char c,
				const char *alpha_set,
				const char *sign_set);
void		single_elements_check(t_minirt *minirt, t_scene *scene);
void		count_elements(t_scene *scene);
void		check_characters_validity(t_minirt *minirt);
void		check_direction_vector(t_minirt *minirt, t_vec3 *dir);
t_light		*new_light(t_vec3 pos, t_vec3 color);
t_ambient	*new_ambiant(t_vec3 color);
void		set_pixel_size(t_camera *camera);

t_camera	*new_camera(t_vec3 from, t_vec3 to, t_vec3 up, double fov);
t_camera	get_camera(int hsize, int vsize, double fov);
void		set_camera_transformation(t_scene *scene);

void		objects_alloc(t_minirt *minirt, t_scene *scene);
t_matrix	get_object_transformation(t_object *obj);
void		create_object_array(t_scene *scene);
void		create_object_from_sphere(t_object *object,
				t_sphere *sphere, int id);
void		create_object_from_plane(t_object *object, t_plane *plane, int id);
void		create_object_from_cylinder(t_object *object,
				t_cylinder *cylinder, int id);
void		create_object_from_cone(t_object *object,
				t_cone *cone, int id);

	
void		fill_intersection_table(t_minirt *minirt, t_render *render);

/*                                 RENDER                                  */

int			render_scene(t_minirt *minirt);
// t_vec3		render_one_pixel_test(t_minirt *minirt, int x, int y);
t_vec3		get_lighting(t_comp *comp, bool in_shadow, t_minirt *minirt, unsigned int depth);
int			start_render(t_minirt *minirt);
void		display_image(t_minirt *minirt);
int			count_intersections(t_scene *scene);
t_inter		get_inter(void);
int			get_cylinder_inter(const t_object *object,
				const t_ray *ray,
				t_inter_list *list);
int			get_cone_inter(const t_object *object,
				const t_ray *ray,
				t_inter_list *list);
t_light		get_light(t_vec3 pos, double brightness, t_vec3 color);
int			free_render(t_render *render);
int			is_debug_pixel(int i, int j);
t_matrix	get_orientation_matrix(t_view view);
t_vec3		shade_hit(t_comp *comp, t_minirt *minirt, unsigned int depth);
void		swap_inters(t_inter *a, t_inter *b);
t_vec3		get_cylinder_normal_at(const t_object *cy,
				const t_vec3 world_point);
t_inter		*get_hit(t_inter_list *lst);
t_vec3		intersect_objects(t_minirt *minirt, t_ray *unique_ray, unsigned int depth);
void		print_borders(t_mlx_data *mlx, int color);
void		display_command_help(t_minirt *minirt, t_mlx_data *mlx);

int			start_threads(t_minirt *minirt);
void		*th_render_scene(void *minirt_arg);
// t_vec3		th_shade_hit(t_minirt *minirt,
// 				t_comp *comp,
// 				t_inter_list *shadow_list,
// 				unsigned int depth);
t_vec3		th_get_lighting(t_comp *comp, bool in_shadow, t_minirt *minirt, t_thread_data *th, unsigned int depth);
t_vec3		th_reflected_color(t_comp *comp, t_minirt *minirt, t_thread_data *th, unsigned int depth);
void		th_display_image(t_minirt *minirt);
t_vec3		th_intersect_objects(t_minirt *minirt, t_ray *unique_ray, t_thread_data *th, unsigned int depth);
int			th_is_shadowed(t_scene *scene, t_comp *comp, t_inter_list *shadow_list);

/*                             COLOR UTILS                                  */

t_vec3		color_int_multiplication(t_vec3 c0, int n);
t_vec3		color_color_multiplication(t_vec3 c1, t_vec3 c2);
int			color_to_int(t_vec3 color);
t_vec3		int_to_color(int int_color);

/*                                SHAPES                                */

t_sphere	*new_sphere(t_vec3 pos, double diameter, t_vec3 color);
t_plane		*new_plane(t_vec3 pos, t_vec3 dir, t_vec3 color);
t_cylinder	*new_cylinder(t_vec3 pos, 
				t_vec3 dir,
				double diameter,
				double height,
				t_vec3 color);
void		free_sphere(t_object *object);

int			get_cylinder_inter(const t_object *object,
				const t_ray *ray, t_inter_list *list);

/*                             Material Utils                               */

t_material	get_material(void);
t_material	get_default_material(t_vec3 color, t_scene *scene);

/*                                 UTILS                                  */

void		my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color);
void		free_tab(char **arr);
void		free_and_null(void	**ptr);
void		print_err(char *file, int line, char *s);
int			get_max_int(int a, int b);
int			get_min_int(int a, int b);
void		swap_doubles(double *a, double *b);
char		*object_type_to_str(t_object *object);
t_vec3		convert_dir_to_euler(t_vec3 dir);

/*                                 EVENTS                                  */

int			end_mlx_loop(t_mlx_data *mlx);
void		event_render(t_minirt *minirt);
void		event_display_command_help(t_minirt *minirt);
void		event_change_string_color(t_minirt *minirt);
int			handle_keypress(int keycode, t_minirt *minirt);
int			handle_mouseclick(int button, int x, int y, t_minirt *minirt);
void		event_print_debug(t_minirt *minirt);
void		print_camera_data(t_minirt *minirt);
void		event_turn_cylinders(t_minirt *minirt);
void		event_sphere_shearing(t_minirt *minirt);
void		event_light_pos(t_minirt *minirt, int keycode);
void		event_reflections(t_minirt *minirt, int keycode);
void		arrows_handle(int keycode, t_minirt *minirt);
int			asdw_handle(int keycode, t_minirt *minirt);
void		erzx_handle(int keycode, t_minirt *minirt);

void		event_object_selection(t_minirt *minirt,
				t_scene *scene, int keycode);
int			set_selected_object_str(t_minirt *minirt, t_scene *scene);
void		event_object_position(t_minirt *minirt, int keycode);
void		event_activate_cylinder_cap(t_minirt *minirt);

/*                              GENERATOR                                */

void		generate_random_scene();
void		gen_print_lights(FILE *file, t_rand *rand);
void		gen_print_sphere(FILE *file);
void		gen_print_plane(FILE *file, t_rand *rand, bool chaos);
void		gen_print_cylinder_cones(FILE *file, char c);
int			generate_random_int(int min, int max);
double		generate_random_double(double min, double max);

void		save_random_scene(t_minirt *minirt);

/*                                 EXIT                                  */

void		free_scene(t_scene *scene);
void		print_exit_info(char *str);
int			quit(t_minirt *minirt, char *str);

/*                                 DEBUG                                  */

int			debug_print_keycode(int keycode);
void		debug_aff_image(t_minirt *minirt);
void		debug_print_scene_data(t_minirt *minirt);
void		debug_print_ray(t_ray *r);
void		debug_print_objects_pointers(t_scene *scene);
void		debug_print_inter_list(t_inter_list *list);
void		debug_print_vec(t_vec3 *v, char *name);
void		debug_print_matrice(t_matrix m, char *matrix_type);

void		print_inter(t_inter *inter);
void		print_scene(t_minirt *minirt, bool asterix);
void		print_scene_ok_message(char *scene);
void		print_vec3(t_vec3 vec, char *vec_name);
void		print_ray(t_ray *r);
void		print_plane_data(t_minirt *minirt);
void		print_spheres_data(t_minirt *minirt);
void		print_cylinder_data(t_minirt *minirt);
void		event_print_debug(t_minirt *minirt);
void		print_render_data(t_render *render);
void		print_render_pixel(t_vec3	pixel_center,
				t_vec3	ray_direction,
				t_ray	ray,
				t_vec3	color);
void		print_inter_list(t_inter_list *list);

/*                                 DOUBLE UTILS                            */

double		double_abs(double d);
int			double_isequal(double a, double b);

/*                                TRANSFORMATIONS                          */

void		set_sphere_transformation(t_sphere *s);
void		set_plane_transformation(t_plane *pl);
void		set_cylinder_tranformation(t_cylinder *cy);
void		set_cone_tranformation(t_cone *co);

// sort intersections

void		sort_inter(t_inter_list *inter_lst);
t_inter		*get_hit(t_inter_list *lst);
t_ray		get_origin_direction(t_camera camera, t_vec3 pixel);
void		put_pixel(t_minirt *minirt, int color, int x, int y);
t_ray		ray_for_pixel(t_camera camera, double px, double py);
void		load_special_scene(int number, t_minirt *minirt);

// reflections

t_vec3		reflected_color(t_comp *comp, t_minirt *minirt, unsigned int depth);
t_vec3		get_reflection(t_vec3 in, t_vec3 normal);

//// TESTS

int			start_all_tests(void);
int			test_tuple_point(void);
int			test_tuple_vector(void);
int			test_adding_tuples(void);
int			test_subtraction_tuples(void);
int			test_scalar_multiplication(void);
int			test_scalar_division(void);
int			test_vec_normalize(void);

t_matrix	get_arb_matrix(int row, int col,
				double a0, double a1, double a2, double a3,
				double b0, double b1, double b2, double b3,
				double c0, double c1, double c2, double c3,
				double d0, double d1, double d2, double d3);

void		test_color_mult(t_vec3 *color, int i, int j);
int			start_all_matrix_tests(void);
int			start_all_ray_tests(void);
int			start_all_intersection_tests(void);
int			start_all_normals_tests(void);
int			start_all_reflection_tests(void);
int			start_all_lighting_tests(void);
int			start_all_world_tests(void);
int			start_all_shadows_tests(void);
int			start_all_camera_tests(void);
int			start_all_planes_tests(void);
int			start_all_cylinders_tests(void);
int			start_all_cones_tests(void);
int			start_all_cubes_tests(void);
void		set_default_world(t_scene *scene);


/// COLORS

t_vec3	color_int_multiplication(t_vec3 c0, int n);
t_vec3	color_color_multiplication(t_vec3 c1, t_vec3 c2);
int		color_to_int(t_vec3 color);
t_vec3	int_to_color(int int_color);


#endif