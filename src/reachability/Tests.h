#ifndef VDSPROJECT_REACHABILITY_TESTS_H
#define VDSPROJECT_REACHABILITY_TESTS_H

#include <gtest/gtest.h>
#include "Reachability.h"

using namespace ClassProject;

struct ReachabilityTest : testing::Test {
    
    // 2 state bits, 3 inputs
    std::unique_ptr<ClassProject::ReachabilityInterface> fsm2 = std::make_unique<ClassProject::Reachability>(2);

    std::vector<BDD_ID> stateVars2 = fsm2->getStates();
    std::vector<BDD_ID> inputVars3 = fsm2->getInputs();

    std::vector<BDD_ID> transitionFunctions;

};

// Example simple
TEST_F(ReachabilityTest, SimpleExampleTest)
{
    BDD_ID s0 = stateVars2.at(0);
    BDD_ID s1 = stateVars2.at(1);

    transitionFunctions.push_back(fsm2->neg(s0)); // s0' = not(s0)
    transitionFunctions.push_back(fsm2->neg(s1)); // s1' = not(s1)
    fsm2->setTransitionFunctions(transitionFunctions);

    fsm2->setInitState({false,false});

    EXPECT_TRUE(fsm2->isReachable({false, false}));
    EXPECT_FALSE(fsm2->isReachable({false, true}));
    EXPECT_FALSE(fsm2->isReachable({true, false}));
    EXPECT_TRUE(fsm2->isReachable({true, true}));
}

// Test constructor error handler
TEST_F(ReachabilityTest, ConstructorTest)
{
    // test label of states
    for (int i = 0; i < stateVars2.size(); i++)
    {
        EXPECT_EQ(fsm2->getTopVarName(stateVars2.at(i)), "s" + std::to_string(i));
    }

    // test label of inputs
    for (int i = 0; i < inputVars3.size(); i++)
    {
        EXPECT_EQ(fsm2->getTopVarName(inputVars3.at(i)), "i" + std::to_string(i));
    }

    // construct with stateSize = 0
    EXPECT_THROW(std::make_unique<ClassProject::Reachability>(0), std::runtime_error);
    EXPECT_THROW(std::make_unique<ClassProject::Reachability>(0, 0), std::runtime_error);
    EXPECT_THROW(std::make_unique<ClassProject::Reachability>(0, 10), std::runtime_error);
}

// Test setTransitionFunc error handler
TEST_F(ReachabilityTest, SetTransitionTestErr)
{
    BDD_ID s0 = stateVars2.at(0);
    BDD_ID s1 = stateVars2.at(1);

    // unknown ID of node in transitionFunctions
    for(int i = (stateVars2.size() + inputVars3.size() + 1); i < 50; i++)
    {
        transitionFunctions.push_back(i);
        transitionFunctions.push_back(i + 1);
        EXPECT_THROW(fsm2->setTransitionFunctions(transitionFunctions), std::runtime_error);
        transitionFunctions.pop_back();
        transitionFunctions.pop_back();
    }

    // large size of transitionFunctions
    transitionFunctions.push_back(fsm2->neg(s0));
    transitionFunctions.push_back(fsm2->neg(s1));
    transitionFunctions.push_back(fsm2->and2(fsm2->neg(s1), s0));
    EXPECT_THROW(fsm2->setTransitionFunctions(transitionFunctions), std::runtime_error);

    // empty transitionFunctions
    transitionFunctions.pop_back();
    transitionFunctions.pop_back();
    transitionFunctions.pop_back();
    EXPECT_THROW(fsm2->setTransitionFunctions(transitionFunctions), std::runtime_error);
}

// Test setInitState error handler
TEST_F(ReachabilityTest, SetInitStateTestErr)
{
    // mismatching size 
    EXPECT_THROW(fsm2->setInitState({true, true, true});, std::runtime_error);
    EXPECT_THROW(fsm2->setInitState({false});, std::runtime_error);
    EXPECT_THROW(fsm2->setInitState({});, std::runtime_error);
}

class ReachabilityExample1Test : public testing::Test {
protected:

    std::unique_ptr<ClassProject::ReachabilityInterface> fsm;
    void SetUp() override
    {
        // 1 state bit, 2 inputs
        fsm = std::make_unique<ClassProject::Reachability>(1, 2);
        
        std::vector<BDD_ID> stateBits = fsm->getStates();
        BDD_ID s0 = stateBits.at(0);

        std::vector<BDD_ID> inputBits = fsm->getInputs();
        BDD_ID i0 = inputBits.at(0);
        BDD_ID i1 = inputBits.at(1);

        std::vector<BDD_ID> transitionFunctions;

        // s0' = neg(s0)*i1 + s0*neg(i0)
        transitionFunctions.push_back(fsm->or2(fsm->and2(fsm->neg(s0), i1), fsm->and2(s0, fsm->neg(i0)))); 

        fsm->setTransitionFunctions(transitionFunctions);

        // Initial state: 0
        fsm->setInitState({false});
    }
};

