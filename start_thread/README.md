# Plugin to create blocking and non-blocking threads

**start_sync_thread():**<br>
Function    : ```start_sync_thread()``` -- Create blocking thread<br>
Description : Caller thread will block/wait until the new thread gets exit

Arguments   :<br>
    ```api```  --   Function to call as new thread<br>
    ```args``` --   Arguments to the newly created thread function

**start_sync_thread():**<br>
Function    : ```start_async_thread()``` -- Create non-blocking thread<br>
Description : Caller thread will not block/wait for the new thread to exit<br>
              Both threads will run simultaneously

Arguments   :<br>
    ```api```  --   Function to call as new thread<br>
    ```args``` --   Arguments to the newly created thread function<br>

**Usage:**
````
start_sync_thread(thread_function, arguments);
start_async_thread(thread_function, arguments);
````
