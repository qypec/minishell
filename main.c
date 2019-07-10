/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qypec <qypec@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:05:37 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/09 14:06:43 by qypec            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					parse_command(char *line)
{
	char				**level;
	char				**cmd;
	int					flag;
	int					i;

	level = ft_strsplit(line, ';');
	i = 0;
	while (level[i] != NULL)
	{
		// cmd = screening((const char *)level[i]);
		cmd = ft_strsplit(level[i], ' ');
		cmd = manage_expansions(cmd);
		if ((flag = is_builtin_launch((const char **)cmd)) == 0)
			check_envpath((const char **)cmd);
		else if (flag == -1)
			cmd_exit(line, level, cmd);
		i++;
		ft_matrixfree(&cmd);
	}
	ft_matrixfree(&level);
}

void					handle_ctrl_c(int sig)
{
	sig = 0;
	write(1, "\n", 1);
	display_prompt();
}

void					get_input(void)
{
	t_buff		*buff;
	char		symb;
	int			ret;

	signal(SIGINT, handle_ctrl_c);
	buff = ft_buffinit(MAIN_BUFF_SIZE);
	while ((ret = read(0, &symb, 1)) > 0)
	{
		if (symb == '\n')
			break ;
		ft_buffreload(buff);
		buff->str[(buff->i)++] = symb;
	}
	if (ret == 0)
	{
		ft_buffdel(&buff);
		ft_putendl("exit");
		exit(0);
	}
	buff->str[buff->i] = '\0';
	parse_command(buff->str);
	ft_buffdel(&buff);
}

int						main(int argc, char **argv, char **envv)
{
	argc = 0;
	argv = NULL;
	init_envv((const char **)envv);
	init_htab_envpath();
	display_prompt();
	while (1)
	{
		get_input();
		display_prompt();
	}
	return (0);
}
