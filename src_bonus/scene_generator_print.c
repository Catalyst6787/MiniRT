#include "minirt.h"

void	set_next_available_filename(char *filename)
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

void	save_random_scene(t_minirt *minirt)
{
	char	filename[21];
	int		fd;

	ft_strlcpy(filename, "scenes/random_000.rt", 21);
	while (!access(filename, F_OK))
	{
		set_next_available_filename(filename);
	}
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("%sError creating file%s\n", RED, CRESET);
		strerror(errno);
		return ;
	}
	if (write(fd, minirt->scene->buffer,
			ft_strlen(minirt->scene->buffer)) == -1)
		printf("%sError writing in file%s\n", RED, CRESET);
	else
		printf("%s\"%s\" file created!%s\n", GREEN, &filename[7], CRESET);
	close(fd);
}

void	gen_print_plane(FILE *file, t_rand *rand)
{
	rand->is_plane = 1;
	fprintf(file, "pl 0,0,10 0,1,0 %.2f,%.2f,%.2f %d,%d,%d %.2f %.2f %d %d 0,0,0,0,0,0\n",
		generate_random_double(0, 10),
		generate_random_double(0, 10),
		generate_random_double(0, 10),
		generate_random_int(0, 255),
		generate_random_int(0, 255),
		generate_random_int(0, 255),
		generate_random_double(0, 1),
		generate_random_double(0, 1),
		generate_random_int(0, 255),
		generate_random_int(0, 1));
}

void	gen_print_object(FILE *file, int type, t_rand *rand, bool chaos)
{
	if (type == 0)
		fprintf(file, "sp ");
	else if (type == 1)
	{
		if (rand->is_plane)
			return ;
		if (!chaos)
		{
			gen_print_plane(file, rand);
			return ;
		}
		fprintf(file, "pl ");
	}
	else if (type == 2)
		fprintf(file, "cy ");
	else if (type == 3)
		fprintf(file, "co ");
	fprintf(file, "%.2f,%.2f,%.2f %.2f,%.2f,%.2f %.2f,%.2f,%.2f %d,%d,%d %.2f %.2f %d %d 0,0,0,0,0,0\n",
		generate_random_double(-10, 10),
		generate_random_double(-10, 10),
		generate_random_double(0, 10),
		generate_random_double(-1, 1),
		generate_random_double(-1, 1),
		generate_random_double(-1, 1),
		generate_random_double(0, 10),
		generate_random_double(0, 10),
		generate_random_double(0, 10),
		generate_random_int(0, 255),
		generate_random_int(0, 255),
		generate_random_int(0, 255),
		generate_random_double(0, 1),
		generate_random_double(0, 1),
		generate_random_int(2, 500),
		generate_random_int(0, 1));
}
