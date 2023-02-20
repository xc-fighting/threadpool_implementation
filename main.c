#include "thread_pool.h"
#include "shm.h"

void task_1(void* args1) {
	printf("This is a long run task 1\n");
	int* val = (int*)args1;
	printf("The value is: %d\n", *val);
	sleep(2);
	printf("Finish the task 1\n");
}

void task_2(void* args2) {
	printf("This is a long run task 2\n");
	sleep(3);
	printf("Finish the task 2\n");
}

void task_3(void* args3) {
	printf("This is a long run task 3\n");
	sleep(2);
	printf("Finish the task 3\n");
}

void task_4(void* args4) {
	printf("This is a long run task 4\n");
	sleep(5);
	printf("Finish the task 4\n");
}

int main() {
    /*task_t t1;
    t1.task_func = task_1;
    int* arg1 = (int*)malloc(sizeof(int));
    *arg1 = 1;
    t1.args = arg1;
    task_t t2;
    t2.task_func = task_2;
    t2.args = NULL;
    task_t t3;
    t3.task_func = task_3;
    t3.args = NULL;
    task_t t4;
    t4.task_func = task_4;
    t4.args = NULL;
    thread_pool_t* pool = init_thread_pool(2, 4);
    add_task_to_thread_pool(pool, &t1);
    add_task_to_thread_pool(pool, &t2);
    add_task_to_thread_pool(pool, &t3);
    add_task_to_thread_pool(pool, &t4);
    sleep(2);
    destroy_thread_pool(pool);*/
    int shm_id;
    enum shm_create_status status = shm_create(200, &shm_id);
    printf("shm create status is %d\n", status);

    return 0;
}