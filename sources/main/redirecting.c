/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirecting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 17:46:55 by fra           #+#    #+#                 */
/*   Updated: 2023/05/26 17:59:15 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	find_next_eof_pos(char *cmd, uint32_t start_pos)
{
	while (cmd && cmd[start_pos] && (cmd[start_pos] != '\n'))
	{
		if (cmd[start_pos] == '<' && is_outside_quotes(cmd, start_pos))
		{
			start_pos++;
			if (cmd[start_pos] == '<')
			{
				start_pos++;
				while (ft_isspace(cmd[start_pos]))
					start_pos++;
				return (start_pos);
			}
		}
		else
			start_pos++;
	}
	return (-1);
}

char	*isolate_eof(char *start)
{
	char 		start_quote;
	char 		*eof;
	uint32_t	i;

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
	char			*new_line;
	char			*eof;
	int32_t			eof_pos;
	bool			keep_reading;
	t_cmd_status	status;
	
	eof_pos = find_next_eof_pos(buffer, 0);
	while (eof_pos != -1)
	{
		eof = isolate_eof(buffer + eof_pos);
		if (eof == NULL)
		{
			free(buffer);
			return (NULL);
		}
		keep_reading = true;
		while (keep_reading)
		{
			status = ft_readline(&new_line, "> ", false);
			if (status == CMD_MEM_ERR)
				break ;
			keep_reading = ft_strncmp(new_line, eof, ft_strlen(eof) + 1) != 0;
			status = concat_input(&buffer, new_line);
			if (status == CMD_MEM_ERR)
				break ;
		}
		free(eof);
		if (status == CMD_MEM_ERR)
			return (NULL);
		eof_pos = find_next_eof_pos(buffer, eof_pos);
	}
	return (buffer);
}
