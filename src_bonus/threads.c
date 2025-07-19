#include "minirt.h"

int	start_threads(t_minirt *minirt)
{
	t_thread_data	thread[NB_THREADS];
	int				i;
	int				count;
	int				diff;
	clock_t		t;

	i = 0;
	count = 0;
	diff = WIN_W / NB_THREADS;
	t = clock();
	while (i < NB_THREADS)
	{
		thread[i].start = count;
		thread[i].end = count + diff - 1;
		thread[i].minirt = minirt;
		while (i == (NB_THREADS - 1) && thread[i].end < (WIN_W - 1))
			thread[i].end ++;
		count = count + diff;
		pthread_create(&thread[i].thread, NULL, th_render_scene, &thread[i]);
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_join(thread[i].thread, NULL);
		i++;
	}
	display_image(minirt);
	t = clock() - t;
	printf("Scene rendered in %f seconds\n", (((double)t) / CLOCKS_PER_SEC) / NB_THREADS);
	return (0);
}
