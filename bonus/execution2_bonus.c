/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:29:28 by lnicolof          #+#    #+#             */
/*   Updated: 2024/04/17 13:34:08 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_arg_child(t_data *pipex, int pfd[2])
{
	int	fd_file;

	fd_file = open(pipex->stdin_file, O_RDONLY);
	if (fd_file == -1)
		ft_error(pipex, "error");
	close(pfd[0]);
	dup2(fd_file, STDIN_FILENO);
	close(fd_file);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
}

void	ft_middle_arg_child(t_data *pipex, int pfd[2])
{
	close(pfd[0]);
	dup2(pipex->fd_prev, STDIN_FILENO);
	close(pipex->fd_prev);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
}

void	ft_last_arg_child(t_data *pipex, int pfd[2])
{
	int	fd_file;

	fd_file = open(pipex->stdout_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file == -1)
		ft_error(pipex, "error");
	close(pfd[0]);
	dup2(fd_file, STDOUT_FILENO);
	close(fd_file);
	dup2(pipex->fd_prev, STDIN_FILENO);
	close(pipex->fd_prev);
}

void	ft_execve(t_list *lst, char **envp, t_data *pipex)
{
	if (access(lst->cmd_path, F_OK) == 0)
		execve(lst->cmd_path, lst->cmds, envp);
	else if (access(lst->cmd_path, F_OK) == -1)
	{
		write(STDERR_FILENO, "command not found : ", 19);
		if (ft_strncmp(lst->cmds[0], "error", 5))
			write(STDERR_FILENO, lst->cmds[0], ft_strlen(lst->cmds[0]));
		write(STDERR_FILENO, "\n", 1);
		pipex->lst = pipex->save_lst;
		ft_free(pipex);
		close(pipex->fd_prev);
		exit(0);
	}
}

void	ft_wait_child(int arg_size, t_data *pipex, int pfd[2])
{
	while (arg_size > 0)
	{
		wait(NULL);
		arg_size--;
	}
	close(pipex->fd_prev);
	close(pfd[0]);
	close(pfd[1]);
}
