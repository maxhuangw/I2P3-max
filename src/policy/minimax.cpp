#include <cstdlib>
#include<iostream>
#include <fstream>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  
  if(!state->legal_actions.size())
    state->get_legal_actions();

  auto actions = state->legal_actions;
  Move best;
  int besteval=-1e9;
  if(depth==0) besteval=1e9;
  auto now=State(state->board, state->player);
  
   for(auto it: actions){
    int nexteval;
    auto n=now.next_state(it);
    
    if(depth!=0){
      nexteval=(n->next_state(Minimax::get_move(n, depth-1)))->evaluate();
      if(nexteval > besteval){
        besteval=nexteval;
        best=it;
      }
    }
    else{
      nexteval=n->evaluate();
      if( nexteval < besteval){
        besteval=nexteval;
        best=it;
      }
    }
  }
  return best;
}