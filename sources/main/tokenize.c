/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 17:08:10 by fra           #+#    #+#                 */
/*   Updated: 2023/05/23 17:05:32 by faru          ########   odam.nl         */
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

// bool	tokenize(t_cmd *cmd_to_fill, char *to_split)
// {
// 	char	*cmd_name;
// 	char	**cmd_full;
// 	int		*redirect;
// 	char	**words;
// 	char	**file;

// 	words = split_into_words(to_split);
// 	if (! words)
// 		return (false);
// 	// ... from words to cmds, option, input, files , ...
// 	cmd_name = get_cmd_name(to_split);
// 	if ((cmd_name != NULL))
// 	{
// 		ft_free_double((void ***) &words, -1);
// 		return (false);
// 	}
// 	cmd_full = get_cmd_full(to_split);
// 	if ((cmd_name != NULL))
// 	{
// 		ft_free_double((void ***) &words, -1);
// 		free(cmd_name);
// 		return (false);
// 	}
// 	redirect = get_redirect(to_split);
// 	if ((cmd_name != NULL))
// 	{
// 		ft_free_double((void ***) &words, -1);
// 		free(cmd_name);
// 		free(cmd_full);
// 		return (false);
// 	}
// 	file = get_file(to_split);
// 	if ((cmd_name != NULL))
// 	{
// 		ft_free_double((void ***) &words, -1);
// 		free(cmd_name);
// 		free(cmd_full);
// 		free(redirect);
// 		return (false);
// 	}
// 	cmd_to_fill->cmd_name = cmd_name;
// 	cmd_to_fill->cmd_full = cmd_full;
// 	cmd_to_fill->redirect = redirect;
// 	cmd_to_fill->file = file;
// 	ft_free_double((void ***) &words, -1);
// 	return (true);
// }

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

char	**split_into_words(char *input_cmd)
{
	char		**words;
	uint32_t	i;
	uint32_t	len;
	char		*tmp;
	bool		plus_one;

	if ((! ft_strchr(input_cmd, '\'')) && (ft_strchr(input_cmd, '\"')))
		return (ft_split(input_cmd, ' ', true));
	words = ft_calloc(n_words(input_cmd) + 1, sizeof(char *));
	if (! words)
		return (NULL);
	i = 0;
	while (ft_isspace(*input_cmd))
		input_cmd++;
	while (*input_cmd)
	{
		// words[i] = NULL;
		plus_one = false;
		while (*input_cmd && (! ft_isspace(*input_cmd)))
		{
			len = 0;
			if (is_quote(*input_cmd))
			{
				input_cmd++;
				while (! is_quote(input_cmd[len]))
					len++;
				plus_one = len;
			}
			else
			{
				while (input_cmd[len] && (! ft_isspace(input_cmd[len])) && (! is_quote(input_cmd[len])))
					len++;
			}
			if (len)
			{
				tmp = ft_calloc(ft_strlen(words[i]) + len + 1, sizeof(char));
				if (tmp == NULL)
					return (ft_free_double((void ***) &words, i));
				ft_memcpy(tmp, words[i], ft_strlen(words[i]));
				ft_memcpy(tmp + ft_strlen(words[i]), input_cmd, len);
				free(words[i]);
				words[i] = ft_trim(tmp, true);
				if (! words[i])
				{
					// free al the stuff
					return (NULL);
				}
				input_cmd += len;
				if (plus_one)
				{
					input_cmd += 1;
					plus_one = false;
				}
			}
			else
				input_cmd++;
		}
		if (words[i] == NULL)
			words[i] = ft_strdup("");
	}
	return (words);
}

char	**split_into_cmds(char *input_cmd)
{
	char		**cmds;
	uint32_t	i;
	uint32_t	len;

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
		cmds[i] = ft_trim(ft_substr(input_cmd, 0, len), true);
		if (cmds[i] == NULL)
			return (ft_free_double((void ***) &cmds, i));
		i++;
		input_cmd += len + (input_cmd[len] != 0);
	}
	return (cmds);
}
