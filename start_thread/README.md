
#Plugin to create blocking and non-blocking threads

**start_sync_thread()**
Function    : ```start_sync_thread()``` -- Create blocking thread
Description : Caller thread will block/wait until the new thread gets exit

Arguments   :
    ```api```  --   Function to call as new thread
    ```args``` --   Arguments to the newly created thread function

**start_sync_thread()**
Function    : ```start_async_thread()``` -- Create non-blocking thread
Description : Caller thread will not block/wait for the new thread to exit
              Both threads will run simultaneously
Arguments   :
    ```api```  --   Function to call as new thread
    ```args``` --   Arguments to the newly created thread function

**Usage:**
````
start_sync_thread(thread_function, arguments);
start_async_thread(thread_function, arguments);
````
