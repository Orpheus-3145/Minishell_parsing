/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:25:47 by fra               #+#    #+#             */
/*   Updated: 2023/05/21 20:02:00 by fra              ###   ########.fr       */
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
		if (status == CMD_MEM_ERR)
		{
			if (cmd)
				free(cmd);
			break ;
		}
		// if (status == CMD_NULL_ERR)
		// 	// ...
		if (*cmd != '\0')
			add_history(cmd);
		if (status == CMD_SIN_ERR)
			ft_printf("sintax error\n");
		else
		{
			input = create_new_input(cmd, depo->env_list, depo->env_arr);
			if (input == NULL)		// MEMORY FAULT
			{
				free(cmd);
				break ;
			}
			append_new_cmd(depo, input);
		}
		cmd = NULL;
	}
	clear_history();		// why rl_clear_history() doesn't work??
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
