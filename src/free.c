/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:01:42 by lnicolof          #+#    #+#             */
/*   Updated: 2024/04/16 16:23:50 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**ft_free__strs(char **strs, size_t words)
{
	size_t	i;

	i = 0;
	while (i < words)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

void	ft_free_lst(t_data *pipex)
{
	t_list	*tmp;

	while (pipex->lst)
	{
		if (pipex->lst->cmd_path)
			free(pipex->lst->cmd_path);
		if (pipex->lst->cmds)
			ft_free__strs(pipex->lst->cmds, ft_tablen(pipex->lst->cmds));
		tmp = pipex->lst;
		pipex->lst = pipex->lst->next;
		free(tmp);
	}
}

void	ft_free(t_data *pipex)
{
	if (pipex->all_paths)
		ft_free__strs(pipex->all_paths, ft_tablen(pipex->all_paths));
	if (pipex->lst)
		ft_free_lst(pipex);
}
