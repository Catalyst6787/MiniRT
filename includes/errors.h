#include "minirt.h"



# define FILE_OPEN_ERR "Error : couldn't open file\n"
# define MALLOC_ERR "Malloc error.\n"
# define EMPTY_FILE_ERR "Error : empty file\n"
# define READ_ERR "Error reading the file\n"
# define CLOSING_FILE_ERR "Error closing fd\n"
# define EXT_MISSING_ERR "Error : file extension missing\n"
# define WRONG_EXT_ERR "Error : wrong extenssion\n"

# define CHAR_ERR "Error : wrong characters in scene\n"
# define SCENE_WRONG_CHAR_ERR "Error : wrong alpha char encountered\n"

# define MISSING_AMB_ERR "Error : scene missing ambiant light\n"
# define MISSING_CAM_ERR "Error : scene missing camera\n"
# define MISSING_LIGHT_ERR "Error : scene missing light\n"

# define TOO_MUCH_AMB_ERR "Error : more than one ambiant light detected\n"
# define TOO_MUCH_CAM_ERR "Error : more than one camera detected\n"
# define TOO_MUCH_LIGHT_ERR "Error : more than one light source detected(delete later for bonuses)\n"

# define MLX_ERR "Error : mlx initialization failed\n"
# define WINDOW_ERR "Error : mlx window initialization failed\n"
# define IMAGE_ERR "Error : mlx image initialization failed\n"
# define ADDR_ERR "Error : mlx addr initialization failed\n"

// # define NO_SPERE_WARNING
// # define NO_PLANE_WARNING
// # define NO_CYL_WARNING
