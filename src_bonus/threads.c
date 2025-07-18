#include "minirt.h"

int	start_threads(t_minirt *minirt)
{
	t_thread_data	thread[NB_THREADS];
	int				i;
	int				count;
	int				diff;
	// pthread_mutex_t	inter_mutex;
	// pthread_mutex_t	shade_mutex;

	pthread_mutex_init(&(minirt->render->printf_mtx), NULL);
	pthread_mutex_init(&(minirt->render->printf_mtx), NULL);
	i = 0;
	count = 0;
	diff = WIN_W / NB_THREADS;
	while (i < NB_THREADS)
	{

		// pthread_mutex_init(&(thread[i].inter_mutex), NULL);
		// pthread_mutex_init(&(thread[i].shade_mutex), NULL);
		// pthread_mutex_init(&(thread[i].ray_mutex), NULL);
		thread[i].start = count;
		thread[i].end = count + diff - 1;
		thread[i].minirt = minirt;
		while (i == (NB_THREADS - 1) && thread[i].end < (WIN_W - 1))
			thread[i].end ++;
		count = count + diff;
		// printf("start : %d\nend : %d\n\n", thread[i].start, thread[i].end);
		// thread[i].inter_mutex = &inter_mutex;
		// thread[i].shade_mutex = &shade_mutex;
		pthread_create(&thread[i].thread, NULL, th_render_scene, &thread[i]);
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_join(thread[i].thread, NULL);
		pthread_mutex_init(&(thread[i].inter_mutex), NULL);
		pthread_mutex_init(&(thread[i].shade_mutex), NULL);
		pthread_mutex_init(&(thread[i].ray_mutex), NULL);
		i++;
	}
	display_image(minirt);
	return (0);
}
