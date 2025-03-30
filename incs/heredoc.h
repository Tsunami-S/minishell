/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:03:24 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/30 19:29:24 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

char	*here_doc(char *limiter, t_var **varlist);
char	*heredoc_expand_var(char *buf, t_var **varlist);
int		heredoc_vars_count(char *str);
char	**heredoc_split_token(char *token, int malloc_size, t_var **varlist);

#endif
