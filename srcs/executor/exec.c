/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:36:28 by hzaz              #+#    #+#             */
/*   Updated: 2024/06/15 17:34:41 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_shell_cmd(char *str)
{
	int		len;
	int		len2;
	char	*tmp;

	tmp = "/minishell";
	len2 = ft_strlen(tmp);
	len = ft_strlen(str);
	while (str[--len] && tmp[--len2])
	{
		if (str[len] != tmp[len2])
			return (0);
	}
	if (tmp[len2])
		return (0);
	return (1);
}

int	is_directory(const char *path)
{
	struct stat	filestat;

	if (path && path[0] == ':' && !path[1])
		return (-1);
	if (stat(path, &filestat) < 0)
	{
		perror("stat");
		return (0);
	}
	return (S_ISDIR(filestat.st_mode));
}

void	check_exec_file(char **f, t_data *shell)
{
	int	code;

	code = 126;
	if (f[0] && f[0][0] == '.' && f[0][1] == '/')
	{
		if (access(f[0], F_OK) != 0)
		{
			perror("minishell :");
			code = 127;
		}
		else if (is_directory(f[0]))
			ft_putstr_fd("minishell: is a directory.\n", 2);
		else if (access(f[0], X_OK) != 0)
			perror("minishell :");
		else
		{
			execve(f[0], f, shell->char_env);
			perror("minishell :");
		}
		exit_free(shell, code);
	}
}

int	handle_error(char **f, int code)
{
	char	*ret;

	ret = NULL;
	if (f[0][0] == '/' && is_directory(f[0]))
	{
		ret = ft_strdup("is a directory.\n");
		code = 126;
	}
	else
		ret = join_free1(ft_strjoin("command not found: ", f[0]), "\n");
	ft_putstr_fd_free(ret, 2);
	return (code);
}

void	exec_cmd(t_data *shell, t_exec *cmd)
{
	char	*tmp;
	char	**f;
	int		code;

	code = 0;
	f = cmd->split_cmd;
	if (!f[0])
		return ;
	if (f[0] && f[0][0] == ':' && !f[0][1])
		exit_free(shell, 0);
	handle_redirections(cmd, shell);
	check_exec_file(f, shell);
	exec_build(shell, f);
	tmp = ft_strjoin("/", f[0]);
	if (access(tmp, F_OK) == 0)
		execve(tmp, f, shell->envp);
	else
		exec_path(shell, f, tmp);
	code = 127;
	code = handle_error(f, code);
	free(tmp);
	exit_free(shell, code);
}
