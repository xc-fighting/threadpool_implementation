#include "shm.h"
#define PATHNAME "."
#define PRO_ID 101

enum shm_create_status shm_create(size_t size, int* pshmid) {
	key_t key;
    key = ftok(PATHNAME, PRO_ID);
    int shmid;
	shmid = shmget(key, size, 0);
	if(shmid == -1) {
		shmid = shmget(key, size, IPC_CREAT|0644);
		if(shmid == -1) {
			perror("Error shmget()");
			return SHM_CREATE_FAIL;
		}
		*pshmid = shmid;
		return SHM_CREATE_NEW;
	}
	else {
		*pshmid = shmid;
		return SHM_HAS_EXIST;
	}
}