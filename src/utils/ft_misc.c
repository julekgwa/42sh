/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 07:32:06 by julekgwa          #+#    #+#             */
/*   Updated: 2016/09/11 12:33:20 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_cmd(char *cmd, int pos)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (i == pos - 1)
		{
			tputs(tgetstr("so", NULL), 1, ft_myputchar);
			ft_putchar(cmd[i]);
			tputs(tgetstr("se", NULL), 1, ft_myputchar);
		}
		else
			ft_putchar(cmd[i]);
		i++;
	}
}

int		ft_is_dir(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

int		ft_chk_env(char ***tmp_cmd, char **envp, int i)
{
	char	**str;

	str = *tmp_cmd;
	while (i < ft_array_len(str))
	{
		if (ft_start_with(str[i], '$'))
		{
			if (ft_get_env(str[i], envp) == NULL)
			{
				ft_putstr(str[i] + 1);
				ft_putendl(": Undefined variable.");
				return (0);
			}
			else
				str[i] = ft_get_env(str[i], envp);
		}
		i++;
	}
	*tmp_cmd = str;
	return (1);
}

void	ft_bck_i_search(char *cmd, int pos, t_stack *hist)
{
	char	*search;

	ft_putstr("\33[2K\r");
	ft_putstr("\33[A\r");
	ft_putstr("\33[2K\r");
	hist->search->results = "";
	hist->search->prev_match = "";
	hist->search->fail = 0;
	prompt_display(hist);
	ft_search_hist(cmd, *hist, hist->search, 1);
	search = hist->search->results;
	if (!ft_strequ(search, ""))
		ft_putstr(search);
	ft_putstr("\n");
	if (hist->search->fail || (ft_strequ(search, "") && ft_strlen(cmd) > 0))
		ft_putstr("failing ");
	ft_putstr("bck-i-search: ");
	ft_display_cmd(cmd, pos);
}

int		ft_array_len(char **arr)
{
	int	count;

	count = 0;
	while (*arr)
	{
		count++;
		arr++;
	}
	return (count);
}
