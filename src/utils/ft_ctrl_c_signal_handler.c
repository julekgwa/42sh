/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_c_signal_handler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:35:34 by goisetsi          #+#    #+#             */
/*   Updated: 2016/09/06 15:54:00 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_c_signal_handler(int signum)
{
	exit(signum);
}

void	ft_print_error(char *erro, int errno)
{
	if (errno == 4)
	{
		ft_putstr("cd: ");
		ft_putstr("no such file or directory: ");
		ft_putendl(erro);
		return ;
	}
	else if (errno == 5)
	{
		ft_putstr("\n42sh: event not found: ");
		ft_putendl(erro);
		return ;
	}
	ft_putstr("42sh: ");
	ft_putstr(erro);
	if (errno == 0)
		ft_putstr(": command not found...\n");
	else if (errno == 1)
		ft_putstr(": is a directory...\n");
	else if (errno == 2)
		ft_putstr(": permition denied....\n");
}

char	*ft_remove_tabs(char *tab)
{
	char	*temp;
	int		i;

	temp = (char *)malloc(sizeof(temp));
	i = 0;
	while (*tab)
	{
		if (*tab != '\t')
		{
			temp[i] = *tab;
			i++;
		}
		tab++;
	}
	temp[i] = '\0';
	return (temp);
}

void	prompt(t_cmd *command, t_stack *hist)
{
	char			*comm;
	char			*buf;
	int				pos;

	ft_set_terminal(hist->envp);
	hist->ps1 = ft_get_env("$PS1", hist->envp);
	buf = ft_memalloc(GET_C_BUFF_SIZE);
	comm = ft_memalloc(4092);
	pos = 0;
	prompt_display(hist);
	tputs(tgetstr("so", NULL), 1, ft_myputchar);
	ft_putchar(' ');
	tputs(tgetstr("se", NULL), 1, ft_myputchar);
	command->get_line = ft_remove_tabs(ft_build_comm(hist, comm, buf, pos));
}
