/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkekana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 16:52:41 by gkekana           #+#    #+#             */
/*   Updated: 2016/09/11 16:52:46 by gkekana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    list_rotate(t_node **list)
{
	t_node	*ptr;
	t_node	*tmp;
	int		size;
	int		i;

	i = 0;
	ptr = *list;
	while (i < (count_nodes(*list) - 2))
	{
		ptr = ptr->next;
		i++;
	}
	tmp = ptr->next;
	tmp->next = *list;
	ptr->next = 0;
	*list = tmp;
}
