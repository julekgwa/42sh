/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_terminal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:32:58 by goisetsi          #+#    #+#             */
/*   Updated: 2016/09/06 10:03:25 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_init_keyboard(struct termios *term, int *ac, char ***av)
{
	(void)ac;
	(void)av;
	if (tgetent(NULL, getenv("TERM")) < 1)
		return (0);
	if (tcgetattr(0, term) == -1)
		return (0);
	term->c_lflag &= ~(ECHO | ECHOE | ICANON);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, term) == -1)
		return (0);
	tputs(tgetstr("ti", NULL), 1, ft_myputchar);
	tputs(tgetstr("vi", NULL), 1, ft_myputchar);
	ft_clear_screen();
	return (1);
}

int		ft_close_keyboard(struct termios *term)
{
	term->c_lflag |= (ECHO | ECHOE | ICANON);
	if (tcsetattr(0, 0, term) == -1)
		return (0);
	tputs(tgetstr("te", NULL), 1, ft_myputchar);
	tputs(tgetstr("ve", NULL), 1, ft_myputchar);
	return (1);
}

void	prompt_display(t_stack *hist)
{
	ft_putstr(GRN);
	if (hist->echo_prompt == 0)
		ft_putstr(hist->ps1);
	else
		ft_putstr("quotes>");
	ft_putchar(' ');
	ft_putstr(RESET);
}

int		ft_function_keys(char *key_pressed)
{
	char	*key;

	key = key_pressed + 1;
	if (ft_strequ(key, "OP"))
		ft_putendl("F1");
	else if (ft_strequ(key, "OQ"))
		ft_putendl("F2");
	else if (ft_strequ(key, "OR"))
		ft_putendl("F3");
	else if (ft_strequ(key, "OS"))
		ft_putendl("F4");
	else if (ft_strequ(key, "[15~"))
		ft_putendl("F5");
	else
		return (0);
	return (1);
}

void	ft_delete_lines(char *comm)
{
	int		i;

	i = ft_check_lines(comm);
	while (i > 0)
	{
		ft_putstr("\33[2K\r");
		ft_putstr("\33[A\r");
		ft_putstr("\33[2K\r");
		i--;
	}
}
