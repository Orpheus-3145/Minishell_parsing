/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 13:51:12 by faru          #+#    #+#                 */
/*   Updated: 2023/05/23 18:05:57 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *tokenize(char *input)
{
	t_token			*token_list;
	t_token			*new_node;
	char			*new_word;
	t_type_token	type;
	bool        	end_token;
	uint32_t		i;
	uint32_t    	len;

	i = 0;
	token_list = NULL;
	while (*input)
	{
		len = 0;
		end_token = false;
		new_word = NULL;
		while (ft_isspace(*input) && is_outside_quotes(input, 0))
			input++;
		while (! end_token)
		{
			if (is_not_symbol(input , len))
			{
				word = ft_append_char(word, input[len])
				if (word == NULL)
				{
					free_tokens(token_list);
					return (NULL);
				}
				len++;
			}
			else if (is_valid_quote(input, len))
				len++;
			else if (is_valid_space(input, len))
				end_token = true;
			else if (is_valid_arrow(input, len))
			{
				if 
			}
		}
		new_node = new_token(new_word, type);
		if (new_node == NULL)
		{
			free_tokens(token_list);
			return (NULL);
		}
		append_token(&token_list, new_token);
	}
	return (token_list);
}