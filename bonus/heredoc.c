/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:08:25 by lnicolof          #+#    #+#             */
/*   Updated: 2024/04/16 15:23:02 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <fcntl.h>

int	ft_limiter(char *s1, char *s2)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s2[i])
	{
		y = 0;
		while (s2[i] == s1[y] && s1[y] && s2[i])
		{
			i++;
			y++;
			if (y == (int)ft_strlen(s1))
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_heredoc(t_data *pipex, char **argv, int argc)
{
	int		file;
	char	*line;

	pipex->stdin_file = "heredoctmp";
	file = open("heredoctmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file == -1)
		perror("open:");
	while (1)
	{
		write(1, "here_doc>  ", 10);
		line = get_next_line(0);
		if (line == NULL)
			printf("malloc error\n");
		if (ft_limiter(argv[2], line) == 1)
			break ;
		write(file, line, ft_strlen(line) - 1);
		write(file, "\n", 1);
		free(line);
	}
	free(line);
	close(file);
	pipex->stdin_file = "heredoctmp";
	pipex->stdout_file = argv[argc - 1];
}
