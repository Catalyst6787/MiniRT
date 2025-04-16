/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:46:11 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/10 16:46:13 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f) (void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
#include <stdlib.h>

void print_content(void *content) {
    printf("%s\n", (char *)content);
}

int main() {
    // Case 1: List of 1 element
    t_list *single_elem_list = malloc(sizeof(t_list));
    single_elem_list->content = "Single Element";
    single_elem_list->next = NULL;

    printf("Case 1: List of 1 element\n");
    ft_lstiter(single_elem_list, print_content);

    // Cleanup
    free(single_elem_list);

    // Case 2: List of multiple elements
    t_list *first_elem = malloc(sizeof(t_list));
    t_list *second_elem = malloc(sizeof(t_list));
    t_list *third_elem = malloc(sizeof(t_list));

    first_elem->content = "First Element";
    first_elem->next = second_elem;
    second_elem->content = "Second Element";
    second_elem->next = third_elem;
    third_elem->content = "Third Element";
    third_elem->next = NULL;

    printf("\nCase 2: List of multiple elements\n");
    ft_lstiter(first_elem, print_content);

    // Cleanup
    free(third_elem);
    free(second_elem);
    free(first_elem);

    // Case 3: Pass an empty list
    t_list *empty_list = NULL;

    printf("\nCase 3: Pass an empty list\n");
    ft_lstiter(empty_list, print_content); // Should handle gracefully

    // Case 4: Pass a NULL function
    t_list *another_list = malloc(sizeof(t_list));
    another_list->content = "Another Element";
    another_list->next = NULL;

    printf("\nCase 4: Pass a NULL function\n");
    ft_lstiter(another_list, NULL); // Should handle gracefully

    // Cleanup
    free(another_list);

    return 0;
}
*/
