
#include "minirt.h"

// good for quick length comparison, less precise but faster than
// vec3_exact_lenght
double	vec3_length_squared(t_vec3 *vec3)
{
	assert(vec3);
	return (vec3->x * vec3->x + vec3->y * vec3->y + vec3->z * vec3->z);
}

double	vec3_exact_length(t_vec3 *vec3)
{
	assert(vec3);
	return (sqrt(vec3_length_squared(vec3)));
}

t_vec3	vec3_normalise(t_vec3 vec3)
{
	t_vec3	normalised;
	double	length;

	length = vec3_exact_length(&vec3);
	assert(length != 0);
	normalised.x = vec3.x / length;
	normalised.y = vec3.y / length;
	normalised.z = vec3.z / length;
	return (normalised);
}

// commutative
double	vec3_dot(t_vec3 *vec3_u, t_vec3 *vec3_v)
{
	assert(vec3_u);
	assert(vec3_v);
	if (vec3_u->w || vec3_v->w)
		print_err(FILE, LINE, "vec3_dot, tring to dot a point");
	return ((vec3_u->x * vec3_v->x)
		+ (vec3_u->y * vec3_v->y)
		+ (vec3_u->z * vec3_v->z));
}

int	vec3_isequal(t_vec3 vec3_a, t_vec3	vec3_b)
{
	if (double_isequal(vec3_a.x, vec3_b.x)
		&& double_isequal(vec3_a.y, vec3_b.y)
		&& double_isequal(vec3_a.z, vec3_b.z))
		return (1);
	return (0);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	if (a.w || b.w)
		print_err(FILE, LINE, "vec3_cross, trying to cross a point");
	return (get_vec3(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}
