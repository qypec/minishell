/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:05:37 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/23 13:19:38 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


	// char * cmd [] = {"ls", (char *)	 0};
	// pid_t			p;

	// p = fork();
	// if (p == 0)
	// 	execve("/bin/ls", cmd, envv);
	// else
	// 	wait(NULL);

// void					parse_command(const char *line)
// {
// 	char				**cmd;

// 	cmd = ft_strsplit(line, ';');
// 	while (*cmd != NULL)
// 	{
// 		if ((i = is_builtin_launch(cmd)) == 0)
// 			check_env_path(cmd);
// 		cmd++;
// 	}
// }

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

	i = 0;
	signal(SIGINT, handle_ctrl_c);
	buff = (char *)ft_memalloc(sizeof(char) * BUFF_SIZE);
	buff_counter = BUFF_SIZE;
	while (read(0, &symb, 1) > 0)
	{
		if (symb == '\n')
			break ;
		if (buff_counter <= i)
		{
			if ((buff = ft_realloc(buff, buff_counter + BUFF_SIZE)) == NULL)
				exit(1);
			buff_counter += BUFF_SIZE;
		}
		buff[i++] = symb;
	}
	buff[i] = '\0';
	// parse_command((const char *)buff);
	ft_strdel(&buff);
}

int							main(int argc, char **argv, char **envv)
{
	init_envv((const char **)envv);
	init_htab_envpath();
	ft_putmap(g_envvpath);
    // display_prompt();
    // while (1)
    // {
    // 	get_input();
    // 	display_prompt();
    // }


	// char * env [] = {"HOME = / usr / home", "LOGNAME = home", (char *) 0};
	// char * cmd [] = {"pwd", (char *) 0};
	// pid_t p;

 //   	printf("process: pid = %d ppid = %d\n\n\n", getpid(), getppid());

	// display_prompt();

    return (0);
}
