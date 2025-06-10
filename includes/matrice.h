#ifndef MATRICE_H
# define MATRICE_H

typedef	struct s_matrix
{
	double	matrix[4][4];
	int		row;
	int		col;
}			t_matrix;

////////		Utils

void			print_matrice(t_matrix m);
t_matrix		get_matrix(int row, int col, bool identity);
bool			matrix_isequal(t_matrix m1, t_matrix m2);
void			matrix_set_elem(t_matrix *m, int i, int j, double elem);
t_matrix		transpose_matrix(t_matrix m);

////////		Operations

t_matrix		translate_nxn_matrice(t_matrix *m, int n);
t_matrix		mutliply_matrix(t_matrix m1, t_matrix m2);

////////		Inversion

double			get_determinant(t_matrix m);
t_matrix		get_submatrice(t_matrix m, int row, int col);
bool			matrix_is_invertible(t_matrix m);
t_matrix		get_inversed_matrix(t_matrix m);




#endif
