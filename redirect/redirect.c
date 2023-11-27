/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 04:12:44 by mgur              #+#    #+#             */
/*   Updated: 2023/09/07 04:12:46 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_all_inputs(t_process *process, int cntrl)
{
	int		i;
	char	**redirects;

	i = 0;
	redirects = process->redirects;
	while (redirects[i])
	{
		if (is_operator(redirects[i]) == RED_INPUT)
			input(redirects[i + 1], cntrl);
		else if (is_operator(redirects[i]) == HERE_DOC \
				&& contain_heredoc(process))
			heredoc(redirects[i + 1]);
		i += 2;
	}
	if (g_ms.ignore)
	{
		close_heredoc_fd();
		return (FALSE);
	}
	return (TRUE);
}

void	set_all_outputs(t_process *process)
{
	int		i;
	char	**redirects;

	i = 0;
	redirects = process->redirects;
	while (redirects[i])
	{
		if (is_operator(redirects[i]) == RED_OUTPUT)
			output(redirects[i + 1], REPLACE);
		else if (is_operator(redirects[i]) == RED_APPEND)
			output(redirects[i + 1], APPEND);
		i += 2;
	}
}
