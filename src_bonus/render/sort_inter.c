/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:54:28 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/01 18:57:53 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	swap_inters(t_inter *a, t_inter *b)
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
			swap_inters(&arr->inters[i], &arr->inters[j]);
		}
		j++;
	}
	swap_inters(&arr->inters[i + 1], &arr->inters[high]);
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
