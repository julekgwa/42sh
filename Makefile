# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktshikot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/06 14:38:52 by ktshikot          #+#    #+#              #
#    Updated: 2016/08/12 13:06:59 by goisetsi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh
SRC = ./src/main.c ./src/commands/ft_commands.c ./src/utils/ft_ctrl_c_signal_handler.c \
	./src/commands/ft_cd.c ./src/commands/ft_echo.c ./src/env/ft_env.c \
	./src/utils/ft_utils.c ./src/exec/ft_get_data.c ./src/history/ft_history.c \
	./src/utils/ft_more_utils.c ./src/signals/ft_signals.c\
	./src/keyboard/ft_ctrl_terminal.c ./src/keyboard/ft_term_utils.c \
	./src/pipe/ft_manage_pipes.c ./src/buffer/ft_manage_buff.c \
	./src/history/ft_hist_utils.c ./src/env/ft_env_utils.c ./src/history/ft_manage_hist.c \
	./src/commands/ft_cmd_utils.c ./src/history/ft_bck_i_search.c ./src/utils/ft_misc.c \
	./src/keyboard/ft_key_press.c ./src/redirection/ft_redirection.c \
src/list/list_rotate.c \
src/list/list_swap.c \
src/list/list_helper.c \
src/list/list_pop.c \
src/list/list_push.c \
src/list/list_delete.c \
src/list/list_qsort.c \
src/autocomplete/split.c \
src/autocomplete/cols.c \
src/autocomplete/tab.c \
src/autocomplete/screen.c \
src/autocomplete/options.c \
src/autocomplete/cmd.c \
src/autocomplete/path.c \


OBJECT = main.o ft_commands.o ft_ctrl_c_signal_handler.o ft_cd.o ft_echo.o \
	ft_env.o ft_utils.o ft_get_data.o ft_more_utils.o ft_ctrl_terminal.o \
	ft_term_utils.o ft_manage_pipes.o ft_manage_buff.o \
	ft_history.o ft_signals.o ft_hist_utils.o ft_env_utils.o ft_manage_hist.o \
	ft_cmd_utils.o ft_bck_i_search.o ft_misc.o ft_key_press.o ft_redirection.o \
list_rotate.o \
list_swap.o \
list_helper.o \
list_pop.o \
list_push.o \
list_delete.o \
list_qsort.o \
split.o \
cols.o \
tab.o \
screen.o \
options.o \
cmd.o \
path.o \

FLAGS = #-Wall -Wextra -Werror -g3
OPTIONS = -c -I libft/includes/ -I includes/

all: $(NAME)

$(NAME):
	@make -C libft/
	@gcc $(FLAGS) $(OPTIONS) $(SRC)
	@gcc -o $(NAME) $(OBJECT) -L libft/ -lft -ltermcap
	@chmod 111 $(NAME)
	@echo "\x1B[32mCompiled project.\x1B[0m"

clean:
	@make -C libft/ clean
	@/bin/rm -f $(OBJECT)
	@echo "\x1B[32mCleaned up object files.\x1B[0m"

fclean: clean
		@make -C libft/ fclean
		@/bin/rm -f $(NAME)
		@echo "\x1B[32mCleaned up compiled files.\x1B[0m"

re: fclean	all
