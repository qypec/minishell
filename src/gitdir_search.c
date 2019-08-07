/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gitdir_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 08:16:12 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/07 15:41:42 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char				*get_path(char *current_path)
{
	char				*path_to_branch_name_file;
	int					len;

	len = ft_strlen(current_path) + ft_strlen("/") + \
		ft_strlen(GIT_BRANCH_NAME_FILE) + 1;
	if ((path_to_branch_name_file = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	ft_strglue(path_to_branch_name_file, current_path, "/", \
						GIT_BRANCH_NAME_FILE, NULL);
	return (path_to_branch_name_file);
}

static char				*cut_off_branch_name(const char *buff)
{
	int					counter;
	int					i;
	char				*result;

	i = 0;
	counter = ft_strlen(buff);
	while (buff[counter--] != '/')
		i++;
	if ((result = (char *)ft_memalloc(sizeof(char) * (i - 1))) == NULL)
		exit(1);
	i = 0;
	counter++;
	while (buff[++counter] != '\n' && buff[counter] != '\0')
		result[i++] = buff[counter];
	result[i] = '\0';
	return (result);
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
		ft_buffaddsymb(buff, symb);
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

char					*gitdir_search(void)
{
	char				*current_path;
	char				*stop_path;
	char				*path_to_branch_name_file;
	char				*branch_name;
	char				dir[PATH_MAX];

	branch_name = NULL;
	stop_path = ft_strdup("/");
	getcwd(dir, PATH_MAX);
	current_path = ft_strdup(dir);
	while (ft_strcmp(current_path, stop_path) != 0)
	{
		path_to_branch_name_file = get_path(current_path);
		if (access(path_to_branch_name_file, 0) == 0)
		{
			branch_name = get_branch_name(path_to_branch_name_file);
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
