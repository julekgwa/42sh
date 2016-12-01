/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_keyboard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:32:58 by goisetsi          #+#    #+#             */
/*   Updated: 2016/09/06 16:30:51 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_enter_key(char **comm, t_stack *hist, int *pos)
{
	*pos = -1;
	if (*comm[0] == '!')
	{
		ft_exclamation(comm, hist, pos);
	}
	else if (*comm[0] == '^')
		ft_man_search_replace(comm, pos, *hist);
	else if (ft_end_with(*comm, ')') && !ft_start_with(*comm, '('))
	{
		ft_putendl("\n42sh: parse error near `)'");
		*comm = "";
		*pos = ft_strlen(*comm);
		ft_cursor(*comm, *pos + 1, hist);
	}
	else
	{
		ft_cursor(*comm, *pos, hist);
		if (hist->ctrl_r == 1)
		{
			*comm = hist->search->results;
			hist->ctrl_r = 0;
		}
		return (1);
	}
	return (0);
}

int		ft_edit_keys(char *key_pressed, int *pos, char *comm, t_stack *hist)
{
	char	*key;
	int		i;

	key = key_pressed + 1;
	i = *pos - 1;
	if (key_pressed[0] == 127 || ft_strequ(key, "[3~") || key_pressed[0] == 8)
	{
		if (*pos > 0 && *comm)
		{
			ft_putstr("\33[2K\r");
			while (*(comm + i) != '\0')
			{
				*(comm + i) = *(comm + i + 1);
				i++;
			}
			*(comm + i) = '\0';
			*pos = *pos - 1;
			ft_cursor(comm, *pos + 1, hist);
		}
		return (1);
	}
	else
		return (0);
}

int		ft_nav_keys(char *key_pressed, int *pos, char **comm, t_stack *hist)
{
	if (ft_strequ(key_pressed + 1, "[D"))
	{
		if (*pos > 0)
			*pos = *pos - 1;
	}
	else if (ft_strequ(key_pressed + 1, "[C"))
	{
		if ((int)ft_strlen(*comm) > *pos)
			*pos = *pos + 1;
	}
	else if (ft_strequ(key_pressed + 1, "[H"))
		*pos = 0;
	else if (ft_strequ(key_pressed + 1, "[F"))
		*pos = (int)ft_strlen(*comm);
	else if (KEYS == 9)
	{
		ft_process_buff(comm, *pos, '\t', hist);
		*pos = *pos + 1;
		ft_cursor(*comm, *pos, hist);
	}
	else
		return (0);
	return (1);
}

int		ft_check_lines(char *comm)
{
	int		count;

	count = 0;
	while (*comm)
	{
		if (*comm == '\n')
			count++;
		comm++;
	}
	return (count);
}

void	ft_cursor(char *comm, int pos, t_stack *hist)
{
	if (hist->ctrl_r)
		ft_bck_i_search(comm, pos, hist);
	else
	{
		ft_putstr("\33[2K\r");
		ft_delete_lines(comm);
		prompt_display(hist);
		ft_display_cmd(comm, pos);
	}
	if ((int)ft_strlen(comm) < pos)
	{
		tputs(tgetstr("so", NULL), 1, ft_myputchar);
		ft_putchar(' ');
		tputs(tgetstr("se", NULL), 1, ft_myputchar);
	}
}
