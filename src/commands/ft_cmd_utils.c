/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 07:28:00 by julekgwa          #+#    #+#             */
/*   Updated: 2016/09/05 07:28:34 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_brackets(char *str)
{
	char	*clean;
	int		i;

	clean = malloc(strlen(str) + 1);
	i = 0;
	if (!ft_start_with(str, '(') && !ft_end_with(str, ')'))
	{
		clean = str;
		return (clean);
	}
	else
	{
		str = str + 1;
		while (*str)
		{
			if (*str != ')')
			{
				clean[i++] = *str;
			}
			str++;
		}
		clean[i] = 0;
		return (clean);
	}
}

int		ft_search_command(char *command)
{
	static char	*cmd = "echo pwd cd history setenv unsetenv env exit clear";
	char		**comm_split;

	comm_split = ft_strsplit(cmd, ' ');
	while (*comm_split)
	{
		if (ft_strcmp(*comm_split, command) == 0)
			return (1);
		comm_split++;
	}
	return (0);
}

void	ft_execute_commands(char **cmd, char *line, char **envp, t_stack *hist)
{
	if (ft_strequ(cmd[0], "cd"))
		ft_cd(cmd, envp, 0);
	else if (ft_strequ(cmd[0], "pwd"))
		ft_putendl(ft_pwd());
	else if (ft_strequ(cmd[0], "echo"))
		ft_echo(line, envp);
	else if (ft_strequ(cmd[0], "env"))
		ft_print_env(envp);
	else if (ft_strequ(cmd[0], "setenv"))
		ft_set_envir(envp, line);
	else if (ft_strequ(cmd[0], "unsetenv"))
		ft_unsetting_env(line, envp);
	else if (ft_strequ(cmd[0], "history"))
		ft_display_hist(hist, cmd, 0, 0);
	else if (ft_strequ(cmd[0], "clear"))
		tputs(tgetstr("cl", NULL), 1, ft_myputchar);
}

int		ft_character_keys(char *key_pressed)
{
	if (key_pressed[0] >= 32 && key_pressed[0] <= 126 && *key_pressed != 27)
		return (1);
	else
		return (0);
}

char	ft_specila_char(char c)
{
	if (c == 'b')
		return ('\b');
	else if (c == 't')
		return ('\t');
	else if (c == 'n')
		return ('\n');
	else if (c == 'v')
		return ('\v');
	else if (c == 'a')
		return ('\a');
	else if (c == '\\')
		return ('\\');
	else if (c == 'e')
		return ('\e');
	else if (c == 'f')
		return ('\f');
	else if (c == 'r')
		return ('\r');
	return (c);
}
