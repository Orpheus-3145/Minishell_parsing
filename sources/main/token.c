/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:56:10 by faru              #+#    #+#             */
/*   Updated: 2023/05/25 02:50:10 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *new_token(char *word)
{
	t_token	*new_ele;

	new_ele = ft_calloc(1, sizeof(t_token));
	if (new_ele)
	{
		new_ele->next = NULL;
		new_ele->prev = NULL;
		if (! is_only_spaces(word))
		{
			new_ele->word = ft_trim(word, true);
			if (new_ele->word == NULL)
			{
				free(new_ele);
				return (NULL);
			}
		}
		new_ele->type = TOK_CMD_NAME;
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
		ft_printf("full input: >>>%s<<<\n", depo->input_list->raw_input);
		while (i < depo->input_list->n_cmd)
		{
			ft_printf("%u) cmd: >>>%s<<<\n", i + 1, depo->input_list->cmd_data[i]._cmd);
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
		ft_printf("\ttoken: >>>%s<<<\n", tokens->word);
		tokens = tokens->next;
	}
}

t_token	*tokenize(char *input)
{
	t_token			*token_list;
	t_token			*new_node;
	char			*new_word;
	// int			save_arrow;
	bool        	end_token;
	uint32_t    	len;

	token_list = NULL;
	while (*input)
	{
		len = 0;
		end_token = false;
		new_word = NULL;
		// save_arrow = 0;
		while (! end_token)
		{
			// ft_printf("curr word: %s\n", new_word);
			// ft_printf("curr char: %c\n", input[len]);
			if (input[len] == '\0')
				end_token = true;
			else if (is_valid_quote(input, len))
				len++;
			else if (is_valid_space(input, len))
			{
				while (is_valid_space(input, len))
					len++;
				end_token = true;
			}
			// else if (is_valid_arrow(input, len))
			// {
			// 	save_arrow++;
			// 	save_arrow += (is_arrow(input[len]) == true) + 1;
			// 	end_token = true;
			// }
			else
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
		}
		new_node = new_token(new_word);
		if (new_node == NULL)
		{
			free_tokens(token_list);
			return (NULL);
		}
		append_token(&token_list, new_node);
		input += len;
	}
	return (token_list);
}

