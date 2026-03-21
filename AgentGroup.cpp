#include "AgentGroup.h"
#include <iostream>

AgentGroup::AgentGroup(int quantity, int opinion1, int opinion2, int obstinacy)
{
  group = {quantity, opinion1, opinion2, obstinacy};
}

void AgentGroup::showGroup()
{
  std::cout << "Cantidad de personas: " << std::get<0>(group) << std::endl;
  std::cout << "Opinion 1: " << std::get<1>(group) << std::endl;
  std::cout << "Opinion 2: " << std::get<2>(group) << std::endl;
  std::cout << "Rigidez: " << std::get<3>(group) << std::endl;
}
