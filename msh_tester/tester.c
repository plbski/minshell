/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:51:10 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/02/14 14:50:51 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void	test_command(const char *cmd, char **env)
{
    const char	*mini_args[] = {"../minishell", (char *)cmd, NULL};
    int			pipefd_out[2];
	int			pid;

    if (pipe(pipefd_out) == -1)
    {
        perror("pipe fail\n");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork fail");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        close(pipefd_out[0]);
        dup2(pipefd_out[1], STDOUT_FILENO);
        close(pipefd_out[1]);
        execve("../minishell", (char *const *)mini_args, env);
        perror("execve fail");
        exit(EXIT_FAILURE);
    }
    else
    {
        close(pipefd_out[1]);
        char buffer[1024];
        int output_fd = open("child_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd == -1)
        {
            perror("file open fail");
            exit(EXIT_FAILURE);
        }
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd_out[0], buffer, sizeof(buffer) - 1)) > 0)
        {
            buffer[bytes_read] = '\0';
            write(output_fd, buffer, bytes_read);
        }
        close(pipefd_out[0]);
        close(output_fd);
        wait(NULL);
    }
}

int main(int argc, char *argv[], char **env)
{
    (void)argc;
    (void)argv;

    const char *commands[] = {
        "echo Hello from parent\n",
        "pwd\n",
        "ls\n",
        NULL
    };
    for (int i = 0; commands[i] != NULL; i++)
    {
        printf("Executing: %s", commands[i]);
        test_command(commands[i], env);
    }
    printf("All commands executed. Output saved in child_output.txt\n");
    return 0;
}
