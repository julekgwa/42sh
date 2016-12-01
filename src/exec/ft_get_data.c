/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:30:29 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:30:32 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**getpath(char **envp)
{
	int		i;
	char	**s1;
	char	**s2;

	i = 0;
	while (envp[i])
	{
		s1 = ft_strsplit(envp[i], '=');
		if (ft_strequ(s1[0], "PATH"))
		{
			s2 = ft_strsplit(s1[1], ':');
			return (s2);
		}
		i++;
	}
	return (NULL);
}

int		ft_is_execute(char *command)
{
	if (access(command, F_OK) == 0)
	{
		ft_print_error(command, 2);
		return (1);
	}
	return (0);
}

char	*ft_build_exec(char **envp, char **split)
{
	char	**new;
	char	*str;
	int		i;

	i = 0;
	new = getpath(envp);
	while (new[i] != '\0')
	{
		str = ft_strjoin(new[i], "/");
		str = ft_strjoin(str, split[0]);
		if (access(str, F_OK) == 0)
			return (str);
		i++;
	}
	ft_strdel(&str);
	return (NULL);
}

void	ft_execute(char *command, char **list_comm, char *get_line, char **envp)
{
	pid_t	pid;
	int		status;
	char	**split_com;

	if ((pid = fork()) < 0)
	{
		ft_putendl("unable to start child process");
		exit(1);
	}
	if (pid == 0)
	{
		if (ft_contains(get_line, '|') || ft_contains(get_line, '>'))
		{
			split_com = ft_strsplit(get_line, '|');
			fork_pipes(ft_array_len(split_com), split_com, envp, 0);
		}
		else
		{
			list_comm = ft_remove_arrow(list_comm);
			execve(command, &list_comm[0], envp);
		}
		exit(1);
	}
	while (wait(&status) != pid)
		;
}
