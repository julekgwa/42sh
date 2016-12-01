/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkekana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 16:52:04 by gkekana           #+#    #+#             */
/*   Updated: 2016/09/11 16:52:06 by gkekana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_nodes(t_node *list)
{
	int		i;
	t_node	*ptr;

	ptr = list;
	i = 0;
	if (ptr)
	{
		while (ptr->next)
		{
			ptr = ptr->next;
			i++;
		}
		i++;
	}
	return (i);
}

t_node	*get_last(t_node *list)
{
	t_node *ptr;

	ptr = list;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

t_node	*get_node(t_node *list, int position)
{
	t_node	*ptr;
	int		i;

	ptr = list;
	i = 0;
	if (position > count_nodes(list) || position < 0)
		return (0);
	while (ptr)
	{
		if (i == position)
			return (ptr);
		ptr = ptr->next;
		i++;
	}
	return (0);
}
