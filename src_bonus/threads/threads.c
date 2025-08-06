#include "minirt.h"

void	th_display_image(t_minirt *minirt)
{
	mlx_put_image_to_window(minirt->mlx->mlx,
		minirt->mlx->mlx_win, minirt->mlx->img_st->img, 0, 0);
	if (minirt->ui->command_help)
	{
		display_command_help(minirt, minirt->mlx);
		mlx_string_put(minirt->mlx->mlx, minirt->mlx->mlx_win,
			WIN_W - 140, 18, color_to_int(minirt->ui->string_color),
			minirt->ui->str_selected_object);
	}
}

void	start_thread(t_minirt *minirt, t_thread_data *thread, int i, int *count)
{
	int	diff;
	int	c;

	c = *count;
	diff = WIN_W / NB_THREADS;
	thread[i].start = c;
	thread[i].end = c + diff - 1;
	thread[i].minirt = minirt;
	while (i == (NB_THREADS - 1) && thread[i].end < (WIN_W - 1))
		thread[i].end ++;
	c = c + diff;
	if (pthread_create(&thread[i].thread, NULL, th_render_scene, &thread[i]) == -1)
		quit(minirt, TH_ERR);
	*count = c;
}

int	start_threads(t_minirt *minirt)
{
	t_thread_data	thread[NB_THREADS];
	int				i;
	int				count;
	struct timeval	start_time;
	struct timeval	end_time; 

	i = 0;
	count = 0;
	gettimeofday(&start_time, NULL);
	while (i < NB_THREADS)
	{
		start_thread(minirt, thread, i, &count);
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_join(thread[i].thread, NULL);
		i++;
	}
	gettimeofday(&end_time, NULL);
	th_display_image(minirt);
	printf("Scene rendered in %f seconds using multithreading\n",
			(end_time.tv_sec - start_time.tv_sec) +
			(end_time.tv_usec - start_time.tv_usec) / 1e6);
	return (0);
}
