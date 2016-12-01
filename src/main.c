/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:26:38 by goisetsi          #+#    #+#             */
/*   Updated: 2016/09/06 16:02:12 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_intermidiate(char **comm, int *pos, t_stack *hist, char *buf)
{
	if (buf[0] == 12)
		ft_ctrl_l(*comm, *pos, hist);
	if (buf[0] == 16)
	{
		*comm = ft_get_prev_hist(*hist);
		*pos = ft_strlen(*comm);
	}
}

char	*ft_build_comm(t_stack *hist, char *comm, char *buf, int pos)
{
	int	ret;

	while (42)
	{
		ret = read(0, buf, 4);
		buf[ret] = '\0';
		if (buf[ret - 1] == '\n')
			if (ft_enter_key(&comm, hist, &pos))
				break ;
		if (buf[0] == '\t')
			handle_tab(&comm);
		else if ((buf[0] == 12) || (buf[0] == 16))
			ft_intermidiate(&comm, &pos, hist, buf);
		else if (buf[0] == 18 && hist->echo_prompt == 0)
			hist->ctrl_r = 1;
		else if (ft_ctrl_b_f(buf))
			ft_move_word(comm, &pos, buf);
		else if (ft_up_down(buf) && hist->echo_prompt == 0)
			manage_up_down(&buf, &comm, hist, &pos);
		else if (ft_edit_keys(buf, &pos, comm, hist) ||
			ft_nav_keys(buf, &pos, &comm, hist))
			;
		else if (ft_character_keys(buf) && buf[0] != 27)
			ft_process_buff(&comm, pos++, buf[0], hist);
		ft_cursor(comm, pos + 1, hist);
	}
	return (comm);
}

void	ft_initiate(t_stack *hist, char **envp)
{
	char			*shelvl;

	ft_init_hist(hist);
	shelvl = ft_get_env("$SHLVL", envp);
	ft_setenv("SHLVL", ft_itoa(ft_atoi(shelvl) + 1), 1, envp);
}

int		main(int ac, char **av, char **envp)
{
	struct termios	term;
	t_stack			hist;
	t_cmd			cmd;

	hist = *ft_create_stack(envp);
	ft_initiate(&hist, envp);
	ft_signal();
	ft_init_keyboard(&term, &ac, &av);
	while (42)
	{
		prompt(&cmd, &hist);
		if (ft_uneven(cmd.get_line))
			ft_complete(&cmd, hist.envp);
		if (!ft_strequ(cmd.get_line, ""))
		{
			ft_putchar('\n');
			cmd.user_comm = ft_strsplit(ft_remove_brackets(cmd.get_line), ' ');
			ft_pro_cmd(&cmd, envp, &term, &hist);
		}
		else
			ft_putchar('\n');
	}
	ft_close_keyboard(&term);
	return (0);
}
