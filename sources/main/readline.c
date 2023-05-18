/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:03:02 by faru              #+#    #+#             */
/*   Updated: 2023/05/18 21:36:50 by fra              ###   ########.fr       */
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
	return (cmd[len_cmd] == '|');
}

bool	is_quote(char to_check)
{
	return ((to_check == '\'') || (to_check == '\"'));
}

bool	is_arrow(char to_check)
{
	return ((to_check == '<') || (to_check == '>'));
}

int32_t	find_next_eof_pos(char *cmd)
{
	uint32_t	pos;
	bool		open_quotes;

	pos = 0;
	open_quotes = false;
	while (cmd && cmd[pos] && (cmd[pos] != '\n'))
	{
		if (is_quote(cmd[pos]))
			open_quotes = ! open_quotes;
		else if (cmd[pos] == '<')
		{
			if (cmd[pos + 1] && (cmd[pos + 1] == '<'))
				return (pos + 2);
		}
		pos++;
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
	return (copy);
}

char	*new_cmd(void)
{
	char	*cmd;
	int32_t	eof_pos;
	char	*new_line;
	char	*eof;
	char	join_char;

	cmd = ft_readline("|-> ");									// puo' ritornare NULL
	if ((! cmd) || (! *cmd))
		return (cmd);
	if (! check_cmd(cmd))
	{
		ft_printf("sintax error!\n");
		return (cmd);
	}
	eof_pos = find_next_eof_pos(cmd);
	if (eof_pos != -1)
		join_char = '\n';
	else
		join_char = ' ';
	while (eof_pos != -1)
	{
		new_line = ft_readline("> ");							// puo' ritornare NULL
		eof = find_eof(cmd + eof_pos);
		while (ft_strncmp(new_line, eof, ft_strlen(eof)))
		{
			cmd = ft_append_char(cmd, join_char);
			if (! cmd)
				return (NULL);								// memory fault
			cmd = ft_concat(cmd, new_line);
			if (! cmd)
				return (NULL);								// memory fault
			new_line = ft_readline("> ");							// puo' ritornare NULL
		}
		ft_printf("str tmp: |%s|\n", cmd + eof_pos);
		eof_pos = find_next_eof_pos(cmd + eof_pos);
		free(new_line);
		free(eof);
	}
	while (trailing_pipe(cmd))
	{
		cmd = ft_append_char(cmd, join_char);
		if (! cmd)											// memory fault
			return (NULL);
		new_line = readline("> ");							// puo' ritornare NULL
		cmd = ft_concat(cmd, new_line);
		if (! cmd)
			return (NULL);									// memory fault
		if (! check_cmd(new_line))
		{
			ft_printf("sintax error!\n");
			return (cmd);
		}
	}
	return (cmd);
}

void	main_loop(void)
{
	t_raw_cmd	*history;
	char		*curr_cmd;
	uint32_t	i;

	history = NULL;
	while (true)
	{
		curr_cmd = new_cmd();
		if (! curr_cmd)				// memory fault
			break ;
		else if (strncmp(curr_cmd, "end", 3) == 0)
		{
			free(curr_cmd);
			break ;
		}
		else
			add_history(curr_cmd);
		i = 0;
		while (ft_isspace(curr_cmd[i]))
			i++;
		if (curr_cmd[i])
		{
			if (! add_raw_cmd(&history, curr_cmd))
				break;				// memory fault
		}
		else
			free(curr_cmd);
	}
	clear_history();
	print_cmds(history);
	free_cmds(&history);
}