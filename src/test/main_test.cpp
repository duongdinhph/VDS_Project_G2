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
    BDD_ID True_ID = managerTest.True();
    EXPECT_EQ(TRUE_ID,True_ID);
    EXPECT_EQ("TRUE",managerTest.unique_table[True_ID].label);
    EXPECT_EQ(TRUE_ID,managerTest.unique_table[True_ID].high);
    EXPECT_EQ(TRUE_ID,managerTest.unique_table[True_ID].low);
    EXPECT_EQ(TRUE_ID,managerTest.unique_table[True_ID].top_var);
}

/// False Node
TEST_F(ManagerTest, false_test){
    BDD_ID False_ID = managerTest.False();
    EXPECT_EQ(FALSE_ID,False_ID);
    EXPECT_EQ("FALSE",managerTest.unique_table[False_ID].label);
    EXPECT_EQ(FALSE_ID,managerTest.unique_table[False_ID].high);
    EXPECT_EQ(FALSE_ID,managerTest.unique_table[False_ID].low);
    EXPECT_EQ(FALSE_ID,managerTest.unique_table[False_ID].top_var);
}

/// Manager Size
TEST_F(ManagerTest, manager_size_test){
    BDD_ID table_size = managerTest.uniqueTableSize();
    EXPECT_EQ(2,table_size);
}

/// Create Variable
TEST_F(ManagerTest, create_var_manager_test){
    EXPECT_EQ(2,managerTest.uniqueTableSize());
    managerTest.createVar("a");
    EXPECT_EQ(3,managerTest.uniqueTableSize());
    managerTest.createVar("b");
    EXPECT_EQ(4,managerTest.uniqueTableSize());
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
        EXPECT_EQ(TRUE_ID,tableTest.unique_table[i].high);
        EXPECT_EQ(FALSE_ID,tableTest.unique_table[i].low);
        EXPECT_EQ(i,tableTest.unique_table[i].top_var);
    }
}

/// Is Constant
TEST_F(TableTest, constant_test){
    bool output[5] = {true, true, false, false, false};

    for (int i = 0; i <= 4; i++){
        BDD_ID current_id = tableTest.unique_table[i].id;
        EXPECT_EQ(output[i], tableTest.isConstant(current_id));   
    }
}

/// Is Variable
TEST_F(TableTest, variable_test){
    bool output[5] = {false, false, true, true, true};

    for (int i = 0; i <= 4; i++){
        BDD_ID current_id = tableTest.unique_table[i].id;
        EXPECT_EQ(output[i], tableTest.isVariable(current_id));   
    }
}

/// Top Variable
TEST_F(TableTest, top_var_test){
    for (int i = 2; i <= 4; i++){
        BDD_ID current_id = tableTest.unique_table[i].id;
        EXPECT_EQ(i, tableTest.topVar(current_id));   
    }
}

/// Negation
TEST_F(TableTest, neg_test){
    for (int i = 2; i <= 4; i++){
        BDD_ID neg_id_new = tableTest.neg(i);
        EXPECT_EQ(tableTest.unique_table[i].high, tableTest.unique_table[neg_id_new].low);
        EXPECT_EQ(tableTest.unique_table[i].low, tableTest.unique_table[neg_id_new].high);  
        
        BDD_ID neg_id_exists = tableTest.neg(i);
        EXPECT_EQ(tableTest.unique_table[i].high, tableTest.unique_table[neg_id_exists].low);
        EXPECT_EQ(tableTest.unique_table[i].low, tableTest.unique_table[neg_id_exists].high); 
        EXPECT_EQ(neg_id_new, neg_id_exists); 
    }
}

