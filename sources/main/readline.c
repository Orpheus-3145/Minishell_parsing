/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:03:02 by faru              #+#    #+#             */
/*   Updated: 2023/05/20 19:11:28 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_status	ft_readline(char **buffer, const char *prompt, bool check_sin)
{
	char	*new_string;

	new_string = readline(prompt);
	if (! new_string)				// gives NULL if ctrl + D is pressed on empty line
		return (CMD_NULL_INPUT);
	*buffer = ft_strdup(new_string);
	free(new_string);
	if (*buffer == NULL)
		return (CMD_MEM_ERR);
	else if (**buffer == '\0')
		return (CMD_EMPTY);
	else if (check_sin && (check_cmd(*buffer) == false))
		return (CMD_SIN_ERR);
	else
		return (CMD_OK);
}

t_cmd_status	concat_input(char **base, char *buffer)
{
	if (*base != NULL)
	{
		*base = ft_append_char(*base, '\n');
		if (*base == NULL)
			return (CMD_MEM_ERR);
	}
	*base = ft_concat(*base, buffer);
	if (*base == NULL)
		return (CMD_MEM_ERR);
	else
		return (CMD_OK);
}

t_cmd_status	read_input(char **curr_cmd)
{
	t_cmd_status	status;
	bool			open_pipe;
	char			*buffer;
	
	status = ft_readline(&buffer, "-> ", true); 
	while (status != CMD_MEM_ERR)
	{
		if ((status == CMD_EMPTY) && (*curr_cmd == NULL))
			break ;
		// else if (status == CMD_NULL_INPUT)
		// 	// ...
		else if (status == CMD_OK)
		{
			open_pipe = trailing_pipe(buffer);
			buffer = read_stdin(buffer);
			if (buffer == NULL)
				return (CMD_MEM_ERR);
		}
		if ((concat_input(curr_cmd, buffer) == CMD_MEM_ERR) || (open_pipe == false))
			break ;
		status = ft_readline(&buffer, "> ", true); 
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
		status = read_input(&curr_cmd);
		if (status == CMD_MEM_ERR)
		{
			if (curr_cmd)
				free(curr_cmd);
			break ;
		}
		else if (status == CMD_SIN_ERR)
			ft_printf("sintax error\n");
		if (status != CMD_EMPTY)
			add_history(curr_cmd);
		else
		{
			if (curr_cmd)
				free(curr_cmd);
		}
		if ((status != CMD_SIN_ERR) && (status != CMD_EMPTY) && (! add_raw_cmd(&history, curr_cmd)))
			break;
		curr_cmd = NULL;
	}
	clear_history();		// why rl_clear_history() doesn't work??
	print_cmds(history);
	free_cmds(&history);
}
