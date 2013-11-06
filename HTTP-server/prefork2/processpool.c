#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include "headers/processpool.h"

extern void add_in_tail(queue_t *proc_queue, entry_t *newproc)
{
    proc_queue->count++;
    printf("add free proc in tail,count = %d",proc_queue->count);

    if(proc_queue->head == NULL)
    {
        proc_queue->head = newproc;
        proc_queue->tail = newproc;
    }
    else
    {
        proc_queue->tail->next = newproc;
        proc_queue->tail = newproc;
    }
}

extern entry_t *pop_free_proc(queue_t *proc_queue)
{
    entry_t *curentry;
    entry_t *return_entry;

    curentry = proc_queue->head;

    if (curentry != NULL)
        return_entry = curentry;

    if(proc_queue->head->next != NULL)
        proc_queue->head = proc_queue->head->next;
    else
    {
        proc_queue->head = NULL;
        proc_queue->tail = NULL;
    }
    proc_queue->count--;
    return return_entry;
}

extern proc_pool_t get_pool()
{
    proc_pool_t ppool;
    queue_t proc_queue;
    ppool.proc_queue = &proc_queue;
    ppool.proc_queue->head = NULL;
    ppool.proc_queue->tail = NULL;
    return ppool;
}


