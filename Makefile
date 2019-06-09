
FLAGS = -Wall -Wextra -Werror
SOURCE = main.c
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
	gcc -g main.c prompt.c -L. -lft -o minishell

clean:
	make -C libft/ clean
	rm -r libft.a

fclean: clean
	make -C libft/ fclean
	rm -r minishell

re: fclean all
