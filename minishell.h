/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:05:57 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/23 22:18:33 by yquaro           ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/stat.h>

# define		BUFF_SIZE					9

# define		GIT_BRANCH_NAME_FILE		".git/HEAD"
# define		BUFF_BRANCH_NAME_SIZE		30
# define		COMMAND_NOT_FOUND			1
# define		NO_SUCH_DIR					2

char				**g_envv;
int					g_envvlen;
t_map				*g_envvpath;

void					display_prompt(void);
void					init_envv(const char **envv);
void					init_htab_envpath();
void					bust(const char *cmd_name, int flag);

int						is_builtin_launch(const char **cmd);
void					check_envpath(const char **cmd);

void					cmd_cd(const char **cmd);
void					cmd_exit(char *line, char **level, char **cmd);


# endif
