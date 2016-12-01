/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bck_i_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 07:30:22 by julekgwa          #+#    #+#             */
/*   Updated: 2016/09/05 07:30:34 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_full_word(char **list, char *cmd, int i)
{
	while (list[i])
	{
		if (strstr(list[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

void	ft_search_hist(char *cmd, t_stack hist, t_search *bck_search, int found)
{
	char	**l;
	int		i;
	int		n;

	if (ft_strequ(cmd, ""))
		return ;
	l = hist.list;
	n = ft_strlen(cmd);
	while (n && found)
	{
		i = -1;
		while (l[++i])
		{
			if (STRSTR(l[i], SUB(cmd, 0, n)) && !FULL(l, SUB(cmd, 0, n), i + 1))
			{
				if (ft_strlen(cmd) > ft_strlen(ft_strsub(cmd, 0, n)))
					bck_search->fail = 1;
				bck_search->prev_match = bck_search->results;
				bck_search->results = l[i];
				found = 0;
				break ;
			}
		}
		n--;
	}
}
