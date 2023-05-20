/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:26:00 by fra               #+#    #+#             */
/*   Updated: 2023/05/20 21:28:16 by fra              ###   ########.fr       */
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
	char		quotes;
	bool		open_quotes;

	i = 0;
	while (ft_isspace(cmd[i]))
		i++;
	if (cmd[i] == '|')
		return (false);
	last_pipe_pos = -1;
	open_quotes = false;
	while(cmd[i])
	{
		if (is_quote(cmd[i]))
		{
			if ((open_quotes == true) && (cmd[i] == quotes))
			{
				quotes = '\0';
				open_quotes = false;
			}
			else if (open_quotes == false)
			{
				quotes = cmd[i];
				open_quotes = true;
			}
		}
		else if ((open_quotes == false) && (cmd[i] == '|'))
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
	char		quotes;
	bool		open_quotes;

	open_quotes = false;
	while (*cmd)
	{
		if (is_quote(*cmd))
		{
			if ((open_quotes == true) && (*cmd == quotes))
			{
				quotes = '\0';
				open_quotes = false;
			}
			else if (open_quotes == false)
			{
				quotes = *cmd;
				open_quotes = true;
			}
		}
		if ((open_quotes == false) && is_arrow(*cmd))
		{
			if (*cmd == '<')
			{
				cmd++;
				if (! *cmd || (*cmd == '>'))
					return (false);
				else if (*cmd == '<')
					cmd++;
			}
			else if (*cmd == '>')
			{
				cmd++;
				if (! *cmd || (*cmd == '<'))
					return (false);
				else if (*cmd == '>')
					cmd++;
			}
			while (ft_isspace(*cmd))
				cmd++;
			if (((*cmd == '|') || (is_arrow(*cmd)) || (! *cmd)))
				return (false);
		}
		else
			cmd++;
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
