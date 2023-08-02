#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>

# define TRUE 1
# define FALSE 0
# define DOLLAR_OP '$'
# define DOUBLE_QUOTE '"'
# define SINGLE_QUOTE '\''
# define CHILD_PROCESS 0
# define MAIN_PROCESS 1
# define REPLACE 1
# define APPEND 0

enum e_builtin_types
{
	CD = 1,
	ENV,
	PWD,
	ECHO,
	EXIT,
	UNSET,
	EXPORT
};

enum e_ttype
{
	PIPE = 1,
	STRING,
	HERE_DOC,
	RED_INPUT,
	RED_APPEND,
	RED_OUTPUT
};

typedef struct s_token
{
	char			*str;
	enum e_ttype	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_process
{
	pid_t				pid;
	int					fd[2];
	int					heredoc_fd[2];
	char				**execute;
	char				**redirects;
	struct s_process	*prev;
	struct s_process	*next;
}	t_process;

typedef struct s_minishell
{
	int			parent_pid;
	int			process_count;
	int			ignore;
	char		**env;
	char		**paths;
	t_token		*token;
	t_process	*process;
}				t_minishell;

extern t_minishell	g_ms;


void tokenn(char *str);
int is_operator(char *str);
char	*ft_strdup(const char *str);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t n);
size_t	ft_strlen(const char *s);
void parse_token_string(char **str);
void skip_whitespace(char **str,char **head);
void without_quote_parse(char **str);
void find_end_pos(char **str,char type);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_substr(char const *str, unsigned int start, size_t len);
int	is_whitespace(char c);
int token_addback(t_token **token,t_token *new_token ,int plus);
t_token *init_token(char *str,enum e_ttype type);




#endif