// Example 1
TEST_F(ReachabilityExample1Test, IsReachableTest)
{
    EXPECT_THROW(fsm->isReachable({false, true}), std::runtime_error);

    EXPECT_TRUE(fsm->isReachable({false}));
    EXPECT_TRUE(fsm->isReachable({true}));
}

TEST_F(ReachabilityExample1Test, StateDistanceTest)
{
    EXPECT_THROW(fsm->stateDistance({true, false}), std::runtime_error);

    EXPECT_EQ(fsm->stateDistance({false}), 0);
    EXPECT_EQ(fsm->stateDistance({true}), 1);
}

class ReachabilityExample2Test : public testing::Test {
protected:

    std::unique_ptr<ClassProject::ReachabilityInterface> fsm;

    void SetUp() override
    {
        // 2 state bits, 1 inputs
        fsm = std::make_unique<ClassProject::Reachability>(2, 1);

        std::vector<BDD_ID> stateBits = fsm->getStates();
        BDD_ID s0 = stateBits.at(0);
        BDD_ID s1 = stateBits.at(1);

        std::vector<BDD_ID> inputBits = fsm->getInputs();
        BDD_ID i0 = inputBits.at(0);

        std::vector<BDD_ID> transitionFunctions;

        // s0' = neg(s1)*neg(s0) + neg(s1)*s0
        transitionFunctions.push_back(fsm->or2(fsm->and2(fsm->neg(s1), fsm->neg(s0)), fsm->and2(fsm->neg(s1), s0))); 

        // s1' = neg(s1)*s0*neg(i0)
        transitionFunctions.push_back(fsm->and2(fsm->and2(fsm->neg(s1), s0), fsm->neg(i0))); 

        fsm->setTransitionFunctions(transitionFunctions);

        // Initial state: 00   
        fsm->setInitState({false, false});
    }
};

// Example 2
TEST_F(ReachabilityExample2Test, IsReachableTest)
{
    EXPECT_THROW(fsm->isReachable({false}), std::runtime_error);

    EXPECT_TRUE(fsm->isReachable({false, false}));
    EXPECT_FALSE(fsm->isReachable({false, true}));
    EXPECT_TRUE(fsm->isReachable({true, false}));
    EXPECT_TRUE(fsm->isReachable({true, true}));
}

TEST_F(ReachabilityExample2Test, StateDistanceTest)
{
    EXPECT_THROW(fsm->stateDistance({false}), std::runtime_error);

    EXPECT_EQ(fsm->stateDistance({false, false}), 0);
    EXPECT_EQ(fsm->stateDistance({false, true}), -1);
    EXPECT_EQ(fsm->stateDistance({true, false}), 1);
    EXPECT_EQ(fsm->stateDistance({true, true}), 2);
}

class ReachabilityExample3Test : public testing::Test {
protected:
    std::unique_ptr<ClassProject::ReachabilityInterface> fsm;

    void SetUp() override
    {
        // 3 state bits, 2 inputs
        fsm = std::make_unique<ClassProject::Reachability>(3, 2);

        std::vector<BDD_ID> stateBits = fsm->getStates();
        BDD_ID s0 = stateBits.at(0);
        BDD_ID s1 = stateBits.at(1);
        BDD_ID s2 = stateBits.at(2);

        std::vector<BDD_ID> inputBits = fsm->getInputs();
        BDD_ID in0 = inputBits.at(0);
        BDD_ID in1 = inputBits.at(1);

        std::vector<BDD_ID> transitionFunctions;

        // s0' = s0 XOR in0
        transitionFunctions.push_back(fsm->xor2(s0, in0));

        // s1' = s1 OR (s0 AND in1)
        transitionFunctions.push_back(fsm->or2(s1, fsm->and2(s0, in1)));

        // s2' = (s2 AND s1)
        transitionFunctions.push_back(fsm->and2(s2, s1));

        fsm->setTransitionFunctions(transitionFunctions);

        // Initial state: 000
        fsm->setInitState({false, false, false});
    }
};

// Example 3
TEST_F(ReachabilityExample3Test, IsReachablTest)
{
    EXPECT_THROW(fsm->isReachable({false, false}), std::runtime_error);

    EXPECT_TRUE(fsm->isReachable({false, false, false}));
    EXPECT_TRUE(fsm->isReachable({true, false, false}));
    EXPECT_TRUE(fsm->isReachable({false, true, false}));
    EXPECT_TRUE(fsm->isReachable({true, true, false}));

    EXPECT_FALSE(fsm->isReachable({false, false, true}));
    EXPECT_FALSE(fsm->isReachable({true, false, true}));
    EXPECT_FALSE(fsm->isReachable({false, true, true}));
    EXPECT_FALSE(fsm->isReachable({true, true, true}));
}

