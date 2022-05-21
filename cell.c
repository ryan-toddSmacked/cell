#include "cell.h"

#include <stdlib.h>

struct Data {
    void * dataPtr;
    void (*_free)(void *);
};

struct Cell {
    struct Data * m_data;        
    size_t m_numel;
};

typedef struct Cell * cell_t;



cell_t cellsAlloc(size_t ncells) {
    cell_t cells = (struct Cell *)calloc(1, sizeof(struct Cell));
    if (cells == NULL) { return NULL; }
    cells->m_data = (struct Data *)calloc(ncells, sizeof(struct Data));
    if (cells->m_data == NULL) { free(cells); return NULL; }
    cells->m_numel = ncells;
    return cells;
}

int cellsSet(cell_t cells, size_t index, void * dataptr, void (*_free)(void *)) {
    if (cells == NULL) { return -1; }
    if (index >= cells->m_numel) { return -1; }
    cells->m_data[index].dataPtr = dataptr;
    cells->m_data[index]._free = _free;
    return 0;
}

void * cellsGet(cell_t cells, size_t index) {
    if (cells == NULL) { return NULL; }
    if (index >= cells->m_numel) { return NULL; }
    return cells->m_data[index].dataPtr;
}

void cellsFree(cell_t cells) {
    size_t i;
    if (cells == NULL) { return; }
    for (i = 0; i < cells->m_numel; i++)
        if (cells->m_data[i]._free)
            cells->m_data[i]._free(cells->m_data[i].dataPtr);
    free(cells->m_data);
    free(cells);
}
