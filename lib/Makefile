# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/07 15:11:54 by yquaro            #+#    #+#              #
#    Updated: 2019/08/07 15:30:27 by yquaro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ../includes/minishell.mk

CFLAGS = -g -Wall -Wextra -Werror
COMPILING = $(CC) $(CFLAGS) $(MINISHELL_H)

all:
	$(COMPILING) *.o $(LIBNAME) -o $(EXECUTABLE)
	@mv $(EXECUTABLE) ../$(EXECUTABLE)

clean:
	@rm -f *.o

fclean:
	@rm -f $(LIBNAME)