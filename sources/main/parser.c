/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:26:00 by fra               #+#    #+#             */
/*   Updated: 2023/05/19 17:43:59 by fra              ###   ########.fr       */
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
	bool		quotes_flag;

	i = 0;
	while (ft_isspace(cmd[i]))
		i++;
	if (cmd[i] == '|')
		return (false);
	last_pipe_pos = -1;
	quotes_flag = false;
	while(cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			quotes_flag = ! quotes_flag;
		if (! quotes_flag && (cmd[i] == '|'))
		{
			if (last_pipe_pos != -1)
			{
				if (cmd[i - 1] == '|')
				{
					if (cmd[i + 1] && cmd[i + 1] == '|')
						return (false);
				}
				else
				{
					while (ft_isspace(cmd[++last_pipe_pos]))
						;
					if ((last_pipe_pos >= (int32_t) i) || (cmd[last_pipe_pos] == '<') || (cmd[last_pipe_pos] == '>'))
						return (false);
				}

			}
			last_pipe_pos = i;
		}
		i++;
	}
	return (true);
}

bool	check_redirections(char *cmd)
{
	bool	quotes_flag;

	quotes_flag = false;
	while (*cmd)
	{
		if (is_quote(*cmd))
			quotes_flag = ! quotes_flag;
		if (! quotes_flag && is_arrow(*cmd))
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
			if ((! quotes_flag) && ((*cmd == '|') || (is_arrow(*cmd)) || (! *cmd)))
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
	else if (! check_quotes(cmd))
		return (false);
	else if (! check_pipes(cmd))
		return (false);
	else if (! check_redirections(cmd))
		return (false);
	else
		return (true);
}
