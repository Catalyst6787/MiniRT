#include "minirt.h"

void	save_random_scene(t_minirt *minirt)
{
	char	filename[21] = "scenes/random_000.rt";
	int		fd;

	while (!access(filename, F_OK))
	{
		filename[16]++;
		if (filename[16] == ':')
		{
			filename[16] = '0';
			filename[15]++;
		}
		if (filename[15] == ':')
		{
			filename[15] = '0';
			filename[14]++;
		}
		if (filename[14] == ':')
		{
			printf("%sCan't save scene, no more space!%s\n", RED, CRESET);
			return ;
		}
	}
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		printf("%sError creating file%s\n", RED, CRESET);
		strerror(errno);
		return ;
	}
	if (write(fd, minirt->scene->buffer, ft_strlen(minirt->scene->buffer)) == -1)
		printf("%sError writing in file%s\n", RED, CRESET);
	else
		printf("%s\"%s\" file created!%s\n", GREEN, &filename[7], CRESET);
	close(fd);
}


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
void	gen_print_plane(FILE *file, t_rand *rand, bool chaos)
{
	if (!chaos)
	{
		rand->is_plane = 1;
		fprintf(file, "pl	0,0,10	0,1,0	%d,%d,%d\n",
			generate_random_int(0, 255),
			generate_random_int(0, 255),
			generate_random_int(0, 255));
		return ;
	}
	fprintf(file, "pl	%d,%d,%d	%.2f,%.2f,%.2f	%d,%d,%d\n",
		generate_random_int(-10, 10),
		generate_random_int(-10, 10),
		generate_random_int(0, 10),
		generate_random_double(-1, 1),
		generate_random_double(-1, 1),
		generate_random_double(-1, 1),
		generate_random_int(0, 255),
		generate_random_int(0, 255),
		generate_random_int(0, 255));
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
