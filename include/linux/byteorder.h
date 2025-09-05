#ifndef _LINUX_BYTEORDER_H
#define _LINUX_BYTEORDER_H
#include <linux/types.h>
#ifdef __ARMEB__
#include <linux/byteorder/big_endian.h>
#else
#include <linux/byteorder/little_endian.h>
#endif
#endif
