#ifndef DEBUG_H
# define DEBUG_H

#include "minirt.h"

int		get_debug_fd(void);

# define PRINT_DEBUG(...) dprintf(get_debug_fd(), __VA_ARGS__)
# define CLOSE_DEBUG_FD close(get_debug_fd())

#endif
