#pragma once
#ifndef __FOLLOW_AGENT_H__
#define __FOLLOW_AGENT_H__
//#include "MengeCore/Agents/BaseAgent.h"
#include <vector>
#include "Menge\MengeCore\Agents\Map.h"
class  FollowAgent {
public:
	int _id;//��ӦBaseAgent��id;

	float _influence;//�Ŷ�Ӱ����
	size_t _leaderID;//-1��ʾ����û���ھӣ�-2��ʾ�Լ���leader
	bool _isFollowing = false;
	bool _missFollowing = false;
	Menge::Math::Vector2 _leaderPrefSpeed;
	Menge::Math::Vector2 _leaderPos;
	std::vector<Menge::Math::Vector2> _leaderPath;
	bool _nextGoalIsTemp;
	int _nextMapIndex;
	int _currentMapIndex;
	bool _catchNextMap;
};

#endif