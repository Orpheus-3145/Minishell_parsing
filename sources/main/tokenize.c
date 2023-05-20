/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:08:10 by fra               #+#    #+#             */
/*   Updated: 2023/05/20 20:31:23 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(char *raw_input)
{
	t_cmd		*new_cmd;
	char		**str_cmds;
	uint32_t	n_cmds;
	uint32_t	i;

	n_cmds = ft_count_occ(raw_input, '|') + 1;
	new_cmd = ft_calloc(n_cmds, sizeof(t_cmd));
	if (new_cmd == NULL)
		return (NULL);
	str_cmds = ft_split(raw_input, '|');
	if (str_cmds == NULL)
	{
		free(new_cmd);
		return (NULL);
	}
	i = 0;
	while (i < n_cmds)
	{
		new_cmd[i].cmd_name = ft_strdup(str_cmds[i]);
		if (new_cmd[i].cmd_name == NULL)
		{
			while(i--)
				free(new_cmd[i].cmd_name);
			free(new_cmd);
			free(str_cmds);
			return (NULL);
		}
		i++;
	}
	free(str_cmds);
	return (new_cmd);
}
