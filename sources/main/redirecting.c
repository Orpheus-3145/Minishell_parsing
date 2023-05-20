/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:46:55 by fra               #+#    #+#             */
/*   Updated: 2023/05/20 04:39:13 by fra              ###   ########.fr       */
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

char	*read_stdin(char *buffer)
{
	char	*new_line;
	char	*eof;
	int32_t	eof_pos;
	bool	keep_reading;
	
	eof_pos = find_next_eof_pos(buffer, 0);
	while (eof_pos != -1)
	{
		eof = find_eof(buffer + eof_pos);
		keep_reading = true;
		while (keep_reading)
		{
			if (ft_readline(&new_line, "> ", false) == CMD_MEM_ERR)
				return (NULL);
			buffer = ft_append_char(buffer, '\n');
			if (! buffer)
				return (NULL);
			keep_reading = ft_strncmp(new_line, eof, ft_strlen(eof) + 1);
			buffer = ft_concat(buffer, new_line);
			if (! buffer)
				return (NULL);
		}
		eof_pos = find_next_eof_pos(buffer, eof_pos);
		free(eof);
	}
	return (buffer);
}
