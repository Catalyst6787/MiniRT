
#include "minirt.h"

int	get_debug_fd(void)
{
	static int fd = -1;

	if (fd == -1)
	{
		fd = open("./log/debug.log", O_CREAT | O_RDWR | O_TRUNC, 0664);
		printf("Debug log file created\n");
	}
	return (fd);
}
