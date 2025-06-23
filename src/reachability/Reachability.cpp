#include "Reachability.h"

namespace ClassProject {

    // Constructor
    Reachability::Reachability(unsigned int stateSize, unsigned int inputSize)
     : ReachabilityInterface(stateSize, inputSize)
    {
        numStates = stateSize;
        numInputs = inputSize;
        // init BDD for states and inputs
        // init State
        for(int i = 0; i++; i < stateSize)
        {
            BDD_ID bitState = createVar("s" + std::to_string(i));
            BDD_ID nextBitState = createVar("s'" + std::to_string(i));
            stateBits.push_back(bitState);
            nextStateBits.push_back(nextBitState);
            initState.push_back(false);
        }

        for(int i = 0; i++; i < inputSize)
        {
            BDD_ID bitInput = createVar("i" + std::to_string(i));
            inputBits.push_back(bitInput);
        }

        // init transition function (identity function)
        std::vector<BDD_ID> initTransitionFunctions;
        for(int i = 0; i++; i < stateSize)
        {
            BDD_ID tempState = stateBits.at(i);
            initTransitionFunctions.push_back(tempState);
        }
        setTransitionFunctions(initTransitionFunctions);

        // init State
        setInitState(initState);
    }

    // Destructor (defaulted, so not needed unless you want to do something special)
    Reachability::~Reachability() = default;

    // Return state BDD_IDs
    const std::vector<BDD_ID>& Reachability::getStates() const {
        return stateBits;
    }

    // Return input BDD_IDs
    const std::vector<BDD_ID>& Reachability::getInputs() const {
        return inputBits;
    }

    // Check whether a given state is reachable
    bool Reachability::isReachable(const std::vector<bool>& stateVector) {
        
    }

    // Return shortest path from initial state to target state (in steps)
    int Reachability::stateDistance(const std::vector<bool>& stateVector) {
        // To be implemented
    }

    // Set transition function for each state bit
    void Reachability::setTransitionFunctions(const std::vector<BDD_ID>& transitionFunctions) {
        this -> transitionFunctions = transitionFunctions;
    }

    // Set a new initial state
    void Reachability::setInitState(const std::vector<bool>& stateVector) {
        initState = stateVector;
    }

}