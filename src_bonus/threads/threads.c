/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:54:53 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:54:54 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_thread(t_minirt *minirt, t_thread_data *th, int i)
{
	th->id = i;
	th->minirt = minirt;
	th->inter_list.inters = malloc(sizeof(t_inter)
			* count_intersections(th->minirt->scene) + 1);
	th->inter_list.capacity = count_intersections(th->minirt->scene);
	th->shadow_list.inters = malloc(sizeof(t_inter)
			* count_intersections(th->minirt->scene) + 1);
	th->shadow_list.capacity = count_intersections(th->minirt->scene);
	th->inter_list.count = 0;
	th->shadow_list.count = 0;
	if (!th->inter_list.inters || !th->shadow_list.inters)
		quit(th->minirt, MALLOC_ERR);
	ft_memset(th->inter_list.inters, 0, sizeof(t_inter)
		* count_intersections(th->minirt->scene));
	ft_memset(th->shadow_list.inters, 0, sizeof(t_inter)
		* count_intersections(th->minirt->scene));
}

int	start_threads(t_minirt *minirt)
{
	t_thread_data	thread[NB_THREADS];
	int				i;

	i = 0;
	while (i < NB_THREADS)
	{
		init_thread(minirt, &thread[i], i);
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		if (pthread_create(&thread[i].thread, NULL, th_render_scene,
				&thread[i]) == -1)
			quit(minirt, TH_ERR);
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_join(thread[i].thread, NULL);
		i++;
	}
	display_image(minirt);
	return (0);
}
