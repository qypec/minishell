/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 20:29:38 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/01 21:15:53 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int				get_len(const char **cmd, int i)
{
	int					j;
	int					len;
	int					space_counter;

	len = 0;
	space_counter = -1;
	while (cmd[i] != NULL)
	{
		space_counter++;
		j = 0;
		while (cmd[i][j++] != '\0')
			len++;
		i++;
	}
	if (space_counter != -1)
		len += space_counter;
	return (len);
}

void					cmd_echo(const char **cmd)
{
	int					flag_n;
	int					i;
	int					j;
	int					len;
	char				*buff;

	flag_n = 0;
	i = 1;
	if (ft_strcmp(cmd[i], "-n") == 0)
	{
		flag_n = 1;
		i++;
	}
	len = get_len(cmd, i) + 1 + 1; // for percent
	if ((buff = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
	{
		printf("error exit : cmd_echo.c->%d\n", __LINE__);
		exit(-1);
	}
	while (cmd[i] != NULL)
	{
		if (cmd[i + 1] != NULL)
			ft_strglue(&buff, cmd[i++], " ");
		else
			ft_strglue(&buff, cmd[i++], "\0");
	}
	if (flag_n == 1)
		ft_strglue(&buff, "%", "\0");
	ft_putendl(buff);
	ft_strdel(&buff);
}
