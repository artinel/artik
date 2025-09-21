#ifndef __KERNEL_FLAGS_H_
#define __KERNEL_FLAGS_H_

/* Some macros to work with flags */
#define SET_FLAG(variable, flag) ((variable) |= (flag))
#define UNSET_FLAG(variable, flag) ((variable) &= ~(flag))
#define TOGGLE_FLAG(variable, flag) ((variable) ^= (flag))
#define CHECK_FLAG(variable, flag) (((variable) & (flag)) != 0)
#define CHECK_FLAG_NOT(variable, flag) (((variable) & (flag)) == 0)

#endif
