/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 13:56:10 by faru          #+#    #+#                 */
/*   Updated: 2023/05/26 18:02:54 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *create_new_token(char *word)
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

// void	drop_token(t_token **token_list, char *word)
// {
// 	t_token *tmp;
//
// 	tmp = *token_list;
// 	while(tmp)
// 	{
// 		if (! ft_strncmp(tmp->word, word, ft_strlen(word)))
// 		{
// 			if (tmp == *token_list)
// 			{
// 				*token_list = (*token_list)->next;
// 				(*token_list)->prev = NULL;
// 			}
// 			else if (tmp->next == NULL)
// 				tmp->prev->next = NULL;
// 			else
// 			{
// 				tmp->prev->next = tmp->next;
// 				tmp->next->prev = tmp->prev;
// 			}
// 			free(tmp->word);
// 			free(tmp);
// 			break;
// 		}
// 		tmp = tmp->next;
// 	}
// }

void	print_tokens(t_var *depo)
{
	uint32_t	i;

	while (depo->input_list)
	{
		i = 0;
		ft_printf("full input: ###%s###\n", depo->input_list->raw_input);
		while (i < depo->input_list->n_cmd)
		{
			ft_printf("%u) cmd: ###%s###\ncmd tokens:\n", i + 1, depo->input_list->cmd_data[i]._cmd);
			print_tks(depo->input_list->cmd_data[i].tokens);
			// ft_printf("redirect tokens:\n");
			// print_tks(depo->input_list->cmd_data[i].redirect_tokens);
			i++;
		}
		ft_printf("--\n");
		depo->input_list = depo->input_list->next;
	}
}

void	print_tks(t_token *tks)
{
	while (tks)
	{
		ft_printf("\ttoken: ###%s###\n", tks->word);
		tks = tks->next;
	}
}

// t_token	*tokenize_cmd(char *input)
// {
// 	char			*new_word;
// 	t_token			*tokens;
// 	t_token			*new_token;
// 	bool        	end_word;
// 	uint32_t    	len;
//
// 	tokens = NULL;
// 	while (*input)
// 	{
// 		len = 0;
// 		end_word = false;
// 		new_word = NULL;
// 		while (! end_word)
// 		{
// 			if (input[len] == '\0')
// 				end_word = true;
// 			else if (is_valid_quote(input, len))
// 				len++;
// 			else if (is_valid_space(input, len))
// 			{
// 				while (ft_isspace(input[len]))
// 					len++;
// 				end_word = true;
// 			}
// 			else if (is_valid_arrow(input, len))
// 			{
// 				len += skip_redirect_chars(input, len);
// 				while (ft_isspace(input[len]))
// 					len++;
// 				end_word = true;
// 			}
// 			else
// 			{
// 				new_word = ft_append_char(new_word, input[len]);
// 				if (new_word == NULL)
// 				{
// 					free_tokens(tokens);
// 					return (NULL);
// 				}
// 				len++;
// 				end_word = input[len] == '\0';
// 			}
// 		}
// 		if (new_word)
// 		{
// 			new_token = create_new_token(new_word);
// 			if (! new_token)
// 			{
// 				free_tokens(tokens);
// 				return (NULL);
// 			}
// 			append_token(&tokens, new_token);
// 		}
// 		input += len;
// 	}
// 	return (tokens);
// }

// t_token	*tokenize_redirect(char *input)
// {
// 	char			*new_word;
// 	t_token			*tokens;
// 	t_token			*new_token;
// 	bool        	end_word;
// 	uint32_t    	len;
// 	uint32_t		i;
//
// 	i = 0;
// 	tokens = NULL;
// 	while (input[i])
// 	{
// 		if (is_valid_arrow(input, i))
// 		{
// 			len = 0;
// 			end_word = false;
// 			new_word = NULL;
// 			while (! end_word)
// 			{
// 				if (input[i + len] == '\0')
// 					end_word = true;
// 				else if (is_valid_space(input, i + len))
// 				{
// 					while (ft_isspace(input[i + len]))
// 						len++;
// 					end_word = true;
// 				}
// 				else
// 				{
// 					new_word = ft_append_char(new_word, input[i + len]);
// 					if (new_word == NULL)
// 					{
// 						free_tokens(tokens);
// 						return (NULL);
// 					}
// 					len++;
// 					if (is_valid_arrow(input, i + len - 1) && (! is_valid_arrow(input, i + len)))
// 						end_word = true;
// 					else
// 						end_word = input[len] == '\0';
// 				}
// 			}
// 			new_token = create_new_token(new_word);
// 			if (! new_token)
// 			{
// 				free_tokens(tokens);
// 				return (NULL);
// 			}
// 			append_token(&tokens, new_token);
// 			input += len;
// 		}
// 		else
// 			i++;
// 	}
// 	return (tokens);
// }

t_token	*tokenize(char *input)
{
	char			*new_word;
	t_token			*tokens;
	t_token			*new_token;
	bool        	end_word;
	uint32_t    	len;

	tokens = NULL;
	while (*input)
	{
		len = 0;
		end_word = false;
		new_word = NULL;
		while (! end_word)
		{
			if (input[len] == '\0')
				end_word = true;
			else if (is_valid_quote(input, len))
				len++;
			else if (is_valid_space(input, len))
			{
				while (ft_isspace(input[len]))
					len++;
				end_word = true;
			}
			else if (is_valid_arrow(input, len) && new_word && (! is_valid_arrow(new_word, 0)))
				end_word = true;
			else if (! is_valid_arrow(input, len) && new_word && is_valid_arrow(input, len - 1))
				end_word = true;
			else
			{
				new_word = ft_append_char(new_word, input[len]);
				if (new_word == NULL)
				{
					free_tokens(tokens);
					return (NULL);
				}
				len++;
				end_word = input[len] == '\0';
			}
		}
		if (new_word)
		{
			new_token = create_new_token(new_word);
			if (! new_token)
			{
				free_tokens(tokens);
				return (NULL);
			}
			append_token(&tokens, new_token);
		}
		input += len;
	}
	return (tokens);
}
