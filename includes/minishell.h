/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:05:57 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/10 13:49:04 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "../libft/includes/libft.h"
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
# define END_OF_FILE 0

# define DEFAULT_HOME_DIR "/Users/yquaro"
# define GIT_BRANCH_NAME_FILE ".git/HEAD"
# define BUFF_BRANCH_NAME_SIZE 30
# define COMMAND_NOT_FOUND 1
# define NO_SUCH_DIR 2
# define NAME_GIT_ENVVAR "GITDIR="
# define SCREENING_BUFF_SIZE 30

# define IS_ABSOLUTE_PATH(c) ((c == '/') ? 1 : 0)

char					**g_envv;
t_map					*g_envvpath;

void					display_prompt(void);
char					*gitdir_search(void);

void					init_global_envv(const char **envv);
void					init_hashtable_from_envvpath(void);
void					update_envvar_path(const char *cmd);
void					bust(const char *cmd_name, int flag);

void					*is_builtin(const char *builtin_name);
void					check_envpath(const char **cmd);
const char				*getvalue_envv(const char *var_name);
int						find_(const char **envv, const char *envvname);

char					**screening(const char *input_line);
int						is_quotes(char c);
int						is_nonscreening_sign(const char *cmd, int i, char sign);
void					screening_loop(const char *input_line, \
					t_buff *token, t_list **result, t_list *operator);
void					preprocessing_extension_characters(t_buff *token, \
										const char *input_line, int *i);
void					wait_quotes_from_input(t_buff *buff, t_list *oper, \
					t_list **result);

void					cmd_cd(const char **cmd);
void					cmd_exit(char *line, char **level, char **cmd);
void					cmd_env(void);
void					cmd_unsetenv(const char **cmd);
void					cmd_setenv(const char **cmd);
void					cmd_echo(const char **cmd);

void					execution(char *fullname, const char **cmd);

#endif
