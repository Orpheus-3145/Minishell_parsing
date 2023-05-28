/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:56:10 by faru              #+#    #+#             */
/*   Updated: 2023/05/28 23:16:33 by fra              ###   ########.fr       */
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
		if (! is_only_spaces(word))
		{
			new_ele->word = ft_trim(word);
			if (new_ele->word == NULL)
				return (ft_free(new_ele));
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
	}
}

void	free_tokens(t_token *token_list)
{
	t_token	*to_free;

	while (token_list)
	{
		to_free = token_list;
		token_list = token_list->next;
		ft_free(to_free->word);
		ft_free(to_free);
	}
}

void	print_tokens(t_var *depo)
{
	uint32_t	i;
	uint32_t	j;
	char		**full_cmd;
	t_input		*inputs;

	inputs = depo->input_list;
	while (inputs)
	{
		i = 0;
		ft_printf("full input: ###%s###\n", inputs->raw_input);
		ft_printf("exp input: ###%s###\n", inputs->exp_input);
		while (i < inputs->n_cmd)
		{
			full_cmd = inputs->cmd_data[i].full_cmd;
			ft_printf("%u) COMMAND\n\tcmd name: %s\n", i + 1, inputs->cmd_data[i].cmd_name);
			while (*full_cmd)
				ft_printf("\t\targ: %s\n", *full_cmd++);
			if (inputs->cmd_data[i].n_redirect > 0)
			{
				ft_printf("\tn. redirections: %u\n", inputs->cmd_data[i].n_redirect);
				j = 0;
				while (j < inputs->cmd_data[i].n_redirect)
				{
					if (inputs->cmd_data[i].redirections[j] == RED_IN_SINGLE)
						ft_printf("\t\tred type: %s file: %s\n", "<", inputs->cmd_data[i].files[j]);
					else if (inputs->cmd_data[i].redirections[j] == RED_OUT_SINGLE)
						ft_printf("\t\tred type: %s file: %s\n", ">", inputs->cmd_data[i].files[j]);
					else if (inputs->cmd_data[i].redirections[j] == RED_IN_DOUBLE)
						ft_printf("\t\tred type: %s file: %s\n", "<<", inputs->cmd_data[i].files[j]);
					else if (inputs->cmd_data[i].redirections[j] == RED_OUT_DOUBLE)
						ft_printf("\t\tred type: %s file: %s\n", ">>", inputs->cmd_data[i].files[j]);
					j++;
				}
			}
			i++;
		}
		ft_printf("--\n");
		inputs = inputs->next;
	}
}

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
			// else if (is_valid_quote(input, len))
			// 	len++;
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
