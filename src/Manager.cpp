#include "Manager.h"
#include <algorithm>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <iostream>

using namespace ClassProject;

Manager::Manager()
{
    Node false_node("FALSE",FALSE_NODE,FALSE_NODE,FALSE_NODE);
    Node true_node("TRUE",TRUE_NODE,TRUE_NODE,TRUE_NODE);
    
    unique_table.push_back(false_node);
    unique_table.push_back(true_node);
}

BDD_ID Manager::createVar(const std::string &label)
{
    BDD_ID table_size = unique_table.size();
    Node new_node(label, TRUE_NODE, FALSE_NODE, table_size);
    unique_table.push_back(new_node);

    return table_size;
}

const BDD_ID &Manager::True()
{
    return TRUE_NODE;
}

const BDD_ID &Manager::False()
{
    return FALSE_NODE;
}

bool Manager::isConstant(BDD_ID f)
{
    return (f == FALSE_NODE || f == TRUE_NODE); 
}

bool Manager::isVariable(BDD_ID x)
{
    return (unique_table[x].high == TRUE_NODE && unique_table[x].low == FALSE_NODE);
}

BDD_ID Manager::topVar(BDD_ID f)
{
    return unique_table[f].top_var;
}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e)
{
    // Terminal Cases
    if (i == TRUE_NODE)
    {
        return t;
    }

    if (i == FALSE_NODE)
    {
        return e;
    }

    if (t == TRUE_NODE && e == FALSE_NODE)
    {
        return i;
    }

    if (t == e)
    {
        return t;
    }

    // Check computed table
    std::string fgh = std::to_string(i) + "-" + std::to_string(t) + "-" + std::to_string(e);

    auto it = computed_table.find(fgh);
    if (it != computed_table.end()) {
        // Key exists, return the stored BDD_ID
        return it->second;
    }

    // Compute top-variable
    BDD_ID topVarOverall, topVarI, topVarT, topVarE;

    topVarI = topVar(i);
    topVarT = topVar(t);
    topVarE = topVar(e);

    topVarOverall = topVarI;

    // Compare with topVarT if it's not constant
    if (!isConstant(topVarT) && topVarT < topVarOverall) {
        topVarOverall = topVarT;
    }

    // Compare with topVarE if it's not constant
    if (!isConstant(topVarE) && topVarE < topVarOverall) {
        topVarOverall = topVarE;
    }

    // Find High & Low successor
    BDD_ID High_ite = ite (coFactorTrue(i, topVarOverall),
                            coFactorTrue(t, topVarOverall),
                            coFactorTrue(e, topVarOverall));

    BDD_ID Low_ite = ite (coFactorFalse(i, topVarOverall),
                            coFactorFalse(t, topVarOverall),
                            coFactorFalse(e, topVarOverall));

    // If High and Low successors are same then return High successor
    if (High_ite == Low_ite)
    {
        computed_table[fgh] = High_ite;
        return High_ite;
    }
  
    // Check if entry with same top, high, low already exists in unique table
    for (size_t i = 0; i < unique_table.size(); ++i) {
        const auto& node = unique_table[i];
        if (node.top_var == topVarOverall && node.high == High_ite && node.low == Low_ite) {
            computed_table[fgh] = i;
            return i;
        }
    }

    std::string unique_table_label = std::to_string(topVarOverall) + "-" + std::to_string(High_ite) + "-" + std::to_string(Low_ite);

    BDD_ID table_size = unique_table.size();
    Node new_node(unique_table_label, High_ite, Low_ite, topVarOverall);
    unique_table.push_back(new_node);

    computed_table[fgh] = table_size;
    return table_size;
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x)
{
    BDD_ID top_variable = topVar(f);

    if (isConstant(f) || isConstant(x) || top_variable > x)
    {
        return f;
    }
    if (top_variable == x)
    {
        return coFactorTrue(f);
    }

    BDD_ID True_CoFactor = coFactorTrue (coFactorTrue(f),x);
    BDD_ID False_CoFactor = coFactorTrue (coFactorFalse(f),x);   
    return ite(top_variable, True_CoFactor, False_CoFactor);
}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x)
{
    BDD_ID top_variable = topVar(f);

    if (isConstant(f) || isConstant(x) || top_variable > x)
    {
        return f;
    }
    if (top_variable == x)
    {
        return coFactorFalse(f);
    }

    BDD_ID True_CoFactor = coFactorFalse (coFactorTrue(f),x);
    BDD_ID False_CoFactor = coFactorFalse (coFactorFalse(f),x);   
    
    return ite(top_variable, True_CoFactor, False_CoFactor);
}

