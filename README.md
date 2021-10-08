# `fresh`

`fresh` is **f**reyam's **r**eal-time **e**=!mc^2 **sh**ell.

![](fresh-vision.jpg)

> _It is even simpler, yet still not working. WOW I am a super genius!_

## Core Commands

### `cd`

`core/cd.c`

-   `cd` - _changes directory to the home path._
-   `cd ~` - _changes directory to the home path._
-   `cd -` - _changes directory to the previous directory._
-   `cd .` - _changes directory to the current directory._
-   `cd ..` - _changes directory to the parent directory._

### `echo`

`core/echo.c`

-   `echo` - _echoes the given string._

### `history`

`core/history.c`

-   `history` - _displays the command history._

### `ls`

`core/ls.c`

-   `ls` - _lists the contents (files and folders) of the current directory._
-   `ls -a` - _lists the contents (files and folders) of the current directory, including hidden files and folders._
-   `ls -l` - _lists the contents (files and folders) of the current directory, including hidden files and folders, with a long listing format._
-   `ls -la` - _lists the contents (files and folders) of the current directory, including hidden files and folders, with a long listing format._
-   `ls dir/` - _lists the contents (files and folders) of the directory dir/._

### `pinfo`

`core/pinfo.c`

-   `pinfo` - _displays information about the current process._
-   `pinfo {pid}` - _displays information about the process with the given pid._

### `pwd`

`core/pwd.c`

-   `pwd` - _displays the current working directory._

### `repeat`

`core/repeat.c`

-   `repeat {count} {command}` - _repeats the given command {count} times._

-   jobs : prints a list of all currently running jobs along with their pid, in particular,background jobs, in order of their creation along with their state – Running or Stopped.

-   sig <jobNumber> <signalNumber> : takes the job id of a running job and
    sends a signal value to that process

-   fg <jobNumber> : brings a running or a stopped background job with given job
    number to foreground.

-   bg <jobNumber> : changes a stopped background job to a running background job

-   overkill : kills all background process at once.

-   quit : exits the shell.

-   CTRL-Z : It is changing the status of currently running job to stop, and pushing it in background process.

-   CTRL-C : It is causing a SIGINT signal to be sent to the current foreground job of my shell. If there is no foreground job, then the signal does have any effect

-   Command Recall using ‘UP’ arrow key:
-   If the ‘UP’ key is pressed ‘K’ times consecutively, the Kth previous command should be executed.

-   replay -c <command> -t <time> -p <period> command which executes a particular command in fixed time interval for a certain period.

## Utility Modules

### `command_executor`

`utils/command_executor.c`

-   `command_executor` - _executes a given command._

### `command_separator`

`utils/command_separator.c`

-   `command_separator` - _separates a command into its individual arguments._

### `input`

`utils/input.c`

-   `input` - _reads a line of input from the user and appends to history._

### `dir`

`utils/dir.c`

-   `print_dir` - _prints the relative location of the home directory._
-   `get_dir` - _returns the relative location of a directory._

### `lookup_history`

`utils/lookup_history.c`

-   `lookup_history` - _looks up a command in the history and lets user modify and execute them._

_Made with :heart: by Freyam._
