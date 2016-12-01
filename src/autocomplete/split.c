/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkekana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 17:44:48 by gkekana           #+#    #+#             */
/*   Updated: 2016/09/11 17:44:49 by gkekana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_delimeter(const char *s, int *i, char c)
{
	while (s[(*i)] == c)
		(*i)++;
}

t_word_list			split(const char *s, char c)
{
    int     i;
    t_word_list	subs;

    i = 0;
    subs.list = (char**)malloc(sizeof(char*) * 1024);
	if (!subs.list)
	{
		ft_printf("There was an error allocationg memory for: subs.list\n");
		exit(0);
	}
	subs.size = 0;
    while (s[i])
    {
        if (s[i] == c)
			skip_delimeter(s, &i, c);
        else
        {
            char *tmp = (char*)malloc(sizeof(char) * 1024);
			if (!tmp)
			{
				ft_printf("There was an error allocationg memory for: subs.list\n");
				exit(ERROR);
			}
            int l = 0;
            while (s[i] != c && s[i])
            {
				if (s[i] == c) break;
                tmp[l] = s[i];
                i++;
                l++;
            }
            tmp[l] = '\0';
            if (tmp)
            {
                subs.list[subs.size] = tmp;
                subs.size++;
            }
        }
    }
	if (subs.size > 0)
	    return (subs);
	else
	{
		free(subs.list);
		return (subs);
	}
}
