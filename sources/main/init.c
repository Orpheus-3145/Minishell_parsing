/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:13:47 by fra               #+#    #+#             */
/*   Updated: 2023/05/18 18:25:10 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint32_t	number_cmds(char *cmd)
{
	uint32_t	count;

	count = 1;
	while (*cmd)
	{
		if (*cmd++ == '|')
		{
			if (*cmd == '|')
				cmd++;
			else
				count++;
		}
	}
	return (count);
}

bool	add_raw_cmd(t_raw_cmd **history, char *new_input)
{
	t_raw_cmd	*new_ele;
	t_raw_cmd	*tmp;
	
	new_ele	= malloc(sizeof(t_raw_cmd));
	if (! new_ele)
		return (false);
    new_ele->next = NULL;
    new_ele->cmd_input = new_input;
    new_ele->n_cmds = number_cmds(new_input);
    new_ele->cmd_list = malloc(new_ele->n_cmds * sizeof(t_cmd));
    if (! new_ele->cmd_list)
    {
        free(new_ele);
        return (false);
    }
    if (! *history)
        *history = new_ele;
    else
    {
        tmp = *history;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = new_ele;
    }
	return (true);
}

void    free_cmds(t_raw_cmd **list)
{
    t_raw_cmd   *to_free;

    while (*list)
    {
        to_free = *list;
        *list = (*list)->next;
        free(to_free->cmd_list);
        free(to_free->cmd_input);
        free(to_free);
    }
    *list = NULL;

}

void    print_cmds(t_raw_cmd *c_list)
{
    while (c_list)
    {
        ft_printf("cmd input: |%s|\nn cmds: %u\n\n", c_list->cmd_input, c_list->n_cmds);
        c_list = c_list->next;
    }
}