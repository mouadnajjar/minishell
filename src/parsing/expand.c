/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/06/02 15:47:13 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

void	handle_exit_status(char **result, size_t *j)
{
	char	*status;
	size_t	k;

	status = ft_itoa(g_shell.last_exit_status);
	if (!status)
	{
		gc_free_all(&gc);
		return ;
	}
	k = 0;
	while (status[k])
		(*result)[(*j)++] = status[k++];
	free(status);
}

void	handle_braced_variable(const char *str, size_t *i, char **result,
		size_t *j)
{
	size_t	start;
	char	*var;
	char	*value;
	size_t	k;

	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '}')
		(*i)++;
	if (str[*i] != '}')
		return ;
	var = ft_substr(str, start, *i - start);
	value = get_env_var(g_shell.envp, var);
	if (value)
	{
		k = 0;
		while (value[k])
			(*result)[(*j)++] = value[k++];
	}
	free(var);
	(*i)++;
}

void	handle_unbraced_variable(const char *str, size_t *i, char **result,
		size_t *j)
{
	size_t	start;
	char	*var;
	char	*value;
	size_t	k;

	start = *i;
	while (isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, start, *i - start);
	value = get_env_var(g_shell.envp, var);
	if (value)
	{
		k = 0;
		while (value[k])
			(*result)[(*j)++] = value[k++];
	}
	free(var);
}

char	*expand_variables(const char *str)
{
	char		*result;
	const char	*p = str;
	char		*var_name;
	char		*value;

	result = ft_strdup("");  // Start with an empty string
	if (!result)
		return (NULL);

	while (*p)
	{
		if (*p == '$')
		{
			p++;  // Move past the $
			size_t var_len = 0;
			while (p[var_len] && (ft_isalnum(p[var_len]) || p[var_len] == '_'))
				var_len++;
			if (var_len == 0)  // Handle case of isolated $ (e.g., echo $)
			{
				result = ft_strjoin_free(result, "$");
				continue;
			}

			var_name = ft_substr(p, 0, var_len);
			if (!var_name)
			{
				free(result);
				return (NULL);
			}

			value = get_env_var(g_shell.envp, var_name);
			free(var_name);
			if (value)
				result = ft_strjoin_free(result, value);
			else
				result = ft_strjoin_free(result, "");

			p += var_len;  // 🚨 Move p forward by variable name length
		}
		else
		{
			char *single_char = ft_substr(p, 0, 1);
			if (!single_char)
			{
				free(result);
				return (NULL);
			}
			result = ft_strjoin_free(result, single_char);
			free(single_char);
			p++;
		}
	}

	return (result);
}



size_t	compute_expanded_length(const char *str)
{
	size_t	len;
	size_t	i;
	int		in_single_quote;
	int		in_double_quote;
	bool	escaped;

	len = 0;
	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	escaped = false;
	while (str[i])
	{
		if (!escaped && str[i] == '\\')
		{
			escaped = true;
			i++;
			len++; // Count the backslash
			continue ;
		}
		if (!escaped && str[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			i++;
			continue ;
		}
		else if (!escaped && str[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			i++;
			continue ;
		}
		if (in_single_quote)
		{
			len++;
			i++;
		}
		else if (!escaped && str[i] == '$' && !in_single_quote)
		{
			i++;
			len += handle_dollar_expansion(str, &i);
		}
		else
		{
			if (escaped && str[i] != '$' && str[i] != '"' && str[i] != '\\')
				len++; // Count the backslash
			len++;
			i++;
			escaped = false;
		}
	}
	return (len);
}
size_t	ft_numlen(int num)
{
	size_t	len;

	len = 1;
	if (num < 0)
	{
		len++; // account for minus sign
		num = -num;
	}
	while (num > 9)
	{
		num /= 10;
		len++;
	}
	return (len);
}
