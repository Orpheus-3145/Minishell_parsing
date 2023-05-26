#ifndef MINISHELL_H
# define MINISHELL_H
# define RED   "\x1B[31m"	// colors for the messages on the stdout
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define RESET "\x1B[0m"     
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
	CMD_NULL_ERR,
}	t_cmd_status;

typedef enum s_red_type
{
	S_IN_RED,		// <
	S_OUT_RED,		// >
	D_IN_RED,		// <<
	D_OUT_RED,		// >>
}	t_red_type;

typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
	bool			has_value;
}   t_env;

typedef struct s_token
{
	struct s_token	*prev;
	struct s_token	*next;
	char			*word;
}	t_token;

typedef struct s_cmd
{
	t_token				*tokens;
	// t_token				*redirect_tokens;
	char				*_cmd;
	char				*cmd_name;
	char				**cmd_full;
	t_red_type			*redirect;			//could be list 
	char				**file;
	int32_t				fd_in;
	int32_t				fd_out;
}	t_cmd;

typedef struct s_input
{	
	t_cmd			*cmd_data;
	char			*raw_input;
	uint32_t		n_cmd;
	struct s_input	*next;
}   t_input;

typedef struct s_var
{
	t_input		*input_list;
	t_env       *env_list;
	char        **env_arr;
	char        **paths;
	int         **pipes;
	pid_t       *pid;
	int         status;
}   t_var;

void 	test_pipes(void);

void 	test_redirections(void);

void	test_trim(void);

void	test_last_pipe(void);

void	test_next_d_red(void);

void	test_eof(void);

void	test_quotes(void);

void	test_split_cmd(void);

void	test_n_cmds(void);

void	test_char_skip(void);


bool    check_pipes(char *cmd);

// bool	check_between_pipes(char *str, int32_t pos1, int32_t pos2);

bool    check_redirections(char *str);

bool	check_quotes(char *cmd);

bool	check_cmd(char *cmd);


t_cmd_status	ft_readline(char **buffer, const char *prompt, bool check);

t_cmd_status	concat_input(char **base, char *buffer);

t_cmd_status	read_input(char **curr_cmd);


void    main_loop(t_var	*main_var);


bool	is_outside_quotes(char *string, uint32_t pos_to_check);

bool	has_trailing_pipe(char	*cmd);

bool	is_quote(char to_check);

bool	is_arrow(char to_check);

bool 	is_valid_pipe(char *string, uint32_t pos_to_check);

bool 	is_valid_arrow(char *string, uint32_t pos_to_check);

bool 	is_valid_quote(char *string, uint32_t pos_to_check);

bool	is_valid_space(char *string, uint32_t pos_to_check);

bool	is_only_spaces(char	*to_check);


int32_t	find_next_eof_pos(char *cmd, uint32_t start_pos);

char	*isolate_eof(char *start);

char	*read_stdin(char *buffer);


t_var   *create_depo(char **envp);

void append_new_input(t_var *depo, t_input *new_input);

t_cmd *create_new_cmd(char *input, uint32_t n_cmds);

t_input *create_new_input(char *input);

void	free_depo(t_var *depo);


uint32_t	n_cmds(char *string);

char	**split_into_cmds(char *input_cmd);

char	**append_string(char **old_matrix, char *to_append);

uint32_t	skip_redirect_chars(char *cmd, uint32_t pos);


t_token *create_new_token(char *word);

void	append_token(t_token **token_list, t_token *new_token);

// t_token	*tokenize_cmd(char *input);

// t_token	*tokenize_redirect(char *input);

t_token	*tokenize(char *input);

// void	drop_token(t_token **token_list, char *word);

void	free_tokens(t_token *token_list);

void	print_tokens(t_var *depo);

void	print_tks(t_token *tks);

#endif