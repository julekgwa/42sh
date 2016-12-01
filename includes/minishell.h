/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goisetsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 17:23:09 by goisetsi          #+#    #+#             */
/*   Updated: 2016/09/06 16:09:35 by goisetsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "list.h"
# include <signal.h>
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>
# include <sys/stat.h>
# include <fcntl.h>
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"
#ifndef STRSTR
# define STRSTR ft_strstr
#endif
#ifndef SUB
# define SUB ft_strsub
#endif
#ifndef FULL
#define FULL ft_full_word
#endif
# define HISTSIZE 10000
# define KEYS *(unsigned int *)key_pressed

typedef struct  s_word_list
{
    char    **list;
    int     size;
}               t_word_list;

typedef struct	s_search
{
	char		*prev_match;
	char		*results;
	int			fail;
}				t_search;

typedef	struct 	s_search_hist
{
	char 		*haystack;
	char 		*needle;
	char 		*with;
	char 		*replace;
}				t_search_hist;

typedef struct	s_stack
{
	int			capacity;
	int			size;
	int			hist_count;
	char		**list;
	char		**envp;
	char		*ps1;
	char		*curr_line;
	char		*hist_file;
	int			click_flag;
	int			ctrl_r;
	int			echo_prompt;
	int			redirect;
	t_search	*search;
}				t_stack;

typedef struct	s_comms
{
	char		**user_comm;
	char		*get_line;
}				t_cmd;

t_word_list     split(const char *s, char c);
void			ft_cd(char **dir, char **envp, int dirflag);
char			*ft_pwd();
void			ft_echo(char *av, char **envp);
void			ft_complete(t_cmd *cmd, char **envp);
int				ft_uneven(char *str);
int				ft_end_with(char *str, char c);
int				ft_start_with(char *str, char c);
char			*ft_first_word(const char *s);
char			*ft_last_word(const char *s);
char			*ft_get_env(const char *env, char **env_list);
void			ft_ctrl_c_signal_handler(int signum);
void			ft_print_env(char **envp);
char			**ft_check_env(char **cmd, char **envp);
int				ft_array_len(char **arr);
int				ft_unsetenv(const char *env, char **envp);
int				ft_setenv(const char *env, const char *val, int ov, char **enp);
void			ft_set_envir(char **envp, char *str);
char			*ft_remove_qoutes(char *s);
char			*ft_rm_quotes(char *s);
void			ft_print_env(char **envp);
char			**ft_check_env(char **cmd, char **envp);
void			ft_unsetting_env(char *names, char **envp);
char			*ft_build_exec(char **envp, char **split);
int				ft_is_execute(char *command);
void			ft_execute(char *cmd, char **l_cmd, char *line, char **envp);
void			ft_print_error(char *erro, int errno);
void			ft_advanced_com(char **cmd, char *line, char **envp, t_stack *h);
int				ft_search_command(char *command);
void			ft_execute_commands(char **cmd, char *l, char **p, t_stack *hi);
char			*ft_get_str(char **av);
int				ft_myputchar(int c);
void			ft_clear_screen(void);
int				ft_init_keyboard(struct termios *term, int *ac, char ***av);
int				ft_close_keyboard(struct termios *term);
int				ft_function_keys(char *key_pressed);
int				ft_character_keys(char *key_pressed);
int				ft_edit_keys(char *key_pressed, int *pos, char *co, t_stack *h);
int				ft_nav_keys(char *key_pressed, int *pos, char **co, t_stack *h);
void			ft_echo_off(char *s, struct termios *term);
char			*ft_build_comm(t_stack *hist, char *comm, char *buf, int pos);
int				fork_pipes(int n, char **cmd, char **envp, int i);
int				ft_contains(char *str, char c);
void			ft_cursor(char *comm, int pos, t_stack *hist);
void			ft_process_buff(char **com, int pos, char c, t_stack *h);
t_stack			*ft_create_stack(char **envp);
void			ft_push(t_stack *stack, char *hist);
char			*ft_up(t_stack *stack);
char			*ft_down(t_stack *stack);
char			*ft_keys_up_down(char *key_pressed, t_stack *hist, int *pos);
int				ft_up_down(char *key_pressed);
void			ft_display_hist(t_stack *hist, char **history, int i, int lim);
char			*ft_get_hist(char *history, t_stack hist);
void			prompt(t_cmd *command, t_stack *hist);
void			ft_signalhandle(int num);
void			ft_signal(void);
void			init_main(int *ac, char ***av);
void			manage_up_down(char **buf, char **com, t_stack *hist, int *pos);
void			ft_ctrl_l(char *comm, int pos, t_stack *h);
void			ft_pro_cmd(t_cmd *c, char **en, struct termios *t, t_stack *hi);
int				ft_cmd_complete(char *cmd);
void			ft_init_hist(t_stack *hist);
void			ft_set_terminal(char **envp);
char			*ft_get_current_dir(char **envp);
void			ft_display_sp(int sp);
char			*ft_get_prev_hist(t_stack hist);
int				ft_ctrl_b_f(char *buf);
void			ft_move_word(char *cmd, int *pos, char *buf);
void			ft_write_hist(t_stack *hist);
void			ft_clear_hist(t_stack *hist);
char			*ft_search_replace(t_search_hist search, int i, int j, int k);
void			ft_man_search_replace(char **cmd, int *pos, t_stack hist);
char			*ft_remove_brackets(char *str);
void			ft_search_hist(char *cmd, t_stack hist, t_search *search, int found);
char			*ft_remove_tabs(char *tab);
void			prompt_display(t_stack *hist);
void			ft_display_cmd(char *cmd, int pos);
void			ft_bck_i_search(char *cmd, int pos, t_stack *hist);
int				ft_enter_key(char **comm, t_stack *hist, int *pos);
int				ft_is_dir(const char *path);
int				ft_chk_env(char ***tmp_cmd, char **envp, int i);
void			ft_exclamation(char **comm, t_stack *hist, int *pos);
int				ft_file_redirection(char **red, char **envp);
int				ft_is_redirect(char **cmd);
int				ft_arrow_pos(char **cmd);
char			**ft_remove_arrow(char **str);
char			ft_specila_char(char c);
int				ft_check_options(char opt, const char *options);
void			ft_delete_lines(char *comm);
int				ft_check_lines(char *comm);
void			ft_process_adv_cmd(char **cmd, char *line, t_stack *hist);
int				ft_printf(char *format, ...);

#endif
