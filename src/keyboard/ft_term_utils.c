/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:32:58 by goisetsi          #+#    #+#             */
/*   Updated: 2016/09/05 07:38:21 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_myputchar(int c)
{
	return (write(2, &c, 1));
}

void		ft_clear_screen(void)
{
	tputs(tgetstr("cl", NULL), 1, ft_myputchar);
}

t_stack		*ft_create_stack(char **envp)
{
	t_stack	*stack;
	int		size;
	char	*hist_file;

	hist_file = "/.42sh_history";
	if (ft_get_env("$HISTSIZE", envp))
		size = ft_atoi(ft_get_env("$HISTSIZE", envp));
	else
		size = HISTSIZE;
	stack = (t_stack *)malloc(sizeof(t_stack) * size);
	if (stack)
	{
		stack->list = (char **)malloc(sizeof(char) * size);
		stack->size = 0;
		stack->hist_count = 0;
		stack->ctrl_r = 0;
		stack->click_flag = 0;
		stack->envp = envp;
		stack->hist_file = ft_strjoin(ft_get_env("$HOME", envp), hist_file);
		stack->capacity = size;
	}
	return (stack);
}

void		ft_push(t_stack *stack, char *hist)
{
	if (stack->size == stack->capacity)
		return ;
	stack->list[stack->size++] = hist;
	stack->hist_count++;
}

void		ft_exclamation(char **comm, t_stack *hist, int *pos)
{
	if (ft_strequ(*comm, "!!") || ft_strequ(*comm, "!-1"))
		*comm = ft_get_prev_hist(*hist);
	else
		*comm = ft_get_hist(*comm, *hist);
	*pos = ft_strlen(*comm);
	ft_cursor(*comm, *pos + 1, hist);
}
