/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:51:29 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/27 15:09:28 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/executor.h"

int is_valid_exit_code(const char *str)
{
    if (!str || !*str)
        return (0);
    if (*str == '-' || *str == '+')
        str++;
    while (*str)
    {
        if (!ft_isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}

int builtin_exit(char **args)
{
    long exit_code;
    int i;

    i = 0;
    ft_putendl_fd("exit", STDOUT_FILENO);
    if (!args[1])
        exit(/*global_exit_code*/);
    if (!is_valid_exit_code(args[1]))
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(argv[1], 2);
        ft_putendl_fd(": numeric argument required", 2);
        exit(255);
    }
    if (args[2])
    {
        ft_putendl_fd("minishell: exit: too many arguments", 2);
        return (1);
    }
    exit_code = ft_atoi(args[1]);
    exit (exit_code % 256);
}
