
#include "../includes/minishell.h"
#include "../includes/parser.h"


void	print_tokens(t_list *tokens)
{
	t_token *tok;

	printf("=== Tokens ===\n");
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		printf("Token: %-10s  Type: %d  Expand: %d\n",
			tok->value, tok->type, tok->can_expand);
		tokens = tokens->next;
	}
	printf("=== End of Tokens ===\n");
}

void	print_cmds(t_cmd *cmd)
{
	int i, j;

	printf("=== Parsed Commands ===\n");
	for (int n = 0; cmd; cmd = cmd->next, n++)
	{
		printf("Command %d:\n", n);
		printf("  argv:\n");
		for (i = 0; cmd->argv && cmd->argv[i]; i++)
			printf("    arg[%d] = %s\n", i, cmd->argv[i]);

		if (cmd->redirs)
		{
			printf("  redirs:\n");
			for (j = 0; cmd->redirs[j].target; j++)
			{
				char *type =
					cmd->redirs[j].type == IN ? "<" :
					cmd->redirs[j].type == OUT ? ">" :
					cmd->redirs[j].type == APPEND ? ">>" : "<<";
				printf("    redir[%d] = %s (type: %s)\n", j,
					cmd->redirs[j].target, type);
			}
		}
		else
			printf("  redirs: none\n");

		printf("  is_pipe: %d\n", cmd->is_pipe);
		printf("  next: %s\n", cmd->next ? "linked" : "none");
	}
	printf("=== End of Parsed Commands ===\n");
}

