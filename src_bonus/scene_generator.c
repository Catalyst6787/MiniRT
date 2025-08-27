#include "minirt.h"

void	gen_print_lights(FILE *file, t_rand *rand)
{
	int	i;

	fprintf(file, "A	%.2f	%d,%d,%d\n",
		rand->lights_ratio[0],
		generate_random_int(0, 255),
		generate_random_int(0, 255),
		generate_random_int(0, 255));
	i = 1;
	while (i < rand->nb_lights)
	{
		fprintf(file, "L	%d,%d,%d	%.2f %d,%d,%d\n",
			generate_random_int(-10, 10),
			generate_random_int(-10, 10),
			generate_random_int(-10, 10),
			rand->lights_ratio[i],
			generate_random_int(100, 255),
			generate_random_int(100, 255),
			generate_random_int(100, 255));
		i++;
	}
}

void	normalize_lights(t_rand *rand)
{
	double	ratio;
	double	total;
	int		i;

	i = 0;
	total = 2;
	ratio = 1;
	while (total > 1)
	{
		total = 0;
		ratio -= 0.1;
		i = 0;
		while (i < rand->nb_lights)
		{
			total += rand->lights_ratio[i] * ratio;
			i++;
		}
	}
	i = 0;
	while (i < rand->nb_lights)
	{
		rand->lights_ratio[i] = rand->lights_ratio[i] * ratio;
		i++;
	}
}

void	fill_lights_ratio(t_rand *rand)
{
	int	i;

	i = 0;
	rand->nb_lights = generate_random_int(2, 4);
	while (i < rand->nb_lights)
	{
		rand->lights_ratio[i] = generate_random_double(0.1, 1);
		i++;
	}
	normalize_lights(rand);
}

void	generate_random_scene(void)
{
	FILE	*file;
	t_rand	rand;
	int		obj_type;

	file = fopen("scenes/random_generation.rt", "w");
	fprintf(file, "C	0,0,-10 0,0,1 70\n");
	srand(time(NULL));
	rand.nb_obj = generate_random_int(3, 12);
	rand.is_plane = 0;
	fill_lights_ratio(&rand);
	gen_print_lights(file, &rand);
	while (rand.nb_obj >= 0)
	{
		obj_type = generate_random_int(0, 3);
		if (obj_type == 0)
			gen_print_sphere(file);
		else if (obj_type == 1 && !rand.is_plane)
			gen_print_plane(file, &rand, false);
		else if (obj_type == 2)
			gen_print_cylinder_cones(file, 'y');
		else if (obj_type == 3)
			gen_print_cylinder_cones(file, 'o');
		rand.nb_obj--;
	}
	fclose(file);
}
