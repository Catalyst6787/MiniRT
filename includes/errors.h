#ifndef ERRORS_H
# define ERRORS_H

# define FILE_OPEN_ERR "Error : couldn't open file\n"
# define MALLOC_ERR "Malloc error.\n"
# define EMPTY_FILE_ERR "Error : empty file\n"
# define READ_ERR "Error reading the file\n"
# define CLOSING_FILE_ERR "Error closing fd\n"
# define EXT_MISSING_ERR "Error : file extension missing\n"
# define WRONG_EXT_ERR "Error : wrong extension\n"

# define EMPTY_FILE "Error : empty file\n"
# define CHAR_ERR "Error : wrong characters in scene\n"
# define SCENE_WRONG_CHAR_ERR "Error : wrong alpha char encountered\n"
# define SCENE_ONLY_WS_ERR "Error : scene only contains whitespaces\n"
# define CHAR_DOUBLE "Error : double character found in scene\n"

# define WRONG_AMB_DATA "Error : wrong ambient light data\n"
# define WRONG_CAM_DATA "Error : wrong camera data\n"
# define WRONG_LIGHT_DATA "Error : wrong light data\n"
# define WRONG_SPH_DATA "Error : wrong sphere data\n"
# define WRONG_PLANE_DATA "Error : wrong plane data\n"
# define WRONG_CYL_DATA "Error : wrong cylinder data\n"

# define MISSING_AMB_ERR "Error : scene missing ambiant light\n"
# define MISSING_CAM_ERR "Error : scene missing camera\n"
# define MISSING_LIGHT_ERR "Error : scene missing light\n"

# define TOO_MANY_AMB_ERR "Error : more than one ambiant light detected\n"
# define TOO_MANY_CAM_ERR "Error : more than one camera detected\n"
# define TOO_MANY_LIGHT_ERR "Error : more than one light source detected\n"

# define MLX_ERR "Error : mlx initialization failed\n"
# define RENDER_INIT_ERR "Error : render initialization failed\n"
# define WINDOW_ERR "Error : mlx window initialization failed\n"
# define WIN_SIZE_ERR "Error : Window sizes less than 10x10\n"

# define IMAGE_ERR "Error : mlx image initialization failed\n"
# define ADDR_ERR "Error : mlx addr initialization failed\n"
# define PIXEL_PUT_ERR "Error : Tried to set pixel outside of window, quitting\n"

# define NORMAL_TYPE_NDEF "Error : get_object_normal_at object type not defined"

# define TESTS_ERR "Error : Test(s) failed\n"

#endif
