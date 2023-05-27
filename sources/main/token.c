/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:56:10 by faru              #+#    #+#             */
/*   Updated: 2023/05/27 02:55:38 by fra              ###   ########.fr       */
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

char	*from_code_to_str(t_red_type type)
{
	if (type == RED_IN_SINGLE)
		return ("<");
	else if (type == RED_OUT_SINGLE)
		return (">");
	else if (type == RED_IN_DOUBLE)
		return ("<<");
	else 
		return (">>");
}

void	print_tokens(t_var *depo)
{
	uint32_t	i;
	uint32_t	j;
	char		**cmd_name;
	char		**full_cmd;
	char		**redirections;
	char		**files;

	while (depo->input_list)
	{
		i = 0;
		ft_printf("full input: ###%s###\n", depo->input_list->raw_input);
		while (i < depo->input_list->n_cmd)
		{
			cmd_name = depo->input_list->cmd_data[i].cmd_name;
			full_cmd = depo->input_list->cmd_data[i].full_cmd;
			redirections = depo->input_list->cmd_data[i].redirections;
			files = depo->input_list->cmd_data[i].files;
			ft_printf("%u) single cmd, n. redirections: %u\n\tcmd name: %s\n", i + 1, depo->input_list->cmd_data[i].n_redirect, cmd_name);
			while (*full_cmd)
				ft_printf("\t##%s##\n", *full_cmd++)
			j = 0;
			while (j < depo->input_list->n_cmd.n_redirect)
			{
				ft_printf("\tred type: %s file: ##%s##\n", from_code_to_str(depo->input_list->cmd_data[i].redirections[j]), depo->input_list->cmd_data[i].files[j]);
				j++;
			}
			i++;
		}
		ft_printf("--\n");
		depo->input_list = depo->input_list->next;
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


int32_t	count_words(t_token *tokens)
{
	uint32_t	cnt;

	cnt = 0;
	while (tokens)
	{
		if (is_arrow(*(tokens->word)))
			tokens = tokens->next;
		else
			cnt++;
		tokens = tokens->next;
	}
	return (cnt);
}

uint32_t	count_redirections(t_token *tokens)
{
	uint32_t	cnt;

	cnt = 0;
	while (tokens)
	{
		if (is_arrow(*(tokens->word)))
			cnt++;
		tokens = tokens->next;
	}
	return (cnt);
}

t_red_type	*fill_red_type(t_token *tokens, uint32_t n_redirect)
{
	t_red_type	*redirections;
	uint32_t	i;

	redirections = ft_calloc(n_redirect, sizeof(t_red_type));
	if (redirections)
	{
		i = 0;
		while (tokens)
		{
			if (is_arrow(*(tokens->word)))
			{
				if (ft_strncmp(tokens->word, "<", 1))
					redirections[i] = RED_IN_SINGLE;
				else if (ft_strncmp(tokens->word, ">", 1))
					redirections[i] = RED_OUT_SINGLE;
				else if (ft_strncmp(tokens->word, "<<", 1))
					redirections[i] = RED_IN_DOUBLE;
				else if (ft_strncmp(tokens->word, ">>", 1))
					redirections[i] = RED_OUT_DOUBLE;
				i++;
			}
			tokens = tokens->next;
		}
	}
	return (redirections);
}

char	**fill_red_files(t_token *tokens, uint32_t n_redirect)
{
	char		**files;
	uint32_t	i;

	files = ft_calloc(n_redirect, sizeof(char *));
	if (files)
	{
		i = 0;
		while (tokens)
		{
			if (is_arrow(*(tokens->word)))
			{
				tokens = tokens->next;
				files[i] = ft_strdup(tokens->word);
				if (files[i] == NULL)
				{
					free(files);
					return (NULL);
				}
				i++;
			}
			tokens = tokens->next;
		}
	}
	return (files);
}

char	*get_cmd_name(t_token *tokens)
{
	while (tokens)
	{
		if (! is_arrow(*(tokens->word)))
			return (ft_strdup(tokens->word));
		tokens = tokens->next;
	}
	return (NULL);
}

char	**get_full_cmd(t_token *tokens, uint32_t n_words)
{
	char		**full_cmd;
	uint32_t	i;

	full_cmd = ft_calloc(n_words, sizeof(char *));
	if (full_cmd)
	{
		i = 0;
		while (tokens)
		{
			if (! is_arrow(*(tokens->word)))
				tokens = tokens->next;
			else
			{
				if (is_quote(*(tokens->word)))
					full_cmd[i] = ft_substr(tokens->word, 1, ft_strlen(tokens->word) - 1);
				else
					full_cmd[i] = ft_strdup(tokens->word);
				if (full_cmd[i] == NULL)
				{
					free(full_cmd);
					return (NULL);
				}
				i++;
			}
			tokens = tokens->next;
		}
	}
	return (full_cmd);
}
