#include <cstdlib>
#include<iostream>
#include <fstream>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */


Move AlphaBeta::get_move(State *state, int depth, int alpha, int beta, int baseplayer){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  Move best;
  auto now=State(state->board, state->player);
  bool issame=(state->player==baseplayer);
   for(auto it: actions){
    int nexteval;
    auto n=now.next_state(it);
    if(depth!=0){
      if(issame) nexteval=(n->next_state(AlphaBeta::get_move(n, depth-1, alpha, beta, baseplayer)))->evaluate();
      else nexteval=(-(n->next_state(AlphaBeta::get_move(n, depth-1, alpha, beta, baseplayer)))->evaluate());
      if(issame){
        if(nexteval > alpha){
          alpha=nexteval;
          best=it;
        }
      }
      else if(nexteval < beta){
          beta=nexteval;
          best=it;
      }
    }
    else{
      nexteval=n->evaluate();
      if(issame) nexteval=(-n->evaluate());
      else nexteval=n->evaluate();
      if(issame){
        if(nexteval > alpha){
          alpha=nexteval;
          best=it;
        }
      }
      else if(nexteval < beta){
          beta=nexteval;
          best=it;
      }
    }
    if(alpha>beta) return best;
  }
  return best;
}