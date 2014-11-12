/*
    sim_pag_lru.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sim_paging.h"

// Function that initialises the tables

void init_tables (ssystem * S)
{
    int i;

    // Reset pages
    memset (S->pgt, 0, sizeof(spage)*S->numpags);

    // Empty LRU stack
    S->lru = -1;

    // Reset LRU(t) time
    S->clock = 0;

    // Circular list of free frames
    for (i=0; i<S->numframes-1; i++)
    {
        S->frt[i].page = -1;
        S->frt[i].next = i+1;
    }

    S->frt[i].page = -1;    // Now i == numframes-1
    S->frt[i].next = 0;     // Close circular list
    S->listfree = i;        // Point to the last one

    // Empty circular list of occupied frames
    S->listoccupied = -1;
}

// Functions that simulate the hardware of the MMU

unsigned sim_mmu (ssystem * S, unsigned virtual_addr, char op)
{
    unsigned physical_addr;
    int page, frame, offset;

    page = virtual_addr / S->pagsz;
    offset = virtual_addr % S->pagsz;

    //check if legal address
    if (page < 0 || page >= S->numpags)
    {
        S->numillegalrefs ++;
        return ~0U;
    }

    //check if present
    if (!S->pgt[page].present) //not present
        handle_page_fault(S, virtual_addr); //interrupt page fault

    //is present, now get physicall address
    frame = S->pgt[page].frame;
    physical_addr = frame * S->pagsz + offset;

    reference_page(S,page, op);

    if (S->detailed)
        printf("\t%c %u == P%d(M%d )+% d\n" ,
                op , virtual_addr , page , frame , offset);

    // TODO: Type in the code that simulates the MMU's (hardware)
    //       behaviour in response to a memory access operation

    return physical_addr;
}

void reference_page (ssystem * S, int page, char op)
{
    S->pgt[page].timestamp = S->clock;
    S->clock ++;

    if (S->clock == 0)
        printf("WARNING!!! CLOCK OVERFLOW\n");

    if (op=='R')                         // If it's a read,
        S->numrefsread ++;               // count it
    else if (op=='W')
    {                                    // If it's a write,
        S->pgt[page].modified = 1;       // count it and mark the
        S->numrefswrite ++;              // page 'modified'
    }
}

// Functions that simulate the operating system

void handle_page_fault (ssystem * S, unsigned virtual_addr)
{
    int page, victim, frame, last;

    S->numpagefaults ++;
    page = virtual_addr / S->pagsz;

    if (S->detailed)
        printf("@ PAGE FAULT in P%d!\n", page );    

    if (S->listfree != -1) //if free frames
    {
        last = S->listfree;
        frame = S->frt[last].next; //take 1st
        if (frame == last)        
            S->listfree = -1; //now all frames are occupied           
        else        
            S->frt[last].next = S->frt[frame].next;
        occupy_free_frame(S, frame, page);
    }else
    {
        victim = choose_page_to_be_replaced(S);
        replace_page(S, victim, page);
    }


    // TODO: Type in the code that simulates the Operating
    //       System's response to a page fault trap
}

int choose_page_to_be_replaced (ssystem * S)
{
    int frame, victim, i;

    frame = 0;
    //search for lru frame
    for (i = 1; i < S->numframes; ++i)
    {
        if (S->pgt[S->frt[frame].page].timestamp >
            S->pgt[S->frt[i].page].timestamp) //frame newer than i
        {
            frame = i;                        
        }
    }

    victim = S->frt[frame].page;

    if (S->detailed)
        printf ("@ Choosing (at LRU) P%d of F%d to be "
                "replaced\n", victim, frame);

    return victim;    
}

void replace_page (ssystem * S, int victim, int newpage)
{
    int frame;

    frame = S->pgt[victim].frame;

    if (S->pgt[victim].modified)
    {
        if (S->detailed)
            printf ("@ Writing modified P%d back (to disc) to "
                    "replace it\n", victim);

        S->numpgwriteback ++;
    }

    if (S->detailed)
        printf ("@ Replacing victim P%d with P%d in F%d\n",
                victim, newpage, frame);

    S->pgt[victim].present = 0;

    S->pgt[newpage].present = 1;
    S->pgt[newpage].frame = frame;
    S->pgt[newpage].modified = 0;

    S->frt[frame].page = newpage;
}

void occupy_free_frame (ssystem * S, int frame, int page)
{
    if (S->detailed)
        printf ("@ Storing P%d in F%d\n", page, frame);

    //link frame to page
    S->frt[frame].page = page;

    //link page to frame and modify page status
    S->pgt[page].frame = frame;
    S->pgt[page].present = 1;
    S->pgt[page].modified = 0;    

    // TODO: Write the code that links the page with the frame and
    //       vice-versa, and wites the corresponding values in the
    //       state bits of the page (presence...)
}

// Functions that show results

void print_page_table (ssystem * S)
{
    int p;

    printf ("%10s %10s %10s   %10s %s\n",
            "PAGE", "Present", "Frame", "Modified", "TimeStamp");

    for (p=0; p<S->numpags; p++)
        if (S->pgt[p].present)
            printf ("%8d   %6d     %8d   %6d   %8d\n", p,
                    S->pgt[p].present, S->pgt[p].frame,
                    S->pgt[p].modified, S->pgt[p].timestamp);
        else
            printf ("%8d   %6d     %8s   %6s   %8s\n", p,
                    S->pgt[p].present, "-", "-","-");
}

void print_frames_table (ssystem * S)
{
    int p, f;

    printf ("%10s %10s %10s   %s\n",
            "FRAME", "Page", "Present", "Modified");

    for (f=0; f<S->numframes; f++)
    {
        p = S->frt[f].page;

        if (p==-1)
            printf ("%8d   %8s   %6s     %6s\n", f, "-", "-", "-");
        else if (S->pgt[p].present)
            printf ("%8d   %8d   %6d     %6d\n", f, p,
                    S->pgt[p].present, S->pgt[p].modified);
        else
            printf ("%8d   %8d   %6d     %6s   ERROR!\n", f, p,
                    S->pgt[p].present, "-");
    }
}

void print_replacement_report (ssystem * S)
{
    printf ("LRU replacement\n");

    //get min & max timestamp    
    int min = S->pgt[0].timestamp;
    int max = min;
    int i;
    for (i = 1; i < S->numpags; ++i)
    {
        if(S->pgt[i].present && min > S->pgt[i].timestamp)
            min = S->pgt[i].timestamp;

        if(S->pgt[i].present && max < S->pgt[i].timestamp)
            max = S->pgt[i].timestamp;
    }

    printf("Clock--------------> %d\n",S->clock );
    printf("Minimum TimeStamp--> %d\n",min);
    printf("Maximum TimeStamp--> %d\n",max);
}


