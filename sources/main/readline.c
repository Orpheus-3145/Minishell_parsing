/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:03:02 by faru              #+#    #+#             */
/*   Updated: 2023/05/19 03:22:36 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	trailing_pipe(char	*cmd)
{
	uint32_t	len_cmd;

	if (*cmd == '\0')
		return (false);
	len_cmd = ft_strlen(cmd) - 1;
	while (len_cmd && ft_isspace(cmd[len_cmd]))
		len_cmd--;
	if (len_cmd <= 1)
		return (false);
	else
		return ((cmd[len_cmd] == '|') && (cmd[len_cmd - 1] != '|'));
}

bool	is_quote(char to_check)
{
	return ((to_check == '\'') || (to_check == '\"'));
}

bool	is_arrow(char to_check)
{
	return ((to_check == '<') || (to_check == '>'));
}

int32_t	find_next_eof_pos(char *cmd, uint32_t start_pos)
{
	bool		open_quotes;

	open_quotes = false;
	while (cmd && cmd[start_pos] && (cmd[start_pos] != '\n'))
	{
		if (is_quote(cmd[start_pos]))
			open_quotes = ! open_quotes;
		else if (cmd[start_pos] == '<')
		{
			if (cmd[start_pos + 1] && (cmd[start_pos + 1] == '<'))
				return (start_pos + 2);
		}
		start_pos++;
	}
	return (-1);
}

char	*find_eof(char *start)
{
	char 		start_quote;
	char 		*eof;
	uint32_t	i;

	while(*start && (ft_isspace(*start)))
		start++;
	i = 0;
	if (is_quote(*start))
	{
		start_quote = *start;
		while (*start && (*start == start_quote))
			start++;
		while (start[i] && (start[i] != start_quote))
			i++;
	}	
	else
	{
		while (start[i] && (! ft_isspace(start[i])) && (! is_arrow(start[i])) && (start[i] != '|'))
			i++;
	}
	eof = ft_calloc((i + 1), sizeof(char));
	if (eof)
	{
		while (i--)
			eof[i] = start[i];
	}
	return (eof);
}

char	*ft_readline(const char *prompt)
{
	char	*new_string;
	char	*copy;

	new_string = readline(prompt);
	if (! new_string)					// readline failed!
		return (NULL);
	copy = ft_strdup(new_string);
	free(new_string);
	return (copy);
}

int32_t	append_input(char *curr_cmd, char **input)
{
	char	*new_line;
	char	*eof;
	int32_t	eof_pos;
	bool	keep_reading;
	
	eof_pos = find_next_eof_pos(curr_cmd, 0);
	while (eof_pos != -1)
	{
		eof = find_eof(curr_cmd + eof_pos);
		keep_reading = true;
		while (keep_reading)		// need to update history for every new line
		{
			new_line = ft_readline("> ");							// gives NULL if ctrl + D is pressed on empty line
			keep_reading = ft_strncmp(new_line, eof, ft_strlen(eof) + 1);
			*input = ft_append_char(*input, '\n');
			if (! *input)
				return (CMD_MEM_ERR);
			*input = ft_concat(*input, new_line);
			if (! *input)
				return (CMD_MEM_ERR);
		}
		eof_pos = find_next_eof_pos(curr_cmd, eof_pos);
		free(eof);
	}
	return (CMD_OK);
}

int32_t	append_pipe(char *curr_cmd, char **pipe, char join_char)
{
	char	*new_line;

	if (! trailing_pipe(curr_cmd))
		return (CMD_OK);
	while (true)		// need to update history for every new line
	{
		*pipe = ft_append_char(*pipe, join_char);
		if (! *pipe)
			return (CMD_MEM_ERR);
		new_line = ft_readline("> ");							// gives NULL if ctrl + D is pressed on empty line
		*pipe = ft_concat(*pipe, new_line);
		if (! *pipe)
			return (CMD_MEM_ERR);
		else if (! check_cmd(*pipe))
			return (CMD_SIN_ERR);
		if (! trailing_pipe(*pipe))
			break;
	}
	return (CMD_OK);
}

int32_t	read_cmd(char **curr_cmd)
{
	char	*input_to_append;
	char	*pipe_to_append;
	char	join_char;

	if ((! *curr_cmd) || (! **curr_cmd))
		return (CMD_EMPTY);
	if (! check_cmd(*curr_cmd))
		return (CMD_SIN_ERR);
	input_to_append = NULL;
	if (append_input(*curr_cmd, &input_to_append) == CMD_MEM_ERR)
		return (CMD_MEM_ERR);
	if (input_to_append)
		join_char = '\n';
	else
		join_char = ' ';
	pipe_to_append = NULL;
	if (append_pipe(*curr_cmd, &pipe_to_append, join_char) == CMD_MEM_ERR)
		return (CMD_MEM_ERR);
	// ...
	return (CMD_OK);
}

void	main_loop(void)
{
	t_raw_cmd	*history;
	char		*curr_cmd;
	int32_t		status;

	history = NULL;
	while (true)
	{
		curr_cmd = ft_readline("|-> ");						// gives NULL if ctrl + D is pressed on empty line
		if (! curr_cmd)
			printf("orcoddio\n");
		status = read_cmd(&curr_cmd);
		if (status == CMD_MEM_ERR)							// memory fault
			break ;
		else if (! ft_strncmp(curr_cmd, "end", 4))
		{
			ft_printf("END\n");
			free(curr_cmd);
			break ;
		}
		if (status != CMD_EMPTY)
			add_history(curr_cmd);
		if (status == CMD_SIN_ERR)
		{
			ft_printf("sintax error\n");
			free(curr_cmd);
		}
		else if (! add_raw_cmd(&history, curr_cmd))
			break;											// memory fault
	}
	clear_history();		// why rl_clear_history() doesn't work??
	print_cmds(history);
	free_cmds(&history);
}
