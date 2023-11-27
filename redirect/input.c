/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 04:12:33 by mgur              #+#    #+#             */
/*   Updated: 2023/09/07 04:12:35 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input(char *file, int cntrl)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (cntrl == 1)
	{
		if (fd == -1)
		{
			g_ms.ignore = TRUE;
			return (no_file_err(file));
		}
		if (g_ms.heredoc_fd[0] > 2)
			dup2(fd, g_ms.heredoc_fd[0]);
	}
	else
	{
		if (fd == -1)
			no_file_err(file);
		dup2(fd, 0);
	}
	if (fd != -1)
		close(fd);
}
