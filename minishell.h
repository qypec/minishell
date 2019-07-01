/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:05:57 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/01 20:35:36 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>

# define				BUFF_SIZE					9

# define				GIT_BRANCH_NAME_FILE		".git/HEAD"
# define				BUFF_BRANCH_NAME_SIZE		30
# define				COMMAND_NOT_FOUND			1
# define				NO_SUCH_DIR					2
# define				NAME_GIT_ENVVAR				"GITDIR="

char					**g_envv;
t_map					*g_envvpath;



void					display_prompt(void);
char					*get_git_branch_name(void);
void					add_gitdirpath_to_envv(const char **envv);
int						gitdir_exist(void);
int						is_gitzone(void);

void					init_envv(const char **envv);
void					init_htab_envpath();
void					bust(const char *cmd_name, int flag);

int						is_builtin_launch(const char **cmd);
void					check_envpath(const char **cmd);
int						find_(const char **envv, const char *envvname);

char					**manage_expansions(char **cmd);

void					cmd_cd(const char **cmd);
void					cmd_exit(char *line, char **level, char **cmd);
void					cmd_env(void);
void					cmd_unsetenv(const char *varname);
void					cmd_setenv(const char **cmd);
void					cmd_echo(const char **cmd);

# endif
