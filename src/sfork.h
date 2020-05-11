#ifndef _SFORK_H_
#define _SFORK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ezfork.h>

int sfork (
	childcb_t  childcb,  void *restrict childcb_args,
	parentcb_t parentcb, void *restrict parentcb_args)
__attribute__ ((nonnull (1, 3), warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _SFORK_H_ */
