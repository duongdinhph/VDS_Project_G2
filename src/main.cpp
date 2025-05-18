//
// Created by Carolina P. Nogueira 2016
//

#include <iostream>
#include <string>
#include "Manager.h"

using namespace ClassProject;

int main(int argc, char* argv[])
{
    Manager bdd_manager;
    
    BDD_ID A_ID = bdd_manager.createVar("a");
    BDD_ID B_ID = bdd_manager.createVar("b");
    BDD_ID C_ID = bdd_manager.createVar("c");
    BDD_ID D_ID = bdd_manager.createVar("d");

    BDD_ID A_OR_B = bdd_manager.or2(A_ID, B_ID);
    BDD_ID C_AND_D = bdd_manager.and2(C_ID, D_ID);

    BDD_ID F = bdd_manager.and2(A_OR_B, C_AND_D);

    bdd_manager.visualizeBDD("example_bdd.dot", F);
}
