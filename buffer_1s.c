/* Public domain. */

#include "buffer.h"

char buffer_1small_space[256];
static buffer it = BUFFER_INIT(buffer_unixwrite,1,buffer_1small_space,sizeof buffer_1small_space);
buffer *buffer_1small = &it;
