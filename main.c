/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:05:37 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/13 22:51:53 by yquaro           ###   ########.fr       */
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


void					parse_command(char *cmd) // move to check_for semicolon when hashtable is ready
{
	write(1, cmd, ft_strlen(cmd));
	write(1, "\n", 1);
	// if (i = check_hashtable(cmd) == 0)
	// 	check_env_path();
	// else
	// 	launch_builtin(i);
	// if (ft_strncmp(cmd, "cd", 3) == 0)								// restruct for hashtabs
	// 	cmd_cd();
	// else if (ft_strncmp(cmd, "echo", 5) == 0)
	// 	cmd_echo();
	// else if (ft_strncmp(cmd, "exit", 5) == 0)
	// {
	// 	write(1, "See you!\n", 9);
	// 	exit(0);
	// }
	// else if (ft_strncmp(cmd, "env", 4) == 0)
	// 	cmd_env();
	// else if (ft_strncmp(cmd, "setenv", 7) == 0)
	// 	cmd_setenv();
	// else if (ft_strncmp(cmd, "unsetenv", 9) == 0)
	// 	cmd_unsetenv();
	// else
	// 	check_env_path(cmd);
}

void					check_for_semicolon(const char *line) // rename to parse_command
{
	char				**cmd;

	cmd = ft_strsplit(line, ';');
	while (*cmd != NULL)
	{
		parse_command(*cmd);
		cmd++;
	}
}

void 					handle_ctrl_c(int sig) 
{ 
    // printf("Caught signal %d\n", sig);
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
	check_for_semicolon((const char *)buff);
	ft_strdel(&buff);
}

// # include <curses.h>

int							main(int argc, char **argv, char **envv)
{
	init_envv((const char **)envv);
    display_prompt();
    while (1)
    {
    	get_input();
    	display_prompt();
    }


	// char * env [] = {"HOME = / usr / home", "LOGNAME = home", (char *) 0};
	// char * cmd [] = {"pwd", (char *) 0};
	// pid_t p;

 //   	printf("process: pid = %d ppid = %d\n\n\n", getpid(), getppid());

	// display_prompt();

    return (0);
}
