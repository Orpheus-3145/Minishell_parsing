/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:46:14 by fra               #+#    #+#             */
/*   Updated: 2023/05/19 17:46:40 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool	trailing_pipe(char	*cmd)
{
	uint32_t	len_cmd;

	if (! cmd || (*cmd == '\0'))
		return (false);
	len_cmd = ft_strlen(cmd) - 1;
	while (len_cmd && ft_isspace(cmd[len_cmd]))
		len_cmd--;
	if (len_cmd <= 1)
		return (false);
	else
		return ((cmd[len_cmd] == '|') && (cmd[len_cmd - 1] != '|'));
}

int32_t	append_pipe(char *curr_cmd, char **pipe)
{
	char	*new_line;

	if (! trailing_pipe(curr_cmd))
		return (CMD_OK);
	while (true)		// need to update history for every new line
	{
		*pipe = ft_append_char(*pipe, ' ');
		if (! *pipe)
			return (CMD_MEM_ERR);
		new_line = ft_readline("> ");							// gives NULL if ctrl + D is pressed on empty line
		*pipe = ft_concat(*pipe, new_line);
		if (! *pipe)
			return (CMD_MEM_ERR);
		else if (! check_cmd(*pipe))
			return (CMD_SIN_ERR);
		if (! trailing_pipe(*pipe))
			break;
	}
	return (CMD_OK);
}