// If-Then-Else
TEST_F(ITETest, ite_test){   
    BDD_ID A_ID = iteTest.createVar("a");
    BDD_ID B_ID = iteTest.createVar("b");
    BDD_ID C_ID = iteTest.createVar("c");
    BDD_ID D_ID = iteTest.createVar("d");

    //Terminal cases
    BDD_ID ite = iteTest.ite(TRUE_ID, A_ID, B_ID);
    EXPECT_EQ(A_ID,ite);

    ite = iteTest.ite(FALSE_ID, A_ID, B_ID);
    EXPECT_EQ(B_ID,ite);

    ite = iteTest.ite(A_ID, TRUE_ID, FALSE_ID);
    EXPECT_EQ(A_ID,ite);

    ite = iteTest.ite(A_ID, B_ID, B_ID);
    EXPECT_EQ(B_ID,ite);

    ite = iteTest.ite(A_ID, FALSE_ID, TRUE_ID);
    EXPECT_EQ(iteTest.neg(A_ID),ite);

    // a*b
    ite = iteTest.ite(A_ID, B_ID, FALSE_ID);
    BDD_ID expected_id_A_AND_B = iteTest.uniqueTableSize()-1;

    EXPECT_EQ(expected_id_A_AND_B, ite);
    EXPECT_EQ(B_ID, iteTest.unique_table[ite].high);
    EXPECT_EQ(FALSE_ID, iteTest.unique_table[ite].low);
    EXPECT_EQ(A_ID, iteTest.unique_table[ite].top_var);

    // c*d
    ite = iteTest.ite(C_ID, D_ID, FALSE_ID);
    BDD_ID expected_id_C_AND_D = iteTest.uniqueTableSize()-1;

    EXPECT_EQ(expected_id_C_AND_D, ite);
    EXPECT_EQ(D_ID, iteTest.unique_table[ite].high);
    EXPECT_EQ(FALSE_ID, iteTest.unique_table[ite].low);
    EXPECT_EQ(C_ID, iteTest.unique_table[ite].top_var);  
    
    // expected_id_A_AND_B + expected_id_C_AND_D
    ite = iteTest.ite(expected_id_A_AND_B, TRUE_ID, expected_id_C_AND_D);

    // Checking intermediate node
    BDD_ID expected_id_intermediate_output = iteTest.uniqueTableSize()-2;

    EXPECT_EQ(expected_id_intermediate_output, ite-1);
    EXPECT_EQ(TRUE_ID, iteTest.unique_table[ite-1].high);
    EXPECT_EQ(expected_id_C_AND_D, iteTest.unique_table[ite-1].low);
    EXPECT_EQ(B_ID, iteTest.unique_table[ite-1].top_var); 
    
    // Checking output node
    BDD_ID expected_id_output = iteTest.uniqueTableSize()-1;

    EXPECT_EQ(expected_id_output, ite);
    EXPECT_EQ(expected_id_intermediate_output, iteTest.unique_table[ite].high);
    EXPECT_EQ(expected_id_C_AND_D, iteTest.unique_table[ite].low);
    EXPECT_EQ(A_ID, iteTest.unique_table[ite].top_var);   

    // Negation of output node
    ite = iteTest.ite(expected_id_output, FALSE_ID, TRUE_ID);
    BDD_ID expected_id_neg_output = iteTest.uniqueTableSize()-1;

    EXPECT_EQ(expected_id_neg_output, ite);
    EXPECT_EQ(expected_id_C_AND_D, iteTest.unique_table[ite].high);
    EXPECT_EQ(expected_id_intermediate_output, iteTest.unique_table[ite].low);
    EXPECT_EQ(A_ID, iteTest.unique_table[ite].top_var);   
}

