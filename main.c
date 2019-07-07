/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:05:37 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/05 16:30:22 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
		cmd = screening((const char *)level[i]);
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

void 					handle_ctrl_c(int sig)
{
	write(1, "\n", 1);
	display_prompt();
}

void					get_input(void)
{
	char		*buff;
	char		symb;
	int			i;
	int			buff_counter;
	int			ret;

	i = 0;
	signal(SIGINT, handle_ctrl_c);
	buff_counter = MAIN_BUFF_SIZE;
	if ((buff = (char *)ft_memalloc(sizeof(char) * buff_counter)) == NULL)
	{
		printf("error exit : main.c->%d\n", __LINE__);
		exit(-1);
	}
	while ((ret = read(0, &symb, 1)) > 0)
	{
		if (symb == '\n')
			break ;
		if (i == buff_counter - 1)
		{
			buff_counter += MAIN_BUFF_SIZE;
			if ((buff = ft_realloc(buff, buff_counter)) == NULL)
			{
				printf("error exit : main.c->get_input");
				exit(1);
			}
		}
		buff[i++] = symb;
	}
	if (ret == 0)
	{
		ft_strdel(&buff);
		ft_putendl("exit");
		exit(0);
	}
	buff[i] = '\0';
	parse_command(buff);
	ft_strdel(&buff);
}

int							main(int argc, char **argv, char **envv)
{
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
