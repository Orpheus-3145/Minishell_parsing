/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:03:02 by faru              #+#    #+#             */
/*   Updated: 2023/05/20 04:38:01 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_status	ft_readline(char **buffer, const char *prompt, bool check)
{
	char	*new_string;

	new_string = readline(prompt);
	if (! new_string)				// gives NULL if ctrl + D is pressed on empty line
		return (CMD_NULL_INPUT);
	*buffer = ft_strdup(new_string);
	free(new_string);
	if (buffer == NULL)
		return (CMD_MEM_ERR);
	else if (**buffer == '\0')
		return (CMD_EMPTY);
	else if (check && (check_cmd(*buffer) == false))
		return (CMD_SIN_ERR);
	else
		return (CMD_OK);
}

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
		return (cmd[len_cmd] == '|');
}

t_cmd_status	single_cmd(char **curr_cmd, char *prompt)
{
	bool		open_pipe;
	char		*buffer;
	t_cmd_status status;

	status = ft_readline(&buffer, prompt, true);
	if (status == CMD_OK)
	{
		open_pipe = trailing_pipe(buffer);
		buffer = read_stdin(buffer);
		if (! buffer)
			return (CMD_MEM_ERR);
		*curr_cmd = ft_concat(*curr_cmd, buffer);
		if (! *curr_cmd)
			return (CMD_MEM_ERR);
		else if (open_pipe)
			return (CMD_OPEN_PIPE);
		else
			return (CMD_OK);
	}
	return (status);
}

t_cmd_status	read_cmd(char **curr_cmd)
{
	t_cmd_status	status;
	char			join_char;

	status = single_cmd(curr_cmd, "-> ");
	join_char = ' ';
	while (status == CMD_OPEN_PIPE)
	{
		if (ft_strnstr(*curr_cmd, "<<", ft_strlen(*curr_cmd)))
			join_char = '\n';
		*curr_cmd = ft_append_char(*curr_cmd, join_char);
		if (! *curr_cmd)
			return (CMD_MEM_ERR);
		status = single_cmd(curr_cmd, "> ");
	}
	return (status);
}

void	main_loop(void)
{
	t_raw_cmd	*history;
	char		*curr_cmd;
	t_cmd_status		status;

	history = NULL;
	curr_cmd = NULL;
	while (true)
	{
		status = read_cmd(&curr_cmd);
		if (status == CMD_MEM_ERR)				// memory fault
			break ;
		else if (status == CMD_SIN_ERR)
			ft_printf("sintax error\n");
		if (status != CMD_EMPTY)
			add_history(curr_cmd);
		else
			free(curr_cmd);
		if ((status != CMD_SIN_ERR) && (status != CMD_EMPTY) && (! add_raw_cmd(&history, curr_cmd)))
			break;											// memory fault
		curr_cmd = NULL;
	}
	clear_history();		// why rl_clear_history() doesn't work??
	print_cmds(history);
	free_cmds(&history);
}
