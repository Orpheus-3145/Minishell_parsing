/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:25:47 by fra               #+#    #+#             */
/*   Updated: 2023/05/27 19:52:33 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void f(void)
{
	system("leaks minishell");
}

void	main_loop(t_var *depo)
{
	t_cmd_status	status;
	t_input			*input;
	char			*cmd;

	cmd = NULL;
	while (true)
	{
		status = read_input(&cmd);
		if ((status == CMD_MEM_ERR) || (status == CMD_NULL_ERR))
		{
			ft_free(cmd);
			break ;
		}
		else if (status != CMD_EMPTY)
			add_history(cmd);
		if (status == CMD_SIN_ERR)
			ft_printf("sintax error\n");
		else if ((status == CMD_OK) && ! is_only_spaces(cmd))
		{
			cmd = ft_trim(cmd);
			if (cmd == NULL)			// MEMORY FAULT
				break ;
			input = create_new_input(cmd);
			if (input == NULL)		// MEMORY FAULT
			{
				ft_free(cmd);
				break ;
			}
			append_new_input(depo, input);
		}
		cmd = NULL;
	}
	print_tokens(depo);
	clear_history();		// why rl_clear_history() doesn't work??
	free_input_list(depo->input_list);
	ft_free(depo);
}

int main(int argc, char**argv, char **envp) 
{
	t_var	*depo;
	
	argc++;
	argv++;
	depo = create_depo(envp);
	if (depo == NULL)
		return (EXIT_FAILURE);
	main_loop(depo);
	return (0);
}
