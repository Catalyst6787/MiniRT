#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"


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
	// t_vec3			camera_dir;
	t_inter_list	inter_list;
}					t_render;





// sort intersections
void	sort_inter(t_inter_list *inter_lst);
t_inter	*get_hit(t_inter_list *lst);

#endif
