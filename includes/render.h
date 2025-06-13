#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"


typedef struct s_inter
{
	const void	*obj;
	double		t;
}			t_inter;

typedef struct s_inter_list
{
	t_inter		*inters;
	int			count;
	int			capacity;
}			t_inter_list;

#endif
