/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:20 by monajjar          #+#    #+#             */
/*   Updated: 2025/06/02 11:58:46 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executor.h"

int get_pwd(void)
{
    char    *cwd;
    
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("minishell: pwd");
        g_exit_status = 1;
        return (1);
    }
    ft_putendl_fd(cwd, 1);
    free (cwd);
    return (0);
}
