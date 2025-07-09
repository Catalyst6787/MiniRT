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
# include "plane.h"
# include "cylinder.h"
# include "object.h"
# include "scene.h"
# include "errors.h"
# include "render.h"
# include "keycodes.h"
# include "colors.h"
# include "test.h"
# include "debug.h"


# define SPACE_SET = " \t\n"

# define WIN_W 1280
# define WIN_H 720
# define VIEWPORT_H 2.0
# define DEBUG_PIXEL_I 10
# define DEBUG_PIXEL_J 10
# define DEBUG 0

# define PIXEL_SIZE_MULT 10 // size of pixels, 1 is normal

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

typedef enum e_move_mode
{
	dir,
	pos,
	height
}				t_move_mode;


typedef struct s_mlx_data
{
	void		*mlx;
	void		*mlx_win;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_img_data	*img_st;
	t_move_mode	move_mode;
	int			selected_object;
	char		*str_selected_object;
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

void		parse_scene(t_minirt *minirt);
void		alloc_elements(t_minirt *minirt, t_scene *scene);

double		ato_buffer(char *ptr, int *cursor, int delim);

int			parse_ambiant_light(t_minirt *minirt, t_scene *scene, int *cursor);
int			parse_camera(t_minirt *minirt, t_scene *scene, int *cursor);
int			parse_light(t_minirt *minirt, t_scene *scene, int *cursor);
int			parse_sphere(t_minirt *minirt, t_scene *scene, t_sphere *sphere, int *cursor);
int			parse_plane(t_minirt *minirt, t_scene *scene, t_plane *plane, int *cursor);
int			parse_cylinder(t_minirt *minirt, t_scene *scene, t_cylinder *cylinder, int *cursor);

void		set_objects_transformation(t_scene *scene);
void		set_objects_material(t_scene *scene);

int			count_comas(char *buffer, int i);
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


t_light		*new_light(t_vec3 pos, t_vec3 color);
t_ambient	*new_ambiant(t_vec3 color);
void			set_pixel_size(t_camera *camera);
t_camera	*new_camera(t_vec3 from, t_vec3 to, t_vec3 up, double fov);
t_camera	get_camera(int hsize, int vsize, double fov);

void		create_object_list(t_scene *scene);
void		create_object_from_sphere(t_object *object, t_sphere *sphere, int id);
void		create_object_from_plane(t_object *object, t_plane *plane, int id);
void		create_object_from_cylinder(t_object *object, t_cylinder *cylinder, int id);


void		fill_intersection_table(t_minirt *minirt, t_render *render);

/*                                 RENDER                                  */

t_inter		get_inter(void);
t_light		get_light(t_vec3 pos, double brightness, t_vec3 color);
int			render_scene(t_minirt *minirt);
t_vec3		render_one_pixel_test(t_minirt *minirt, int x, int y);
// t_vec3		get_lighting(t_comp comp, bool in_shadow);
t_vec3		get_lighting(t_comp *comp, bool in_shadow);
int			free_render(t_render *render);
int			is_debug_pixel(int i, int j);
t_matrix	get_orientation_matrix(t_view view);
t_vec3		shade_hit(t_render *render, t_scene *scene, t_comp *comp);
void		swap_inters(t_inter *a, t_inter *b);

/*                             COLOR UTILS                                  */

t_vec3		color_int_multiplication(t_vec3 c0, int n);
t_vec3		color_color_multiplication(t_vec3 c1, t_vec3 c2);
int			color_to_int(t_vec3 color);
t_vec3		int_to_color(int int_color);

/*                                SHAPES                                */

t_sphere	*new_sphere(t_vec3 pos, double diameter, t_vec3 color);
t_plane		*new_plane(t_vec3 pos, t_vec3 dir, t_vec3 color);
t_cylinder	*new_cylinder(t_vec3 pos, t_vec3 dir, double diameter, double height, t_vec3 color);
void		free_sphere(t_object *object);

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
char		*object_type_to_str(t_object *object, bool selected);

/*                                 EVENTS                                  */

int			end_mlx_loop(t_mlx_data *mlx);
int			handle_keypress(int keycode, t_minirt *minirt);
int			handle_mouseclick(int button, int x, int y, t_minirt *minirt);
void		event_print_debug(t_minirt *minirt);
void		print_camera_data(t_minirt *minirt);
void		event_turn_cylinders(t_minirt *minirt);
void		event_sphere_shearing(t_minirt *minirt);
void		event_light_pos(t_minirt *minirt, int keycode);
void		arrows_handle(int keycode, t_minirt *minirt);
void		asdw_handle(int keycode, t_minirt *minirt);

void		event_object_selection(t_minirt *minirt, t_scene *scene, int keycode);
void		set_selected_object_str(t_minirt *minirt, t_scene *scene);
void		event_obj_pos(t_minirt *minirt, int keycode);

/*                                 EXIT                                  */

void		free_scene(t_scene *scene);
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
void		print_scene_ok_message(char *scene);
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
void		sort_inter(t_inter_list *inter_lst);
t_inter		*get_hit(t_inter_list *lst);
t_vec3		get_reflection(t_vec3 in, t_vec3 normal);
t_ray		ray_for_pixel(t_camera camera, double px, double py);
void		load_special_scene(int number, t_minirt *minirt);

#endif
