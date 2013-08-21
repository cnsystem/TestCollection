#ifndef TYPES
typedef int				int32;
typedef short			int16;
typedef char			int8;
typedef	unsigned int	uint32;
typedef unsigned short	uint16;
typedef unsigned char	uint8;
#define OFFSETOF(type, field) \
(((char*) &((type *)0)->field) - ((char*) (type *) 0))
#endif
#define TYPES
#define Return_OK 0
#define Return_ERROR -1