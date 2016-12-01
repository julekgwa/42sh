/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkekana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 17:44:23 by gkekana           #+#    #+#             */
/*   Updated: 2016/09/11 17:44:24 by gkekana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     get_width()
{
    struct winsize  ws;

    if (ioctl(1, TIOCGWINSZ, &ws) < 0)
        exit(0);
    return (ws.ws_col);
}

void    handle_tab(char **comm)
{
    t_word_list words;
    char        *last;
	int			size;
	int			i;

	last = (char*)malloc(sizeof(char) * 1024);
	if (!last)
	{
		ft_printf("Couldn't allocate memory for: char *last\n");
		exit(0);
	}
    words = split(*comm, ' ');
	size = words.size;
	ft_strcpy(last, words.list[words.size - 1]);
	i = 0;
	while (i < size)
	{
		free(words.list[i]);
		i++;
	}
	free(words.list);
    if (size == 1)
        search_cmd();
    else if (size > 1)
        search_path(last, comm);
}

