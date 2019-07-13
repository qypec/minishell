/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gitdir_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 08:16:12 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/13 09:56:54 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char				*get_current_path(void)
{
	int					indexofpwd;
	char				*current_path;
	char				dir[PATH_MAX];

	if ((indexofpwd = find_((const char **)g_envv, "PWD=")) == -1)
	{
		getcwd(dir, PATH_MAX);
		current_path = ft_strdup(dir);
	}
	else
		current_path = ft_strdup(g_envv[indexofpwd] + ft_strlen("PWD="));
	return (current_path);
}

static char				*get_stop_path(void)
{
	int					indexofhome;
	char				*stop_path;

	if ((indexofhome = find_((const char **)g_envv, "HOME=")) == -1)
		stop_path = ft_strdup("/");
	else
		stop_path = ft_strdup(g_envv[indexofhome] + ft_strlen("HOME="));
	return (stop_path);
}

static char				*get_path(char *current_path)
{
	char				*path_to_branch_name_file;
	int					len;

	len = ft_strlen(current_path) + ft_strlen("/") + \
		ft_strlen(GIT_BRANCH_NAME_FILE) + 1;
	if ((path_to_branch_name_file = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	ft_strglue(&path_to_branch_name_file, current_path, "/");
	ft_strglue(&path_to_branch_name_file, GIT_BRANCH_NAME_FILE, "\0");
	return (path_to_branch_name_file);
}

static char				*get_branch_name(char *path)
{
	int					fd;
	t_buff				*buff;
	char				*branch_name;
	char				symb;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	buff = ft_buffinit(BUFF_BRANCH_NAME_SIZE);
	while (read(fd, &symb, 1) > 0)
	{
		ft_buffreload(buff);
		buff->str[(buff->i)++] = symb;
	}
	close(fd);
	branch_name = cut_off_branch_name((const char *)buff->str);
	ft_buffdel(&buff);
	return (branch_name);
}

static void				move_to_lower_level(char *current_path)
{
	int					i;

	i = ft_strlen(current_path);
	while (current_path[i] != '/')
		current_path[i--] = '\0';
	if (i != 0)
		current_path[i] = '\0';
}

static int				is_home_or_root_dir(char *current_path, char *stop_path)
{
	if (ft_strcmp(current_path, stop_path) == 0)
		return (1);
	return (0);
}

char					*gitdir_search(void)
{
	char				*current_path;
	char				*stop_path;
	char				*path_to_branch_name_file;
	char				*branch_name;

	branch_name = NULL;
	stop_path = get_stop_path();
	current_path = get_current_path();
	// printf("stop = %s\n", stop_path);
	// printf("current = %s\n", current_path);
	while (!is_home_or_root_dir(current_path, stop_path))
	{
		path_to_branch_name_file = get_path(current_path);
		// printf("path = %s\n", path_to_branch_name_file);
		if (access(path_to_branch_name_file, 0) == 0)
		{
			branch_name = get_branch_name(path_to_branch_name_file);
			// printf("after get_branch_name = %s\n", branch_name);
			ft_strdel(&path_to_branch_name_file);
			break ;
		}
		move_to_lower_level(current_path);
		ft_strdel(&path_to_branch_name_file);
	}
	ft_strdel(&stop_path);
	ft_strdel(&current_path);
	return (branch_name);
}
