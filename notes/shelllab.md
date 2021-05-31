#  Personal notes / Understanding
This lab is meant to reinforce the understanding of signal handling, through making a tiny shell program. This tiny shell will has limited of functions including the ctrl - c , ctrl - z keystrokes, fg, bg and jobs command. 

#  Personal notes / Understanding
This lab is meant to reinforce the understanding of signal handling, through making a tiny shell program. This tiny shell will has limited of functions including the ctrl - c , ctrl - z keystrokes, fg, bg and jobs command.

<h3> Reaping Child Process </h3>

 - When the process is terminated for any reason , the kernel does not remove it immediately, but it will kept until the process's parent reap it. 
 -  A terminated process that has not yet reaped by the parent is called a zombie. ( Terminated but still in process table )
 - Once the parent read the child's exit status through wait() function, then the zombie's entry is removed from the process table and it is said to be "reaped".
 - If a parent process terminates, the kernel will arrange init process to become the adopted parent of any orphaned children to reap the children.
 - By default, the waitpid() suspends execution of the calling process until a child process in its wait set terminates.
 - Further detail about the wait function such as modifying the default behavior, member of the wait set, exit status of a reaped child and etc can be read from the manual.

<h3> Signal </h3>

![image](https://user-images.githubusercontent.com/68408911/120140877-07230b80-c20e-11eb-83e0-2cebff2f3974.png)

- Pretty much like what the word imply, signal is a small message that notifies a process that an event of some type has occured.
- The figure above show some signal corresponding to their event and the default action to the signal.
- All default action associated with a signal can be modified except SIGSTOP and SIGKILL.
- By default, a child process belongs to the same process group as its parent, and we can use setpgid() to change the process group.
- Only one same type of signal can be handled at a time and because the pending bit vector contains exactly one bit for each type of signal, there can be at most one pending signal of any particular type.
- For example: When signal K is sent to the process, and the signal is not blocked at the moment, then the process will start to handle the signal K. If there is another signal K arrive, then the new signal K will be pending. And if there is another signal K arrive, the  last signal K will be simply discarded.

<h3> Race Condition </h3>

 - Because of the concurrency and interleaving behavior, synchronization error known as race can occur.
 - Hence, different approaches are needed such as signal blocking, explicitly waiting for signals.
 - sigprocmask() functions able to changes the set of currently blocked signals.
 - Signal sets such as set are manipulated using the following functions: The sigemptyset initializes set to the empty set. The sigfillset function adds every signal to set. The sigaddset function adds signum to set, sigdelset deletes signum from set, and sigismember returns 1 if signum is a member of set, and 0 if not.

<h3> Lab </h3>

**Flow for the shell**
1. The command will save into cmdline at first, and go through eval function.
2. Call parseline() to parse the argument and check if the instruction is run in background or foreground.
3. Block the signal before fork() and change the process group id.
4. If execve failed, remember to call exit() because the jobs will still remain in the entry, without exit the parent unable to reap it.
5. If run in foreground, we will call waitfg to suspend the process until it terminate and send the signal to sigchld_handler.
 7. Sigchld_handler will handle it depend on the exit status.
 8. CTRL - C will be handled by the sigint_handler, CTRL - Z will be handled by the sigtstp_handler.
 9. To resume the process that pause by CTRL - Z, simply use kill ( - pid, SIGCONT) and change the job state.
 
