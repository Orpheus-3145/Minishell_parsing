/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:20:39 by fra               #+#    #+#             */
/*   Updated: 2023/05/27 18:34:18 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint32_t	count_words(t_token *tokens)
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

bool	get_cmd(t_token *tokens, t_cmd *cmd)
{
	uint32_t	i;

	cmd->full_cmd = ft_calloc(cmd->n_words + 1, sizeof(char *));
	if (cmd->full_cmd)
	{
		i = 0;
		while (tokens)
		{
			if (is_arrow(*(tokens->word)))
				tokens = tokens->next;
			else
			{
				if (is_quote(*(tokens->word)))
					cmd->full_cmd[i] = ft_substr(tokens->word, 1, ft_strlen(tokens->word) - 1);
				else
					cmd->full_cmd[i] = ft_strdup(tokens->word);
				if (cmd->full_cmd[i] == NULL)
				{
					ft_free(cmd->full_cmd);
					return (false);
				}
				i++;
			}
			tokens = tokens->next;
		}
		cmd->cmd_name = *(cmd->full_cmd);
	}
	return (true);
}

bool	get_redirections(t_token *tokens, t_cmd *cmd)
{
	uint32_t	i;

	cmd->redirections = ft_calloc(cmd->n_redirect, sizeof(t_red_type));
	cmd->files = ft_calloc(cmd->n_redirect + 1, sizeof(char *));
	if ((cmd->redirections == NULL) || (cmd->files == NULL))
	{
		ft_free(cmd->redirections);
		ft_free(cmd->files);
		return (false);
	}
	i = 0;
	while (tokens)
	{
		if (is_arrow(*(tokens->word)))
		{
			if (! ft_strncmp(tokens->word, "<", 1))
				cmd->redirections[i] = RED_IN_SINGLE;
			else if (! ft_strncmp(tokens->word, ">", 1))
				cmd->redirections[i] = RED_OUT_SINGLE;
			else if (! ft_strncmp(tokens->word, "<<", 2))
				cmd->redirections[i] = RED_IN_DOUBLE;
			else if (! ft_strncmp(tokens->word, ">>", 2))
				cmd->redirections[i] = RED_OUT_DOUBLE;
			tokens = tokens->next;
			cmd->files[i] = ft_strdup(tokens->word);
			if (cmd->files[i] == NULL)
			{
				ft_free(cmd->redirections);
				ft_free(cmd->files);
				return (false);
			}
			i++;
		}
		tokens = tokens->next;
	}
	return (true);
}

bool	split_input(t_cmd *cmd, char *input)
{
	t_token		*tokens;
	bool		status;

	tokens = tokenize(input);
	if (tokens == NULL)
		return (false);
	cmd->n_words = count_words(tokens);
	status = get_cmd(tokens, cmd);
	if (status == false)
	{
		free_tokens(tokens);
		return (false);
	}
	cmd->n_redirect = count_redirections(tokens);
	if (cmd->n_redirect > 0)
	{
		status = get_redirections(tokens, cmd);
		if (status == false)
		{
			ft_free(cmd->full_cmd);
			free_tokens(tokens);
			return (false);
		}
	}
	else
	{
		cmd->redirections = NULL;
		cmd->files = NULL;
	}
	free_tokens(tokens);
	return (true);
}
