/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 04:12:49 by mgur              #+#    #+#             */
/*   Updated: 2023/09/07 11:33:07 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_end_pos(char **str, char type)
{
	(*str)++;
	while (**str)
	{
		if (**str == type)
		{
			(*str)++;
			while (**str && !is_whitespace(**str) && !is_operator(*str))
				(*str)++;
			return (1);
		}
		(*str)++;
	}
	write (2, "quote hasn't been closed\n", 26);
	return (0);
}

void	without_quote_parse(char **str)
{
	while (**str)
	{
		if (is_whitespace(**str))
			break ;
		if (is_operator(*str))
			break ;
		(*str)++;
	}
}

void	skip_whitespace(char **str, char **head)
{
	while (**str && is_whitespace(**str))
		(*str)++;
	*head = *str;
}

void	for_token_string(int len, char **str, char *head)
{
	char	*token_str;

	len = *str - head;
	if (len > 0)
	{
		token_str = ft_substr(head, 0, len);
		token_addback(&g_ms.token, init_token(token_str, STRING), 0);
	}
}

int	parse_token_string(char **str, int len)
{
	char	*head;

	skip_whitespace(str, &head);
	if (**str && ((**str == DOUBLE_QUOTE && (*(*str + 1)) == DOUBLE_QUOTE) || \
		(**str == SINGLE_QUOTE && (*(*str + 1)) == SINGLE_QUOTE)) && \
		(g_ms.process != NULL && g_ms.process->prev != NULL))
	{
		(*str) += 2;
		head = *str;
	}
	else if (**str && **str == DOUBLE_QUOTE)
	{
		if (!extra(str))
			return (0);
	}
	else if (**str && **str == SINGLE_QUOTE)
	{
		if (!find_end_pos(str, SINGLE_QUOTE))
			return (0);
	}
	else
		without_quote_parse(str);
	for_token_string(len, str, head);
	return (1);
}
