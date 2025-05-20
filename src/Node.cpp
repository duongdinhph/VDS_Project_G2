#include "Node.h"

namespace ClassProject{

    Node::Node(const std::string &c_label, BDD_ID c_high, BDD_ID c_low, BDD_ID c_top_var) {
        label = c_label;
        high = c_high;
        low = c_low;
        top_var = c_top_var;
    }

};