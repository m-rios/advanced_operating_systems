/*
    example.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

void show_command (command * C);

int main ()
{
    command C;
    int r;

    printf ("Type commands (press Ctrl-D to finish)\n");

    do              // Read commands and show them
    {
        init_command (&C);

        printf ("$ ");
        r = read_command (&C, stdin);

        if (r < 0)
            fprintf (stderr, "\nError %d: %s\n",
                             -r, err_messages[-r]);
        else
            show_command (&C);

        free_command (&C);
    }
    while (r==0);   // Repeat until error or EOF

    return 0;
}

void show_command (command * C)
{
    int i;

    printf ("\tRaw command: \"%s\"\n", C->raw_command);
    printf ("\tNumber of arguments: %d\n", C->argc);

    for (i=0; i<=C->argc; i++)
        if (C->argv[i] != NULL)
            printf ("\t\targv[%d]: \"%s\"\n", i, C->argv[i]);
        else
            printf ("\t\targv[%d]: NULL\n", i);

    if (C->input)
        printf ("\tInput: \"%s\"\n", C->input);

    if (C->output)
        printf ("\tOutput: \"%s\"\n", C->output);

    if (C->output_err)
        printf ("\tErr. output: \"%s\"\n", C->output_err);

    printf ("\tExecute in background: %s\n",
            C->background ? "Yes" : "No");
}


