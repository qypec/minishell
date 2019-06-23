/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:05:57 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/21 17:11:37 by yquaro           ###   ########.fr       */
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

t_map				*g_envv;
int					g_envvlen;
t_map				*g_envvpath;

void				display_prompt(void);
void				init_envv(const char **envv);
void				init_htab_envpath();


# endif
