/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:31:47 by lnicolof          #+#    #+#             */
/*   Updated: 2024/04/17 13:30:43 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_paths_and_cmds(char *path, char *cmds)
{
	char	*good_paths;

	if (ft_strchr(cmds, '/'))
		return (ft_strdup(cmds));
	if (cmds[0] == '~')
		return (ft_strdup(cmds));
	good_paths = malloc(sizeof(char *) * (ft_strlen(path) + ft_strlen(cmds)
				+ 2));
	if (!good_paths)
		return (NULL);
	ft_strlcpy(good_paths, path, ((size_t)ft_strlen(path) + 1));
	ft_strlcat(good_paths, cmds, ((size_t)(ft_strlen(path) + ft_strlen(cmds)
				+ 1)));
	return (good_paths);
}

void	ft_find_good_path(t_data *pipex)
{
	int		i;
	char	*temp_paths;

	while (pipex->lst)
	{
		i = 0;
		while (pipex->all_paths[i])
		{
			temp_paths = ft_paths_and_cmds(pipex->all_paths[i],
					pipex->lst->cmds[0]);
			if (access(temp_paths, F_OK) == 0)
			{
				pipex->lst->cmd_path = temp_paths;
				pipex->lst->access = 1;
				break ;
			}
			if (access(temp_paths, F_OK) == -1)
			{
				free(temp_paths);
				pipex->lst->access = 0;
			}
			i++;
		}
		pipex->lst = pipex->lst->next;
	}
}

void	ft_parse_data(int argc, char **argv, char *envp[], t_data *pipex)
{
	int		i;
	char	*temp;
	t_list	*new_node;

	i = 2;
	if (ft_strncmp(argv[1], "heredoc", 7) == 0)
		i = 3;
	pipex->all_paths = get_all_paths(envp);
	pipex->lst = NULL;
	while (i < argc - 1)
	{
		temp = argv[i];
		if (ft_strlen(temp) == 0)
			temp = ft_nods_error("error error");
		new_node = ft_lstnew(ft_split(temp, ' '));
		ft_lstadd_back(&pipex->lst, new_node);
		i++;
	}
	pipex->save_lst = pipex->lst;
	if (envp)
		ft_find_good_path(pipex);
	pipex->lst = pipex->save_lst;
	pipex->fd_prev = -1;
	pipex->arg_size = ft_lst_size(&(pipex->lst));
}

char	**get_all_paths(char *envp[])
{
	char	*paths;
	char	**env_paths;

	paths = ft_get_env_path(envp);
	if (paths)
	{
		env_paths = ft_split(paths, ':');
		return (env_paths);
	}
	else
		return (NULL);
}

int	main(int argc, char **argv, char *envp[])
{
	t_data	pipex;

	if (envp[0] == NULL)
		return (0);
	ft_memset(&pipex, 0, sizeof(pipex));
	if (argc < 5 || argc > 5)
	{
		write(STDERR_FILENO, "Argument error. Please enter the good input.\n",
			46);
		return (0);
	}
	else
	{
		pipex.stdin_file = argv[1];
		pipex.stdout_file = argv[argc - 1];
	}
	ft_parse_data(argc, argv, envp, &pipex);
	pipex.lst = pipex.save_lst;
	ft_execute(&pipex, envp);
	pipex.lst = pipex.save_lst;
	ft_free(&pipex);
}
