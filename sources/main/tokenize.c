/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 17:08:10 by fra           #+#    #+#                 */
/*   Updated: 2023/05/17 11:03:09 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd(t_cmd **history, t_raw_cmd *raw_cmd)
{
    raw_cmd++;
    history++;
	// t_cmd	*new_ele;
	// t_cmd	*tmp;
	
	// new_ele	= malloc(sizeof(t_cmd));
	// if (! new_ele)
	// 	ft_printf("errorz!\n");
	// else
	// {
	// 	new_ele->cmd_name = cmd[0];
	// 	new_ele->cmd_full = cmd;
	// 	new_ele->file = file_name;
	// 	new_ele->redirect = redirect;
	// }
	// if (! *history)
	// 	*history = new_ele;
	// else
	// {
	// 	tmp = *history;
	// 	while(tmp->next)
	// 		tmp = tmp->next;
	// 	tmp->next = new_ele;
	// }
}