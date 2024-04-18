/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:24:48 by lnicolof          #+#    #+#             */
/*   Updated: 2024/04/16 14:27:54 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_parent_process(int pfd[2], int i, t_data *pipex)
{
	close(pfd[1]);
	if (i != 0)
		close(pipex->fd_prev);
	pipex->fd_prev = pfd[0];
}

void	ft_execute(t_data *pipex, char **envp)
{
	int		pfd[2];
	pid_t	pid;
	int		i;

	i = 0;
	while (pipex->lst)
	{
		pipe(pfd);
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				first_arg_child(pipex, pfd);
			else if (i == pipex->arg_size - 1)
				ft_last_arg_child(pipex, pfd);
			else
				ft_middle_arg_child(pipex, pfd);
			ft_execve(pipex->lst, envp, pipex);
		}
		else
			ft_parent_process(pfd, i, pipex);
		i++;
		pipex->lst = pipex->lst->next;
	}
	ft_wait_child(pipex->arg_size, pipex, pfd);
}
