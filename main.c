/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 04:15:04 by mgur              #+#    #+#             */
/*   Updated: 2023/09/07 12:53:00 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_ms;

void	init_app(char **env)
{
	errno = 0;
	g_ms.paths = NULL;
	set_env(env);
	set_paths();
}

void	init_shell(char *input)
{
	g_ms.token = NULL;
	g_ms.ignore = FALSE;
	g_ms.process = NULL;
	g_ms.process_count = 0;
	g_ms.ex_flag = 0;
	if (!(tokenize(input)))
		return ;
	if (!lexer_start())
		return ;
	start_cmd();
	free_process();
}

void	ctrl_c(int sig)
{
	(void)sig;
	errno = 1;
	g_ms.ignore = TRUE;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
}

void	ctrl_d(char *input)
{
	if (input == NULL)
	{
		printf("\n");
		printf("\033[A");
		write(1, "\033[32m", 5);
		printf("\033[A");
		printf("\nMinishell_> exit\n");
		exit(0);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;

	init_app(env);
	while (ac && av)
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, sig_quit_handler);
		write(1, "\033[32m", 5);
		input = readline("minishell_> ");
		write(1, "\033[0m", 4);
		ctrl_d(input);
		if (g_ms.ignore)
		{
			g_ms.ignore = FALSE;
			free(input);
			input = ft_calloc(sizeof(char *), 1);
		}
		if (*input)
		{
			init_shell(input);
			add_history(input);
		}
		free(input);
	}
	exit(errno);
}
