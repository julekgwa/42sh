/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkekana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 16:52:51 by gkekana           #+#    #+#             */
/*   Updated: 2016/09/11 16:52:52 by gkekana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap(t_node **a, t_node **b)
{
	void	*tmp;

	tmp = (*a)->data;
	(*a)->data = (*b)->data;
	(*b)->data = tmp;
}

void	list_swap(t_node **list, int p1, int p2)
{
	t_node	*a;
	t_node	*b;

	if (*list)
	{
		a = get_node(*list, p1);
		b = get_node(*list, p2);
		if (a && b)
			ft_swap(&a, &b);
	}
}
