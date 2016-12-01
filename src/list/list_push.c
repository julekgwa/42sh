/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkekana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 16:52:29 by gkekana           #+#    #+#             */
/*   Updated: 2016/09/11 16:52:29 by gkekana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(void *data)
{
	t_node	*tmp;

	tmp = (t_node*)malloc(sizeof(t_node));
	tmp->data = data;
	tmp->next = NULL;
	return (tmp);
}

void	push_front(t_node **head, void *data)
{
	t_node	*ptr;

	if (!*head)
		*head = create_node(data);
	else
	{
		ptr = create_node(data);
		ptr->next = *head;
		*head = ptr;
	}
}

void	push_back(t_node **head, void *data)
{
	t_node	*ptr;

	ptr = *head;
	if (!*head)
		*head = create_node(data);
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = create_node(data);
	}
}
