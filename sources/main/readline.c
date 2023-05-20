/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:03:02 by faru              #+#    #+#             */
/*   Updated: 2023/05/20 21:37:04 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_status	ft_readline(char **buffer, const char *prompt, bool check_sin)
{
	char	*new_string;

	new_string = readline(prompt);
	if (! new_string)				// gives NULL if ctrl + D is pressed on empty line
		return (CMD_NULL_ERR);
	*buffer = ft_strdup(new_string);
	free(new_string);
	if (*buffer == NULL)
		return (CMD_MEM_ERR);
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

	open_pipe = false;
	status = ft_readline(&buffer, "-> ", true); 
	while (status != CMD_MEM_ERR)
	{
		// if (status == CMD_NULL_ERR)
		// 	// ...
		if (status == CMD_OK)
		{
			open_pipe = trailing_pipe(buffer);
			if ((*buffer == '\0') && (*curr_cmd != NULL))
				open_pipe = true;
			buffer = read_stdin(buffer);
			if (buffer == NULL)
				return (CMD_MEM_ERR);
		}
		if ((concat_input(curr_cmd, buffer) == CMD_MEM_ERR) || (open_pipe == false) || (status == CMD_SIN_ERR))
			break ;
		status = ft_readline(&buffer, "> ", true); 
	}
	return (status);
}

void	main_loop(t_var *main_var)
{
	t_cmd_status	status;
	char			*input;
	main_var++;

	input = NULL;
	while (true)
	{
		status = read_input(&input);
		if (status == CMD_MEM_ERR)
		{
			if (input)
				free(input);
			break ;
		}
		// if (status == CMD_NULL_ERR)
		// 	// ...
		if (*input != '\0')
			add_history(input);
		if (status == CMD_SIN_ERR)
			ft_printf("sintax error\n");
		else
			// tokenize command and execute it
		input = NULL;
	}
	clear_history();		// why rl_clear_history() doesn't work??
}
