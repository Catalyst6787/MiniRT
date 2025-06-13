#include "minirt.h"

static void	swap(t_inter *a, t_inter *b)
{
	t_inter	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	partition(t_inter_list *arr, int low, int high)
{
	t_inter	pivot;
	int		i;
	int		j;

	pivot = arr->inters[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr->inters[j].t < pivot.t)
		{
			i++;
			swap(&arr->inters[i], &arr->inters[j]);
		}
		j++;
	}
	swap(&arr->inters[i + 1], &arr->inters[high]);
	return (i + 1);
}

static void	quicksort(t_inter_list *arr, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition(arr, low, high);
		quicksort(arr, low, pi -1);
		quicksort(arr, pi +1, high);
	}
}

void	sort_inter(t_inter_list *inter_lst)
{
	quicksort(inter_lst, 0, inter_lst->count -1);
}
