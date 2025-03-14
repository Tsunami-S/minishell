#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haito <haito@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/07 06:53:24 by haito             #+#    #+#              #
#    Updated: 2025/03/15 02:13:18 by haito            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJDIR = objs
SRCS =	minishell_main.c \
		minishell_init.c \
		minishell_free.c \
		minishell_error.c \
		minishell_utils.c \
		minishell_utils2.c \
		minishell_utils3.c \
		find_brackets_pair.c \
		sep_input_to_cmds.c \
		handle_node.c \
		trim_space.c \
		pipe.c \
		fork.c \
		ft_split.c \
		export_utils.c \
		init_varlist.c \
		replace_vars.c \
		replace_vars_count.c \
		replace_vars_split.c \
		tokenizer.c \
		expander.c \
		ft_eprintf/ft_eprintf.c \
		ft_eprintf/ft_eprintf_option.c \
		ft_eprintf/ft_eprintf_option2.c \
		ft_eprintf/ft_eprintf_utils.c \
		ft_eprintf/ft_eprintf_utils2.c

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
INC = -I . -I ft_eprintf

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -l readline -o $(NAME)

bonus: $(NAME)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

$(OBJDIR)/%.o:%.c
	mkdir -p $(@D)
	$(CC) $(WFLAG) $(IFLAG) -c $< -o $@
