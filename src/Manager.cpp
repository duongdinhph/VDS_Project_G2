#include "Manager.h"

using namespace ClassProject;

Manager::Manager()
{
    std::string false_str = "FALSE";
    std::string true_str  = "TRUE";

    Node false_node(0,false_str,0,0,0);
    Node true_node(1,true_str,1,1,1);
    
    unique_table.push_back(false_node);
    unique_table.push_back(true_node);
}


BDD_ID Manager::createVar(const std::string &label)
{
    BDD_ID table_size = unique_table.size();
    Node new_node(table_size, label, 1, 0, table_size);
    unique_table.push_back(new_node);

    return table_size;
}

const BDD_ID &Manager::True()
{
    return unique_table[1].id;
}

const BDD_ID &Manager::False()
{
    return unique_table[0].id;
}

bool Manager::isConstant(BDD_ID f){}

bool Manager::isVariable(BDD_ID x){}

BDD_ID Manager::topVar(BDD_ID f){}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){}

BDD_ID Manager::coFactorTrue(BDD_ID f){}

BDD_ID Manager::coFactorFalse(BDD_ID f){}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b){}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b){}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){}

BDD_ID Manager::neg(BDD_ID a){}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){}

std::string Manager::getTopVarName(const BDD_ID &root){}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){}

size_t Manager::uniqueTableSize()
{
    size_t no_nodes;
    no_nodes = unique_table.size();
    return no_nodes;
}

void Manager::visualizeBDD(std::string filepath, BDD_ID &root){}
