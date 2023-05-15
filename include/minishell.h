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

typedef struct s_cmd
{
	struct s_cmd    next;
	char            **file;
	char            **cmd_full;
	char            *cmd_name;
	int             *redirect;
}   t_cmd;

typedef struct s_var
{
	t_cmd   *cmd_data;
	t_env   *env_list;
	pid_t   *pid;
	char    **env_arr;
	int     **pipes;
	int     size;
	int     status;
}   t_var;

typedef struct s_env
{
	struct s_env    *next;
	char            *key;
	char            *value;
}   t_env;

#endif