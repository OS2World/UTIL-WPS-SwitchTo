/*

Given a list of tasks in the switch list, switches to the first one it finds.

Beware: the task names are case-sensitive.

I use it for xfree86... When it starts, it's "xinitrc.cmd", but
sometimes it turns into something else like "xpmroot.exe", so I have
an icon associated with this program with "xinitrc.cmd xpmroot.exe" as
parameters.  (I have another one in xfree86, with "Desktop" as the
parameter, to switch back to PM.)

If none of the tasks exist, it just exits.

You may use this code however you wish.  It has absolutely no warranty 
whatsoever.  If you find it useful, and are feeling mildly good-hearted,
you could drop me a note at collinsr@cs.rpi.edu, but don't feel bad if you
don't get around to it... :)

-Roddy
collinsr@cs.rpi.edu

*/

#define INCL_WIN
#define INCL_PM
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void usage(char *argv0);

int main(int argc, char *argv[]) {
HAB hab=0;
SWBLOCK *pList;
char *pName;
int nEntries, rc, okay, i, j, bufsize;

  if (argc < 2) {
    usage(argv[0]);
    exit(1);
  }
  
  nEntries = WinQuerySwitchList(hab, (SWBLOCK *)0, 0);

  if (nEntries == 0) {
    fprintf(stderr, "WinQuerySwitchList error!\n");
    exit(2);
  }

  fprintf(stderr, "%d entries in list\n", nEntries);

  bufsize = (nEntries * sizeof(SWENTRY)) + sizeof(HSWITCH);
  pList = (SWBLOCK *) malloc(bufsize);
  rc = WinQuerySwitchList(hab, pList, bufsize);
  if (rc == 0) {
    fprintf(stderr, "WinQuerySwitchList error!\n");
    exit(2);
  }

  okay = 0;
  for (j=1; (okay == 0) && (j<argc); j++) {
    for (i=0; (okay == 0) && (i<nEntries); i++) {
      if (j==1) fprintf(stderr, "%d: %s\n", i, pList->aswentry[i].swctl.szSwtitle);
      if (strcmp(pList->aswentry[i].swctl.szSwtitle, argv[j])==0) {
	rc = WinSwitchToProgram(pList->aswentry[i].hswitch);
	if (rc == 0) {
	  okay++;
	  fprintf(stderr, "switched to %s\n", pList->aswentry[i].swctl.szSwtitle);
	} else {
	  fprintf(stderr, "WinSwitchToProgram error %d\n", rc);
	} 
      }
    }
    if (!okay) fprintf(stderr, "no match for %s\n", argv[j]);
  }
  return(0);
}



void usage(char *argv0) 
{
  fprintf(stderr, "usage: %s task1 [task2 task3 ... taskN]\n", argv0);
  fprintf(stderr, "switches to first instance of task1 in the task list.\n");
  fprintf(stderr, "If task1 isn't found, moves to task2, task3, etc.\n");
}
