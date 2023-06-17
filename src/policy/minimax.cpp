#include <cstdlib>
//#include<iostream>

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
  int besteval=0;
  if(state->player==1) besteval=1e9;
  auto now=State(state->board);

  for(auto it: actions){
    int run=depth;
    int nexteval=0;
    auto now=State(state->board);
    auto n=now.next_state(it);
    int teval;
    teval=n->evaluate();
    if(state->player==0){
      if(teval > besteval){
        besteval=teval;
        best=it;
      }
    }
    else if(state->player==1){
      if(teval < besteval){
        besteval=teval;
        best=it;
      }
    }
  }
  /*
  for(auto it: actions){
    int run=depth;
    int nexteval=0;
    auto now=State(state->board);
    auto n=now.next_state(it);
    int teval;

    if(depth!=0){
      now=State(state->board);
      teval=now.next_state(Minimax::get_move(n, depth-1))->evaluate();
      if(state->player==0){
        if(teval > besteval){
          besteval=teval;
          best=it;
        }
      }
      else if(state->player==1){
        if(teval < besteval){
          besteval=teval;
          best=it;
        }
      }
    }
    else{
      teval=n->evaluate();
      if(state->player==0){
        if(teval > besteval){
          besteval=teval;
          best=it;
        }
      }
      else if(state->player==1){
        if(teval < besteval){
          besteval=teval;
          best=it;
        }
      }
    }
  }
  */
    
  //return actions[(rand()+depth)%actions.size()];
  return best;
}