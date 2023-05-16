/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:26:00 by fra               #+#    #+#             */
/*   Updated: 2023/05/16 20:30:16 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// it is supposed to never have a | as the trailing char
bool    check_pipes(char *cmd)
{
	uint32_t	i;
	int32_t		last_pipe_pos;
	bool		quotes_flag;

	i = 0;
	if (cmd[i++] == '|')
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
					if (last_pipe_pos == (int32_t) i)
						return (false);
				}

			}
			last_pipe_pos = i;
		}
		i++;
	}
	if (last_pipe_pos != -1)
	{
		while(ft_isspace(cmd[++last_pipe_pos]))
			;
		if (! cmd[last_pipe_pos])
			return (false);
	}
	return (true);
}

bool	check_quotes(char *cmd)
{
	bool	closed_quotes;

	closed_quotes = true;
	while(*cmd)
	{
		if (*cmd == '\'' || *cmd == '\"')
			closed_quotes = ! closed_quotes;
		cmd++;
	}
	return (closed_quotes);
}

bool	check_redirections(char *str)
{
	bool	input_red;
	bool	output_red;
	bool	quotes_flag;

	input_red = false;
	output_red = false;
	quotes_flag = false;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			quotes_flag = ! quotes_flag;
		if (! quotes_flag && ((*str == '<') || (*str == '>')))
		{
			if (*str == '<')
			{
				if (input_red)
					return (false);
				input_red = true;
				str++;
				if (*str == '>')
					return (false);
				else if (*str == '<')
					str++;
			}
			else if (*str == '>')
			{
				if (output_red)
					return (false);
				output_red = true;
				str++;
				if (*str == '<')
					return (false);
				else if (*str == '>')
					str++;
			}
			while (ft_isspace(*str))
				str++;
			if (! *str || (*str == '|') || (*str == '<') || (*str == '>'))
				return (false);
		}
		if (! quotes_flag &&  (*str == '|'))
		{
			input_red = false;
			output_red = false;
		}
		str++;
	}
	return (true);
}

bool	check_cmd(char *cmd)
{
	if (! cmd || ! *cmd)
		return (false);
	while (ft_isspace(*cmd))
		cmd++;
	if (! check_quotes(cmd))
		return (false);
	else if (! check_pipes(cmd))
		return (false);
	else if (! check_redirections(cmd))
		return (false);
	else
		return (true);
}
