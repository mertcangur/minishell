/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 04:09:18 by mgur              #+#    #+#             */
/*   Updated: 2023/09/07 04:09:24 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "cd"))
		return (CD);
	if (ft_strcmp(command, "env"))
		return (ENV);
	if (ft_strcmp(command, "pwd"))
		return (PWD);
	if (ft_strcmp(command, "echo"))
		return (ECHO);
	if (ft_strcmp(command, "exit"))
		return (EXIT);
	if (ft_strcmp(command, "unset"))
		return (UNSET);
	if (ft_strcmp(command, "export"))
		return (EXPORT);
	return (0);
}

void	run_builtin(char **execute, int cntrl)
{
	int	type;

	type = is_builtin(execute[0]);
	if (type == CD)
		builtin_cd(execute, cntrl);
	if (type == ENV)
		builtin_env(cntrl);
	if (type == PWD)
		builtin_pwd(cntrl);
	if (type == ECHO)
		builtin_echo(execute, cntrl);
	if (type == EXIT)
		builtin_exit(execute);
	if (type == UNSET)
		builtin_unset(execute, cntrl);
	if (type == EXPORT)
		builtin_export(execute, cntrl);
}
