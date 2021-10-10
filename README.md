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

### `jobs`

`core/jobs.c`

-   `jobs` - _displays the list of jobs currently running with their current status._

### `sig`

`core/sig.c`

-   `sig {job} {signal}` - _sends the given signal to the given job._

### `fg`

`core/fg.c`

-   `fg {job}` - _makes the given job the foreground job._

### `bg`

`core/bg.c`

-   `bg {job}` - _makes the given job the background job._

### `replay`

`core/replay.c`

-   `replay -command {command} -interval {interval} -period {period}` - _executes a particular command in fixed time interval for a certain period._

### Signal Handling

-   `CTRL-Z` : _suspends the current job._

-   `CTRL-C` : _terminates the current job._

-   `CTRL-D` : _log you out from your shell._

## Utility Modules

There are several utility modules that can be used to perform various intermediate tasks. These can be found in the `utils` directory.
