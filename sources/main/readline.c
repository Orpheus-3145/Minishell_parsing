/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 11:03:02 by faru          #+#    #+#                 */
/*   Updated: 2023/05/17 17:45:42 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	trailing_pipe(char	*cmd)
{
	uint32_t	len_cmd;

	len_cmd = ft_strlen(cmd);
	while (len_cmd && ft_isspace(cmd[--len_cmd]))
		;
	return (cmd[len_cmd] == '|');
}

bool	heredoc(char *cmd)
{
	uint32_t	len_cmd;

	len_cmd = ft_strlen(cmd);
	while (len_cmd && ft_isspace(cmd[--len_cmd]))
		;
	return (cmd[len_cmd] == '|');
}
char	*add_cmd_to_hist(void)
{
	char	*cmd;
	char	*trimmed;
	
	cmd = readline("|-> ");
	while (trailing_pipe(cmd))
	{
		cmd = ft_append_char(cmd, ' ');
		if (! cmd)
			return (NULL);		// memory fault
		cmd = ft_concat(cmd, readline("> "));
		if (! cmd)
			return (NULL);		// memory fault
	}
	trimmed = ft_trim(cmd);
	if (! trimmed)
		return (NULL);			// memory fault
	if (*trimmed)
		add_history(trimmed);
	return (trimmed);
}

void	read_and_store(void)
{
	char	*curr_cmd;
	t_raw_cmd	*history;

	history = NULL;
	while (true)
	{
		curr_cmd = add_cmd_to_hist();
		if (! curr_cmd)
			break;
		if (! check_cmd(curr_cmd))
		{
			ft_printf("sintax error!\n");
			free(curr_cmd);
		}
		else if (! add_raw_cmd(&history, curr_cmd))
		{
			// memory fail -> kill program
			break;
		}
	}
	clear_history();
	print_cmds(history);
	free_cmds(&history);
}