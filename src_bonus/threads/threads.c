#include "minirt.h"


int	start_threads(t_minirt *minirt)
{
	t_thread_data	thread[NB_THREADS];
	int				i;

	i = 0;
	while (i < NB_THREADS)
	{
		thread[i].id = i;
		thread[i].minirt = minirt;
		if (pthread_create(&thread[i].thread, NULL, th_render_scene, &thread[i]) == -1)
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
