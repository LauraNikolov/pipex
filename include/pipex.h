/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolof <lnicolof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:32:10 by lnicolof          #+#    #+#             */
/*   Updated: 2024/04/17 13:35:30 by lnicolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define ARG_ERROR 88
# define HEDC_ERROR 87

typedef struct s_list
{
	char			*cmd_path;
	char			**cmds;
	bool			access;
	struct s_list	*next;
}					t_list;

typedef struct s_data
{
	char			*stdin_file;
	char			*stdout_file;
	int				fd_prev;
	char			**all_paths;
	int				arg_size;
	struct s_list	*lst;
	struct s_list	*save_lst;
}					t_data;

char				*ft_get_env_path(char *envp[]);
char				**ft_split(char const *s, char c);
int					ft_tablen(char **str);
t_list				*ft_lstnew(char **content);
t_list				*ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstlast(t_list *lst);
int					ft_lst_size(t_list **lst);
void				ft_parse_data(int argc, char **argv, char *envp[],
						t_data *pipex);
char				**get_all_paths(char *envp[]);
void				ft_find_good_path(t_data *pipex);
char				*ft_paths_and_cmds(char *path, char *cmds);
void				ft_execute(t_data *pipex, char **envp);
void				ft_heredoc(t_data *pipex, char **argv, int argc);
void				ft_free(t_data *pipex);
int					ft_limiter(char *s1, char *s2);
void				ft_error(t_data *pipex, char *error_str);
void				ft_last_arg_child(struct s_data *pipex, int pfd[2]);
void				first_arg_child(struct s_data *pipex, int pfd[2]);
void				ft_middle_arg_child(struct s_data *pipex, int *pfd);
void				ft_execve(t_list *lst, char **envp, t_data *pipex);
void				ft_wait_child(int arg_size, struct s_data *pipex,
						int pfd[2]);
char				*ft_nods_error(char *str);

#endif