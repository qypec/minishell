# include "header.h"



// int					is_ctrl_c(const char symb)
// {
// 	if (symb == 3)
// 		return (1);
// 	return (0);
// }

void 					handle_sigint(int sig) 
{ 
    printf("Caught signal %d\n", sig);
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
	// char * env [] = {"HOME = / usr / home", "LOGNAME = home", (char *) 0};
	// char * cmd [] = {"ls", (char *) 0};
	signal(SIGINT, handle_sigint);
	buff = (char *)ft_memalloc(sizeof(char) * BUFF_SIZE);
	buff_counter = BUFF_SIZE;
	while ((ret = read(0, &symb, 1)))
	{
		if (symb == '\n')
		{
			printf("break\n");
			break ;
		}
		if (buff_counter <= i)
		{
			buff = ft_realloc(buff, buff_counter + BUFF_SIZE);
			buff_counter += BUFF_SIZE;
		}
		buff[i++] = symb;
	}

	// pid_t p;

	// printf("process: pid = %d\n ppid = %d\n", getpid(), getppid());
	// p = fork();
	// if (buff[0] == 'l' && buff[1] == 's')
	// 	execve("/bin/ls", cmd, env);
	// printf("process: pid = %d\n ppid = %d\n", getpid(), getppid());
	// printf("hello\n");
	// printf("buff = %s\n", buff);
	// parse_input(&buff);
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
	// if ((p = fork()) == 0)
	// {
	// 	printf("process: p = %d\n", p);
	// 	printf("process: pid = %d ppid = %d\n\n", getpid(), getppid());
	// 	execve("/bin/pwd", cmd, envv);
	// }
	// else
	// {
	// 	wait(NULL);
	// 	printf("process: p = %d\n", p);
	// 	printf("process: pid = %d ppid = %d\n", getpid(), getppid());
	// }
	// display_prompt();

    return (0);
}
