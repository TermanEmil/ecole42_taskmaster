#define  _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

const char *signal_name(const int signum)
{
    static char  buffer[32];
    switch (signum) {
    case SIGINT:  return "INT";
    case SIGHUP:  return "HUP";
    case SIGTERM: return "TERM";
    default:
        snprintf(buffer, sizeof buffer, "%d", signum);
        return (const char *)buffer;
    }
}

int main(void)
{
    const long mypid = getpid();
    sigset_t   set;
    siginfo_t  info;
    int        result;

    printf("Child: Child process %ld started!\n", mypid);
    fflush(stdout);

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGHUP);
    sigaddset(&set, SIGTERM);
    sigprocmask(SIG_BLOCK, &set, NULL);
    result = sigwaitinfo(&set, &info);
    if (result == -1) {
        printf("Child: Child process %ld failed: %s.\n", mypid, strerror(errno));
        return EXIT_FAILURE;
    }

    if (info.si_pid == 0)
        printf("Child: Child process %ld terminated by signal %s via terminal.\n", mypid, signal_name(result));
    else
    if (info.si_pid == getppid())
        printf("Child: Child process %ld terminated by signal %s sent by the parent process %ld.\n",
               mypid, signal_name(result), (long)info.si_pid);
    else
        printf("Child: Child process %ld terminated by signal %s sent by process %ld.\n",
               mypid, signal_name(result), (long)info.si_pid);
    return EXIT_SUCCESS;
}