TEST_F(ReachabilityExample3Test, StateDistanceTest)
{
    EXPECT_THROW(fsm->stateDistance({false, true}), std::runtime_error);

    EXPECT_EQ(fsm->stateDistance({false, false, false}), 0);
    EXPECT_EQ(fsm->stateDistance({true, false, false}), 1);
    EXPECT_EQ(fsm->stateDistance({true, true, false}), 2);
    EXPECT_EQ(fsm->stateDistance({false, true, false}), 2);

    EXPECT_EQ(fsm->stateDistance({false, false, true}), -1); 
    EXPECT_EQ(fsm->stateDistance({true, false, true}), -1);
    EXPECT_EQ(fsm->stateDistance({false, true, true}), -1);
    EXPECT_EQ(fsm->stateDistance({true, true, true}), -1);
}

class ReachabilityExample4Test : public testing::Test {
protected:
    std::unique_ptr<ClassProject::ReachabilityInterface> fsm;

    void SetUp() override
    {
        // 3 state bits, 2 inputs
        fsm = std::make_unique<ClassProject::Reachability>(3, 2);

        std::vector<BDD_ID> stateBits = fsm->getStates();
        BDD_ID s0 = stateBits.at(0);
        BDD_ID s1 = stateBits.at(1);
        BDD_ID s2 = stateBits.at(2);

        std::vector<BDD_ID> inputBits = fsm->getInputs();
        BDD_ID in0 = inputBits.at(0);
        BDD_ID in1 = inputBits.at(1);

        std::vector<BDD_ID> transitionFunctions;

        // s0' = s0 XOR in0
        transitionFunctions.push_back(fsm->xor2(s0, in0));

        // s1' = s1 OR (s0 AND in1)
        transitionFunctions.push_back(fsm->or2(s1, fsm->and2(s0, in1)));

        // s2' = s2 OR (s1 AND s0 AND in1)
        transitionFunctions.push_back(fsm->or2(
            s2,
            fsm->and2(s1, fsm->and2(s0, in1))));

        fsm->setTransitionFunctions(transitionFunctions);

        // Initial state: 000
        fsm->setInitState({false, false, false});
    }
};

// Example 4
TEST_F(ReachabilityExample4Test, IsReachableTest)
{
    EXPECT_THROW(fsm->isReachable({false, false}), std::runtime_error);

    EXPECT_TRUE(fsm->isReachable({false, false, false}));
    EXPECT_TRUE(fsm->isReachable({true, false, false}));
    EXPECT_TRUE(fsm->isReachable({false, true, false}));
    EXPECT_TRUE(fsm->isReachable({true, true, false}));
    EXPECT_TRUE(fsm->isReachable({false, true, true}));
    EXPECT_TRUE(fsm->isReachable({true, true, true}));

    EXPECT_FALSE(fsm->isReachable({false, false, true}));
    EXPECT_FALSE(fsm->isReachable({true, false, true}));
};

TEST_F(ReachabilityExample4Test, StateDistanceTest)
{
    EXPECT_THROW(fsm->stateDistance({false, true}), std::runtime_error);

    EXPECT_EQ(fsm->stateDistance({false, false, false}), 0);
    EXPECT_EQ(fsm->stateDistance({true, false, false}), 1);
    EXPECT_EQ(fsm->stateDistance({false, true, false}), 2);
    EXPECT_EQ(fsm->stateDistance({true, true, false}), 2);
    EXPECT_EQ(fsm->stateDistance({false, true, true}), 3);
    EXPECT_EQ(fsm->stateDistance({true, true, true}), 3);

    EXPECT_EQ(fsm->stateDistance({false, false, true}), -1);
    EXPECT_EQ(fsm->stateDistance({true, false, true}), -1);
};

// The failed test from supervisor
struct ReachabilityLastTest : testing::Test {

    std::unique_ptr<ClassProject::ReachabilityInterface> fsm1 = std::make_unique<ClassProject::Reachability>(1);

};

TEST_F(ReachabilityLastTest, SetInitState) { /* NOLINT */

    ASSERT_NO_THROW(fsm1->setInitState({true}));

    ASSERT_FALSE(fsm1->isReachable({false}));
    ASSERT_TRUE(fsm1->isReachable({true}));

    ASSERT_NO_THROW(fsm1->setInitState({false}));

    ASSERT_FALSE(fsm1->isReachable({true}));
    ASSERT_TRUE(fsm1->isReachable({false}));
}

#endif
