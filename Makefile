# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hito <hito@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/07 06:53:24 by haito             #+#    #+#              #
#    Updated: 2025/03/19 18:30:48 by hito             ###   ########.fr        #
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
		minishell_utils4.c \
		minishell_utils5.c \
		builtin/builtin.c \
		builtin/builtin_error.c \
		builtin/builtin_set_stdio.c \
		builtin/builtin_redirect.c \
		builtin/builtin_here_doc.c \
		builtin/builtin_export.c \
		builtin/builtin_export_list.c \
		builtin/builtin_env.c \
		builtin/builtin_echo.c \
		builtin/builtin_unset.c \
		builtin/builtin_cd.c \
		builtin/builtin_exit.c \
		parent_process/find_brackets_pair.c \
		parent_process/sep_input_to_cmds.c \
		parent_process/handle_node.c \
		parent_process/trim_space.c \
		parent_process/pipe.c \
		parent_process/fork.c \
		parent_process/fork2.c \
		ft_split.c \
		export_utils.c \
		init_varlist.c \
		expander/expander.c \
		expander/pre_tokenizer.c \
		expander/more_tokenizer.c \
		expander/replace_vars.c \
		expander/replace_vars_count.c \
		expander/replace_vars_split.c \
		expander/replace_vars_split2.c \
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
		here_doc/heredoc_expand_vars.c \
		here_doc/heredoc_vars_count.c \
		here_doc/heredoc_vars_split.c \
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
