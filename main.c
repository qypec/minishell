# include "header.h"



// int					is_ctrl_c(const char symb)
// {
// 	if (symb == 3)
// 		return (1);
// 	return (0);
// }

int						is_exit(const char *buff)
{
	if (ft_strncmp(buff, "exit", 4) == 0 && buff[4] == '\0')
		return (1);
	return (0);
}

void					parse_command(const char *buff)
{
// 	char * env [] = {"HOME = / usr / home", "LOGNAME = home", (char *) 0};
// 	char * cmd [] = {"ls", (char *) 0};
// 	pid_t			p;

// 	p = fork();
// 	if ((p = fork()) == 0)
// 		execve("/bin/pwd", cmd, envv);
// 	else
// 		wait(NULL);
	if (is_exit(buff) == 1)
	{
		write(1, "See you!\n", 9);
		exit(0);
	}
}

void 					handle_sigint(int sig) 
{ 
    // printf("Caught signal %d\n", sig);
    write(1, "\n", 1);
    display_prompt();
} 
  

void					get_input(void)
{
	char		*buff;
	char		symb;
	int			ret;
	int			i;
	int			buff_counter;

	i = 0;

	signal(SIGINT, handle_sigint);
	buff = (char *)ft_memalloc(sizeof(char) * BUFF_SIZE);
	buff_counter = BUFF_SIZE;
	while ((ret = read(0, &symb, 1)))
	{
		if (symb == '\n')
		{
			// write(1, "break\n", 6);
			break ;
		}
		if (buff_counter <= i)
		{
			buff = ft_realloc(buff, buff_counter + BUFF_SIZE);
			buff_counter += BUFF_SIZE;
		}
		buff[i++] = symb;
	}
	parse_command(buff);
	ft_strdel(&buff);
}

# include <curses.h>

int							main(int argc, char **argv, char **envv)
{
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
