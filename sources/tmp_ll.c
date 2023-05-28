/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_ll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:01:04 by faru              #+#    #+#             */
/*   Updated: 2023/05/29 00:03:04 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fill_list(t_env **list)
{
    *list = ft_calloc(1, sizeof(t_env));
    (*list)->key = "key1";
    (*list)->value = "prova split ciao";
    
    (*list)->next = ft_calloc(1, sizeof(t_env));
    (*list)->next->key = "key2";
    (*list)->next->value = "value2";
    
    (*list)->next->next = ft_calloc(1, sizeof(t_env));
    (*list)->next->next->key = "key3";
    (*list)->next->next->value = "value3";
    
    (*list)->next->next->next = ft_calloc(1, sizeof(t_env));
    (*list)->next->next->next->key = "key4";
    (*list)->next->next->next->value = "value4";
    
    (*list)->next->next->next->next = NULL;
}

void free_list(t_env *list)
{
    ft_free(list->next->next->next);
    ft_free(list->next->next);
    ft_free(list->next);
    ft_free(list);
}