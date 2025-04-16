/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:45:31 by lfaure            #+#    #+#             */
/*   Updated: 2024/10/10 16:45:33 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
#include <stdio.h>
#include <stdlib.h>

// Function to create a new list node
t_list *create_node(int data) {
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node) return NULL;
    new_node->content = (void *)(long)data; // Using long to store int
    new_node->next = NULL;
    return new_node;
}

// Function to append a node to the list
void append_node(t_list **head, int data) {
    t_list *new_node = create_node(data);
    if (!*head) {
        *head = new_node;
        return;
    }
    t_list *current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
}

int main() {
    t_list *head = NULL;

    // Create a linked list with 5 nodes
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);

    // Test ft_lstsize
    int size = ft_lstsize(head);
    printf("Size of the linked list: %d\n", size);

    // Free the linked list
    t_list *current = head;
    while (current) {
        t_list *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
*/
