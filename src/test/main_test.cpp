//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"
#include <gtest/gtest.h>
#include <string>

using namespace ClassProject;

/// Manager Constructor
TEST_F(ManagerTest, constructor_size_test){
    BDD_ID table_size = managerTest.unique_table.size();
    EXPECT_EQ(2,table_size);
}

/// True Node
TEST_F(ManagerTest, true_test){
    EXPECT_EQ(1,managerTest.True());
}

/// False Node
TEST_F(ManagerTest, false_test){
    EXPECT_EQ(0,managerTest.False());
}

/// Manager Size
TEST_F(ManagerTest, manager_size_test){
    BDD_ID table_size = managerTest.uniqueTableSize();
    EXPECT_EQ(2,table_size);
}

/// Unique Table Size
TEST_F(TableTest, size_create_var_test){
    BDD_ID table_size = tableTest.uniqueTableSize();
    EXPECT_EQ(5,table_size);
}

/// Create Variable
TEST_F(TableTest, check_create_var_test){
    std::string labels[3] = {"a", "b", "c"};

    for (int i = 2; i <= 4; i++){
        EXPECT_EQ(i,tableTest.unique_table[i].id);
        EXPECT_EQ(labels[i - 2],tableTest.unique_table[i].label);
        EXPECT_EQ(1,tableTest.unique_table[i].high);
        EXPECT_EQ(0,tableTest.unique_table[i].low);
        EXPECT_EQ(i,tableTest.unique_table[i].top_var);
    }
}



int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
