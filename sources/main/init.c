/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:13:47 by fra               #+#    #+#             */
/*   Updated: 2023/05/24 01:24:19 by fra              ###   ########.fr       */
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
	// ...
	return (depo);
	
}

void	free_depo(t_var *depo)
{
	t_input *to_free;

	while (depo->input_list)
	{
		free_tokens(depo->input_list->cmd_data->tokens);
		free(depo->input_list->cmd_data->_cmd);
		free(depo->input_list->cmd_data);
		free(depo->input_list->raw_input);
		to_free = depo->input_list;
		depo->input_list = depo->input_list->next;
		free(to_free);
	}
	free(depo);
}

void append_new_input(t_var *depo, t_input *new_input)
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

t_cmd	*create_new_cmd(char *input, uint32_t n_cmds)
{
	t_cmd       *new_cmd;
	char        **str_cmds;
	uint32_t    i;

	str_cmds = split_into_cmds(input);
	if (str_cmds == NULL)
		return (NULL);
	new_cmd = ft_calloc(n_cmds, sizeof(t_cmd));
	if (new_cmd == NULL)
		return (ft_free_double((void ***) &str_cmds, -1));
	i = 0;
	while (i < n_cmds)
	{
		new_cmd->_cmd = str_cmds[i];
		new_cmd->tokens = tokenize(str_cmds[i]);
		// if (new_cmd->tokens == NULL)
		// {
		// 	free(new_cmd);
		// 	return (ft_free_double((void ***) &str_cmds, -1));
		// }
		new_cmd++;
	}
	free(str_cmds[i]);
	free(str_cmds);
	return (new_cmd);
}

t_input	*create_new_input(char *input)
{
	t_input *new_input;

	new_input = malloc(sizeof(t_input));
	if (new_input != NULL)
	{
		new_input->raw_input = ft_trim(input, true);
		if (new_input->raw_input == NULL)
		{
			free(new_input);
			return (NULL);
		}
		new_input->n_cmd = n_cmds(new_input->raw_input);
		new_input->cmd_data = create_new_cmd(new_input->raw_input, new_input->n_cmd);
		if (new_input->cmd_data == NULL)
		{
			free(new_input->raw_input);
			free(new_input);
			return (NULL);
		}
		new_input->next = NULL;
	}
	return (new_input);
}
