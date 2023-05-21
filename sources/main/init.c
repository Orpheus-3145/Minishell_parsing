/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:13:47 by fra               #+#    #+#             */
/*   Updated: 2023/05/21 20:00:59 by fra              ###   ########.fr       */
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

void append_new_cmd(t_var *depo, t_input *new_input)
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

    str_cmds = ft_split(input, '|');
    if (str_cmds == NULL)
        return (NULL);
    n_elems = ft_count_occ(input, '|');
    new_cmd = ft_calloc(n_elems, sizeof(t_cmd));
    if (new_cmd == NULL)
    {
        free(str_cmds);
        return (NULL);
    }
    i = 0;
    while (str_cmds[i] != NULL)
    {
        // new_cmd[i].cmd_name = get_cmd_name(str_cmds[i]);
        // new_cmd[i].cmd_full = get_cmd_full(str_cmds[i]);
        // new_cmd[i].redirect = get_redirect(str_cmds[i]);
        // new_cmd[i].file = get_file(str_cmds[i]);
        // check NULL
        new_cmd[i].env_list = env_list;
        new_cmd[i].env_arr = env_arr;
        i++;
    }
    return (new_cmd);
}

t_input *create_new_input(char *input, t_env  *env_list, char	**env_arr)
{
    t_input *new_input;

    new_input = ft_calloc(1, sizeof(t_input));
    if (new_input != NULL)
    {
        new_input->next = NULL;
        new_input->n_cmd = ft_count_occ(input, '|');
        new_input->cmd_data = create_new_cmd(input, env_list, env_arr);
        if (new_input->cmd_data == NULL)
        {
            free(new_input);
            return (NULL);
        }
    }
    return (new_input);
}
