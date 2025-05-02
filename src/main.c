/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:17 by monajjar          #+#    #+#             */
/*   Updated: 2025/05/02 16:51:21 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

int main(void)
{
    char *line;
    t_cmd *cmd;
	t_cmd *tmp;
	int i;

    while (1)
    {
        line = readline(PROMPT);
		if (!line)
        {
            write(1, "exit\n", 6);
            break ;
        }

/////////// start the parcing //
        cmd = parse_input(line);
////////////////////////////////

////////// Print the parsed commands//

		tmp = cmd;
		while (tmp)
		{
			i = 0;
			while (tmp->argv[i])
			{
				printf("arg[%d]: %s\n", i, tmp->argv[i]);
				i++;
			}
			if (tmp->is_pipe)
				printf("-> PIPE\n");
			tmp = tmp->next;
		}
        free_cmds(cmd);
        free(line);
/////////////////////////////////////
    }
    return 0;
}

