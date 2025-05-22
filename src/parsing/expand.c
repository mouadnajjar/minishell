/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:00 by ahlahfid          #+#    #+#             */
/*   Updated: 2025/05/22 16:30:19 by ahlahfid         ###   ########.fr       */
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

char *expand_variables(const char *str)
{
    size_t i = 0, j = 0;
    char *result;
    size_t len;
    int in_single_quote = 0;
    int in_double_quote = 0;
    bool escaped = false;

    len = compute_expanded_length(str);
    result = gc_malloc(&gc, len + 1);
    if (!result)
        return (NULL);
    ft_memset(result, 0, len + 1);

    while (str[i])
    {
        if (!escaped && str[i] == '\\')
        {
            escaped = true;
            i++;
            continue;
        }

        // If we see a single-quote:
        if (!escaped && str[i] == '\'' && !in_double_quote)
        {
            // Toggle in_single_quote so that expansions won't happen inside
            in_single_quote = !in_single_quote;

            // Also KEEP the quote in the final string:
            result[j++] = str[i++];

            // Do not lose the quote, so don't continue.
            // Let the next iteration proceed with the updated i.
            continue;
        }
        // If we see a double-quote:
        else if (!escaped && str[i] == '"' && !in_single_quote)
        {
            // Toggle
            in_double_quote = !in_double_quote;

            // Also keep the literal "
            result[j++] = str[i++];

            continue;
        }

        // If we are inside single quotes, expansions do NOT occur,
        // so any '$' you see is literal.
        if (in_single_quote)
        {
            // Just copy the character over
            result[j++] = str[i++];
            escaped = false;
        }
        // Otherwise, if we see a '$' and we are not in single quotes:
        else if (!escaped && str[i] == '$')
        {
            // do your existing handle_dollar(...) logic
            i++;
            handle_dollar(str, &i, &result, &j);
        }
        else
        {
            // Normal character
            if (escaped && str[i] != '$' && str[i] != '"' && str[i] != '\\')
                result[j++] = '\\';  // preserve backslash if it was meaningless
            result[j++] = str[i++];
            escaped = false;
        }
    }
    result[j] = '\0';
    return (result);
}

size_t compute_expanded_length(const char *str)
{
    size_t len = 0;
    size_t i = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;
    bool escaped = false;

    while (str[i])
    {
        if (!escaped && str[i] == '\\')
        {
            escaped = true;
            i++;
            len++; // Count the backslash
            continue;
        }

        if (!escaped && str[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            i++;
            continue;
        }
        else if (!escaped && str[i] == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            i++;
            continue;
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
size_t ft_numlen(int num)
{
    size_t len = 1;

    if (num < 0) {
        len++; // account for minus sign
        num = -num;
    }
    while (num > 9) {
        num /= 10;
        len++;
    }
    return len;
}
