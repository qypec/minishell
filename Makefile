# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/09 14:21:08 by yquaro            #+#    #+#              #
#    Updated: 2019/06/13 21:16:44 by yquaro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
SOURCE = main.c prompt.c environment.c
OBJS = *.o
OBJDIR = .obj
NAME = minishel.a

all:
	make -C libft/ re
	mv libft/libft.a libft.a
	# gcc -c $(SOURCE)  # не забыть про ФЛАГИ!!!!!
	# mkdir $(OBJDIR)
	# mv $(OBJS) $(OBJDIR)
	# ar rc $(NAME) $(OBJDIR)/$(OBJS) libft/$(OBJDIR)/*.o
	# ranlib $(NAME)
	gcc -g $(SOURCE) -L. -lft -o minishell

clean:
	make -C libft/ clean
	rm -r libft.a

fclean: clean
	make -C libft/ fclean
	rm -r minishell

re: fclean all
