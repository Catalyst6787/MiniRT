/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:57:24 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/15 17:57:32 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

int	ft_printf(const char *s, ...);
int	ft_putchar_c(char c);
int	ft_putstr_c(char *s);
int	ft_putnbr_c(int n);
int	ft_putunsigned_c(unsigned int n);
int	ft_putlonghex_c(unsigned long n, unsigned int up, int a);
int	ft_putunsignedhex_c(unsigned int n, unsigned int up);

#endif