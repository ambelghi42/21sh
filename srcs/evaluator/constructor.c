#include "libft.h"
#include "exec.h"
#include "parser.h"
#include "var.h"
#include "sh.h"

void	cmd_to_process(t_list **lst, t_list *s_cmd)
{
	t_process		process;
	t_simple_cmd	*cmd;

	ft_bzero(&process, sizeof(t_process));
	process.std[0] = STDIN_FILENO;
	process.std[1] = STDOUT_FILENO;
	process.status = WAITING;
	while (s_cmd)
	{
		cmd = s_cmd->data;
		process.cmd = ft_strdup(cmd->cmd_name);
		process.av = ft_tabdup(cmd->av);
		process.redir = cmd->redir;
		process.assign = cmd->assign;
		ft_lst_push_back(lst, &process, sizeof(process));
		s_cmd = s_cmd->next;
	}
}

void	cmd_to_job(t_cfg *shell, t_job *job, t_list *s_cmd, char *cmd)
{
	ft_bzero(job, sizeof(t_job));
	cmd_to_process(&job->process, s_cmd);
	job->cur = 32;
	job->cmd = ft_strdup(cmd);
	job->std[0] = 253;
	do_my_dup2(STDIN_FILENO, job->std[0]);
	job->std[1] = 254;
	do_my_dup2(STDOUT_FILENO, job->std[1]);
	job->std[2] = 255;
	do_my_dup2(STDERR_FILENO, job->std[2]);
	term_create_eval(&shell->term_origin, &job->term_eval);
}
