#ifndef __KERNEL_FLAGS_H_
#define __KERNEL_FLAGS_H_

/* Some macros to work with flags */
#define CHECK_FLAG(flags, f)	((flags & f) == f)
#define SET_FLAG(flags, f)	(flags |= f)
#define UNSET_FLAG(flags, f)	(flags ^= f)

#endif
