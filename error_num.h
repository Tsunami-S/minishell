/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_num.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haito <haito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 01:44:14 by haito             #+#    #+#             */
/*   Updated: 2025/03/23 20:58:15 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_NUM_H
# define ERROR_NUM_H

# define ERROR -1
# define FAILED 1
# define SUCCESS 0
# define SYNERR 2

# define REDIRECTERROR -400
# define CMDERROR -401
# define EXPORTERROR -402
# define AMBIGUOUS -403
# define FILENUMERROR -404
# define PATHERROR -405
# define EXIT_NOCMD 127
# define EXIT_PERM 126
# define EXIT_SYNTAX 2

# define ERRNO_ONE 1
# define ERRNO_TWO 2
# define ERRNO_THREE 3
# define ERRNO_FOUR 4

# define IS_OR 1
# define IS_ANDAND 2
# define IS_AND 3

#endif
