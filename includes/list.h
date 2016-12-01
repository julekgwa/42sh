/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkekana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 17:46:51 by gkekana           #+#    #+#             */
/*   Updated: 2016/09/11 17:46:52 by gkekana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include <sys/ioctl.h>
# define ERROR -1

typedef	struct	s_node
{
	void			*data;
	struct s_node	*next;
}				t_node;

t_node	*create_node(void *data);
t_node	*delete_node(t_node *node);
void	delete_all_nodes(t_node **root);
void	push_back(t_node **head, void *data);
void	push_front(t_node **head, void *data);
void	pop_front(t_node **head);
void	pop_back(t_node **head);
int		count_nodes(t_node *list);
void	print_nodes(t_node *list);
t_node	*get_last(t_node *list);
t_node	*get_node(t_node *list, int position);
void	list_qsort(int count, t_node *list);
void	list_swap(t_node **list, int p1, int p2);
void	list_rotate(t_node **list);

void	search_cmd(void);
void	create_cols(t_node *list);
void	matches(int last, int count, t_node *list, char **comm);
void	search_path(char *last, char **buffer);
void	move_cursor(int start, int end);
void	clear_line(int end);
int		get_width();
void	handle_tab(char **comm);

t_node	*get_files(const char *file_name);

#endif
