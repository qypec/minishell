# include "header.h"

void					display_prompt(void)
{
	write(1, "\033[0;32m(mini)\033[0m ", 18);
}

// int					is_ctrl_c(const char symb)
// {
// 	if (symb == 3)
// 		return (1);
// 	return (0);
// }

void				get_input(void)
{
	char		*buff;
	char		symb;
	int			ret;
	int			i;
	int			buff_counter;

	i = 0;
	buff = (char *)ft_memalloc(sizeof(char) * BUFF_SIZE);
	buff_counter = BUFF_SIZE;
	while ((ret = read(0, &symb, 1)))
	{
		// printf("print symb |%d|\n", symb);
		if (symb == '\n')
		{
			printf("break\n");
			break ;
		}
		// if (is_ctrl_c(symb))
		// {
		// 	printf("ctrl C\n");
		// 	break ;
		// }
		if (buff_counter <= i)
		{
			buff = ft_realloc(buff, buff_counter + BUFF_SIZE);
			buff_counter += BUFF_SIZE;
		}
		buff[i++] = symb;
	}
	// printf("buff = %s\n", buff);
	// parse_input(&buff);
	ft_strdel(&buff);
}

int					main(int argc, char **argv, char **envv)
{
    display_prompt();
    while (1)
    {
    	get_input();
    	display_prompt();
    }
    return (0);
}
