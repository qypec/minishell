/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screening.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:45:43 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/02 22:09:41 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int						is_nonscreening_sign(const char *cmd, int i, char sign)
{
	if (i != 0)
	{
		if (cmd[i] == sign && cmd[i - 1] != '\\')
			return (1);
		else
			return (0);
	}
	else if (cmd[i] == sign)
		return (1);
	return (0);
}

char					**screening(const char *str)
{
	t_list				*head;
	char				*buff;
	int					buff_counter;
	int					i;

	buff_counter = BUFF_SIZE;
	if ((buff = (char *)ft_memalloc(sizeof(char) * buff_counter)) == NULL)
	{
		printf("error exit : screening.c->%d\n", __LINE__);
		exit(-1);
	}
	while (str[i] != "\0")
	{
		if (str[i] == ' ')
		if (i == buff_counter - 1)
		{
			if ((buff = ft_realloc(buff, buff_counter + BUFF_SIZE)) == NULL)
			{
				printf("error exit : main.c->get_input");
				exit(1);
			}
			buff_counter += BUFF_SIZE;
		}
		i++;
	}
}
