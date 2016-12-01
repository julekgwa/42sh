/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkekana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 17:44:42 by gkekana           #+#    #+#             */
/*   Updated: 2016/09/11 17:44:43 by gkekana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    move_cursor(int start, int end)
{
    int l;

    l = start;
    while (l < end)
    {
        ft_printf("\033[D");
        l++;
    }
}

void    clear_line(int end)
{
    move_cursor(0, end);
    ft_printf("\033[0K");
}

