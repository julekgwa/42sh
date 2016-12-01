/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:37:50 by goisetsi          #+#    #+#             */
/*   Updated: 2016/09/05 08:00:18 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_up(t_stack *stack)
{
	if (stack->list[stack->size - 1])
		stack->size--;
	if (stack->size >= 0)
		return (stack->list[stack->size]);
	else
		return (NULL);
}

char	*ft_down(t_stack *stack)
{
	if (stack->list[stack->size + 1])
		stack->size++;
	else
	{
		stack->click_flag = 0;
		return (stack->curr_line);
	}
	if (stack->size < stack->hist_count)
		return (stack->list[stack->size]);
	else
		return (NULL);
}

int		ft_up_down(char *key_pressed)
{
	char	*key;

	key = key_pressed + 1;
	if (ft_strequ(key, "[A") || ft_strequ(key, "[5~"))
		return (1);
	else if (ft_strequ(key, "[B") || ft_strequ(key, "[6~"))
		return (1);
	return (0);
}

char	*ft_keys_up_down(char *key_pressed, t_stack *hist, int *pos)
{
	char	*key;
	char	*res;

	key = key_pressed + 1;
	res = NULL;
	if (ft_strequ(key, "[A") || ft_strequ(key, "[5~"))
	{
		hist->click_flag = 1;
		if (hist->size > 0)
			res = ft_up(hist);
	}
	else if (ft_strequ(key, "[B") || ft_strequ(key, "[6~"))
	{
		hist->click_flag = 1;
		if (hist->size < hist->hist_count)
			res = ft_down(hist);
	}
	else
		hist->click_flag = 0;
	if (res != NULL)
		*pos = (int)ft_strlen(res);
	return (res);
}

void	ft_write_hist(t_stack *hist)
{
	int		fd;
	int		len;
	char	*tmp;
	char	**list;

	fd = open(hist->hist_file, O_WRONLY | O_APPEND | O_TRUNC);
	list = hist->list;
	if (fd)
	{
		while (*list)
		{
			if (!ft_strequ(*list, ""))
			{
				tmp = *list;
				len = ft_strlen(tmp);
				tmp[len] = '\n';
				write(fd, tmp, len + 1);
			}
			list++;
		}
	}
	close(fd);
}
