#ifndef BDD_NODE
#define BDD_NODE

#include "ManagerInterface.h"

namespace ClassProject{
    class Node{
        public:
            BDD_ID high;
            BDD_ID low;
            BDD_ID top_var;
            std::string label;

            Node (const std::string &c_label, BDD_ID c_high, BDD_ID c_low, BDD_ID c_top_var);
       };
};

#endif