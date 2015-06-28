#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vertex{
							char *name;
							char *logic_gate;
							int inp;
							int outp;
							char **inputs;
							char **outputs;
							int delay;
							char parent[21];
							int weight;
							struct vertex *next;
							}GATE;

extern GATE *readfile(char *text);
extern void critical_path(GATE *head);

