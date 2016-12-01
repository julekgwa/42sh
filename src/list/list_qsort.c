/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_qsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkekana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 16:52:35 by gkekana           #+#    #+#             */
/*   Updated: 2016/09/11 16:52:36 by gkekana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(int *tab, int i, int j)
{
	int	t;

	t = tab[i];
	tab[i] = tab[j];
	tab[j] = t;
}

static void	quicksort(t_node *list, int *tab, int l, int r)
{
	int	c[2];
	int	pivot;

	if (l < r)
	{
		pivot = l;
		c[0] = l;
		c[1] = r;
		while (c[0] < c[1])
		{
			while (tab[c[0]] <= tab[pivot] && c[0] <= r)
				c[0]++;
			while (tab[c[1]] > tab[pivot] && c[1] >= l)
				c[1]--;
			if (c[0] < c[1])
			{
				swap(tab, c[0], c[1]);
				list_swap(&list, c[0], c[1]);
			}
		}
		swap(tab, c[1], pivot);
		list_swap(&list, c[1], pivot);
		quicksort(list, tab, l, c[1] - 1);
		quicksort(list, tab, c[1] + 1, r);
	}
}

static int		*create_tab(t_node *list)
{
	int		*tab;
	t_node	*ptr;
	int		i;

	i = 0;
	ptr = 0;
	tab = 0;
	ptr = list;
	tab = (int*)malloc(sizeof(int) * 1024);
	if (!tab)
		return (0);
	while (ptr)
	{
		tab[i] = ft_strlen((char*)ptr->data);
		ptr = ptr->next;
		i++;
	}
	tab[i] = 0;
	return (tab);
}


void	list_qsort(int count, t_node *list)
{
	int	*tab;

	tab = create_tab(list);
	quicksort(list, tab, 0, count - 1);
	free(tab);
}
