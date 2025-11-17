/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:53:44 by lfaure            #+#    #+#             */
/*   Updated: 2025/09/02 12:45:22 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter	*get_hit(t_inter_list *lst)
{
	int	i;

	i = 0;
	while (i < lst->count)
	{
		if (lst->inters[i].t > 0)
			return (&lst->inters[i]);
		i++;
	}
	return (NULL);
}
