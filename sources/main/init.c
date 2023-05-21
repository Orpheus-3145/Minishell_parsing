/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:13:47 by fra               #+#    #+#             */
/*   Updated: 2023/05/21 22:54:01 by fra              ###   ########.fr       */
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
		free(depo->input_list->raw_input);
		free(depo->input_list->cmd_data);
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

t_cmd *create_new_cmd(char *input, t_env  *env_list, char	**env_arr)
{
	t_cmd       *new_cmd;
	char        **str_cmds;
	uint32_t    n_elems;
	uint32_t    i;

	str_cmds = ft_split(input, '|');		// NB pipes inside quotes must be ignored!
	if (str_cmds == NULL)
		return (NULL);
	n_elems = ft_count_occ(input, '|');		// NB pipes inside quotes must be ignored!
	new_cmd = ft_calloc(n_elems, sizeof(t_cmd));
	if (new_cmd == NULL)
		return (ft_free_double((void ***) &str_cmds, -1));
	i = 0;
	while (i < n_elems)
	{
		// if (! tokenize(new_cmd + i, str_cmds[i]))
		// {
		// 	free(new_cmd);
		// 	return (ft_free_double((void ***) &str_cmds, -1));
		// }
		new_cmd[i].env_list = env_list;
		new_cmd[i].env_arr = env_arr;
		free(str_cmds[i]);
		i++;
	}
	ft_free_double((void ***) &str_cmds, -1);
	return (new_cmd);
}

t_input *create_new_input(char *input, t_env  *env_list, char	**env_arr)
{
	t_input *new_input;

	new_input = malloc(sizeof(t_input));
	if (new_input != NULL)
	{
		new_input->raw_input = input;
		new_input->n_cmd = ft_count_occ(input, '|');
		new_input->cmd_data = create_new_cmd(input, env_list, env_arr);
		if (new_input->cmd_data == NULL)
		{
			free(new_input);
			return (NULL);
		}
		new_input->next = NULL;
	}
	return (new_input);
}
