#include "search.h"
#include "position.h"
#include "uci_helper.h"

int bench(UCIHelper *uciHelper, Position *pos)
{
    nodes = 0;
    root_search(uciHelper, pos);
    return nodes;
}