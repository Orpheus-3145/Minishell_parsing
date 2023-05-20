#ifndef MINISHELL_H
# define MINISHELL_H
# define RED   "\x1B[31m"	// colors for the messages on the stdout
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define RESET "\x1B[0m"
# define S_IN_RED 2         // <
# define S_OUT_RED 3        // >
# define D_IN_RED 4         // <<
# define D_OUT_RED 5        // >>
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>    	// malloc(), free()
# include <unistd.h>    	// write(), read(), ...
# include <fcntl.h>			// macro to open files (O_CREAT, O_WRONLY, O_RDONLY ..)
# include <stdbool.h>		// boolean types
# include <stdint.h>		// cross-compiler types

typedef enum s_cmd_status
{
	CMD_OK,
	CMD_SIN_ERR,
	CMD_MEM_ERR,
	CMD_EMPTY,
	CMD_OPEN_PIPE,
	CMD_NULL_INPUT,
} t_cmd_status;

typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
}   t_env;

typedef struct s_cmd
{
	char	*cmd_name;
	char	**cmd_full;
	int		*redirect;			//could be list 
	char	**file;
	t_env	*env_list;
	char	**env_arr;
}   t_cmd;

typedef struct s_raw_cmd
{
	struct s_raw_cmd	*next;
	char				*cmd_input;
	uint32_t			n_cmds;
	t_cmd				*cmd_list;
}   t_raw_cmd;

typedef struct s_var
{
	t_cmd		*cmd_data;
	uint32_t	n_cmd;
	t_env		*env_list;
	char		**env_arr;
	int			**pipes;
	pid_t		*pid;
	int			status;
}   t_var;

void 	test_pipes(void);

void 	test_redirections(void);

void	test_trim(void);

void	test_last_pipe(void);

void	test_next_d_red(void);

void	test_eof(void);

void	test_quotes(void);


bool    check_pipes(char *cmd);

bool	check_between_pipes(char *str, int32_t pos1, int32_t pos2);

bool    check_redirections(char *str);

bool	check_quotes(char *cmd);

bool	check_cmd(char *cmd);


bool	add_raw_cmd(t_raw_cmd **history, char *new_input);

void    free_cmds(t_raw_cmd **list);

void    print_cmds(t_raw_cmd *c_list);


t_cmd_status	ft_readline(char **buffer, const char *prompt, bool check);

t_cmd_status	concat_input(char **base, char *buffer);

t_cmd_status	read_input(char **curr_cmd);

void    main_loop(void);


bool	trailing_pipe(char	*cmd);

bool	is_quote(char to_check);

bool	is_arrow(char to_check);


int32_t	find_next_eof_pos(char *cmd, uint32_t start_pos);

char	*find_eof(char *start);

char	*read_stdin(char *buffer);

#endif