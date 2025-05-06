#ifndef BDD_NODE
#define BDD_NODE

#include "ManagerInterface.h"

using namespace std;

namespace ClassProject{
    class Node{
        public:
            BDD_ID id;
            BDD_ID high;
            BDD_ID low;
            BDD_ID top_var;
            string label;

            Node (BDD_ID c_id, string &c_label, BDD_ID c_high, BDD_ID c_low, BDD_ID c_top_var);
       };
};

#endif