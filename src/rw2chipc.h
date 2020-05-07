#ifndef _RW2CHIPC_H_
#define _RW2CHIPC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sfork.h>

#define NUM_PIPES (2)

/* since pipes are unidirectional, we need two pipes.
   one for data to flow from parent's stdout to child's
   stdin and the other for child's stdout to flow to
   parent's stdin */

#define PARENT_WRITE_PIPE  (0)
#define PARENT_READ_PIPE   (1)

/* always in a pipe[], pipe[0] is for read and
   pipe[1] is for write */
#define READ_FD  (0)
#define WRITE_FD (1)

#define PARENT_READ_FD(P)  ((P)[PARENT_READ_PIPE ][READ_FD ])
#define PARENT_WRITE_FD(P) ((P)[PARENT_WRITE_PIPE][WRITE_FD])

#define CHILD_READ_FD(P)   ((P)[PARENT_WRITE_PIPE][READ_FD ])
#define CHILD_WRITE_FD(P)  ((P)[PARENT_READ_PIPE ][WRITE_FD])

typedef __attribute__ ((nonnull (1), warn_unused_result))
int (*rwchildcb_t) (int pipes[NUM_PIPES][2], void *restrict) ;

typedef __attribute__ ((nonnull (2), warn_unused_result))
int (*rwparentcb_t) (pid_t, int pipes[NUM_PIPES][2], void *restrict) ;

int rw2chipc (
	rwchildcb_t  childcb,  void *restrict childcb_args,
	rwparentcb_t parentcb, void *restrict parentcb_args)
__attribute__ ((nonnull (1, 3), warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _RW2CHIPC_H_ */
