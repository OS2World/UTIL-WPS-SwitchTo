switchto, a small program that switches to other programs specified on
the command line.

I use it with XFree86-OS/2:

 - On the X desktop, I have a menu selection that runs "switchto Desktop", 
which lets me mouse my way back to PM.

 - On PM, I have a program object that runs "switchto xinitrc.cmd xpmroot.exe",
which looks for both "xinitrc.cmd" and "xpmroot.exe", because although
*usually* xinitrc.cmd exists in my task list, sometimes (especially if
I kill programs in X) it turns into xpmroot.exe.

Notes: 

 - The task entries are case-sensitive!

 - If the task name has a space in it, enclose the name in quotes.

To-do?

 - If the task doesn't exist, start it.

You may use this code however you wish.  It has absolutely no warranty 
whatsoever.  If you find it useful, and are feeling mildly good-hearted,
you could drop me a note at collinsr@cs.rpi.edu, but don't feel bad if you
don't get around to it... :)

-Roddy
collinsr@cs.rpi.edu
