
#ifndef __GLOBALPLAN_AGENT_H__
#define __GLOBALPLAN_AGENT_H__
//#include "MengeCore/Agents/BaseAgent.h"
#include <vector>
#include "Menge\MengeCore\Agents\Map.h"
class  GlobalPlanAgent  {
public:
	int _id;//��ӦBaseAgent��id;
	//std::vector<Menge::Agents::Map *> _maps;
	//std::vector<bool> environmentFamiliaritySet;//��map�Ƿ���Ϥ
	int _environmentFamiliarity;//0��ʾ����Ϥ�� 1��ʾ�У�2��ʾ��
    //float _influence;//�Ŷ�Ӱ����
	//bool _needRePlan;
};

#endif