#ifndef __CELL_C_DECL_H
#define __CELL_C_DECL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct Cell * cell_t;

cell_t cellsAlloc(size_t ncells);

int    cellsSet(cell_t cells, size_t index, void * dataptr, void (*_free)(void *));
void * cellsGet(cell_t cells, size_t index);

void cellsFree(cell_t cells);



#ifdef __cplusplus
}
#endif

#endif
