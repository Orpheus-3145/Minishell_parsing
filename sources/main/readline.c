/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:03:02 by faru              #+#    #+#             */
/*   Updated: 2023/05/19 19:13:52 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(const char *prompt)
{
	char	*new_string;
	char	*copy;

	new_string = readline(prompt);
	if (! new_string)					// readline failed!
		return (NULL);
	copy = ft_strdup(new_string);
	free(new_string);
	return (copy);
}

int32_t	build_cmd(char **curr_cmd, char *input_to_append, char *pipe_to_append)
{
	if (input_to_append)
	{
		*curr_cmd = ft_concat(*curr_cmd, input_to_append);
		if (! *curr_cmd)
			return (CMD_MEM_ERR);
		if (pipe_to_append)
		{
			*curr_cmd = ft_append_char(*curr_cmd, '\n');
			if (! *curr_cmd)
				return (CMD_MEM_ERR);
		}
	}
	if (pipe_to_append)
	{
		*curr_cmd = ft_concat(*curr_cmd, pipe_to_append);
		if (! *curr_cmd)
			return (CMD_MEM_ERR);
	}
	return (CMD_OK);
}

int32_t	read_cmd(char **curr_cmd)
{
	char	*input_to_append;
	char	*pipe_to_append;
	bool	last_pipe;

	*curr_cmd = ft_readline("|-> ");						// gives NULL if ctrl + D is pressed on empty line
	if (! *curr_cmd)
		printf("orcoddio\n");
	if ((! *curr_cmd) || (! **curr_cmd))
		return (CMD_EMPTY);
	if (! check_cmd(*curr_cmd))
		return (CMD_SIN_ERR);
	while (true)
	{
		input_to_append = NULL;
		pipe_to_append = NULL;
		last_pipe = ! trailing_pipe(*curr_cmd);
		if (append_input(*curr_cmd, &input_to_append) == CMD_MEM_ERR)
			return (CMD_MEM_ERR);
		if (input_to_append)
		{
			*curr_cmd = ft_concat(*curr_cmd, input_to_append);
			if (! *curr_cmd)
				return (CMD_MEM_ERR);
		}
		if (last_pipe)
			break ;
		if (append_pipe(&pipe_to_append) == CMD_MEM_ERR)
			return (CMD_MEM_ERR);
		if (pipe_to_append)
		{
			if (input_to_append)
			{
				*curr_cmd = ft_append_char(*curr_cmd, '\n');
				if (! *curr_cmd)
					return (CMD_MEM_ERR);
			}
			*curr_cmd = ft_concat(*curr_cmd, pipe_to_append);
			if (! *curr_cmd)
				return (CMD_MEM_ERR);
		}
		if (! trailing_pipe(*curr_cmd))
			break;
	}
	// ft_printf("input: %s\n", *curr_cmd);
	return (CMD_OK);
}

void	main_loop(void)
{
	t_raw_cmd	*history;
	char		*curr_cmd;
	int32_t		status;

	history = NULL;
	while (true)
	{
		status = read_cmd(&curr_cmd);
		if (status == CMD_MEM_ERR)							// memory fault
			break ;
		else if (! ft_strncmp(curr_cmd, "end", 4))
		{
			ft_printf("END\n");
			free(curr_cmd);
			break ;
		}
		if (status != CMD_EMPTY)
			add_history(curr_cmd);
		if (status == CMD_SIN_ERR)
		{
			ft_printf("sintax error\n");
			free(curr_cmd);
		}
		else if (! add_raw_cmd(&history, curr_cmd))
			break;											// memory fault
	}
	clear_history();		// why rl_clear_history() doesn't work??
	print_cmds(history);
	free_cmds(&history);
}
