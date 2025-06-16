
#include "minirt.h"
#include "ray.h"
#include "vec3.h"
#include <float.h>
#include <math.h>


int	render_scene(t_minirt *minirt)
{
	// t_ray			original_ray;
	// t_ray			unique_ray;
	// t_ray			r;

	if (!minirt)
		return (print_err(FILE, LINE, "render_scene: NULL prt!"), 1);
	printf("inter count: [%d], inter capacity: [%d]",
		minirt->render->inter_list.count, minirt->render->inter_list.capacity);

	return (0);
}
