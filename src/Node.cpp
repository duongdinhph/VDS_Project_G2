#include "Node.h"

using namespace std;

namespace ClassProject{

    Node::Node(BDD_ID id, string &label, BDD_ID high, BDD_ID low, BDD_ID top_var)
    : id(id), label(label), high(high), low(low), top_var(top_var) {
        
    }

};