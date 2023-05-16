/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:25:47 by fra               #+#    #+#             */
/*   Updated: 2023/05/16 20:31:36 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_cmd_to_hist(void)
{
	char *cmd;
	
	cmd = NULL;
	while (true)
	{
		cmd = readline("|-> ");
		
	}
	if (cmd && *cmd)
		add_history(cmd);
	if (! ft_strncmp((const char *) cmd, "end", 3))
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
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

int main() 
{
	// test_redirections();
	test_pipes();
	read_and_store();
	return (0);
}
