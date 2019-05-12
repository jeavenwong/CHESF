
#ifndef __GLOBALPLAN_AGENT_H__
#define __GLOBALPLAN_AGENT_H__
//#include "MengeCore/Agents/BaseAgent.h"
#include <vector>
#include "Menge\MengeCore\Agents\Map.h"
class  GlobalPlanAgent  {
public:
	int _id;//对应BaseAgent的id;
	//std::vector<Menge::Agents::Map *> _maps;
	//std::vector<bool> environmentFamiliaritySet;//对map是否熟悉
	int _environmentFamiliarity;//0表示低熟悉度 1表示中，2表示高
    //float _influence;//团队影响力
	//bool _needRePlan;
};

#endif