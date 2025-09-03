/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_more_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:53:30 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:53:31 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_light_data(t_minirt *minirt)
{
	int	i;

	i = -1;
	while (++i < minirt->scene->nb_light)
	{
		printf("Light[%d/%d] :\n\n", i + 1, minirt->scene->nb_light);
		printf("	x y z : %.2f %.2f %.2f\n",
			minirt->scene->lights[i]->pos.x,
			minirt->scene->lights[i]->pos.y,
			minirt->scene->lights[i]->pos.z);
		printf("	r g b : %f %f %f\n",
			minirt->scene->lights[i]->color.r,
			minirt->scene->lights[i]->color.g,
			minirt->scene->lights[i]->color.b);
		printf("	brightness: %f\n\n", minirt->scene->lights[i]->brightness);
	}
}

void	event_print_debug(t_minirt *minirt)
{
	printf("\n");
	printf("Ambiant light :\n\n");
	printf("	Ratio : %.2f\n", minirt->scene->ambient->brightness);
	printf("	r g b : %.2f %.2f %.2f\n\n",
		minirt->scene->ambient->color.r,
		minirt->scene->ambient->color.g,
		minirt->scene->ambient->color.b);
	print_camera_data(minirt);
	printf("Light(s) :\n\n");
	print_light_data(minirt);
}

void	print_scene(t_minirt *minirt, bool asterix)
{
	if (asterix == true)
	{
		printf("\n* * * * * * * * * * * * * * * * * * * * * *\n");
		printf("*                  Scene                  *");
		printf("\n\n");
	}
	printf("\n");
	printf("%s", minirt->scene->buffer);
	printf("\n");
	if (asterix == true)
	{
		printf("\n\n");
		printf("*                                         *\n");
		printf("* * * * * * * * * * * * * * * * * * * * * *\n\n");
	}
}

void	print_inter_list(t_inter_list *list)
{
	int	i;

	i = 0;
	printf("Inter Count %d\n", list->count);
	while (i < list->count)
	{
		printf("Inter obj [%d] : %p\n", i, (void *)list->inters[i].obj);
		printf("Inter  [%d] : %.3f\n", i, list->inters[i].t);
		i++;
	}
}
