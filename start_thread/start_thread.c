
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

/*
	We are executing this function as seperate thread.
*/
void *thread_function(void *data)
{
	pthread_t tid = 0;
	void  *retval = NULL;
	char *msg = (char *)data;

	tid = pthread_self();

	printf("%s: i was running as thread -- id: %lu\n", __func__, tid);

	/* FIXME: need to check the behaviour */
	pthread_detach(tid); /* forcefully detach the thread */

	sleep(3);

	printf("%s: tid=%lu: Message: %s\n", __func__, tid, msg);

	retval = (void *)55;
	pthread_exit(retval);
}


/*
	Function    : start_sync_thread() -- Create blocking thread
	Description : Caller thread will block/wait until the new thread gets exit

	Arguments   :
		api  --   Function to call as new thread
	    args --   Arguments to the newly created thread function
*/
int start_sync_thread(void *api, void *args)
{
    int retval = -1;
	int   tret = -1;
    pthread_t tid = -1;

    do {
		printf("\nmain thread: creating new sync thread ...\n");
        retval = pthread_create(&tid, NULL, api, args);
        if (retval < 0) {
            printf("%s: pthread_create() failed: %s\n", __func__, strerror(errno));
            retval = -1;
            break;
        }

		printf("main thread: in wait ...\n");

		/*
		   pthread_join() is used to hold the caller thread to block/wait until the new thread gets exit
		   This function also, collect the exit status of the threaded function and store it in 'tret'.
		*/
		retval = pthread_join(tid, (void *)&tret);
        if (retval < 0) {
            printf("%s: pthread_join() failed: %s\n", __func__, strerror(errno));
            retval = -1;
            break;
        }

		printf("main thread: received thread retval = %d\n", tret);
		retval = 0;
    } while(0);

    return retval;
} 


/*
	Function    : start_async_thread() -- Create non-blocking thread
	Description : Caller thread will not block/wait for the new thread to exit
	              Both threads will run simultaneously
	Arguments   :
		api  --   Function to call as new thread
	    args --   Arguments to the newly created thread function
*/
int start_async_thread(void *api, void *args)
{
    int retval = -1;
	int   tret = -1;
    pthread_t tid = -1;

    do {
		printf("\nmain thread: creating new async thread ...\n");
        retval = pthread_create(&tid, NULL, api, args);
        if (retval < 0) {
            printf("%s: pthread_create() failed: %s\n", __func__, strerror(errno));
            retval = -1;
            break;
        }

		printf("main thread: new async thread created ...\n");
		retval = 0;
    } while(0);

    return retval;
} 


int main()
{
	int retval = -1;
	char  *msg = NULL;

	/*
	   Here the function 'thread_function()' is called as new thread 
	   and it will be executed in linear fashion by start_sync_thread() plugin
	*/
	msg = "Hello from Sync Thread 1 !";
	retval = start_sync_thread(thread_function, msg);

	msg = "Hello from Sync Thread 2 !";
	retval = start_sync_thread(thread_function, msg);

	msg = "Hello from Sync Thread 3 !";
	retval = start_sync_thread(thread_function, msg);


	/*
	   Here the same 'thread_function()' is called as new thread 
	   and it will be executed simultaneously by start_async_thread() plugin
	*/
	msg = "Hello from Async Thread 1 !";
	retval = start_async_thread(thread_function, msg);

	msg = "Hello from Async Thread 2 !";
	retval = start_async_thread(thread_function, msg);

	msg = "Hello from Async Thread 3 !";
	retval = start_async_thread(thread_function, msg);

	/*
		Using pthread_exit() at the end of the main() will hold/wait the main thread
		until the newly created threads get exits.

		If not, all running child thread will killed on the exit of main thread 
	*/
	pthread_exit(NULL);
	//return 0;
}


//EOF
