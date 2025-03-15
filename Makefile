#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haito <haito@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/07 06:53:24 by haito             #+#    #+#              #
#    Updated: 2025/03/15 20:06:42 by tssaito          ###   ########.fr        #
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
		minishell_utils4.c \
		find_brackets_pair.c \
		sep_input_to_cmds.c \
		handle_node.c \
		trim_space.c \
		pipe.c \
		fork.c \
		ft_split.c \
		export_utils.c \
		init_varlist.c \
		expander/expander.c \
		expander/tokenizer.c \
		expander/replace_vars.c \
		expander/replace_vars_count.c \
		expander/replace_vars_split.c \
		ft_eprintf/ft_eprintf.c \
		ft_eprintf/ft_eprintf_option.c \
		ft_eprintf/ft_eprintf_option2.c \
		ft_eprintf/ft_eprintf_utils.c \
		ft_eprintf/ft_eprintf_utils2.c \
		continue_child/continue_child.c \
		continue_child/exit_child.c \
		continue_child/make_cmds.c \
		continue_child/make_envp.c \
		continue_child/make_fullpath.c \
		continue_child/redirect.c \
		continue_child/here_doc.c \
		free_utils.c 

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
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
