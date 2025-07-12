#include "minirt.h"

double	double_abs(double d)
{
	if (d < 0)
		return (-d);
	return (d);
}

int	double_isequal(double a, double b)
{
	if (double_abs(a - b) < EPSILON)
		return (1);
	return (0);
}
