/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_him.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:08:17 by hedi              #+#    #+#             */
/*   Updated: 2024/06/15 17:26:39 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_build(t_data *shell, char **f)
{
	if (ft_same_str(f[0], "echo", 4))
		shell->last_return_code = ft_echo(f);
	else if (ft_same_str(f[0], "cd", 2))
		shell->last_return_code = ft_cd(f, shell);
	else if (ft_same_str(f[0], "pwd", 3))
		shell->last_return_code = ft_pwd(shell);
	else if (ft_same_str(f[0], "export", 6))
		shell->last_return_code = ft_export(f, shell);
	else if (ft_same_str(f[0], "unset", 5))
		shell->last_return_code = ft_unset(shell, f);
	else if (ft_same_str(f[0], "env", 3))
		shell->last_return_code = ft_env(shell, f);
	else if (ft_same_str(f[0], "exit", 4))
		ft_exit(f, shell);
	else
		return ;
	exit_free(shell, 0);
}

static void	init_exec_path(int *i, t_env **e, t_data *sh)
{
	*i = -1;
	*e = sh->env;
}

static void	incr_j(t_env *e, int *j)
{
	while (e->val[*j] != ':' && e->val[*j] && e->val)
		(*j)++;
}

void	mini_exec(char c, char **f, t_data *sh, char *ret)
{
	if (c == ':')
		if (access(ret, F_OK) == 0)
			execve(ret, f, sh->char_env);
	free(ret);
}

void	exec_path(t_data *sh, char **f, char *tmp)
{
	int		i;
	int		j;
	int		k;
	char	*ret;
	t_env	*e;

	init_exec_path(&i, &e, sh);
	while (e)
	{
		if (ft_same_str(e->var_name, "PATH", 4))
		{
			j = -1;
			while (e->val && e->val[++j])
			{
				k = j;
				incr_j(e, &j);
				ret = join_free1(ft_substr(e->val, k, ((j) - k)), tmp);
				mini_exec(e->val[j], f, sh, ret);
				if (!e->val[j])
					break ;
			}
		}
		e = e->next;
	}
}
