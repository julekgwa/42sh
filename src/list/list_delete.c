/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkekana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 16:51:56 by gkekana           #+#    #+#             */
/*   Updated: 2016/09/11 16:51:57 by gkekana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*delete_node(t_node *node)
{
	t_node	*tmp;

	tmp = node->next;
	free(node);
	return (tmp);
}

void	delete_all_nodes(t_node **root)
{
	t_node	*ptr;
	t_node	*tmp;

	ptr = *root;
	while (ptr->next)
	{
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	free(ptr);
}
