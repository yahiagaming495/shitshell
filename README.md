# shitshell
A shell made for people who hate their lives
-----------

**DISCLAIMER: This shell was a hard project to do, Especially for me as a beginner. I asked AI to clarify to me what everything means. So of course this shell is not and will not be perfect. Please report bugs to the bugs section in this repo**

Now with that disclaimer said, Let's clarify what this shell can and can't do

This shell can:
- Run commands
  
- Store command history for the current session to navigate between commands (Using GNU readline)

- Run "cd" and "exit" commands and any other UNIX command

- Run third-party applications

- The shell supports the "~" symbol (without quotes) to go to the home directory

- Tab auto-completion (Enter a portion of the command/file/folder/etc. and press tab to complete it)

This shell can't:

- Do piping

- Say which directory it is in (like zsh)

- Be customized at all

- All other features that is NOT in the list of what the shell can do

**Compiling:**
------
> **NOTE:** There is already a pre-compiled version of the program (shell, run using `./shell` on most systems),
> But if for some reason you want to compile it yourself. Here is how


**Compile using gcc:** 
------
**Arch linux:** `sudo pacman -S gcc` and then `gcc -o shell shell.c -lreadline`


**Fedora:** `sudo dnf install gcc` and then `gcc -o shell shell.c -lreadline`

**Debian:** `sudo apt install gcc` and then `gcc -o shell shell.c -lreadline`

------

> **NOTE: This shell works like any other shell, But with some features not implmented (it will be some day). Normal Linux commands will work and external commands will also work**

Here is an example:

`Shit_shell< whoami
yahia
Shit_shell< ls /usr/bin/zsh
/usr/bin/zsh
Shit_shell< cd ~/Desktop/Projects
Shit_shell< ls
cprograms  pythonshit
Shit_shell< cd cprograms/
Shit_shell< ls
calcproject  shitshell
Shit_shell< cd ..
Shit_shell< grep
Usage: grep [OPTION]... PATTERNS [FILE]...
Try 'grep --help' for more information.
Shit_shell< gcc
gcc: fatal error: no input files
compilation terminated.
Shit_shell< cc
cc: fatal error: no input files
compilation terminated.
Shit_shell< `

Features planned next:

- Customization

- Piping

