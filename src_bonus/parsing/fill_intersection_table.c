#include "minirt.h"

static int	count_intersections(t_scene *scene)
{
	int	count;

	count = 0;
	count += (scene->nb_sphere * 2);
	count += scene->nb_plane;
	count += (scene->nb_cylinder * 2);
	return (count);
}

static void	fill_inter_objects(t_render *render, t_scene *scene)
{
	int	i;
	int	obj_id;

	obj_id = 0;
	i = 0;
	while (obj_id < scene->nb_objects)
	{
		if (scene->objects[obj_id].type == PLANE)
			render->inter_list.inters[i++].obj = &scene->objects[obj_id++];
		else
		{
			render->inter_list.inters[i++].obj = &scene->objects[obj_id];
			render->inter_list.inters[i++].obj = &scene->objects[obj_id++];
		}
	}
}

void	fill_intersection_table(t_minirt *minirt, t_render *render)
{
	render->inter_count = count_intersections(minirt->scene);
	render->inter_list.inters
		= malloc(sizeof(t_inter) * render->inter_count + 1);
	if (!render->inter_list.inters)
		quit(minirt, MALLOC_ERR);
	render->shadow_list.inters
		= malloc(sizeof(t_inter) * render->inter_count + 1);
	if (!render->shadow_list.inters)
		quit(minirt, MALLOC_ERR);
	ft_memset(render->inter_list.inters, 0, render->inter_count);
	ft_memset(render->shadow_list.inters, 0, render->inter_count);
	render->inter_list.capacity = render->inter_count;
	render->shadow_list.capacity = render->inter_count;
	fill_inter_objects(minirt->render, minirt->scene);
}
