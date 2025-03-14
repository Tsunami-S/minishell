# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haito <haito@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/07 06:53:24 by haito             #+#    #+#              #
#    Updated: 2025/03/14 17:01:59 by tssaito          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
		ft_split.c \
		export_utils.c \
		init_varlist.c \
		replace_vars.c \
		replace_envp_utils.c \
		replace_envp_utils2.c \
		tokenizer.c \
		expander.c

		
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
INC = -I .

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
