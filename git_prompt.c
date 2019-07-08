/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:18:47 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/07 06:32:37 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						is_gitzone(void)
{
	int					pwd_number;
	int					gitdir_number;
	int					size_gitdir_without_name;

	if ((pwd_number = find_((const char **)g_envv, "PWD=")) == -1)
		return (0);
	if ((gitdir_number = find_((const char **)g_envv, NAME_GIT_ENVVAR)) == -1)
		return (0);
	size_gitdir_without_name = ft_strlen(g_envv[gitdir_number] + \
								ft_strlen(NAME_GIT_ENVVAR));
	if (ft_strncmp((const char *)(g_envv[pwd_number] + ft_strlen("PWD=")), \
		(const char *)(g_envv[gitdir_number] + ft_strlen(NAME_GIT_ENVVAR)), \
		size_gitdir_without_name) == 0)
		return (1);
	return (0);
}

static char				*parse_branch_name(const char *buff)
{
	int			counter;
	int			i;
	char		*result;

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

char					*get_git_branch_name(void)
{
	int			fd;
	char		*buff;
	char		*result;
	int			i;
	char		*gitdir_path;

	i = find_((const char **)g_envv, NAME_GIT_ENVVAR);
	gitdir_path = (char *)ft_memalloc(sizeof(char) * \
		(ft_strlen(g_envv[i] + ft_strlen(NAME_GIT_ENVVAR)) + \
			ft_strlen("/") + ft_strlen(GIT_BRANCH_NAME_FILE) + 1));
	ft_strglue(&gitdir_path, g_envv[i] + ft_strlen(NAME_GIT_ENVVAR), "/");
	ft_strglue(&gitdir_path, GIT_BRANCH_NAME_FILE, "\0");
	if ((fd = open(gitdir_path, O_RDONLY)) < 0)
		return (NULL);
	if ((buff = (char *)ft_memalloc(sizeof(char) * \
						BUFF_BRANCH_NAME_SIZE)) == NULL)
		exit(1);
	i = 1;
	while (read(fd, buff, BUFF_BRANCH_NAME_SIZE) > 0)
		buff = ft_realloc(buff, BUFF_BRANCH_NAME_SIZE * (i++));
	result = parse_branch_name(buff);
	ft_strdel(&buff);
	ft_strdel(&gitdir_path);
	close(fd);
	return (result);
}

int						gitdir_exist(void)
{
	int				fd;

	if ((fd = open(GIT_BRANCH_NAME_FILE, O_RDONLY)) < 0)
		return (0);
	else
	{
		close(fd);
		return (1);
	}
}

void					add_gitdirpath_to_envv(const char **envv)
{
	int					i;

	if (gitdir_exist() == 1)
	{
		if ((i = find_((const char **)envv, "PWD=")) == -1)
			exit(-1);
		g_envv[0] = (char *)ft_memalloc(sizeof(char) * \
				(ft_strlen(envv[i] + 4) + ft_strlen(NAME_GIT_ENVVAR) + 1));
		ft_strglue(&g_envv[0], NAME_GIT_ENVVAR, envv[i] + 4);
	}
	else
		g_envv[0] = NAME_GIT_ENVVAR;
}
