/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 21:26:00 by fra           #+#    #+#                 */
/*   Updated: 2023/05/26 17:47:12 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_quotes(char *cmd)
{
	bool	s_quotes_closed;
	bool	d_quotes_closed;

	s_quotes_closed = true;
	d_quotes_closed = true;
	while (*cmd)
	{
		if (*cmd == '\'')
			s_quotes_closed = ! (d_quotes_closed && s_quotes_closed);
		else if (*cmd == '\"')
			d_quotes_closed = ! (s_quotes_closed && d_quotes_closed);
		cmd++;
	}
	return (s_quotes_closed && d_quotes_closed);
}

bool    check_pipes(char *cmd)
{
	uint32_t	i;
	int32_t		last_pipe_pos;

	i = 0;
	while (ft_isspace(cmd[i]))
		i++;
	if (cmd[i] == '|')
		return (false);
	last_pipe_pos = -1;
	while(cmd[i])
	{
		if ((cmd[i] == '|') && is_outside_quotes(cmd, i))
		{
			if (last_pipe_pos != -1)
			{
				while(ft_isspace(cmd[++last_pipe_pos]))
					;
				if (last_pipe_pos == (int32_t) i)
					return (false);
			}
			last_pipe_pos = i;
		}
		i++;
	}
	return (true);
}

bool	check_redirections(char *cmd)
{
	uint32_t	i;
	char		open_arrow;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (is_valid_arrow(cmd, i))
		{
			open_arrow = cmd[i++];
			if (cmd[i] == open_arrow)
				i++;
			else if (is_arrow(cmd[i]) && (cmd[i] != open_arrow))
				return (false);
			while (ft_isspace(cmd[i]))
				i++;
			if (((cmd[i] == '|') || (is_arrow(cmd[i])) || (cmd[i] == '\0')))
				return (false);
		}
		else
			i++;
	}
	return (true);
}

bool	check_cmd(char *cmd)
{
	if (! cmd)
		return (false);
	if (! check_quotes(cmd))
		return (false);
	if (! check_pipes(cmd))
		return (false);
	if (! check_redirections(cmd))
		return (false);
	else
		return (true);
}
