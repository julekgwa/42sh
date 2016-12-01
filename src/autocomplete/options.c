/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkekana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 17:44:37 by gkekana           #+#    #+#             */
/*   Updated: 2016/09/11 17:44:38 by gkekana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_options(int count, t_node *list, char **comm)
{
	list_qsort(count, list);
	ft_printf("\n");
	create_cols(list);
}

void	matches(int	last, int count, t_node *list, char **comm)
{
	char	*tmp;
	t_node	*ptr;
	t_node	*node;

	if (count == 1)
	{
		tmp = (char*)malloc(sizeof(char) * (ft_strlen((char*)list->data + last + 1)));
		clear_line(ft_strlen(*comm) + 1);
		ft_strcpy(tmp, *comm);
		ft_strcat(tmp, (char*)list->data + last);
		ft_putstr(tmp);
		ft_bzero(*comm, 1024);
		ft_strcpy(*comm, tmp);
		ptr = list;
		while (ptr->next)
		{
			node = ptr;
			ptr = ptr->next;
			free(node);
		}
		free(tmp);
	}
	else if (count > 1)
		print_options(count, list, comm);
}
