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
Move Minimax::get_move(State *state, int depth, int baseplayer){
  
  if(!state->legal_actions.size())
    state->get_legal_actions();

  auto actions = state->legal_actions;
  Move best;
  int besteval;
  auto now=State(state->board, state->player);
  bool issame=(state->player==baseplayer);
  if(issame)besteval=-1e9;
  else besteval=1e9;
  
   for(auto it: actions){
    int nexteval;
    auto n=now.next_state(it);
    
    if(depth!=0){
      if(issame) nexteval=(n->next_state(Minimax::get_move(n, depth-1, baseplayer))->evaluate());
      else nexteval=(-(n->next_state(Minimax::get_move(n, depth-1, baseplayer)))->evaluate());
      if(issame){
        if(nexteval > besteval){
          besteval=nexteval;
          best=it;
        }
      }
      else if(nexteval<besteval){
          besteval=nexteval;
          best=it;
      }
    }
    else{
      if(issame) nexteval=(-n->evaluate());
      else nexteval=n->evaluate();
      if(issame){
        if(nexteval > besteval){
          besteval=nexteval;
          best=it;
        }
      }
      else if(nexteval<besteval){
          besteval=nexteval;
          best=it;
      }
    }
  }
  return best;
}