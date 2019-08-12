/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:05:37 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/12 15:50:25 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				commands_interpretation(char *input_line)
{
	char				**commands_set;
	char				**command;
	void				(*launch_builtin)(const char **);
	int					i;

	i = 0;
	commands_set = ft_strsplit(input_line, ';');
	while (commands_set[i] != NULL)
	{
		command = screening((const char *)commands_set[i]);
		if (ft_strcmp("exit", command[0]) == 0)
			cmd_exit(input_line, commands_set, command);
		if ((launch_builtin = is_builtin(command[0])) != NULL)
			launch_builtin((const char **)command);
		else
			check_envpath((const char **)command);
		i++;
		ft_matrdel(&command);
	}
	ft_matrdel(&commands_set);
}

static void				ctrl_d_tracking(int ret, t_buff **buff)
{
	if (ret == END_OF_FILE)
	{
		ft_buffdel(buff);
		ft_mapdel(&g_envvpath);
		ft_matrdel(&g_envv);
		ft_printf("exit\n");
		exit(0);
	}
}

static void				user_input_loop(void)
{
	t_buff		*buff;
	char		symb;
	int			ret;

	buff = ft_buffinit(MAIN_BUFF_SIZE);
	while ((ret = read(0, &symb, 1)) > 0 && symb != '\n')
		ft_buffaddsymb(buff, symb);
	ctrl_c_tracking();
	ctrl_d_tracking(ret, &buff);
	commands_interpretation(buff->str);
	ft_buffdel(&buff);
}

int						main(int argc, char **argv, char **envv)
{
	argc = 0;
	argv = NULL;
	g_signalflag = 0;
	signal(SIGINT, handle_ctrl_c);
	init_global_envv((const char **)envv);
	init_hashtable_from_envvpath();
	while (1)
	{
		display_prompt();
		user_input_loop();
	}
	return (0);
}