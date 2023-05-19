/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:46:55 by fra               #+#    #+#             */
/*   Updated: 2023/05/19 17:47:24 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
