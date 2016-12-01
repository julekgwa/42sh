/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkekana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 16:52:21 by gkekana           #+#    #+#             */
/*   Updated: 2016/09/11 16:52:22 by gkekana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pop_front(t_node **head)
{
	t_node	*ptr;
	t_node	*tmp;

	if (ptr)
	{
		ptr = *head;
		tmp = ptr->next;
			free(ptr);
		*head = tmp;
	}
}

void	pop_back(t_node **head)
{
	t_node	*ptr;
	t_node	*last;
	int		size;
	int		i;

	ptr = *head;
	if (ptr)
	{
		size = count_nodes(ptr);
		last = get_last(ptr);
		while (i < size - 1)
		{
			ptr = ptr->next;
			i++;
		}
		ptr->next = NULL;
		free(last);
		last->next = NULL;
		last = NULL;
	}
}
