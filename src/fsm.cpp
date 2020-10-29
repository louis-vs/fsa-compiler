#include <vector>
#include <string>
#include <iostream>

// class for a state of an FSM
// very simple - has a label and a boolean to determine if accepting (i.e. final state) or not
class State {
  public:
  std::string name;
  bool accepting;
  State(std::string name, bool accepting) : name(name), accepting(accepting) {};
};

// class for a symbol within the alphabet of an FSM
// currently very barebones
class Symbol {
  public:
  std::string name;
  Symbol(std::string name) : name(name) {};

  // bool operator==(Symbol other) { return name == other.name; }
};

// effectively an entry in a transition table. maps start state->next state based on input.
// optionally includes translated symbol for finite-state transducers
class Transition {
  public:
  State *start;
  State *end;
  Symbol *symbol;
  Symbol *translation;

  Transition(State *start, State *end, Symbol *s, Symbol *translation) : 
    start(start), end(end), symbol(s), translation(translation) {}

  Transition(State *start, State *end, Symbol *s) : 
    start(start), end(end), symbol(s), translation(nullptr) {}
};

// basic FSM
class FiniteStateMachine {
  public:
  // constructor
  FiniteStateMachine(std::vector<Transition *> transitionTable, State *initialState) 
    : transitions(transitionTable), currentState(initialState), accepting(false) { }

  // advance FSM based on input
  FiniteStateMachine *next(Symbol *input) {
    for(Transition *t : transitions) {
      if(t->start == currentState && t->symbol == input) {
        currentState = t->end;
        accepting = currentState->accepting;
      }
    }
    // to allow pretty chaining
    return this;
  }

  // getters
  bool isAccepting() { return accepting; }
  const State *getState() { return currentState; };
  const std::vector<Symbol *>& getOutput() { return output; }

  private:
  std::vector<Transition *> transitions;
  State *currentState;
  bool accepting;
  std::vector<Symbol *> output;

};

int main() {
  // test code
  std::vector<State *> states;
  std::vector<Symbol *> symbols;
  std::vector<Transition *> transitions;

  states.push_back(new State("0", false));
  states.push_back(new State("1", false));
  states.push_back(new State("2", true));
  symbols.push_back(new Symbol("a"));
  symbols.push_back(new Symbol("b"));
  transitions.push_back(new Transition(states[0], states[1], symbols[1], nullptr));
  transitions.push_back(new Transition(states[0], states[0], symbols[0], nullptr));
  transitions.push_back(new Transition(states[1], states[2], symbols[0], nullptr));

  FiniteStateMachine *fsm = new FiniteStateMachine(transitions, states[0]);
  
  std::cout << fsm->isAccepting() << ":" << fsm->getState()->name << std::endl;
  fsm->next(symbols[0]);
  std::cout << fsm->isAccepting() << ":" << fsm->getState()->name << std::endl;
  fsm->next(symbols[0]);
  std::cout << fsm->isAccepting() << ":" << fsm->getState()->name << std::endl;
  fsm->next(symbols[1]);
  std::cout << fsm->isAccepting() << ":" << fsm->getState()->name << std::endl;
  fsm->next(symbols[0]);
  std::cout << fsm->isAccepting() << ":" << fsm->getState()->name << std::endl;

  return 0;
}
