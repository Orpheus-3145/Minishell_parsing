/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:13:47 by fra               #+#    #+#             */
/*   Updated: 2023/05/29 15:46:25 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var   *create_depo(char **envp)
{
	t_var *depo;

	depo = ft_calloc(1, sizeof(t_var));
	if (depo == NULL)
		return (NULL);
	depo->env_arr = envp;
	depo->input_list = NULL;
	fill_list(&depo->env_list);
	return (depo);
}

t_input	*create_new_input(char *input, t_env *env_vars)
{
	t_input *new_input;

	new_input = ft_calloc(1, sizeof(t_input));
	if (new_input != NULL)
	{
		new_input->raw_input = input;
		new_input->exp_input = expand_vars(new_input->raw_input, env_vars);
		if (new_input->exp_input == NULL)
			return (ft_free(new_input));
		new_input->n_cmd = n_cmds(new_input->exp_input);
		new_input->cmd_data = create_new_cmd(new_input->exp_input, new_input->n_cmd);
		if (new_input->cmd_data == NULL)
		{
			ft_free(new_input->exp_input);
			return (ft_free(new_input));
		}
		new_input->next = NULL;
	}
	return (new_input);
}

void	append_new_input(t_var *depo, t_input *new_input)
{
	t_input *tmp;

	if (depo->input_list == NULL)
		depo->input_list = new_input;
	else
	{
		tmp = depo->input_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_input;
	}
}

void	free_input_list(t_input *input_list)
{
	t_input 	*to_free;
	uint32_t	i;

	while (input_list)
	{
		i = 0;
		while (i < input_list->n_cmd)
		{
			ft_free_double((void **) input_list->cmd_data[i].full_cmd, -1);
			ft_free_double((void **) input_list->cmd_data[i].files, -1);
			ft_free(input_list->cmd_data[i].redirections);
			i++;
		}
		ft_free(input_list->cmd_data);
		ft_free(input_list->raw_input);
		ft_free(input_list->exp_input);
		to_free = input_list;
		input_list = input_list->next;
		ft_free(to_free);
	}
}

t_cmd	*create_new_cmd(char *input, uint32_t n_cmds)
{
	t_cmd       *new_cmd;
	char        **str_cmds;
	bool		cmd_status;
	uint32_t    i;

	str_cmds = split_into_cmds(input);
	if (str_cmds == NULL)
		return (NULL);
	new_cmd = ft_calloc(n_cmds, sizeof(t_cmd));
	if (new_cmd == NULL)
		return (ft_free_double((void **) str_cmds, -1));
	i = 0;
	while (i < n_cmds)
	{
		new_cmd->fd_in = 0;
		new_cmd->fd_out = 1;
		// ft_printf("splitting: %s\n", str_cmds[i]);
		cmd_status = split_input(new_cmd, str_cmds[i]);
		if (cmd_status == false)
		{
			ft_free(new_cmd);
			return (ft_free_double((void **) str_cmds, -1));
		}
		new_cmd++;
		i++;
	}
	new_cmd -= n_cmds;
	ft_free_double((void **) str_cmds, -1);
	return (new_cmd);
}
