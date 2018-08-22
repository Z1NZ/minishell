/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 04:03:56 by srabah            #+#    #+#             */
/*   Updated: 2015/02/13 17:43:00 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

const char		*g_signals[] = {
	"",
	"Hangup",
	"",
	"Quit",
	"Illegal instruction",
	"Trace/BPT trap",
	"Abort trap",
	"EMT trap",
	"Floating point exception",
	"Killed",
	"Bus error",
	"Segmentation fault",
	"Bad system call",
	"",
	"Alarm clock",
	"Terminated",
	"",
	"Stopped",
	"Stopped",
	"",
	"",
	"Stopped",
	"Stopped",
	"",
	"Cputime limit exceeded",
	"Filesize limit exceeded",
	"Virtual timer expired",
	"Profiling timer expired",
	"",
	"",
	"User defined signal 1",
	"User defined signal 2",
	NULL
};

void			handle_statut(int status)
{
	int ret;

	if (WIFSIGNALED(status) == 0)
		return ;
	ret = WTERMSIG(status);
	if (ret >= 0 && ret < 32 && g_signals[ret][0] != '\0')
	{
		ft_putnbr_fd(ret, 2);
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(g_signals[ret], 2);
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(g()->cmd[0], 2);
		ft_putchar_fd('\n', 2);
	}
}

static void		ft_sh_eco3(char *line)
{
	ft_putstr("zsh: command not found:");
	ft_putendl(line);
}

static void		ft_sh_eco2(struct stat *buf, char *line)
{
	int			i;
	pid_t		tpid;
	int			status;

	if (g()->cmd[0][0] == '.' || g()->cmd[0][0] == '/')
	{
		tpid = fork ();
		if (tpid == 0)
			i = execve(g()->cmd[0], g()->cmd, g()->env);
		else
		{
			waitpid(0, &status, 0);
			handle_statut(status);
		}
		if (i == -1 && ((lstat(g()->cmd[0], buf)) == 0))
			ft_sh(ft_strjoin("zsh ", g()->cmd[0]));
		else if (i == -1)
		{
			ft_putstr("zsh: no such file or directory:");
			ft_putendl(line);
		}
	}
	else
		ft_sh_eco3(line);
}

static void		ft_sh_eco(struct stat *buf, char *line)
{
	if (ft_strcmp(g()->cmd[0], "setenv") == 0)
	{
		if (g()->cmd[1] && g()->cmd[2])
			env_change_val(g()->cmd[1], g()->cmd[2]);
		else
			ft_putendl("setenv: fatal error\nfor example : setenv val data");
	}
	else if (ft_strcmp(g()->cmd[0], "exit") == 0)
	{
		if (g()->cmd[1])
			exit(ft_atoi(g()->cmd[1]));
		else
			exit(0);
	}
	else if (ft_strcmp(g()->cmd[0], "unsetenv") == 0)
	{
		if (g()->cmd[1])
			ft_unsetenv();
		else
			ft_putendl("un setenv: fatal error: no input data or val");
	}
	else if (g()->cmd && ft_env_path_chr())
		ft_fork();
	else
		ft_sh_eco2(buf, line);
}

void			ft_sh(char *line)
{
	struct stat	*buf;

	buf = NULL;
	if (sh_line_splite(line) == -1)
		return ;
	if (ft_strcmp(line, "env") == 0)
		ft_env();
	else if (ft_strcmp(g()->cmd[0], "cd") == 0)
	{
		if (g()->cmd[1])
		{
			if (g()->cmd[1][0] == '/')
				ft_open_path();
			else if (g()->cmd[1][0] == '~')
				ft_open_path_with_home();
			else
				ft_cd();
		}
		else if (env_chr_return_val("HOME=/"))
			ft_cd_nothink();
		else
			ft_putendl("zsh:cd: HOME not set");
	}
	else
		ft_sh_eco(buf, line);
}
