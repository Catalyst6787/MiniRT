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
		render->inter_list.inters[i++].obj = &scene->objects[obj_id];
		render->inter_list.inters[i++].obj = &scene->objects[obj_id++];
	}
	// obj_id = 0;
	// while (obj_id < scene->nb_plane)
	// {
	// 	render->inter_list.inters[i++].obj = scene->planes[obj_id++];
	// }
	// obj_id = 0;
	// while (obj_id < scene->nb_cylinder)
	// {
	// 	render->inter_list.inters[i++].obj = scene->cylinders[obj_id];
	// 	render->inter_list.inters[i++].obj = scene->cylinders[obj_id++];
	// }
}

void	fill_intersection_table(t_minirt *minirt, t_render *render)
{
	int	inter_count;

	inter_count = count_intersections(minirt->scene);
	render->inter_list.inters = malloc(sizeof(t_inter) * inter_count + 1);
	if (!render->inter_list.inters)
		quit(minirt, MALLOC_ERR);
	ft_memset(render->inter_list.inters, 0, inter_count);
	render->inter_list.capacity = inter_count;
	fill_inter_objects(minirt->render, minirt->scene);
}
