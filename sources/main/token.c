/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 13:56:10 by faru          #+#    #+#                 */
/*   Updated: 2023/05/24 18:24:20 by faru          ########   odam.nl         */
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

void	drop_token(t_token **token_list, char *word)
{
	t_token *tmp;

	tmp = *token_list;
	while(tmp)
	{
		if (! ft_strncmp(tmp->word, word, ft_strlen(word)))
		{
			if (tmp == *token_list)
			{
				*token_list = (*token_list)->next;
				(*token_list)->prev = NULL;
			}
			else if (tmp->next == NULL)
				tmp->prev->next = NULL;
			else
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			free(tmp->word);
			free(tmp);
			break;
		}
		tmp = tmp->next;
	}
}

void	print_tokens(t_var *depo)
{
	uint32_t	i;

	while (depo->input_list)
	{
		i = 0;
		ft_printf("full input: %s\n", depo->input_list->raw_input);
		while (i < depo->input_list->n_cmd)
		{
			ft_printf("%u) cmd: %s\n", i + 1, depo->input_list->cmd_data[i]._cmd);
			print_tks(depo->input_list->cmd_data[i].tokens);
			i++;
		}
		ft_printf("--\n");
		depo->input_list = depo->input_list->next;
	}
}

void	print_tks(t_token *tokens)
{
	while (tokens)
	{
		ft_printf("word: %s\n", tokens->word);
		tokens = tokens->next;
	}
}

t_token	*tokenize(char *input)
{
	t_token			*token_list;
	t_token			*new_node;
	char			*new_word;
	t_type_token	type;
	bool        	end_token;
	// uint32_t		i;
	uint32_t		cnt;
	uint32_t    	len;

	// i = 0;
	cnt = 0;
	token_list = NULL;
	while (*input)
	{
		cnt++;
		if (cnt == 20)
			break;
		len = 0;
		end_token = false;
		type = TOK_CMD_NAME;
		new_word = NULL;
		// while (ft_isspace(*input) && is_outside_quotes(input, 0))
		// 	input++;
		while (! end_token)
		{
			// ft_printf("curr word: %s\n", new_word);
			// ft_printf("curr char: %c\n", input[len]);
			if (is_not_symbol(input , len))
			{
				new_word = ft_append_char(new_word, input[len]);
				if (new_word == NULL)
				{
					free_tokens(token_list);
					return (NULL);
				}
				len++;
				end_token = input[len] == '\0';
			}
			// else if (is_valid_quote(input, len))
			// 	len++;
			else if (is_valid_space(input, len))
			{
				input++;
				end_token = true;
			}
			// else if (is_valid_arrow(input, len))
			// {
			// 	// if (is_arrow(input[len + 1]))

			// 	end_token = true;
			// }
		}
		new_node = new_token(new_word, type);
		if (new_node == NULL)
		{
			free_tokens(token_list);
			return (NULL);
		}
		append_token(&token_list, new_node);
		input += len;
		// ft_printf("new node created! starting now from: %%%s%%, len %u\n", input, len);
	}
	// print_tks(token_list);
	return (token_list);
}

