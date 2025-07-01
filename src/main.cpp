//
// Created by Carolina P. Nogueira 2016
//

#include <iostream>
#include <string>
#include "Manager.h"
#include "ManagerInterface.h"

using namespace ClassProject;

int main(int argc, char* argv[])
{

    Manager bdd_manager;
    
    // BDD_ID A_ID = bdd_manager.createVar("a");
    // BDD_ID B_ID = bdd_manager.createVar("b");
    // BDD_ID C_ID = bdd_manager.createVar("c");
    // BDD_ID D_ID = bdd_manager.createVar("d");

    // // Implement function f = (a + b) * c * d
    // BDD_ID A_OR_B = bdd_manager.or2(A_ID, B_ID);
    // BDD_ID C_AND_D = bdd_manager.and2(C_ID, D_ID);
    // BDD_ID F = bdd_manager.and2(A_OR_B, C_AND_D);

    // bdd_manager.visualizeBDD("example_bdd.dot", F);

    BDD_ID x1_ID = bdd_manager.createVar("x1");
    BDD_ID x2_ID = bdd_manager.createVar("x2");
    BDD_ID x3_ID = bdd_manager.createVar("x3");

    BDD_ID _x2_AND_x3 = bdd_manager.and2(bdd_manager.neg(x2_ID), x3_ID);
    BDD_ID _x1_AND__x2_AND_x3 = 
        bdd_manager.and2(bdd_manager.neg(x1_ID), _x2_AND_x3);
    BDD_ID x1_AND_x2 = bdd_manager.and2(x1_ID, x2_ID);

    BDD_ID F = bdd_manager.or2(x1_AND_x2, _x1_AND__x2_AND_x3);

    std::set<BDD_ID> list_Var = {};
    bdd_manager.findNodes(F, list_Var);

    bdd_manager.visualizeBDD("example_bdd.dot", F);
}
