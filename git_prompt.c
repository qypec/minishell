/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 18:41:37 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/13 09:57:03 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char				*get_path(int indexof_gitenvvar)
{
	char				*path_to_branch_name_file;
	char				*path_to_gitdir;
	int					len;

	path_to_gitdir = g_envv[indexof_gitenvvar] + ft_strlen(NAME_GIT_ENVVAR);
	len = ft_strlen(path_to_gitdir) + ft_strlen("/") + \
			ft_strlen(GIT_BRANCH_NAME_FILE) + 1;
	if ((path_to_branch_name_file = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	ft_strglue(&path_to_branch_name_file, path_to_gitdir, "/");
	ft_strglue(&path_to_branch_name_file, GIT_BRANCH_NAME_FILE, "\0");
	return (path_to_branch_name_file);
}

char					*cut_off_branch_name(const char *buff)
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

static char				*get_branch_name(int indexof_gitenvvar)
{
	char				*path_to_branch_name_file;
	int					fd;
	t_buff				*buff;
	char				*branch_name;
	char				symb;

	path_to_branch_name_file = get_path(indexof_gitenvvar);
	if ((fd = open(path_to_branch_name_file, O_RDONLY)) == -1)
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
	ft_strdel(&path_to_branch_name_file);
	return (branch_name);
}

static int				is_git_envvar_zone()
{
	int					i;
	int					indexofpwd;

	if ((indexofpwd = find_((const char **)g_envv, "PWD=")) == -1)
		return (0);
	i = 0;
	while (g_envv[i] != NULL)
	{
		if ((ft_strncmp((const char *)g_envv[i], \
			NAME_GIT_ENVVAR, ft_strlen(NAME_GIT_ENVVAR)) == 0) \
			&& \
			(ft_strncmp(g_envv[i] + ft_strlen(NAME_GIT_ENVVAR), \
			g_envv[indexofpwd] + ft_strlen("PWD="), \
			ft_strlen(g_envv[indexofpwd] + ft_strlen("PWD="))) == 0))
			return (i);
		i++;
	}
	return (0);
}

char					*is_gitzone(void)
{
	int					indexof_gitenvvar;

	if ((indexof_gitenvvar = is_git_envvar_zone()) != 0)
		return (get_branch_name(indexof_gitenvvar));
	return (gitdir_search());
}
