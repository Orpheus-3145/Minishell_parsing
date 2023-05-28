/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   substitution.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 01:49:19 by fra           #+#    #+#                 */
/*   Updated: 2023/05/28 17:55:12 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sub_var(char *input, t_env *env_vars)
{
	uint32_t	i;
	uint32_t	start;
	uint32_t	end;
	char		*var_name;
	char		*var_value;
	char		*exp_input;

	i = 0;
	while (input[i])
	{
		if (is_valid_d_sign(input, i))
		{
			i++;
			start = i;
			end = start;
			while (input[end] && (! ft_isspace(input[end])) && (input[end] != '|'))
				end++;
			var_name = ft_substr(input, start, end - start);
			if (var_name == NULL)
				return (NULL);
			var_value = get_var_value(env_vars, var_name);
			exp_input = insert_var(input, var_value, start, end);
			if (exp_input == NULL)
				return (ft_free(var_name));
			ft_free(input);
			input = exp_input;
			if (var_name == NULL)
				i = end + 1;
			else
				i += ft_strlen(var_name) = 1;
			ft_printf("new str: >%s<\nstarting now at: >%s<\n", input, input + i);
		}
		else
			i++;
	}
	return (input);
}

char	*get_var_value(t_env *env_vars, char *var_name)
{
	while (env_vars)
	{
		if (ft_strncmp(env_vars->key, var_name, ft_strlen(var_name)) == 0)
			return (env_vars->value);
		env_vars = env_vars->next;
	}
	return (NULL);
}

char	*insert_var(char *input, char *var_value, uint32_t start, uint32_t end)
{
	uint32_t	tot_len;
	uint32_t	new_len;
	uint32_t	len_var_value;
	char		*update_str;
	char		*tmp;

	tot_len = ft_strlen(input);
	len_var_value = ft_strlen(var_value);
	new_len = start - 1 + len_var_value + tot_len - end;
	update_str = ft_calloc(new_len + 1, sizeof(char));
	if (update_str)
	{
		tmp = update_str;
		ft_strlcpy(tmp, input, start);
		// ft_printf("1string tmp: >>%s<<\n", tmp);
		tmp += start - 1;
		ft_strlcpy(tmp, var_value, len_var_value + 1);
		// ft_printf("2string tmp: >>%s<<\n", tmp);
		tmp += len_var_value;
		input += end;
		ft_strlcpy(tmp, input, tot_len - end + 1);
		// ft_printf("3string tmp: >>%s<<\n", tmp);
	}
	return (update_str);
}
// a$bc defg