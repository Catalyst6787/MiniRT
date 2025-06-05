#ifndef MATRICE_H
# define MATRICE_H

typedef	struct s_matrix
{
	int		cols;
	int		rows;
	double	**matrix;
}			t_matrix;

void		print_matrice(t_matrix matrice);
void		free_matrice(t_matrix *matrix);
t_matrix	new_matrix(int rows, int cols, bool identity);
t_matrix	multiply_4x4_matrix(t_matrix m1, t_matrix m2);

#endif