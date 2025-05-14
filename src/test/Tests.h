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
};

#endif
