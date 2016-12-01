#include "minishell.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

t_node	*get_files(const char *file_name)
{
	DIR				*dir;
	struct dirent	*dp;
	char			p_error[50];
	char			path[4096];
	t_node			*root;

	root = 0;
	if (!(dir = opendir(file_name)))
	{
		ft_strcpy(p_error, "\nminishell: cannot access ");
		ft_strcat(p_error, file_name);
		ft_putstr(p_error);
		exit(0);
	}
	while ((dp = readdir(dir)) != NULL)
		push_back(&root, dp->d_name);
	free(dp);
	closedir(dir);
    return (root);
}

static void    search_dir(char *path, char *last, char **comm)
{
    t_node  *root;
    t_node  *ptr;
	t_node	*tmp;
    int     match_count;
    t_node  *match_list;
	int		len;

    match_count = 0;
	len = 0;
    root = 0;
    ptr = 0;
    match_list = 0;
    root = get_files(path);
    ptr = root;
    while (ptr)
    {
		if (ft_strncmp(last, (char*)ptr->data, ft_strlen(last)) == 0)
        {
            match_count++;
            push_back(&match_list, (char*)ptr->data);
        }
        ptr = ptr->next;
    }
	ptr = root;
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		free(ptr);
	}
	root = 0;
	len = ft_strlen(last);
	free(last);
    matches(len, match_count, match_list, comm);
}

void    search_path(char *last, char **buffer)
{
    if (strrchr(last, '/') != NULL)
        ft_putstr("Search deeper paths\n");
    else
        search_dir(".", last, buffer);
}

