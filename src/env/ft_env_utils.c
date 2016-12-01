/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 07:29:45 by julekgwa          #+#    #+#             */
/*   Updated: 2016/09/05 07:30:00 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_terminal(char **envp)
{
	char	*username;
	char	*machine_name;
	char	*cwd;
	char	*display;

	cwd = ft_get_current_dir(envp);
	username = ft_strjoin("[", ft_get_env("$USER", envp));
	ft_setenv("HOSTNAME", "jhb.42.fr", 1, envp);
	machine_name = ft_get_env("$HOSTNAME", envp);
	display = ft_strjoin(username, "@");
	display = ft_strjoin(display, machine_name);
	cwd = ft_strjoin(" ", cwd);
	cwd = ft_strjoin(cwd, "]");
	if (geteuid() == 0)
		cwd = ft_strjoin(cwd, "#");
	else
		cwd = ft_strjoin(cwd, "$");
	display = ft_strjoin(display, cwd);
	ft_setenv("PS1", display, 1, envp);
}

char	*ft_get_current_dir(char **envp)
{
	char	*cwd;
	int		i;
	char	*home;

	cwd = NULL;
	home = ft_get_env("$HOME", envp);
	cwd = getcwd(cwd, 1024);
	i = ft_strlen(cwd);
	if (ft_strequ(cwd, home))
		return ("~");
	if (ft_strequ(cwd, "/"))
		return ("/");
	while (i)
	{
		if (cwd[i] == '/')
			break ;
		i--;
	}
	i++;
	return (cwd + i);
}

void	ft_display_sp(int sp)
{
	int	i;

	i = 0;
	while (i < sp)
	{
		ft_putchar(' ');
		i++;
	}
}
