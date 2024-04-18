/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:47:41 by lnicolof          #+#    #+#             */
/*   Updated: 2024/04/17 13:34:52 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_error(t_data *pipex, char *error_str)
{
	perror(error_str);
	ft_free(pipex);
	exit(0);
}

char	*ft_nods_error(void)
{
	char	*error;

	error = ft_strdup("error");
	return (error);
}
