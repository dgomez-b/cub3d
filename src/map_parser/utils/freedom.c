#include <stdlib.h>

void	freedom(void **ptr)
{
	if (!*ptr)
		return ;
	free(*ptr);
	*ptr = (void *)0;
}
