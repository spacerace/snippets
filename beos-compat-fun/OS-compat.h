#ifndef __BEOS_OS_COMPAT_H__
#define __BEOS_OS_COMPAT_H__

#include <inttypes.h>

/* constants */
#define B_NO_ERROR	0
#define B_OK		B_NO_ERROR
#define B_ERROR		-1

/* datatypes + enums */
typedef int32_t	status_t;
typedef int64_t	bigtime_t;
typedef struct {
	bigtime_t active_time;
} cpu_info;



/* functions */
status_t get_system_info(system_info *info);
int32_t	 is_computer_on(void);
double	 is_computer_on_fire(void);


#endif // __BEOS_OS_COMPAT_H__

