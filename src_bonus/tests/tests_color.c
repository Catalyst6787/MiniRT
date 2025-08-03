#include "minirt.h"


/**Test for pixel color multiplication
 */
void	test_color_mult(t_vec3 *color, int i,int j)
{
	(void) i;
	if ((j < WIN_H / 2 + 50 && j > WIN_H / 2 - 50))
	{
		t_vec3	color_red;

		set_color(&color_red, 1, 0, 0.5);
		*color = color_color_multiplication(*color, color_red);
		PRINT_DEBUG("r %.2f g %.2f b %.2f\n", color->r, color->g, color->b);
	}
}

