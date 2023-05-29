/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:09:49 by fra               #+#    #+#             */
/*   Updated: 2023/05/29 19:00:22 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint32_t	n_cmds(char *string)
{
	uint32_t	cnt;
	uint32_t	curr_pos;

	cnt = 1;
	curr_pos = 0;
	while (string[curr_pos])
	{
		if ((string[curr_pos] == '|') && is_outside_quotes(string, curr_pos))
			cnt++;
		curr_pos++;
	}
	return (cnt);
}

char	**split_into_cmds(char *input_cmd)
{
	char		**cmds;
	uint32_t	i;
	uint32_t	len;
	char	*tmp;

	cmds = ft_calloc(n_cmds(input_cmd) + 1, sizeof(char *));
	if (! cmds)
		return (NULL);
	i = 0;
	while (*input_cmd)
	{
		len = 0;
		while (input_cmd[len])
		{
			if (is_valid_pipe(input_cmd, len))
				break ;
			len++;
		}
		tmp = ft_substr(input_cmd, 0, len);
		cmds[i] = ft_trim(tmp);
		if (cmds[i] == NULL)
			return (ft_free_double((void **) cmds, i));
		i++;
		input_cmd += len + (input_cmd[len] != 0);
	}
	return (cmds);
}

char	**append_string(char **old_matrix, char *to_append)
{
	char		**new_matrix;
	uint32_t	n_words;
	uint32_t	i;

	if (! to_append)
		return (old_matrix);
	n_words = 0;
	while (old_matrix && old_matrix[n_words])
		n_words++;
	new_matrix = ft_calloc((n_words + 2), sizeof(char *));
	if (new_matrix)
	{
		i = 0;
		while (old_matrix && i < n_words)
		{
			new_matrix[i] = old_matrix[i];
			i++;
		}
		new_matrix[i++] = to_append;
	}
	ft_free(old_matrix);
	return (new_matrix);
}

uint32_t	skip_redirect_chars(char *cmd, uint32_t pos)
{
	uint32_t	start_pos;

	start_pos = pos;
	while (is_valid_arrow(cmd, pos))
	{
		pos++;
		pos += is_arrow(cmd[pos]);
		while (ft_isspace(cmd[pos]))
			pos++;
		while (! is_valid_space(cmd, pos) && (! is_valid_arrow(cmd, pos)) && cmd[pos])
			pos++;
	}
	return (pos - start_pos);
}

bool	is_only_spaces(char	*to_check)
{
	while (ft_isspace(*to_check))
		to_check++;
	return (*to_check == '\0');
}

char	*clear_str(char *to_clear)
{
	char		*cleaned_str;
	uint32_t	len;
	uint32_t	i;
	
	if ((! ft_strchr(to_clear, '\'')) && (! ft_strchr(to_clear, '\"')))
		return (ft_strdup(to_clear));
	else
	{
		len = ft_strlen(to_clear);
		i = 0;
		while (to_clear[i])
		{
			if (is_val)
		}
		cleaned_str = ft_calloc(len + 1, sizeof(char));
		if (cleaned_str)
		{
			i = 0;
			while (*to_clear)
			{
				if (! is_quote(*to_clear))
					cleaned_str[i++] = *to_clear;
				to_clear++;
			}
		}
		return (cleaned_str);
	}
}

bool	has_trailing_pipe(char	*cmd)
{
	uint32_t	len_cmd;

	if (! cmd || (*cmd == '\0'))
		return (false);
	len_cmd = ft_strlen(cmd) - 1;
	while (len_cmd && ft_isspace(cmd[len_cmd]))
		len_cmd--;
	if (len_cmd <= 1)
		return (false);
	else
		return (cmd[len_cmd] == '|');
}

bool	is_outside_quotes(char *string, uint32_t pos_to_check)
{
	uint32_t	i;
	char		quotes;
	bool		open_quotes;

	i = 0;
	open_quotes = false;
	while (string[i] && (i < pos_to_check))
	{
		if (is_quote(string[i]))
		{
			if ((open_quotes == true) && (string[i] == quotes))
			{
				quotes = '\0';
				open_quotes = false;
			}
			else if (open_quotes == false)
			{
				quotes = string[i];
				open_quotes = true;
			}
		}
		i++;
	}
	return (! open_quotes);
}