BDD_ID Manager::coFactorTrue(BDD_ID f)
{
    return unique_table[f].high;
}

BDD_ID Manager::coFactorFalse(BDD_ID f)
{
    return unique_table[f].low;
}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b)
{
    return ite (a, b, FALSE_NODE);
}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b)
{
    return ite (a, TRUE_NODE, b);
}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b)
{
    return ite (a, neg(b), b);
}

BDD_ID Manager::neg(BDD_ID a)
{
    return ite (a, FALSE_NODE, TRUE_NODE);
}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b)
{
    return ite (a, neg(b), TRUE_NODE);
}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b)
{
    return ite (a, FALSE_NODE, neg(b));
}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b)
{
    return ite (a, b, neg(b));
}

std::string Manager::getTopVarName(const BDD_ID &root)
{
    BDD_ID top_var = unique_table[root].top_var;
    return unique_table[top_var].label;
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root)
{
    if (nodes_of_root.find(root) == nodes_of_root.end()) {
        nodes_of_root.insert(root);
    }
    
    if (!isConstant(root))
    {
        findNodes(unique_table[root].high, nodes_of_root);
        findNodes(unique_table[root].low, nodes_of_root);
        return;        
    }
}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root)
{
    BDD_ID top_var = topVar(root);
    if (!isConstant(root) && (vars_of_root.find(top_var) == vars_of_root.end())) {
        vars_of_root.insert(top_var);
    }
    if (!isConstant(root))
    {
        findVars(unique_table[root].high, vars_of_root);
        findVars(unique_table[root].low, vars_of_root);
        return;
    }
}

size_t Manager::uniqueTableSize()
{
    size_t no_nodes;
    no_nodes = unique_table.size();
    return no_nodes;
}

void Manager::visualizeBDD(std::string filepath, BDD_ID &root) {
    std::ofstream dot_file(filepath);
    if (!dot_file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return;
    }

    dot_file << "digraph BDD {\n";
    dot_file << "  rankdir=TB;\n";
    dot_file << "  size=\"8,10\";\n";
    dot_file << "  node [shape = circle];\n";

    std::set<BDD_ID> visited;
    std::vector<BDD_ID> stack;
    stack.push_back(root);

    while (!stack.empty()) {
        BDD_ID current = stack.back();
        stack.pop_back();

        if (visited.find(current) != visited.end()) continue;
        visited.insert(current);

        const Node &node = unique_table[current];

        // Terminal nodes representation
        if (node.top_var == 0 || node.top_var == 1) {
            dot_file << "  " << current << " [shape=box, label=\"" << std::to_string(node.top_var) << "\"];\n";
        } else {
            dot_file << "  " << current << " [label=\"" << std::to_string(node.top_var) << "\"];\n";
        }

        // Connect to low and high
        if (node.low != current) {  // Avoid self-loop
            dot_file << "  " << current << " -> " << node.low << " [style=dotted label=\"0\"];\n";
            stack.push_back(node.low);
        }
        if (node.high != current) {  // Avoid self-loop
            dot_file << "  " << current << " -> " << node.high << " [label=\"1\"];\n";
            stack.push_back(node.high);
        }
    }

    dot_file << "}\n";
    dot_file.close();
}
