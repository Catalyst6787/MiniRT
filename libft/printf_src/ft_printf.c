/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:56:41 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/16 12:49:51 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_choose_format(char f, va_list ptr)
{
	if (!f)
		return (0);
	else if (f == 'c')
		return (ft_putchar_c(va_arg(ptr, int)));
	else if (f == 's')
		return (ft_putstr_c(va_arg(ptr, char *)));
	else if (f == 'p')
		return (ft_putlonghex_c(va_arg(ptr, unsigned long), 0, 1));
	else if (f == 'd' || f == 'i')
		return (ft_putnbr_c(va_arg(ptr, int)));
	else if (f == 'u')
		return (ft_putunsigned_c(va_arg(ptr, unsigned int)));
	else if (f == 'x')
		return (ft_putunsignedhex_c(va_arg(ptr, unsigned int), 0));
	else if (f == 'X')
		return (ft_putunsignedhex_c(va_arg(ptr, unsigned int), 1));
	else if (f == '%')
		return (ft_putchar_c('%'));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	ptr;
	int		c;
	int		i;

	c = 0;
	i = 0;
	va_start(ptr, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			c += ft_choose_format(s[i + 1], ptr);
			i++;
		}
		else
			c += ft_putchar_c(s[i]);
		i++;
	}
	va_end(ptr);
	return (c);
}
/*
#include <limits.h>
#include <stdio.h>
int	main(void)
{
	ft_printf("%d\n", ft_printf("%p\n", NULL));
	printf("%d\n", printf("%p\n", NULL));
	ft_printf("%p\n", LONG_MIN);
	printf("%p\n", LONG_MIN);
	
	int test = 42;
	ft_printf(" %p \n", NULL);
	printf(" %p \n", NULL);
	char *s = NULL;
	ft_printf(" NULL %s NULL \n", s);
	printf(" NULL %s NULL \n", s);
	ft_printf("%p\n", (void*)ptest);
	ft_printf("print a string: %s\n", "'a string'");
	ft_printf("print an empty string: %s\n", "");
	ft_printf("print a one char string: %s\n", "a");
	ft_printf("printf a char: %c\n", 'X');
	ft_printf("print a new line (actually two) :\n\n");
	ft_printf("print an int with d: %d\n", -42);
	ft_printf("print an int with i: %i\n", -42);
	ft_printf("print int min: %i\n", INT_MIN);
	ft_printf("print int max: %i\n", INT_MAX);
	ft_printf("print an unsigned int: %u\n", 4294967295);
	ft_printf("print an hexadecimal int: %x\n", 42);
	ft_printf("print a negative HEXADECIMAL int: %X\n", -42);
	printf("compare with previous: %p\n", (void*)ptest);

	ft_printf("print a percent sign: %%\n");
	ft_printf("print nothing: %\n\n");

	//tests
	//char *test = "test";
	//printf("%p\n", test);
	//printf("LONG_MIN: %ld\n", LONG_MIN);


	return(0);
}


* gc ft_printf.c  -I./ -I./libft/includes -L./libft -lft && ./a.out:w
*

*
 * • %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign.
*/
