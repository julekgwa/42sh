/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_more_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:35:34 by goisetsi          #+#    #+#             */
/*   Updated: 2016/08/07 17:35:42 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_contains(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_multi_com(char **split_com, char **envp, t_stack *hist)
{
	char	**tmp_com;

	while (*split_com)
	{
		tmp_com = ft_strsplit(*split_com, ' ');
		if (tmp_com)
			ft_advanced_com(tmp_com, *split_com, envp, hist);
		split_com++;
	}
}

void	ft_advanced_com(char **cmd, char *line, char **envp, t_stack *hist)
{
	char	**split_com;

	if (ft_contains(line, ';'))
	{
		split_com = ft_strsplit(line, ';');
		ft_multi_com(split_com, envp, hist);
	}
	else
	{
		if (!ft_chk_env(&cmd, envp, 0))
			return ;
		if (ft_contains(line, '>') || ft_contains(line, '|'))
			ft_execute(NULL, cmd, line, envp);
		else if ((**cmd == '/' || **cmd == '.') && ft_is_dir(cmd[0]) > 0)
			ft_print_error(cmd[0], 1);
		else if (ft_search_command(ft_strsplit(line, ' ')[0]))
			ft_execute_commands(cmd, line, envp, hist);
		else if (ft_build_exec(envp, cmd))
			ft_execute(ft_build_exec(envp, cmd), cmd, line, envp);
		else if (ft_is_execute(cmd[0]))
			ft_execute(cmd[0], cmd, line, envp);
		else
			ft_print_error(cmd[0], 0);
	}
}

char	*ft_last_word(const char *s)
{
	int		i;
	char	*last;
	int		j;

	i = 0;
	j = 0;
	last = (char *)malloc(sizeof(char) * ft_strlen(s));
	while (s[i])
		i++;
	i -= 1;
	while (s[i] == ' ' || s[i] == '\t')
		i--;
	while ((s[i] != ' ' && s[i] != '\t') && i >= 0)
		i--;
	i += 1;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
	{
		last[j] = s[i];
		i++;
		j++;
	}
	return (last);
}

char	*ft_first_word(const char *s)
{
	int		i;
	char	*first;
	int		j;

	i = 0;
	j = 0;
	first = (char *)malloc(sizeof(char) * ft_strlen(s));
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
	{
		first[j] = s[i];
		i++;
		j++;
	}
	return (first);
}
