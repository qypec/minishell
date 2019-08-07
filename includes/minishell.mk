# Base variables for minishell

CC = gcc
CFLAGS = -g -c -Wall -Wextra -Werror
MINISHELL_H = -I ../includes/
COMPILING = $(CC) $(CFLAGS) $(MINISHELL_H)
EXECUTABLE = minishell
LIBNAME = libft.a
