/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:05:57 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/11 03:46:08 by yquaro           ###   ########.fr       */
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
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>

# define MAIN_BUFF_SIZE 9

# define YES 1
# define NO 0

# define GIT_BRANCH_NAME_FILE ".git/HEAD"
# define BUFF_BRANCH_NAME_SIZE 30
# define COMMAND_NOT_FOUND 1
# define NO_SUCH_DIR 2
# define NAME_GIT_ENVVAR "GITDIR="
# define SCREENING_BUFF_SIZE 30

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

char					**screening(const char *str);
void					screening_loop(const char *str, t_buff *buff, t_list **result, t_list *oper);
void					preprocessoring(t_buff *buff, const char *str, int *i);
int						is_nonscreening_sign(const char *cmd, int i, char sign);
void					wait_quote_from_input(t_buff *buff, t_list *oper, t_list **result);

void					cmd_cd(const char **cmd);
void					cmd_exit(char *line, char **level, char **cmd);
void					cmd_env(void);
void					cmd_unsetenv(const char *varname);
void					cmd_setenv(const char **cmd);
void					cmd_echo(const char **cmd);

#endif
