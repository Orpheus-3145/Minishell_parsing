/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:26:00 by fra               #+#    #+#             */
/*   Updated: 2023/05/16 00:34:05 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// needs to receive a non-NULL string, must be at least 1-char long
// it is supposed to never have a | as the trailing char
bool    check_pipes(char *cmd)
{
	uint32_t	i;
	int32_t		last_pipe_pos;

	i = 0;
	if (cmd[i++] == '|')
		return (false);
	last_pipe_pos = -1;
	while(cmd[i])
	{
		if (cmd[i] == '|')
		{
			if (last_pipe_pos != -1)
			{
				if (cmd[i - 1] == '|')
				{
					if (cmd[i + 1] && cmd[i + 1] == '|')
						return (false);
				}
				else if (! check_between_pipes(cmd, last_pipe_pos + 1, i))
					return (false);
			}
			last_pipe_pos = i;
		}
		i++;
	}
	return (true);
}

bool	check_between_pipes(char *str, int32_t pos1, int32_t pos2)
{
	while (pos1 < pos2)
	{
		if (! ft_isspace(str[pos1]))
			return (true);
		pos1++;
	}
	return (false);
}
