#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

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
	const void	*obj;
	double		t;
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

// sort intersections
void	sort_inter(t_inter_list *inter_lst);
t_inter	*get_hit(t_inter_list *lst);
t_vec3	get_normal_at(const t_sphere *s, const t_vec3 world_point);
t_vec3	get_reflection(t_vec3 in, t_vec3 normal);
int		get_sphere_inter(const t_sphere *sphere,
			const t_ray ray, t_inter_list *list);
int		get_plane_inter(const t_plane *plane,
			const t_ray ray, t_inter_list *list);
t_comp	get_computations(t_scene *scene, t_inter *hit, t_ray r);

#endif
