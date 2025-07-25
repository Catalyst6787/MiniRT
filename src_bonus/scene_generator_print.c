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

void	gen_print_sphere(FILE *file)
{
	fprintf(file, "sp	%d,%d,%d	%.1f	%d,%d,%d\n",
		generate_random_int(-10, 10),
		generate_random_int(-10, 10),
		generate_random_int(0, 10),
		generate_random_double(0.1, 15.0),
		generate_random_int(0, 255),
		generate_random_int(0, 255),
		generate_random_int(0, 255));
}
void	gen_print_plane(FILE *file, t_rand *rand)
{
	rand->is_plane = 1;
	fprintf(file, "pl	0,0,10	0,1,0	%d,%d,%d\n",
		generate_random_int(0, 255),
		generate_random_int(0, 255),
		generate_random_int(0, 255));
	// fprintf(file, "pl	%d,%d,%d	%.2f,%.2f,%.2f	%d,%d,%d\n",
	// 	generate_random_int(-10, 10),
	// 	generate_random_int(-10, 10),
	// 	generate_random_int(0, 10),
	// 	generate_random_double(-1, 1),
	// 	generate_random_double(-1, 1),
	// 	generate_random_double(-1, 1),
	// 	generate_random_int(0, 255),
	// 	generate_random_int(0, 255),
	// 	generate_random_int(0, 255));
}

void	gen_print_cylinder_cones(FILE *file, char c)
{
	if (c == 'y')
		fprintf(file, "cy	");
	else if (c == 'o')
		fprintf(file, "co	");
	fprintf(file, "%d,%d,%d	%.2f,%.2f,%.2f	%.1f	%.1f	%d,%d,%d\n",
			generate_random_int(-10, 10),
			generate_random_int(-10, 10),
			generate_random_int(0, 10),
			generate_random_double(-1, 1),
			generate_random_double(-1, 1),
			generate_random_double(-1, 1),
			generate_random_double(0.1, 5.0),
			generate_random_double(0.1, 5.0),
			generate_random_int(0, 255),
			generate_random_int(0, 255),
			generate_random_int(0, 255));
}
