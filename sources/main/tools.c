/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:09:49 by fra               #+#    #+#             */
/*   Updated: 2023/05/24 00:55:55 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint32_t	n_cmds(char *string)
{
	uint32_t	cnt;
	uint32_t	curr_pos;

	cnt = 1;
	curr_pos = 0;
	while (string[curr_pos])
	{
		if ((string[curr_pos] == '|') && is_outside_quotes(string, curr_pos))
			cnt++;
		curr_pos++;
	}
	return (cnt);
}

char	**split_into_cmds(char *input_cmd)
{
	char		**cmds;
	uint32_t	i;
	uint32_t	len;

	cmds = ft_calloc(n_cmds(input_cmd) + 1, sizeof(char *));
	if (! cmds)
		return (NULL);
	i = 0;
	while (*input_cmd)
	{
		len = 0;
		while (input_cmd[len])
		{
			if (is_valid_pipe(input_cmd, len))
				break ;
			len++;
		}
		cmds[i] = ft_trim(ft_substr(input_cmd, 0, len), true);
		if (cmds[i] == NULL)
			return (ft_free_double((void ***) &cmds, i));
		i++;
		input_cmd += len + (input_cmd[len] != 0);
	}
	return (cmds);
}
