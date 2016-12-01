/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:28:38 by goisetsi          #+#    #+#             */
/*   Updated: 2016/09/10 16:23:31 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_char(char *s, char c)
{
	int		i;
	char	tmp;

	i = 0;
	while (s[i])
	{
		tmp = s[i];
		if (s[i] == '\\')
		{
			tmp = ft_specila_char(s[i + 1]);
			i++;
		}
		ft_putchar(tmp);
		i++;
	}
	ft_putchar(c);
}

void	ft_echo(char *echo, char **envp)
{
	char	**split;
	int		count;

	split = ft_strsplit(echo, ' ');
	count = ft_array_len(split);
	if (count == 0)
		ft_putchar('\n');
	else
	{
		if (!ft_start_with(split[1], '-'))
		{
			split++;
			while (*split)
			{
				if (ft_start_with(*split, '$'))
					ft_putstr_char(ft_rm_quotes(ft_get_env(*split, envp)), ' ');
				else
					ft_putstr_char(ft_rm_quotes(*split), ' ');
				split++;
			}
			ft_putchar('\n');
		}
	}
}

int		ft_uneven(char *str)
{
	int	countsingle;
	int	countdouble;

	countsingle = 0;
	countdouble = 0;
	while (*str)
	{
		if (*str == '\"')
			countdouble++;
		if (*str == '\'')
			countsingle++;
		str++;
	}
	if ((countdouble % 2 == 0) && (countsingle % 2 == 0))
		return (0);
	else
		return (1);
}

void	ft_init_complete(t_stack *hist, char **envp)
{
	ft_init_hist(hist);
	hist->envp = envp;
	hist->click_flag = 0;
	hist->echo_prompt = 1;
}

void	ft_complete(t_cmd *cmd, char **envp)
{
	char		*line;
	t_cmd		*command;
	t_stack		*hist;

	if (ft_uneven(cmd->get_line))
	{
		ft_putchar('\n');
		command = malloc(sizeof(t_cmd));
		hist = ft_create_stack(envp);
		ft_init_complete(hist, envp);
		line = ft_strdup(cmd->get_line);
		while (ft_uneven(line))
		{
			prompt(command, hist);
			if (!ft_strequ(command->get_line, ""))
				ft_putchar('\n');
			else
				ft_putchar('\n');
			line = ft_strjoin(line, "\n");
			line = ft_strjoin(line, command->get_line);
		}
		cmd->get_line = line;
		free(command);
	}
}
