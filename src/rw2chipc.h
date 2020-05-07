#ifndef _RW2CHIPC_H_
#define _RW2CHIPC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sfork.h>

typedef __attribute__ ((warn_unused_result))
int (*rwchildcb_t) (fd_t rd, fd_t wr, void *restrict) ;

typedef __attribute__ ((warn_unused_result))
int (*rwparentcb_t) (pid_t, fd_t rd, fd_t wr, void *restrict) ;

int rw2chipc (
	rwchildcb_t  childcb,  void *restrict childcb_args,
	rwparentcb_t parentcb, void *restrict parentcb_args)
__attribute__ ((nonnull (1, 3), warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _RW2CHIPC_H_ */