// Co-factor True
TEST_F(ITETest, co_factor_true_test){
    BDD_ID A_ID = iteTest.createVar("a");
    BDD_ID B_ID = iteTest.createVar("b");
    BDD_ID C_ID = iteTest.createVar("c");
    BDD_ID D_ID = iteTest.createVar("d");

    BDD_ID expected_id_A_AND_B = iteTest.ite(A_ID, B_ID, FALSE_ID);
    BDD_ID expected_id_C_AND_D = iteTest.ite(C_ID, D_ID, FALSE_ID);
    BDD_ID expected_id_output = iteTest.ite(expected_id_A_AND_B, TRUE_ID, expected_id_C_AND_D); //Inserts 2 new nodes

    // With one argument
    EXPECT_EQ(iteTest.coFactorTrue(TRUE_ID), TRUE_ID);
    EXPECT_EQ(iteTest.coFactorTrue(FALSE_ID), FALSE_ID);

    for (int i = 2; i < iteTest.uniqueTableSize()-4 ; i++){
        EXPECT_EQ(iteTest.coFactorTrue(i), TRUE_ID);
    }

    EXPECT_EQ(iteTest.coFactorTrue(expected_id_A_AND_B), B_ID);    
    EXPECT_EQ(iteTest.coFactorTrue(expected_id_C_AND_D), D_ID);
    EXPECT_EQ(iteTest.coFactorTrue(expected_id_output-1), TRUE_ID);
    EXPECT_EQ(iteTest.coFactorTrue(expected_id_output), expected_id_output-1);


    // With two arguments
    EXPECT_EQ(iteTest.coFactorTrue(expected_id_A_AND_B, A_ID), B_ID); 
    EXPECT_EQ(iteTest.coFactorTrue(expected_id_C_AND_D, C_ID), D_ID);   
    EXPECT_EQ(iteTest.coFactorTrue(expected_id_C_AND_D, A_ID), expected_id_C_AND_D);    
    EXPECT_EQ(iteTest.coFactorTrue(expected_id_C_AND_D, B_ID), expected_id_C_AND_D);    

}

// Co-factor False
TEST_F(ITETest, co_factor_false_test){
    BDD_ID A_ID = iteTest.createVar("a");
    BDD_ID B_ID = iteTest.createVar("b");
    BDD_ID C_ID = iteTest.createVar("c");
    BDD_ID D_ID = iteTest.createVar("d");

    BDD_ID expected_id_A_AND_B = iteTest.ite(A_ID, B_ID, FALSE_ID);
    BDD_ID expected_id_C_AND_D = iteTest.ite(C_ID, D_ID, FALSE_ID);
    BDD_ID expected_id_output = iteTest.ite(expected_id_A_AND_B, TRUE_ID, expected_id_C_AND_D); //Inserts 2 new nodes

    // With one argument
    EXPECT_EQ(iteTest.coFactorFalse(TRUE_ID), TRUE_ID);
    EXPECT_EQ(iteTest.coFactorFalse(FALSE_ID), FALSE_ID);

    for (int i = 2; i < iteTest.uniqueTableSize()-4 ; i++){
        EXPECT_EQ(iteTest.coFactorFalse(i), FALSE_ID);
    }

    EXPECT_EQ(iteTest.coFactorFalse(expected_id_A_AND_B), FALSE_ID);
    EXPECT_EQ(iteTest.coFactorFalse(expected_id_C_AND_D), FALSE_ID);
    EXPECT_EQ(iteTest.coFactorFalse(expected_id_output-1), expected_id_C_AND_D);
    EXPECT_EQ(iteTest.coFactorFalse(expected_id_output), expected_id_C_AND_D);


    // With two arguments
    EXPECT_EQ(iteTest.coFactorFalse(expected_id_A_AND_B, A_ID), FALSE_ID); 
    EXPECT_EQ(iteTest.coFactorFalse(expected_id_C_AND_D, C_ID), FALSE_ID);   
    EXPECT_EQ(iteTest.coFactorFalse(expected_id_C_AND_D, A_ID), expected_id_C_AND_D);    
    EXPECT_EQ(iteTest.coFactorFalse(expected_id_C_AND_D, B_ID), expected_id_C_AND_D);   

}

