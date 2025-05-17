//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include <gtest/gtest.h>
#include "../Manager.h"

using namespace ClassProject;

class ManagerTest : public testing::Test {
public:
    Manager managerTest;
    BDD_ID TRUE_ID = 1;
    BDD_ID FALSE_ID = 0; 
};

class TableTest : public testing::Test {
public:
    Manager tableTest;

    void SetUp() override
    {
        tableTest.createVar("a");
        tableTest.createVar("b");
        tableTest.createVar("c");
    }

    BDD_ID TRUE_ID = 1;
    BDD_ID FALSE_ID = 0; 
};

class ITETest : public testing::Test {
public:
    Manager iteTest;

    BDD_ID TRUE_ID = 1;
    BDD_ID FALSE_ID = 0; 
};

class GateTest : public testing::Test {
public:
    Manager gateTest;

    BDD_ID A_ID = gateTest.createVar("a");
    BDD_ID B_ID = gateTest.createVar("b");
    BDD_ID C_ID = gateTest.createVar("c");
    BDD_ID D_ID = gateTest.createVar("d");

    BDD_ID TRUE_ID = 1;
    BDD_ID FALSE_ID = 0; 
};

#endif
