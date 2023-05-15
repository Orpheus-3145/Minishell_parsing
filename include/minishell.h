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

typedef struct s_env
{
    struct s_env    *next;
    char            *key;
    char            *value;
}   t_env;

typedef struct s_cmd
{
    char    *cmd_name;
    char    **cmd_full;
    int     *redirect;
    char    **file;
    t_env   *env_list;
    char    **env_arr;
}   t_cmd;


typedef struct s_var
{
    t_cmd   *cmd_data;
    int     size;
    t_env   *env_list;
    char    **env_arr;
    int     **pipes;
    pid_t   *pid;
    int     status;
}   t_var;

bool    check_pipes(char *cmd);

bool	check_between_pipes(char *str, int32_t pos1, int32_t pos2);

#endif