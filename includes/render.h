#ifndef RENDER_H
# define RENDER_H


typedef struct s_comp
{
	void		*object;
	double		t;
	t_vec3		point;
	t_vec3		eyev;
	t_vec3		normalv;
	bool		inside;
	t_material	m;
	t_light		light;
}				t_comp;

typedef struct s_inter
{
	const t_object	*obj;
	double			t;
}			t_inter;

typedef struct s_inter_list
{
	t_inter		*inters;
	int			count;
	int			capacity;
}			t_inter_list;

typedef struct s_render
{
	t_vec3			camera_center;
	t_vec3			camera_dir;
	double			wall_distance;
	double			wall_size;
	double			canva_height;
	double			canva_width;
	double			pixel_size;
	double			half;
	double			world_y;
	double			world_x;
	t_vec3			wall_point;
	t_ray			original_ray;
	t_ray			unique_ray;
	t_inter_list	inter_list;
}					t_render;

typedef struct s_view
{
	t_vec3		from;
	t_vec3		to;
	t_vec3		up;
}				t_view;


// sort intersections
void	sort_inter(t_inter_list *inter_lst);
t_inter	*get_hit(t_inter_list *lst);
t_vec3	get_sphere_normal_at(const t_object *s, const t_vec3 world_point);
t_vec3	get_reflection(t_vec3 in, t_vec3 normal);
int		get_sphere_inter(const t_object *object,
			const t_ray ray, t_inter_list *list);
int		get_plane_inter(const t_object *plane,
			const t_ray ray, t_inter_list *list);
t_comp	get_computations(t_scene *scene, t_inter *hit, t_ray r);
int		get_intersection(t_object *object, t_ray ray, t_inter_list *list);

#endif
