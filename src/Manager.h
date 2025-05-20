// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <vector>
#include <unordered_map>
#include "Node.h"

namespace ClassProject {
    class Manager : public ManagerInterface {
        public:
            // Unique table is vector of nodes
            std::vector<Node> unique_table;
            std::unordered_map<std::string, BDD_ID> unique_table_hashmap;

            BDD_ID TRUE_NODE = 1;
            BDD_ID FALSE_NODE = 0;

            // Computed table is map with string representing fgh and BDD_ID shows respective ite node in unqiue table
            std::unordered_map<std::string, BDD_ID> computed_table;

            /**
             * Constructor of Manager class
             */

            Manager();

            /**
             * Create a new Variable with input label
             *
             * @param label String label
             * @return ID of BDD Node
             */
            BDD_ID createVar(const std::string &label) override;

            /**
             * Gets id of True node (1)
             *
             * @return ID of True Node
             */     
            const BDD_ID &True() override;

            /**
             * Gets id of False node (0)
             *
             * @return ID of False Node
             */ 
            const BDD_ID &False() override;

            /**
             * Checks if input node is constant
             *
             * @param f BDD_ID input node
             * @return true if input node is leaf node else false
             */ 
            bool isConstant(BDD_ID f) override;

            /**
             * Checks if input node is variable
             *
             * @param x BDD_ID input node
             * @return true if input node has high as 1 & low as 0 else false
             */ 
            bool isVariable(BDD_ID x) override;

            /**
             * Provides the top variable of input node
             *
             * @param f BDD_ID input node
             * @return id of top variable
             */ 
            BDD_ID topVar(BDD_ID f) override;

            /**
             * Implements the if-then-else algorithm
             *
             * @param i BDD_ID of if
             * @param t BDD_ID of then
             * @param e BDD_ID of else
             * @return id of top variable
             */ 
            BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e) override;

            /**
             * Returns the positive co-factor of the function represented by ID f w.r.t.variable x
             *
             * @param f BDD_ID of function node
             * @param x BDD_ID of variable node
             * @return id of positive cofactor node
             */ 
            BDD_ID coFactorTrue(BDD_ID f, BDD_ID x) override;

            /**
             * Returns the negative co-factor of the function represented by ID f w.r.t.variable x
             *
             * @param f BDD_ID of function node
             * @param x BDD_ID of variable node
             * @return id of negative cofactor node
             */ 
            BDD_ID coFactorFalse(BDD_ID f, BDD_ID x) override;

            /**
             * Returns the positive co-factor of the function represented by ID f
             *
             * @param f BDD_ID of function node
             * @return id of positive cofactor node
             */ 
            BDD_ID coFactorTrue(BDD_ID f) override;

            /**
             * Returns the negative co-factor of the function represented by ID f
             *
             * @param f BDD_ID of function node
             * @return id of negative cofactor node
             */ 
            BDD_ID coFactorFalse(BDD_ID f) override;

            /**
             * Returns the id of function represnting a and b
             *
             * @param a BDD_ID of the first node
             * @param b BDD_ID of the second node
             * @return id of node represnting a and b
             */
            BDD_ID and2(BDD_ID a, BDD_ID b) override;

            /**
             * Returns the id of function represnting a or b
             *
             * @param a BDD_ID of the first node
             * @param b BDD_ID of the second node
             * @return id of node represnting a or b
             */
            BDD_ID or2(BDD_ID a, BDD_ID b) override;

            /**
             * Returns the id of function represnting a xor b
             *
             * @param a BDD_ID of the first node
             * @param b BDD_ID of the second node
             * @return id of node represnting a xor b
             */
            BDD_ID xor2(BDD_ID a, BDD_ID b) override;

            /**
             * Returns the id of function represnting neg a
             *
             * @param a BDD_ID of node to negate
             * @return id of node represnting neg a
             */
            BDD_ID neg(BDD_ID a) override;

            /**
             * Returns the id of function represnting a nand b
             *
             * @param a BDD_ID of the first node
             * @param b BDD_ID of the second node
             * @return id of node represnting a nand b
             */
            BDD_ID nand2(BDD_ID a, BDD_ID b) override;

            /**
             * Returns the id of function represnting a nor b
             *
             * @param a BDD_ID of the first node
             * @param b BDD_ID of the second node
             * @return id of node represnting a nor b
             */
            BDD_ID nor2(BDD_ID a, BDD_ID b) override;

            /**
             * Returns the id of function represnting a xnor b
             *
             * @param a BDD_ID of the first node
             * @param b BDD_ID of the second node
             * @return id of node represnting a xnor b
             */
            BDD_ID xnor2(BDD_ID a, BDD_ID b) override;

            /**
             * Returns the label of top variable of root node
             *
             * @param root BDD_ID of the root node
             * @return string label of top variable of root
             */
            std::string getTopVarName(const BDD_ID &root) override;

            /**
             * This function takes a node root and an empty set nodes_of_root. 
             * It returns the set of all nodes which are reachable from root including itself.
             *
             * @param root BDD_ID of the root node
             * @param nodes_of_root Empty set of nodes
             */
            void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

            /**
             * This function takes a node root and an empty set vars_of_root. 
             * It returns the set of all variables which are reachable from root including itself if root is a variable.
             *
             * @param root BDD_ID of the root node
             * @param nodes_of_root Empty set of variable nodes
             */
            void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;

            /**
             * Gives the number of Nodes existing in unique table
             *
             * @return No. of Nodes currently existing
             */ 
            size_t uniqueTableSize() override;

            /**
             * Creates a file that contains a visual representation of the BDD represented by the root node.
             * 
             * @param filepath string filepath to save image
             * @param root BDD_IDD of the root node
             */
            void visualizeBDD(std::string filepath, BDD_ID &root) override;

    };

}

#endif
