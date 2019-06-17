# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/13 21:16:45 by yquaro            #+#    #+#              #
#    Updated: 2019/06/18 02:30:49 by yquaro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# (ar rc)
# The c option makes you create a library if it is not available,
# and the r (replace) option replaces old object files with new versions.

# (ranlib)
# Adds a character index to the archive

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCES = environment.c main.c prompt.c
OBJECTS = environment.o main.o prompt.o
EXECUTABLE = minishell

LIBNAME = libft.a

all: $(EXECUTABLE)
$(EXECUTABLE):
	@make -C libft/ all
	$(CC) $(SOURCES) -L. -lft -o $(EXECUTABLE) # НЕ ЗАБЫТЬ ФЛАГИ!!!!
	
clean: fclean

fclean:
	@make -C libft/ fclean
	@rm $(EXECUTABLE)
	@rm $(LIBNAME)

re: fclean all