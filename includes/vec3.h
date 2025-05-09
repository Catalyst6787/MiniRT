/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:56:45 by lfaure            #+#    #+#             */
/*   Updated: 2025/05/09 15:43:09 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

// CREATE
t_vec3	*vec3_default_alloc(void);
t_vec3	*vec3_new_alloc(const double x, const double y, const double z);
int		vec3_init(t_vec3 *vec3, const double x, const double y, const double z);
t_vec3	*vec3_dup_alloc(t_vec3 *to_dup);
int		vec3_copy(t_vec3 *dest, t_vec3 *origin);

// BASIC OPS
int		vec3_reverse_inplace(t_vec3 *vec_to_rev);
int		vec3_substract_inplace(t_vec3 *vec_value, const t_vec3 *to_subtract);
int		vec3_add_inplace(t_vec3 *vec_value, const t_vec3 *to_add);
int		vec3_multiply_inplace(t_vec3 *vec_value, const t_vec3 *to_multiply_by);
int		vec3_divide_inplace(t_vec3 *vec_value, const t_vec3 *to_divide_by);

// BASIC OPS BY
int		vec3_substract_by_inplace(t_vec3 *vec_value, const double to_subtract);
int		vec3_add_by_inplace(t_vec3 *vec_value, const double to_add);
int		vec3_multiply_by_inplace(t_vec3 *vec_value,
			const double to_multiply_by);
int		vec3_divide_by_inplace(t_vec3 *vec_value, const double to_divide_by);

// COMPLEX OPS
double	vec3_length_squared(t_vec3 *vec3);
double	vec3_exact_length(t_vec3 *vec3);
void	vec3_normalise_inplace(t_vec3 *vec3);
double	vec3_dot(t_vec3 *vec3_u, t_vec3 *vec3_v);

#endif
