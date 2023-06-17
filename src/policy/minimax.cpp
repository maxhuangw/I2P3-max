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
  if(state->player==1) besteval=1e9;
  auto now=State(state->board, state->player);

  for(auto it: actions){
    int nexteval;
    //auto now=State(state->board);
    auto n=now.next_state(it);
    
    if(depth!=0){
      //std::cout<<it.first.first<<it.first.second<<" "<<it.second.first<<it.second.second;
      nexteval=(n->next_state(Minimax::get_move(n, depth-1)))->evaluate();
      //std::cout<<nexteval<<"\n\n";
      if((state->player)%2==0 && nexteval > besteval){
        besteval=nexteval;
        best=it;
      }
      else if((state->player)%2==1 && nexteval < besteval){
        besteval=nexteval;
        best=it;
      }
    }
    else{
      nexteval=n->evaluate();
      //std::cout<<nexteval<<" "<<it.first.first<<it.first.second<<" "<<it.second.first<<it.second.second<<" "<<state->player<<" "<<besteval<<std::endl;
      if((state->player)%2==0 && nexteval > besteval){
        besteval=nexteval;
        best=it;
      }
      else if((state->player)%2==1 && nexteval < besteval){
        besteval=nexteval;
        best=it;
      }
    }
  }

  //std::cout<<besteval<<" "<<" "<<best.first.first<<best.first.second<<" "<<best.second.first<<best.second.second<<std::endl;
  
  
  //return actions[(rand()+depth)%actions.size()];
  return best;
}