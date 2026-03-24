#include "AgentGroup.h"
#include <iostream>
#include <cmath>

using namespace std;

AgentGroup::AgentGroup(int quantity, int opinion1, int opinion2, double obstinacy, int index)
{
  group = {quantity, opinion1, opinion2, obstinacy, index};
}

void AgentGroup::showGroup()
{
  cout << "Cantidad de personas: " << get<0>(group) << endl;
  cout << "Opinion 1: " << get<1>(group) << endl;
  cout << "Opinion 2: " << get<2>(group) << endl;
  cout << "Rigidez: " << get<3>(group) << endl;
  cout << "Conflicto: " << get<3>(group) << endl;
  cout << "Esfuerzo para el grupo entero: " << getEffort(get<0>(group)) << endl;
}

int AgentGroup::getConflict(int n) const
{
  return n * pow((get<1>(group) - get<2>(group)), 2);
}

int AgentGroup::getEffort (int n) const
{
  return abs(get<1>(group) - get<2>(group)) * get<3>(group) * n;
}

int AgentGroup::getQuantity() const
{
  return get<0>(group);
}

double AgentGroup::getObstinacy() const
{
  return get<3>(group);
}

int AgentGroup::getIndex() const
{
  return get<4>(group);
}