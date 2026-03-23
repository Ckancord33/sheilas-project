#include "AgentGroup.h"

int main(){
  AgentGroup* agentGroup = new AgentGroup(10, -100, 100, 1);
  agentGroup->showGroup();
  return 0;
}