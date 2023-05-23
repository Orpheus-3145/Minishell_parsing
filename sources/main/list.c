/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 13:56:10 by faru          #+#    #+#                 */
/*   Updated: 2023/05/23 15:35:59 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *new_token(char *word, t_type_token type)
{
	t_token	*new_ele;

	new_ele = ft_calloc(1, sizeof(t_token));
	if (new_ele)
	{
		new_ele->next = NULL;
		new_ele->prev = NULL;
		new_ele->word = word;
		new_ele->type = type;
	}
	return (new_ele);
}

void	append_token(t_token **token_list, t_token *new_token)
{
	t_token	*tmp;

	if (*token_list == NULL)
		*token_list = new_token;
	else
	{
		tmp = *token_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
		new_token->prev = tmp;
	}
}

void	free_tokens(t_token *token_list)
{
	t_token	*to_free;

	while (token_list)
	{
		to_free = token_list;
		token_list = token_list->next;
		free(to_free->word);
		free(to_free);
	}
}
