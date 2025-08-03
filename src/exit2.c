#include "minirt.h"

void	print_exit_info(char *str)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (errno)
	{
		ft_putstr_fd("(strerror[", STDERR_FILENO);
		ft_putnbr_fd(errno, STDERR_FILENO);
		ft_putstr_fd("] : ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(")\n", STDERR_FILENO);
	}
	ft_putstr_fd(COLOR_RESET, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
