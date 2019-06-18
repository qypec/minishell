/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:05:57 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/18 05:20:47 by yquaro           ###   ########.fr       */
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

# define		BUFF_SIZE					9

# define		GIT_BRANCH_NAME_FILE		".git/HEAD"
# define		BUFF_BRANCH_NAME_SIZE		30
# define		EXTRA_MEMORY_FOR_SETENV		10

char				**g_envv;
int					g_envvlen;
ht_list				*g_htab;

void				display_prompt(void);
void				init_envv(const char **envv);
void				init_htab_envpath();


# endif
