/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cols.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkekana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 17:44:31 by gkekana           #+#    #+#             */
/*   Updated: 2016/09/11 17:44:32 by gkekana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_in_cols(int *end, int i, t_node *list)
{
    int k;
    int q;
    while (list)
    {
        k = 0;
        while ((k < i) && list)
        {
            ft_putstr((char*)list->data);
            q = ft_strlen((char*)list->data);
            while (q < end[k])
            {
                ft_printf(" ");
                q++;
            }
            pop_front(&list);
            k++;
        }
        ft_printf("\n");
    }
	q = 0;
	while (q < k + 1)
	{
		ft_printf("\033[0K");
		q++;
	}
}

void    create_cols(t_node *list)
{
    int end[10] = {0};
	int offset;
	int i;

	i = 0;
	offset = get_width();
	while (offset > 0 && list)
    {
        if (count_nodes(list) > 1)
            list_rotate(&list);
        offset = offset - ft_strlen((char*)list->data) + 1;
        if (offset <= 5)
            break;
		end[i] = ft_strlen((char*)list->data) + 1;
		ft_printf("%s ", (char*)list->data);
		pop_front(&list);
		i++;
	}
	ft_printf("\n");
	print_in_cols(end, i, list);
}
