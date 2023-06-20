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
  int besteval=alpha;
  if(depth==0) besteval=beta;
  auto now=State(state->board, state->player);
  bool issame=(state->player==baseplayer);
  
    
   for(auto it: actions){
    int nexteval;
    //auto now=State(state->board);
    auto n=now.next_state(it);
    
    if(depth!=0){
      //std::cout<<it.first.first<<it.first.second<<" "<<it.second.first<<it.second.second;
      if(issame) nexteval=(n->next_state(AlphaBeta::get_move(n, depth-1, alpha, beta, baseplayer)))->evaluate();
      else nexteval=(-(n->next_state(AlphaBeta::get_move(n, depth-1, alpha, beta, baseplayer)))->evaluate());
      //std::cout<<nexteval<<"\n\n";
      if(issame){
        if(nexteval > alpha){
          alpha=nexteval;
          best=it;
        }
      }
      else if(nexteval<beta){
          beta=nexteval;
          best=it;
      }
    }
    else{
      nexteval=n->evaluate();
      if(issame) nexteval=(-n->evaluate());
      else nexteval=n->evaluate();
      //std::cout<<nexteval<<" "<<it.first.first<<it.first.second<<" "<<it.second.first<<it.second.second<<" "<<state->player<<" "<<besteval<<std::endl;
      if(issame){
        if(nexteval > alpha){
          alpha=nexteval;
          best=it;
        }
      }
      else if(nexteval<beta){
          beta=nexteval;
          best=it;
      }
    }
    if(alpha>beta) return best;
  }
  
  if(depth!=0)besteval=alpha;
  else besteval=-beta;
  std::cout<<besteval<<" "<<" "<<best.first.first<<best.first.second<<" "<<best.second.first<<best.second.second<<std::endl;
  
  
  //return actions[(rand()+depth)%actions.size()];
  return best;
}