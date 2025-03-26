/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tssaito <tssaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:58:43 by tssaito           #+#    #+#             */
/*   Updated: 2024/12/13 22:58:17 by tssaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			c;
	int				check;
	static t_buf	buf;
	t_line			ans;

	if (fd < 0)
		return (NULL);
	ft_init(&ans);
	while (1)
	{
		c = ft_getchar(fd, &buf);
		if (c == READ_ERROR)
			return (free(ans.line), NULL);
		if (c == EOF)
			break ;
		if (ans.len == SIZE_MAX)
			return (free(ans.line), NULL);
		check = ft_make_ans(c, &ans);
		if (check == MALLOC_ERROR)
			return (NULL);
		if (c == '\n')
			break ;
	}
	return (ans.line);
}

//# include <fcntl.h>
//int	main(int argc, char **argv)
//{
//	char	*line;
//	int		fd;
//
//	(void)argc;
//	fd = open(argv[1], O_RDONLY);
//	while (1)
//	{
//		line = get_next_line(fd);
//		if (!line)
//		{
//			printf("line: NULL\n");
//			printf("=================\n");
//			break;
//		}
//		printf("line: %s", line);
//		printf("=================\n");
//		free(line);
//	}
//	close(fd);
//	return (0);
//}
