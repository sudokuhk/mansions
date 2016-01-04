/*************************************************************************
    > File Name: mansions.c
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2015-12-28 17:31:11
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>

#include <typedefs.h>
#include <macro.h>
#include <enumerate.h>

typedef void (*sighandler_t)(int);
sighandler_t g_old_handler[32];

void daemonize(void)
{
    pid_t pid = -1;
    
    //dettach from current session. and child would be a leader of new session.
    if ((pid = fork()) > 0) {
        exit(0);
    } else if (pid < 0) {
        exit(1);
    }

    //child not to be leader.
    if ((pid = fork()) > 0) {
        exit(0);
    } else if (pid < 0) {
        exit(1);
    } 

    printf("pid = %d\n", getpid());
    chdir("/");
    umask(0);

    return;
}

void mon_signal_handle(int32_t signum)
{
    switch (signum) {
        case SIGHUP:
            printf("SIGHUP\n");
            break;
        default:
            printf("sig:%d\n", signum);
            break;
    }
}

int mon_set_signal(void)
{
    int32_t i;

    for (i = 0; i < ARRAY_SIZE(g_old_handler); i++) {
        g_old_handler[i]    = NULL;
    }
    g_old_handler[SIGHUP]   = signal(SIGHUP, mon_signal_handle);
    g_old_handler[SIGINT]   = signal(SIGINT, mon_signal_handle);
    g_old_handler[SIGQUIT]  = signal(SIGQUIT, mon_signal_handle);
    g_old_handler[SIGKILL]  = signal(SIGKILL, mon_signal_handle);
    g_old_handler[SIGCHLD]  = signal(SIGCHLD, mon_signal_handle);

    return MON_OK;
}

int mon_parse_args(int argc, char * argv[])
{
    return MON_OK;
}

int main(int argc, char * argv[])
{
    printf("This is beginning!\n");
    //daemonize();
    sleep(-1);
    return 0;
}
