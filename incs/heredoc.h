/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:03:24 by tssaito           #+#    #+#             */
/*   Updated: 2025/03/31 06:57:29 by haito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

char	*here_doc(char *limiter, t_var **varlist, t_status **st_head);
char	*heredoc_expand_var(char *buf, t_var **varlist);
int		heredoc_vars_count(char *str);
char	**heredoc_split_token(char *token, int malloc_size, t_var **varlist);
int		check_heredoc(t_status **st_head, t_var **var);
int		has_heredoc(t_status *st);
int		error_check_heredoc(t_var **var);
void	delete_tmpfile(t_status *st);

#endif
