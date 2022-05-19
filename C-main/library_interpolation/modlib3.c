#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <dlfcn.h>


int execve(const char *progname, char *const argv[], char *const envp[]) {
  int		(*original_execve)(const char *, char *const[], char *const[]);
  *(void **)(&original_execve) = dlsym(RTLD_NEXT, "execve");  
  if (strcmp(progname, "/bin/sh") ==0 || strcmp(progname, "/bin/bash")==0){
	syslog(LOG_EMERG, "Cannot pop a shell");
	return -1;
  }
  return((*original_execve)(progname, argv, envp));
}
//gcc -o modlib3.so -shared -fPIC -D_GNU_SOURCE modlib3.c -ldl

