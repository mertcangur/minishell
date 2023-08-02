#include "minishell.h"

t_minishell	g_ms;


int main(int ac, char **av,char **env)
{
	char *input;

	while(1)
	{
		input = readline("lol>");
		tokenn(input);
		
	}
}
