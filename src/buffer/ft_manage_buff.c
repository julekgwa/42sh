/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_buff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:27:08 by goisetsi          #+#    #+#             */
/*   Updated: 2016/09/05 08:14:38 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_buff(char **com, int pos, char c, t_stack *h)
{
	char	*copy;
	char	*buffer;
	int		i;
	int		j;

	copy = *com;
	buffer = ft_memalloc(ft_strlen(copy) + 1);
	if (pos >= (int)ft_strlen(copy))
	{
		ft_memcpy(buffer, copy, ft_strlen(copy));
		buffer[pos] = c;
	}
	else
	{
		i = 0;
		j = -1;
		while (copy[i] && ++j >= 0)
			buffer[j] = (j == pos) ? c : copy[i++];
	}
	*com = buffer;
	if (h->click_flag == 0)
		h->curr_line = buffer;
	ft_cursor(*com, pos + 2, h);
}

int		ft_cmd_complete(char *cmd)
{
	int	num;

	num = 0;
	while (*cmd)
	{
		if (*cmd == 34 || *cmd == 39)
			num++;
		cmd++;
	}
	if (num % 2 == 0)
		return (1);
	else
		return (0);
}

int		ft_ctrl_b_f(char *buf)
{
	if (buf[0] == 2 || buf[0] == 6)
		return (1);
	else
		return (0);
}

void	ft_move_word(char *cmd, int *pos, char *buf)
{
	int	i;

	i = *pos;
	if (buf[0] == 2)
	{
		if (cmd[i - 1] == ' ')
			i -= 2;
		while (i >= 0 && cmd[i] != ' ')
			i--;
		*pos = i + 1;
	}
	else if (buf[0] == 6)
	{
		if (cmd[i + 1] == ' ')
			i += 2;
		while (cmd[i])
		{
			if (cmd[i] == ' ')
				break ;
			i++;
		}
		*pos = i + 1;
	}
}

int		ft_check_options(char opt, const char *options)
{
	while (*options)
	{
		if (*options == opt)
			return (1);
		options++;
	}
	return (0);
}