// AND
TEST_F(GateTest, and_test){
    // a*b
    BDD_ID ite = gateTest.and2(A_ID, B_ID);
    BDD_ID expected_id_A_AND_B = gateTest.uniqueTableSize()-1;

    EXPECT_EQ(expected_id_A_AND_B, ite);
    EXPECT_EQ(B_ID, gateTest.unique_table[ite].high);
    EXPECT_EQ(FALSE_ID, gateTest.unique_table[ite].low);
    EXPECT_EQ(A_ID, gateTest.unique_table[ite].top_var);

    // c*d
    ite = gateTest.and2(C_ID, D_ID);
    BDD_ID expected_id_C_AND_D = gateTest.uniqueTableSize()-1;

    EXPECT_EQ(expected_id_C_AND_D, ite);
    EXPECT_EQ(D_ID, gateTest.unique_table[ite].high);
    EXPECT_EQ(FALSE_ID, gateTest.unique_table[ite].low);
    EXPECT_EQ(C_ID, gateTest.unique_table[ite].top_var); 
}

// OR
TEST_F(GateTest, or_test){
    // a+b
    BDD_ID ite = gateTest.or2(A_ID, B_ID);
    BDD_ID expected_id_A_OR_B = gateTest.uniqueTableSize()-1;

    EXPECT_EQ(expected_id_A_OR_B, ite);
    EXPECT_EQ(TRUE_ID, gateTest.unique_table[ite].high);
    EXPECT_EQ(B_ID, gateTest.unique_table[ite].low);
    EXPECT_EQ(A_ID, gateTest.unique_table[ite].top_var);

    // c+d
    ite = gateTest.or2(C_ID, D_ID);
    BDD_ID expected_id_C_OR_D = gateTest.uniqueTableSize()-1;

    EXPECT_EQ(expected_id_C_OR_D, ite);
    EXPECT_EQ(TRUE_ID, gateTest.unique_table[ite].high);
    EXPECT_EQ(D_ID, gateTest.unique_table[ite].low);
    EXPECT_EQ(C_ID, gateTest.unique_table[ite].top_var); 
}

// XOR
TEST_F(GateTest, xor_test){
    // a XOR b
    BDD_ID ite = gateTest.xor2(A_ID, B_ID);
    BDD_ID expected_id_A_XOR_B = gateTest.uniqueTableSize()-1;

    EXPECT_EQ(expected_id_A_XOR_B, ite);
    EXPECT_EQ(expected_id_A_XOR_B-1, gateTest.unique_table[ite].high);
    EXPECT_EQ(B_ID, gateTest.unique_table[ite].low);
    EXPECT_EQ(A_ID, gateTest.unique_table[ite].top_var);

    // c XOR d
    ite = gateTest.xor2(C_ID, D_ID);
    BDD_ID expected_id_C_XOR_D = gateTest.uniqueTableSize()-1;

    EXPECT_EQ(expected_id_C_XOR_D, ite);
    EXPECT_EQ(expected_id_C_XOR_D-1, gateTest.unique_table[ite].high);
    EXPECT_EQ(D_ID, gateTest.unique_table[ite].low);
    EXPECT_EQ(C_ID, gateTest.unique_table[ite].top_var); 
}

// XNOR
TEST_F(GateTest, xnor_test){
    // a XNOR b
    BDD_ID ite = gateTest.xnor2(A_ID, B_ID);
    BDD_ID expected_id_A_XNOR_B = gateTest.uniqueTableSize()-1;

    EXPECT_EQ(expected_id_A_XNOR_B, ite);
    EXPECT_EQ(B_ID, gateTest.unique_table[ite].high);
    EXPECT_EQ(expected_id_A_XNOR_B-1, gateTest.unique_table[ite].low);
    EXPECT_EQ(A_ID, gateTest.unique_table[ite].top_var);

    // c XNOR d
    ite = gateTest.xnor2(C_ID, D_ID);
    BDD_ID expected_id_C_XNOR_D = gateTest.uniqueTableSize()-1;

    EXPECT_EQ(expected_id_C_XNOR_D, ite);
    EXPECT_EQ(D_ID, gateTest.unique_table[ite].high);
    EXPECT_EQ(expected_id_C_XNOR_D-1, gateTest.unique_table[ite].low);
    EXPECT_EQ(C_ID, gateTest.unique_table[ite].top_var); 
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
