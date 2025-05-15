#include "Manager.h"

using namespace ClassProject;

Manager::Manager()
{
    Node false_node(FALSE_NODE,"FALSE",FALSE_NODE,FALSE_NODE,FALSE_NODE);
    Node true_node(TRUE_NODE,"TRUE",TRUE_NODE,TRUE_NODE,TRUE_NODE);
    
    unique_table.push_back(false_node);
    unique_table.push_back(true_node);
}

BDD_ID Manager::createVar(const std::string &label)
{
    BDD_ID table_size = unique_table.size();
    Node new_node(table_size, label, TRUE_NODE, FALSE_NODE, table_size);
    unique_table.push_back(new_node);

    return table_size;
}

const BDD_ID &Manager::True()
{
    return unique_table[TRUE_NODE].id;
}

const BDD_ID &Manager::False()
{
    return unique_table[FALSE_NODE].id;
}

bool Manager::isConstant(BDD_ID f)
{
    if (unique_table[f].id == FALSE_NODE || unique_table[f].id == TRUE_NODE)
    {
        return true;
    }
    else
    {
        return false;
    } 
}

bool Manager::isVariable(BDD_ID x)
{
    if (unique_table[x].high == TRUE_NODE && unique_table[x].low == FALSE_NODE)
    {
        return true;
    }
    else
    {
        return false;
    } 
}

BDD_ID Manager::topVar(BDD_ID f)
{
    return unique_table[f].top_var;
}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e)
{
    
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){}

BDD_ID Manager::coFactorTrue(BDD_ID f){}

BDD_ID Manager::coFactorFalse(BDD_ID f){}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b){}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b){}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){}

BDD_ID Manager::neg(BDD_ID a)
{

}

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
