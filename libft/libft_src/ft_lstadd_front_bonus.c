/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:47:15 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/10 16:47:17 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new)
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // Create initial list
    t_list *head = NULL;

    // Create new nodes
    int *int_content = malloc(sizeof(int));
    *int_content = 42;
    t_list *int_node = ft_lstnew(int_content);

    char *str_content = strdup("Hello");
    t_list *str_node = ft_lstnew(str_content);

    // Test adding the integer node to the front
    ft_lstadd_front(&head, int_node);
    printf("Added int node. Head content: %d\n", *(int *)head->content);

    // Test adding the string node to the front
    ft_lstadd_front(&head, str_node);
    printf("Added string node. Head content: %s\n", (char *)head->content);

    // Cleanup the list
    t_list *current = head;
    while (current) {
        t_list *next = current->next;
        free(current->content);
        free(current);
        current = next;
    }

    return 0;
}
*/
