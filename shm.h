#ifndef _SHM_
#define _SHM_

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

enum shm_create_status {
	SHM_HAS_EXIST = 0,
	SHM_CREATE_NEW,
	SHM_CREATE_FAIL
};

extern enum shm_create_status shm_create(size_t size, int* pshmid);

#endif