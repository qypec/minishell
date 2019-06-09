# include "header.h"

void					display_git_prompt(char *branch_name)
{
	// ft_printf("\033[0;32m(mini)\x1b[35m -> (%s)\x1b[0m ", branch_name);
	write(1, "\033[0;32m(mini)\x1b[35m -> (", 23);
	write(1, branch_name, ft_strlen(branch_name));
	write(1, ")\x1b[0m ", 6);
}

void					display_default_prompt(void)
{
	write(1, "\033[0;32m(mini)\033[0m", 18);
}

char					*parse_branch_name(const char *buff)
{
	int			counter;
	int			len;
	int			i;
	char		*result;

	i = 0;
	counter = ft_strlen(buff);
	while (buff[counter--] != '/')
		i++;
	if ((result = (char *)ft_memalloc(sizeof(char) * (i - 1))) == NULL)
		exit(1);
	i = 0;
	counter++;
	while (buff[++counter] != '\n' && buff[counter] != '\0')
		result[i++] = buff[counter];
	result[i] = '\0';
	return (result);
}

char				*get_git_branch_name(void)
{
	int			fd;
	char		*buff;
	char		*result;
	int			i;

	i = 1;
	if ((fd = open(GIT_BRANCH_NAME_FILE, O_RDONLY)) < 0)
		return (NULL); // file not exist
	if ((buff = (char *)ft_memalloc(sizeof(char) * BUFF_BRANCH_NAME_SIZE)) == NULL)
		exit(1);
	while (read(fd, buff, BUFF_BRANCH_NAME_SIZE) > 0)
		buff = ft_realloc(buff, BUFF_BRANCH_NAME_SIZE * (i++));
	result = parse_branch_name(buff);
	ft_strdel(&buff);
	return (result);
}

void				display_prompt(void)
{
	char			*branch_name;
	
	// нужно написать быстрый чекер на измененный файл .git/HEAD
	branch_name = get_git_branch_name();
	if (branch_name == NULL)
	{
		display_default_prompt();
		return ;
	}
	display_git_prompt(branch_name);
	ft_strdel(&branch_name);
}