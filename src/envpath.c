/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:25:48 by yquaro            #+#    #+#             */
/*   Updated: 2019/11/15 19:36:44 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Updates the structure of environment variables 
** if the PATH variable has changed.
**
** @param 		variable
** @return		N/A
*/

void					update_envvar_path(const char *variable)
{
	int					size;

	size = ft_strlen("PATH");
	if (ft_strncmp(variable, "PATH", size) == 0 && \
		(variable[size] == '\0' || variable[size] == '='))
	{
		ft_mapdel(&g_envvpath);
		init_hashtable_from_envvpath();
	}
}

/*
** Execution
**
** @param 		fullname	fullname from builtin	
** @param 		command		set of command and flags
** @return		N/A
*/

void					execution(const char *fullname, const char **command)
{
	pid_t				pid;

	if (bust(command[0], get_errorcode(fullname)) != 0)
		return ;
	if ((pid = fork()) == 0)
		execve(fullname, (char **)command, g_envv);
	else
		wait(&pid);
}

/*
** Runs executables located in this directory
**
** @param 		command		set of command and flags
** @return		N/A
*/

void					launch_executable_from_this_directory(\
													const char **command)
{
	const char			current_dir[PATH_MAX];
	const char			*fullname;

	getcwd((char *)current_dir, PATH_MAX);
	fullname = current_dir;
	ft_strglue((char *)fullname, command[0] + 1, NULL);
	execution(fullname, command);
}

/*
** Glues the full path to the file and its name
**
** @param 		builtin		name of bultin
** @return		fullname	name and path to it
*/

static char				*get_fullname(const char *builtin)
{
	int					len;
	char				*fullname;
	const char			*value;

	value = ft_mapvalue(g_envvpath, builtin);
	len = ft_strlen(value) + ft_strlen("/") + ft_strlen(builtin) + 1;
	if ((fullname = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	ft_strglue(fullname, value, "/", builtin, NULL);
	return (fullname);
}

/*
** Runs executables
**
** @param 		command		set of command and flags
** @return		N/A
*/

void					launch_executable(const char **command)
{
	char				*fullname;

	if (command[0][0] == '.')
		launch_executable_from_this_directory(command);
	else if (IS_ABSOLUTE_PATH(command[0][0]))
		execution(command[0], command);
	else
	{
		fullname = get_fullname(command[0]);
		execution(fullname, command);
		ft_strdel(&fullname);
	}
}
