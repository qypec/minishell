# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/14 13:54:33 by yquaro            #+#    #+#              #
#    Updated: 2019/06/18 17:05:01 by yquaro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -g -c -Wall -Wextra -Werror
SOURCES = ft_hashfunc.c ft_htabadd.c ft_mapnew.c ft_putmap.c ht_list.c \
			ft_htabdelone.c ft_htabfree.c ft_ishtabitem.c
OBJECTS = ft_hashfunc.o ft_htabadd.o ft_mapnew.o ft_putmap.o ht_list.o \
			ft_htabdelone.o ft_htabfree.o ft_ishtabitem.o

NAME = libhashtab.a

all: $(SOURCES) print_echo $(NAME)
	
print_echo:
	@echo \*\*\* Compiling ft_hashtab

.c.o:
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@mv $(NAME) ../lib/$(NAME)

fclean: 
	@rm ../lib/$(NAME)
	@rm *.o