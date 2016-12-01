/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:28:38 by goisetsi          #+#    #+#             */
/*   Updated: 2016/09/05 07:57:40 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_count_space(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			j++;
		i++;
	}
	return (j);
}

char	*ft_remove_qoutes(char *s)
{
	int	slen;

	if (!ft_start_with(s, '"') || !ft_end_with(s, '"'))
		return (s);
	if (*s == '"')
		s += 1;
	slen = ft_strlen(s);
	if (s[slen - 1] == '"')
		s[slen - 1] = '\0';
	return (s);
}

char	*ft_clean_str(char *s)
{
	char	*clean;
	int		i;
	int		j;

	if (!ft_start_with(s, '"') && !ft_end_with(s, '"'))
		return (s);
	clean = ft_memalloc(ft_strlen(s) + ft_count_space(s));
	i = 0;
	j = 0;
	if (clean)
	{
		while (s[i])
		{
			if (s[i] == ' ')
			{
				clean[j] = '\\';
				j++;
			}
			clean[j] = s[i];
			i++;
			j++;
		}
		s = clean;
	}
	return (s);
}

void	ft_modpwd(int f, char *oldpwd, char **envp)
{
	if ((f = 1))
	{
		ft_setenv("OLDPWD", oldpwd, 1, envp);
		ft_setenv("PWD", getcwd(oldpwd, 1024), 1, envp);
	}
}

void	ft_cd(char **directory, char **envp, int dirflag)
{
	char	*dir;
	char	oldpwd[1024];

	getcwd(oldpwd, 1024);
	dir = directory[1];
	if (dir == NULL || ft_strequ(dir, "~"))
		dirflag = chdir(ft_get_env("$HOME", envp));
	else if (ft_strncmp(dir, "~", 1) == 0 && ft_strlen(dir) > 1)
	{
		dir += 1;
		directory[1] = ft_strcat(ft_strdup(ft_get_env("$HOME", envp)), dir);
		ft_cd(directory, envp, 0);
	}
	else if (ft_strequ(dir, "-"))
		dirflag = chdir(ft_get_env("$OLDPWD", envp));
	else
	{
		dir = ft_remove_qoutes(ft_clean_str(dir));
		if ((dirflag = chdir(dir) == -1))
		{
			ft_print_error(dir, 4);
			return ;
		}
	}
	ft_modpwd(dirflag, oldpwd, envp);
}
