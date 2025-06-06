#ifndef MATRICE_H
# define MATRICE_H

typedef	struct s_matrix
{
	double	matrix[4][4];
	int		row;
	int		col;
}			t_matrix;

void			print_matrice(t_matrix matrice);
t_matrix		get_matrix(int row, int col, bool identity);
t_matrix		multiply_4x4_matrix(t_matrix m1, t_matrix m2);
bool			matrix_isequal(t_matrix m1, t_matrix m2);
void			matrix_set_elem(t_matrix *m, int i, int j, double elem);

#endif
