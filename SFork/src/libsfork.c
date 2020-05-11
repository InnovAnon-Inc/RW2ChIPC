#if HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif
#include <signal.h>
#include <sys/wait.h>

#include <restart.h>

#include <sfork.h>

typedef struct {
   parentcb_t parentcb;
   void *restrict pargs;
} parentcb_wait_t;

__attribute__ ((nonnull (2), warn_unused_result))
static int parentcb_wait (pid_t cpid, void *restrict arg) {
   parentcb_wait_t *p        = arg;
   parentcb_t       parentcb = p->parentcb;
   void *restrict   pargs    = p->pargs;

   int wstatus;
   error_check (parentcb (cpid, pargs) != 0) {
      kill (cpid, SIGKILL);
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      r_waitpid (cpid, &wstatus, 0);
	#
      return -1;
   }

   error_check (r_waitpid (cpid, &wstatus, 0) == -1) return -1;
   error_check (WIFEXITED (wstatus) != true) return -2;
   return 0;
}

__attribute__ ((nonnull (1, 3), warn_unused_result))
int sfork (childcb_t childcb, void *restrict cargs, parentcb_t parentcb, void *restrict pargs) {
   parentcb_wait_t p;
   p.parentcb = parentcb;
   p.pargs    = pargs;
   return ezfork (childcb, cargs, parentcb_wait, &p);
}

