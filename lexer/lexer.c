/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 04:12:14 by mgur              #+#    #+#             */
/*   Updated: 2023/09/07 12:09:21 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_append(void)
{
	free_token();
	free_process();
}

int	append_arguments(t_token **token, t_process *process)
{
	char		*data;

	if ((*token)->type == STRING)
	{
		data = clean_quote((*token)->str);
		process->execute = push_array(process->execute, data);
	}
	else
	{
		data = clean_quote((*token)->str);
		process->redirects = push_array(process->redirects, data);
		*token = (*token)->next;
		if (!(*token) || (*token)->type != STRING)
		{
			if (!(*token))
				token_err(0);
			else
				token_err((*token)->type);
			free_append();
			return (FALSE);
		}
		data = clean_quote((*token)->str);
		process->redirects = push_array(process->redirects, data);
	}
	return (TRUE);
}

int	lexer_extra(t_token *token)
{
	if (!token || token->type == PIPE)
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		free_token();
		free_process();
		errno = 258;
		return (FALSE);
	}
	return (TRUE);
}

int	lexer(t_token *token, t_process *process)
{
	token = g_ms.token;
	while (token)
	{
		if (token->type == PIPE || token->prev == NULL)
		{
			if (token->type == PIPE)
			{
				token = token->next;
				if (!token || token->type == PIPE)
					return (lexer_extra(token));
			}
			process = init_process();
			process_addback(&g_ms.process, process);
			g_ms.process_count++;
		}
		if (!token)
			break ;
		if (!append_arguments(&token, process))
			return (FALSE);
		if (token)
			token = token->next;
	}
	free_token();
	return (TRUE);
}

int	lexer_start(void)
{
	t_token		*token;
	t_process	*process;

	token = NULL;
	process = NULL;
	if (lexer(token, process))
		return (1);
	return (0);
}
