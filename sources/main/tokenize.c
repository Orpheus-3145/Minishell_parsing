/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fra <fra@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:08:10 by fra               #+#    #+#             */
/*   Updated: 2023/05/22 00:49:35 by fra              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_name(char *input)
{
	input++;
	return (NULL);
}

char	**get_cmd_full(char *input)
{
	input++;
	return (NULL);
}

int	*get_redirect(char *input)
{
	input++;
	return (NULL);
}

char	**get_file(char *input)
{
	input++;
	return (NULL);
}

bool	tokenize(t_cmd *cmd_to_fill, char *to_split)
{
	char	*cmd_name;
	char	**cmd_full;
	int		*redirect;
	char	**file;

	cmd_name = get_cmd_name(to_split);
	if ((cmd_name != NULL))
		return (false);
	cmd_full = get_cmd_full(to_split);
	if ((cmd_name != NULL))
	{
		free(cmd_name);
		return (false);
	}
	redirect = get_redirect(to_split);
	if ((cmd_name != NULL))
	{
		free(cmd_name);
		free(cmd_full);
		return (false);
	}
	file = get_file(to_split);
	if ((cmd_name != NULL))
	{
		free(cmd_name);
		free(cmd_full);
		free(redirect);
		return (false);
	}
	cmd_to_fill->cmd_name = cmd_name;
	cmd_to_fill->cmd_full = cmd_full;
	cmd_to_fill->redirect = redirect;
	cmd_to_fill->file = file;
	return (true);
}

char	*isolate_next_word(char	*string)
{
	char		*new_word;
	uint32_t	len;
	char		*tmp;
	bool		plus_one;
	
	new_word = NULL;
	plus_one = false;
	while (*string && (*string != ' '))
	{
		len = 0;
		if (is_quote(*string))
		{
			string++;
			while (is_quote(string[len]))
				len++;
			plus_one = len;
		}
		else
		{
			while (string[len] && (string[len] != ' ') && (! is_quote(string[len])))
				len++;
		}
		if (len)
		{
			tmp = ft_calloc(ft_strlen(new_word) + len + 1, sizeof(char));
			if (tmp == NULL)
			{
				if (new_word)
					free(new_word);
				return (NULL);
			}
			ft_memcpy(tmp, new_word, ft_strlen(new_word));
			ft_memcpy(tmp + ft_strlen(new_word), string, len);
			free(new_word);
			new_word = tmp;
			string += len;
			if (plus_one)
			{
				string += 1;
				plus_one = false;
			}
		}
		else
			string++;
	}
	if (new_word == NULL)
		new_word = ft_strdup("");
	return (new_word);
}

uint32_t	n_words(char *string)
{
	uint32_t	cnt;
	uint32_t	curr_pos;

	cnt = 1;
	curr_pos = 0;
	while (ft_isspace(string[curr_pos]))
		curr_pos++;
	while (string[curr_pos])
	{
		if (ft_isspace(string[curr_pos]) && is_outside_quotes(string, curr_pos))
		{
			while (ft_isspace(string[curr_pos]))
				curr_pos++;
			if (string[curr_pos])
				cnt++;
		}
		else
			curr_pos++;
	}
	return (cnt);
}

// char **split_into_words(char *cmd)
// {
// 	char		**matrix;
// 	// char	*sub_str;
// 	size_t		index;
// 	char		*new_word;
// 	uint32_t	len;
// 	char		*tmp;
// 	bool		plus_one;
	
// 	if ((! ft_strchr(cmd, '\'')) && (ft_strchr(cmd, '\"')))
// 		return (ft_split(cmd));
// 	index = 0;
// 	matrix = ft_calloc((ft_n_substr(cmd, split) + 1) * sizeof(char *));
// 	if (! matrix)
// 		ft_raise_error("(ft_split) Memory error", 0);
// 	new_word = NULL;
// 	plus_one = false;
// 	while (*string && (*string != ' '))
// 	{
// 		len = 0;
// 		if (is_quote(*string))
// 		{
// 			string++;
// 			while (is_quote(string[len]))
// 				len++;
// 			plus_one = len;
// 		}
// 		else
// 		{
// 			while (string[len] && (string[len] != ' ') && (! is_quote(string[len])))
// 				len++;
// 		}
// 		if (len)
// 		{
// 			tmp = ft_calloc(ft_strlen(new_word) + len + 1, sizeof(char));
// 			if (tmp == NULL)
// 			{
// 				if (new_word)
// 					free(new_word);
// 				return (NULL);
// 			}
// 			ft_memcpy(tmp, new_word, ft_strlen(new_word));
// 			ft_memcpy(tmp + ft_strlen(new_word), string, len);
// 			free(new_word);
// 			new_word = tmp;
// 			string += len;
// 			if (plus_one)
// 			{
// 				string += 1;
// 				plus_one = false;
// 			}
// 		}
// 		else
// 			string++;
// 	}
// 	if (new_word == NULL)
// 		new_word = ft_strdup("");
// 	return (new_word);

// 	index = 0;
// 	matrix = ft_calloc((ft_n_substr(cmd, split) + 1) * sizeof(char *));
// 	if (! matrix)
// 		ft_raise_error("(ft_split) Memory error", 0);
// 	while (matrix && *cmd)
// 	{
// 		if (*cmd != split)
// 		{
// 			sub_str = ft_substr(cmd, 0, len_substr(cmd, split));
// 			if (! sub_str)
// 				return (ft_free_double((void ***) &matrix, index));
// 			matrix[index++] = sub_str;
// 			cmd += ft_strlen(sub_str) - 1;
// 		}
// 		cmd++;
// 	}
// 	return (matrix);
// }
