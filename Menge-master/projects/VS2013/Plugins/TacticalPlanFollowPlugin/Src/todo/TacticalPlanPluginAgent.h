#pragma once
#ifndef __FOLLOW_AGENT_H__
#define __FOLLOW_AGENT_H__
//#include "MengeCore/Agents/BaseAgent.h"
#include <vector>
#include "Menge\MengeCore\Agents\Map.h"
class  FollowAgent {
public:
	int _id;//对应BaseAgent的id;

	float _influence;//团队影响力
	size_t _leaderID;//-1表示附近没有邻居，-2表示自己是leader
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