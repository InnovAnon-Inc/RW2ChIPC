#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <restart.h>

#include <rw2chipc.h>

typedef struct {
   int          (*restrict pipes)[NUM_PIPES][2];
   rwchildcb_t             childcb;
   void          *restrict args;
} cargs_t;

__attribute__ ((nonnull (1), warn_unused_result))
static int mychildcb (void *restrict args) {
   cargs_t          *restrict cargs                = args;
   int             (*restrict pipes)[NUM_PIPES][2] = cargs->pipes;
   rwchildcb_t                childcb              = cargs->childcb;
   void             *restrict child_args           = cargs->args;

   /* Close fds not required by child. Also, we don't
   want the exec'ed program to know these existed */
   int err = r_close (PARENT_READ_FD  (*pipes));
   err    |= r_close (PARENT_WRITE_FD (*pipes));
   error_check (err != 0) { return err; }
 
   return childcb (CHILD_READ_FD (*pipes), CHILD_WRITE_FD (*pipes), child_args);
}

typedef struct {
   int          (*restrict pipes)[NUM_PIPES][2];
   rwparentcb_t            parentcb;
   void          *restrict args;
} pargs_t;

__attribute__ ((nonnull (2), warn_unused_result))
static int myparentcb (pid_t cpid, void *restrict args) {
   pargs_t       *restrict pargs                = args;
   int          (*restrict pipes)[NUM_PIPES][2] = pargs->pipes;
   rwparentcb_t            parentcb             = pargs->parentcb;
   void          *restrict parent_args          = pargs->args;

   /* close fds not required by parent */       
   int err = r_close (CHILD_READ_FD  (*pipes));
   err    |= r_close (CHILD_WRITE_FD (*pipes));
   error_check (err != 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      r_close (PARENT_READ_FD  (*pipes));
      r_close (PARENT_WRITE_FD (*pipes));
	#pragma GCC diagnostic pop
      return -1;
   }
   
   error_check ((err = parentcb (cpid, PARENT_READ_FD (*pipes), PARENT_WRITE_FD (*pipes), parent_args)) != 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      r_close (PARENT_READ_FD  (*pipes));
      r_close (PARENT_WRITE_FD (*pipes));
	#pragma GCC diagnostic pop
      return -2;
   }

   err  = r_close (PARENT_READ_FD  (*pipes));
   err |= r_close (PARENT_WRITE_FD (*pipes));
   return err;
}
 
__attribute__ ((nonnull (1, 3), warn_unused_result))
int rw2chipc (rwchildcb_t childcb, void *restrict cargs, rwparentcb_t parentcb, void *restrict pargs) {
   int pipes[NUM_PIPES][2];
   cargs_t child_args;
   pargs_t parent_args;

   /* pipes for parent to write and read */
   error_check (pipe (pipes[PARENT_READ_PIPE ]) != 0) return -1;
   error_check (pipe (pipes[PARENT_WRITE_PIPE]) != 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      r_close (PARENT_READ_FD (pipes));
      r_close (CHILD_WRITE_FD (pipes));
	#pragma GCC diagnostic pop
      return -2;
   }

   child_args.pipes   = &pipes;
   child_args.childcb = childcb;
   child_args.args    = cargs;
   parent_args.pipes    = &pipes;
   parent_args.parentcb = parentcb;
   parent_args.args     = pargs;
   return sfork (mychildcb, &child_args, myparentcb, &parent_args);
}

