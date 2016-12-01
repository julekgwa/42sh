/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:37:50 by goisetsi          #+#    #+#             */
/*   Updated: 2016/09/11 08:56:43 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_up_down(char **buf, char **comm, t_stack *hist, int *pos)
{
	char	*k;
	int		cnt;
	int		size;

	k = *buf + 1;
	cnt = hist->hist_count;
	size = hist->size;
	if (hist->size >= 0)
	{
		if (size == 0 && (ft_strequ(k, "[A") || ft_strequ(k, "[5~")) && cnt > 0)
			hist->size = 1;
		if (hist->hist_count > 0)
		{
			if ((*comm = ft_keys_up_down(*buf, hist, pos)) != NULL)
				ft_process_buff(comm, *pos, '\0', hist);
			else
			{
				*comm = "";
				ft_process_buff(comm, 0, '\0', hist);
			}
		}
	}
}

void	ft_ctrl_l(char *comm, int pos, t_stack *h)
{
	ft_clear_screen();
	ft_cursor(comm, pos + 1, h);
}

char	*ft_get_hist(char *history, t_stack hist)
{
	char	*tmp;
	int		i;
	char	*com;
	int		index;

	tmp = history + 1;
	i = -1;
	com = "";
	if ((index = ft_atoi(tmp)))
	{
		index -= 1;
		while (hist.list[++i] && i != index)
			if (i == index)
				com = hist.list[i];
	}
	else
	{
		while (hist.list[++i])
			if (ft_strncmp(tmp, hist.list[i], ft_strlen(tmp)) == 0)
				com = hist.list[i];
	}
	if (ft_strequ(com, ""))
		ft_print_error(tmp, 5);
	return (com);
}

void	ft_init_hist(t_stack *hist)
{
	int			fd;
	char		*line;
	mode_t		mode;
	t_search	*temp;

	mode = S_IRUSR | S_IWUSR;
	fd = open(hist->hist_file, O_RDONLY | O_CREAT, mode);
	if (fd)
	{
		while (get_next_line(fd, &line))
			ft_push(hist, line);
	}
	close(fd);
	hist->search = (t_search *)malloc(sizeof(t_search));
	temp = hist->search;
	temp->prev_match = NULL;
	temp->results = NULL;
	hist->echo_prompt = 0;
	hist->redirect = 0;
}

char	*ft_get_prev_hist(t_stack hist)
{
	char	*prev;
	int		i;

	i = 0;
	prev = "";
	while (hist.list[i])
	{
		prev = hist.list[i];
		i++;
	}
	return (prev);
}
