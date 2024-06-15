/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:26:17 by vabertau          #+#    #+#             */
/*   Updated: 2024/06/15 17:40:59 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_same_str_exact_free1(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (ft_strlen(str1) != ft_strlen(str2))
	{
		free(str1);
		return (0);
	}
	while (str1 && str2 && str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
		{
			free(str1);
			return (0);
		}
		i++;
	}
	if (str1[i] || str2[i])
		return (0);
	free(str1);
	return (1);
}

int	ft_same_str_exact(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	printf("%s\n%s\n", str1, str2);
	while (str1 && str2 && str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
		{
			printf("\ntest2\n");
			return (0);
		}
		i++;
	}
	if (str1[i] || str2[i])
		return (0);
	return (1);
}

void	handle_redirections(t_exec *cmd, t_data *shell)
{
	t_token	*redir;

	redir = cmd->redir;
	while (redir != NULL)
	{
		if (redir->type == LEFT1 || redir->type == LEFT2)
			handle_input_redirection(redir, shell);
		else if (redir->type == RIGHT1 || redir->type == RIGHT2)
			handle_output_redirection(redir, shell);
		redir = redir->next;
	}
}

void	filler_hd(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}
