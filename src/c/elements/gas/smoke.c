#include "../elements.h"
#include "../../color.h"
#include "../../main.h"
#include "../../random.h"
#include "../../fluidsim.h"

#define ELEMENT_NAME smoke

_Bool VARPREF(attempt)(Element *el, Cell *cell, Cell *target) {
    if(getType(target) == EMPTY) {
        moveElement(cell, target);
        return 1;
    }
    return 0;
}

void VARPREF(update)(Element *el, Cell *cell, U16 x, U16 y) {
    el->rv -= 1;
    if(el->rv == 0) {
        freeCell(cell);
        return;
    }
    if(cell->x < 10) el->sbpx += 0.4;
    else if(cell->x >= width - 10) el->sbpx -= 0.4;

    if(!attempt_smoke(el, cell, getCell(x + RANDDIR, y - randomBool()))) {
        if(randEveryU8(4)) cell->el->color += 1;
    }
}

ElementInfo VARPOST(info) = {
    .handler = VARPREF(update),
    .attempt = VARPREF(attempt),

    .state = s_GAS,
    .weight = 0.2,
    .baseColor = TOHSL(0, 0, 7)
};

#undef ELEMENT_NAME