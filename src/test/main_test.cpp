//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"
#include <gtest/gtest.h>

using namespace ClassProject;

/// Manager Constructor
TEST_F(ManagerTest, constructor_sizeok){

    BDD_ID table_size = managerTest.unique_table.size();
    EXPECT_EQ(2,table_size);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
