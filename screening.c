/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screening.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:45:43 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/02 20:41:14 by yquaro           ###   ########.fr       */
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
	char				**cmd;
	char				**buff;
	int					buff_counter;
	int					i;

	if ((buff = (char **)malloc(sizeof(char) * BUFF_SIZE)) == NULL)
	{
		printf("error exit : screening.c->%d\n", __LINE__);
		exit(-1);
	}
	buff_counter = BUFF_SIZE;
	while (buff)
}
