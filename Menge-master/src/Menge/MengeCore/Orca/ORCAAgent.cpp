/*

License

Menge
Copyright ?and trademark ?2012-14 University of North Carolina at Chapel Hill.
All rights reserved.

Permission to use, copy, modify, and distribute this software and its documentation
for educational, research, and non-profit purposes, without fee, and without a
written agreement is hereby granted, provided that the above copyright notice,
this paragraph, and the following four paragraphs appear in all copies.

This software program and documentation are copyrighted by the University of North
Carolina at Chapel Hill. The software program and documentation are supplied "as is,"
without any accompanying services from the University of North Carolina at Chapel
Hill or the authors. The University of North Carolina at Chapel Hill and the
authors do not warrant that the operation of the program will be uninterrupted
or error-free. The end-user understands that the program was developed for research
purposes and is advised not to rely exclusively on the program for any reason.

IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE AUTHORS
BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS
DOCUMENTATION, EVEN IF THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE
AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS SPECIFICALLY
DISCLAIM ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND ANY STATUTORY WARRANTY
OF NON-INFRINGEMENT. THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND
THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS HAVE NO OBLIGATIONS
TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

Any questions or comments should be sent to the authors {menge,geom}@cs.unc.edu

*/


#include "MengeCore/Orca/ORCAAgent.h"

#include "MengeCore/Math/consts.h"
#include "MengeCore/Orca/ORCASimulator.h"
#include "MengeCore/Core.h"
#include <algorithm>
#include <cassert>
#include <limits>

namespace ORCA {

	using Menge::Math::Vector2;
	using Menge::Math::sqr;

	/////////////////////////////////////////////////////////////////////////////
	//                     Implementation of ORCA::Agent
	/////////////////////////////////////////////////////////////////////////////

	// AGENT DEFAULT PARAMETERS
	///< The default value for tau (the time horizon w.r.t. other agents).
	const float Agent::TAU = 2.5f;
	///< The default value for tau obstacles (the time horizon w.r.t. obstacles).
	const float Agent::TAU_OBST = 0.15f;
	const std::string Agent::NAME = "orca";

	/////////////////////////////////////////////////////////////////////////////

	Agent::Agent() : Menge::Agents::BaseAgent() {
		_timeHorizon = TAU;
		_timeHorizonObst = TAU_OBST;
	}

	/////////////////////////////////////////////////////////////////////////////

	Agent::~Agent() {
	}

	/////////////////////////////////////////////////////////////////////////////
	float Agent::computeDistanceSq_PosToGoal() {

		float disSq = 0;
		float chaX = _pos._x - _nextGoal._x;
		float chaY = _pos._y - _nextGoal._y;
		disSq = pow(chaX, 2) + pow(chaY, 2);
		return disSq;
	}

	/////////////////////////////////////////////////////////////////////////////

	void Agent::obstacleLine(size_t obstNbrID, const float invTau, bool flip) {
		const Menge::Agents::Obstacle* obst = _nearObstacles[obstNbrID].obstacle;
		const float LENGTH = obst->length();
		const Vector2 P0 = flip ? obst->getP1() : obst->getP0();
		const Vector2 P1 = flip ? obst->getP0() : obst->getP1();
		const Vector2 obstDir = flip ? -obst->_unitDir : obst->_unitDir;
		const bool p0Convex = flip ? obst->p1Convex(true) : obst->p0Convex(true);
		const bool p1Convex = flip ? obst->p0Convex(true) : obst->p1Convex(true);
		const Menge::Agents::Obstacle* const leftNeighbor =
			flip ? obst->_nextObstacle : obst->_prevObstacle;
		const Menge::Agents::Obstacle* const rightNeighbor =
			flip ? obst->_prevObstacle : obst->_nextObstacle;

		const Vector2 relativePosition1 = P0 - _pos;
		const Vector2 relativePosition2 = P1 - _pos;

		/*
		* Check if velocity obstacle of obstacle is already taken care of by
		* previously constructed obstacle ORCA lines.
		*/
		bool alreadyCovered = false;

		for (size_t j = 0; j < _orcaLines.size(); ++j) {
			if (det(invTau * relativePosition1 - _orcaLines[j]._point,
				_orcaLines[j]._direction) - invTau * _radius >=
				-Menge::EPS && det(invTau * relativePosition2 - _orcaLines[j]._point,
					_orcaLines[j]._direction) - invTau * _radius >= -Menge::EPS) {
				alreadyCovered = true;
				break;
			}
		}

		if (alreadyCovered) {
			return;
		}

		/* Not yet covered. Check for collisions. */

		const float distSq1 = absSq(relativePosition1);
		const float distSq2 = absSq(relativePosition2);

		const float radiusSq = sqr(_radius);

		const float s = -(relativePosition1 * obstDir);
		const float distSqLine = absSq(relativePosition1 + s * obstDir);

		Menge::Math::Line line;

		if (s < 0 && distSq1 <= radiusSq) {
			/* Collision with left vertex. Ignore if non-convex. */
			if (p0Convex) {
				line._point = Vector2(0.f, 0.f);
				line._direction = norm(Vector2(-relativePosition1.y(), relativePosition1.x()));
				_orcaLines.push_back(line);
			}
			return;
		}
		else if (s > LENGTH && distSq2 <= radiusSq) {
			/* Collision with right vertex. Ignore if non-convex
			* or if it will be taken care of by neighoring obstace */
			if ((obst->_nextObstacle == 0x0) || (p1Convex && det(relativePosition2,
				obst->_nextObstacle->_unitDir) >= 0)) {
				line._point = Vector2(0.f, 0.f);
				line._direction = norm(Vector2(-relativePosition2.y(), relativePosition2.x()));
				_orcaLines.push_back(line);
			}
			return;
		}
		else if (s >= 0 && s < LENGTH && distSqLine <= radiusSq) {
			/* Collision with obstacle segment. */
			line._point = Vector2(0.f, 0.f);
			line._direction = -obstDir;
			_orcaLines.push_back(line);
			return;
		}

		/*
		* No collision.
		* Compute legs. When obliquely viewed, both legs can come from a single
		* vertex. Legs extend cut-off line when nonconvex vertex.
		*/

		Vector2 leftLegDirection, rightLegDirection;

		/*!
		 *	These booleans short-cut the later code in which we make sure a leg direction does not
		 *	cut into a "neighboring" obstacle.
		 *
		 *	In the case where the agent is "obliquely viewing" the obstacle near the left or right
		 *	edge, we end up testing one of the legs against obstacle 1 itself.  However, by
		 *	definition, we know that both legs lie outside of the obstacle.
		 */
		bool prevIsCurrent = false;
		bool nextIsCurrent = false;
		if (s < 0 && distSqLine <= radiusSq) {
			/*
			 * Obstacle viewed obliquely so that left vertex defines velocity obstacle.
			 */
			if (!p0Convex) {
				/* Ignore obstacle. */
				return;
			}

			nextIsCurrent = true;

			const float leg1 = std::sqrt(distSq1 - radiusSq);
			leftLegDirection = Vector2(relativePosition1.x() * leg1 -
				relativePosition1.y() * _radius,
				relativePosition1.x() * _radius +
				relativePosition1.y() * leg1) / distSq1;
			rightLegDirection = Vector2(relativePosition1.x() * leg1 +
				relativePosition1.y() * _radius,
				-relativePosition1.x() * _radius +
				relativePosition1.y() * leg1) / distSq1;
		}
		else if (s > LENGTH && distSqLine <= radiusSq) {
			/*
			* Obstacle viewed obliquely so that right vertex defines velocity obstacle.
			*/
			if (!p1Convex) {
				/* Ignore obstacle. */
				return;
			}

			prevIsCurrent = true;

			const float leg2 = std::sqrt(distSq2 - radiusSq);
			leftLegDirection = Vector2(relativePosition2.x() * leg2 -
				relativePosition2.y() * _radius,
				relativePosition2.x() * _radius +
				relativePosition2.y() * leg2) / distSq2;
			rightLegDirection = Vector2(relativePosition2.x() * leg2 +
				relativePosition2.y() * _radius,
				-relativePosition2.x() * _radius +
				relativePosition2.y() * leg2) / distSq2;
		}
		else {
			/* Usual situation. */
			if (p0Convex) {
				const float leg1 = std::sqrt(distSq1 - radiusSq);
				leftLegDirection = Vector2(relativePosition1.x() * leg1 -
					relativePosition1.y() * _radius,
					relativePosition1.x() * _radius +
					relativePosition1.y() * leg1) / distSq1;
			}
			else {
				/* Left vertex non-convex; left leg extends cut-off line. */
				leftLegDirection = -obstDir;
			}

			if (p1Convex) {
				const float leg2 = std::sqrt(distSq2 - radiusSq);
				rightLegDirection = Vector2(relativePosition2.x() * leg2 +
					relativePosition2.y() * _radius,
					-relativePosition2.x() * _radius +
					relativePosition2.y() * leg2) / distSq2;
			}
			else {
				/* Right vertex non-convex; right leg extends cut-off line. */
				rightLegDirection = obstDir;
			}
		}

		/*
		* Legs can never point into neighboring edge when convex vertex,
		* take cutoff-line of neighboring edge instead. If velocity projected on
		* "foreign" leg, no constraint is added.
		*/
		bool isLeftLegForeign = false;
		bool isRightLegForeign = false;

		if (!prevIsCurrent) {
			if (leftNeighbor != 0x0) {
				if (p0Convex && det(leftLegDirection, -leftNeighbor->_unitDir) >= 0.0f) {
					/* Left leg points into obstacle. */
					leftLegDirection = -leftNeighbor->_unitDir;
					isLeftLegForeign = true;
				}
			}
		}

		if (!nextIsCurrent) {
			if (rightNeighbor != 0x0) {
				if (p1Convex && det(rightLegDirection, rightNeighbor->_unitDir) <= 0.0f) {
					/* Right leg points into obstacle. */
					rightLegDirection = rightNeighbor->_unitDir;
					isRightLegForeign = true;
				}
			}
		}

		/* Compute cut-off centers. */
		const Vector2 leftCutoff = invTau *
			(prevIsCurrent ? relativePosition2 : relativePosition1);
		const Vector2 rightCutoff = nextIsCurrent ? leftCutoff : (invTau * relativePosition2);
		const Vector2 cutoffVec = rightCutoff - leftCutoff;
		const bool obstaclesSame = nextIsCurrent || prevIsCurrent;


		/* Project current velocity on velocity obstacle. */
		/* Check if current velocity is projected on cutoff circles. */
		const float t = obstaclesSame ?
			0.5f : ((_vel - leftCutoff) * (cutoffVec / absSq(cutoffVec)));
		const float tLeft = ((_vel - leftCutoff) * leftLegDirection);
		const float tRight = ((_vel - rightCutoff) * rightLegDirection);

		if ((t < 0.0f && tLeft < 0.0f) || (obstaclesSame && tLeft < 0.0f && tRight < 0.0f)) {
			/* Project on left cut-off circle. */
			const Vector2 unitW = norm(_vel - leftCutoff);
			line._direction = Vector2(unitW.y(), -unitW.x());
			line._point = leftCutoff + _radius * invTau * unitW;
			_orcaLines.push_back(line);
			return;
		}
		else if (t > 1.0f && tRight < 0.0f) {
			/* Project on right cut-off circle. */
			const Vector2 unitW = norm(_vel - rightCutoff);
			line._direction = Vector2(unitW.y(), -unitW.x());
			line._point = rightCutoff + _radius * invTau * unitW;
			_orcaLines.push_back(line);
			return;
		}

		/*
		* Project on left leg, right leg, or cut-off line, whichever is closest
		* to velocity.
		*/
		const float distSqCutoff = ((t < 0.0f || t > 1.0f || obstaclesSame) ?
			std::numeric_limits<float>::infinity() :
			absSq(_vel - (leftCutoff + t * cutoffVec)));
		const float distSqLeft = ((tLeft < 0.0f) ?
			std::numeric_limits<float>::infinity() :
			absSq(_vel - (leftCutoff + tLeft * leftLegDirection)));
		const float distSqRight = ((tRight < 0.0f) ?
			std::numeric_limits<float>::infinity() :
			absSq(_vel - (rightCutoff + tRight * rightLegDirection)));

		if (distSqCutoff <= distSqLeft && distSqCutoff <= distSqRight) {
			/* Project on cut-off line. */
			line._direction = -obstDir;
			line._point = leftCutoff + _radius * invTau * Vector2(-line._direction.y(),
				line._direction.x());
			_orcaLines.push_back(line);
		}
		else if (distSqLeft <= distSqRight) {
			/* Project on left leg. */
			if (!isLeftLegForeign) {
				line._direction = leftLegDirection;
				line._point = leftCutoff + _radius * invTau * Vector2(-line._direction.y(),
					line._direction.x());
				_orcaLines.push_back(line);
			}
		}
		else {
			/* Project on right leg. */
			if (!isRightLegForeign) {
				line._direction = -rightLegDirection;
				line._point = rightCutoff + _radius * invTau * Vector2(-line._direction.y(),
					line._direction.x());
				_orcaLines.push_back(line);
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////

	size_t Agent::computeORCALines() {
		_orcaLines.clear();

		const float invTimeHorizonObst = 1.0f / _timeHorizonObst;

		/* Create obstacle ORCA lines. */
		for (size_t i = 0; i < _nearObstacles.size(); ++i) {

			const Menge::Agents::Obstacle* obst = _nearObstacles[i].obstacle;
			const Vector2 P0 = obst->getP0();
			const Vector2 P1 = obst->getP1();
			const bool agtOnRight = leftOf(P0, P1, _pos) < 0.f;
			obstacleLine(i, invTimeHorizonObst, !agtOnRight && obst->_doubleSided);
		}

		const size_t numObstLines = _orcaLines.size();

		const float invTimeHorizon = 1.0f / _timeHorizon;

		/* Create agent ORCA lines. */
		for (size_t i = 0; i < _nearAgents.size(); ++i) {
			const Agent* const other = static_cast<const Agent *>(_nearAgents[i].agent);

			const Vector2 relativePosition = other->_pos - _pos;
			const Vector2 relativeVelocity = _vel - other->_vel;

			const float distSq = absSq(relativePosition);
			const float combinedRadius = _radius + other->_radius;
			const float combinedRadiusSq = sqr(combinedRadius);

			Menge::Math::Line line;
			Vector2 u;

			if (distSq > combinedRadiusSq) {
				/* No collision. */
				const Vector2 w = relativeVelocity - invTimeHorizon * relativePosition;
				/* Vector from cutoff center to relative velocity. */
				const float wLengthSq = absSq(w);

				const float dotProduct1 = w * relativePosition;

				if (dotProduct1 < 0.0f && sqr(dotProduct1) > combinedRadiusSq * wLengthSq) {
					/* Project on cut-off circle. */
					const float wLength = std::sqrt(wLengthSq);
					const Vector2 unitW = w / wLength;

					line._direction = Vector2(unitW.y(), -unitW.x());
					u = (combinedRadius * invTimeHorizon - wLength) * unitW;
				}
				else {
					/* Project on legs. */
					const float leg = std::sqrt(distSq - combinedRadiusSq);

					if (det(relativePosition, w) > 0.0f) {
						/* Project on left leg. */
						line._direction = Vector2(relativePosition.x() * leg -
							relativePosition.y() * combinedRadius,
							relativePosition.x() * combinedRadius +
							relativePosition.y() * leg) / distSq;
					}
					else {
						/* Project on right leg. */
						line._direction = -Vector2(relativePosition.x() * leg +
							relativePosition.y() * combinedRadius,
							-relativePosition.x() * combinedRadius +
							relativePosition.y() * leg) / distSq;
					}

					const float dotProduct2 = relativeVelocity * line._direction;

					u = dotProduct2 * line._direction - relativeVelocity;
				}

				line._point = _vel + 0.5f * u;
			}
			else {
				/* Collision. Project on cut-off circle of time timeStep. */
				const float invTimeStep = 1.0f / Simulator::TIME_STEP;

				/* Vector from cutoff center to relative velocity. */
				const Vector2 w = relativeVelocity - invTimeStep * relativePosition;

				const float wLength = abs(w);
				const Vector2 unitW = w / wLength;

				line._direction = Vector2(unitW.y(), -unitW.x());
				u = (combinedRadius * invTimeStep - wLength) * unitW;
				float coopWeight = 0.5f;
				line._point = _vel + coopWeight * u;
			}

			_orcaLines.push_back(line);
		}
		return numObstLines;
	}

	/////////////////////////////////////////////////////////////////////////////

	void Agent::computeNewVelocity() {
		Vector2 velPref(_velPref.getPreferredVel());
		//Vector2 velPref = _nextPrefSpeed;		
		const size_t numObstLines = computeORCALines();

		size_t lineFail = linearProgram2(_orcaLines, _maxSpeed, velPref, false, _velNew);

		if (lineFail < _orcaLines.size()) {
			linearProgram3(_orcaLines, numObstLines, lineFail, _maxSpeed, _velNew);
		}
	}

	/////////////////////////////////////////////////////////////////////////////

	std::string Agent::getStringId() const {
		return "orca";
	}

	/////////////////////////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS

	bool linearProgram1(const std::vector<Menge::Math::Line>& lines, size_t lineNo, float radius,
		const Vector2& optVelocity, bool directionOpt, Vector2& result) {
		const float dotProduct = lines[lineNo]._point * lines[lineNo]._direction;
		const float discriminant = sqr(dotProduct) + sqr(radius) - absSq(lines[lineNo]._point);

		if (discriminant < 0.0f) {
			/* Max speed circle fully invalidates line lineNo. */
			return false;
		}

		const float sqrtDiscriminant = std::sqrt(discriminant);
		float tLeft = -dotProduct - sqrtDiscriminant;
		float tRight = -dotProduct + sqrtDiscriminant;

		for (size_t i = 0; i < lineNo; ++i) {
			const float denominator = det(lines[lineNo]._direction, lines[i]._direction);
			const float numerator = det(lines[i]._direction,
				lines[lineNo]._point - lines[i]._point);

			if (std::fabs(denominator) <= Menge::EPS) {
				/* Lines lineNo and i are (almost) parallel. */
				if (numerator < 0.0f) {
					return false;
				}
				else {
					continue;
				}
			}

			const float t = numerator / denominator;

			if (denominator >= 0.0f) {
				/* Line i bounds line lineNo on the right. */
				tRight = std::min(tRight, t);
			}
			else {
				/* Line i bounds line lineNo on the left. */
				tLeft = std::max(tLeft, t);
			}

			if (tLeft > tRight) {
				return false;
			}
		}

		if (directionOpt) {
			/* Optimize direction. */
			if (optVelocity * lines[lineNo]._direction > 0.0f) {
				/* Take right extreme. */
				result = lines[lineNo]._point + tRight * lines[lineNo]._direction;
			}
			else {
				/* Take left extreme. */
				result = lines[lineNo]._point + tLeft * lines[lineNo]._direction;
			}
		}
		else {
			/* Optimize closest point. */
			const float t = lines[lineNo]._direction * (optVelocity - lines[lineNo]._point);

			if (t < tLeft) {
				result = lines[lineNo]._point + tLeft * lines[lineNo]._direction;
			}
			else if (t > tRight) {
				result = lines[lineNo]._point + tRight * lines[lineNo]._direction;
			}
			else {
				result = lines[lineNo]._point + t * lines[lineNo]._direction;
			}
		}

		return true;
	}

	/////////////////////////////////////////////////////////////////////////////

	size_t linearProgram2(const std::vector<Menge::Math::Line>& lines, float radius,
		const Vector2& optVelocity, bool directionOpt, Vector2& result) {
		if (directionOpt) {
			/*
			* Optimize direction. Note that the optimization velocity is of unit
			* length in this case.
			*/
			result = optVelocity * radius;
		}
		else if (absSq(optVelocity) > sqr(radius)) {
			/* Optimize closest point and outside circle. */
			result = norm(optVelocity) * radius;
		}
		else {
			/* Optimize closest point and inside circle. */
			result = optVelocity;
		}

		for (size_t i = 0; i < lines.size(); ++i) {
			if (det(lines[i]._direction, lines[i]._point - result) > 0.0f) {
				/* Result does not satisfy constraint i. Compute new optimal result. */
				const Vector2 tempResult = result;
				if (!linearProgram1(lines, i, radius, optVelocity, directionOpt, result)) {
					result = tempResult;
					return i;
				}
			}
		}

		return lines.size();
	}

	/////////////////////////////////////////////////////////////////////////////

	void linearProgram3(const std::vector<Menge::Math::Line>& lines, size_t numObstLines,
		size_t beginLine, float radius, Vector2& result) {
		float distance = 0.0f;

		for (size_t i = beginLine; i < lines.size(); ++i) {
			if (det(lines[i]._direction, lines[i]._point - result) > distance) {
				/* Result does not satisfy constraint of line i. */
				std::vector<Menge::Math::Line> projLines(lines.begin(),
					lines.begin() + numObstLines);

				for (size_t j = numObstLines; j < i; ++j) {
					Menge::Math::Line line;

					float determinant = det(lines[i]._direction, lines[j]._direction);

					if (std::fabs(determinant) <= Menge::EPS) {
						/* Math::Line i and line j are parallel. */
						if (lines[i]._direction * lines[j]._direction > 0.0f) {
							/* Line i and line j point in the same direction. */
							continue;
						}
						else {
							/* Line i and line j point in opposite direction. */
							line._point = 0.5f * (lines[i]._point + lines[j]._point);
						}
					}
					else {
						line._point = lines[i]._point + (det(lines[j]._direction,
							lines[i]._point - lines[j]._point) / determinant) *
							lines[i]._direction;
					}

					line._direction = norm(lines[j]._direction - lines[i]._direction);
					projLines.push_back(line);
				}

				const Vector2 tempResult = result;
				if (linearProgram2(projLines, radius, Vector2(-lines[i]._direction.y(),
					lines[i]._direction.x()), true, result) < projLines.size()) {
					/* This should in principle not happen.  The result is by definition
					* already in the feasible region of this linear program. If it fails,
					* it is due to small floating point error, and the current result is
					* kept.
					*/
					result = tempResult;
				}

				distance = det(lines[i]._direction, lines[i]._point - result);
			}
		}
	}


	//������ �ڸ�����agent�� ����ͬ��һ���Ŷӵģ�Ӱ�����ߵ�agent��ID
	size_t Agent::getGoalInterface() const {
		if (_nearAgents.size() == 0) return -1;//����������� ����û���Ŷӳ�Աʱִ��̽����Ϊ
//TODO ��ʱû�����Ŷ�
		Agent * currAgent = (Agent *)(_nearAgents[0].agent);
		float maxInfluence = currAgent->_influence;
		int maxId = 0;
		for (size_t i = 1; i < _nearAgents.size(); i++) {
			Agent * tempAgent = (Agent *)(_nearAgents[i].agent);
			float tempInfluence = tempAgent->_influence;
			if (maxInfluence < tempInfluence) {
				maxInfluence = tempInfluence;
				maxId = i;
			}
		}

		if (_influence >= maxInfluence) {
			return -2;//��ǰagent��Ӱ�����ߣ���leader
		}
		//�ҵ�������leader
		return maxId;

	}

	//���Ӧ�ý� getleaderID ������
	size_t Agent::getGoal() {

		//if (_groupAgents.size() == 0) {
		//	_leaderID = -1;
		//	return -1;
		//}//����������� ����û���Ŷӳ�Աʱִ��̽����Ϊ
		// //TODO ��ʱû�����Ŷ�
		//Agent * currAgent = (Agent *)(_groupAgents[0]);
		//int maxInfluence = currAgent->_influence;
		//int maxId = 0;
		//for (size_t i = 1; i < _groupAgents.size(); i++) {
		//	Agent * tempAgent = (Agent *)(_groupAgents[i]);
		//	int tempInfluence = tempAgent->_influence;
		//	if (maxInfluence < tempInfluence) {
		//		maxInfluence = tempInfluence;
		//		_leaderID = tempAgent->_id;
		//		maxId = i;
		//	}
		//}

		//if (_influence >= maxInfluence) {
		//	_leaderID = -2;
		//	return -2;//��ǰagent��Ӱ�����ߣ���leader
		//}
		//Agent * leaderAgent = (Agent *)(_groupAgents[maxId]);
		//leaderAgent->_influence += _influence;
		////�ҵ�������leader
		//return maxId;




		if (_nearAgents.size() == 0) {
			_leaderID = -1;
			return -1;
		}//����������� ����û���Ŷӳ�Աʱִ��̽����Ϊ
		 //TODO ��ʱû�����Ŷ�
		Agent * currAgent = (Agent *)(_nearAgents[0].agent);
		int maxInfluence = currAgent->_influence;
		int maxId = 0;
		for (size_t i = 1; i < _nearAgents.size(); i++) {
			Agent * tempAgent = (Agent *)(_nearAgents[i].agent);
			int tempInfluence = tempAgent->_influence;
			if (maxInfluence < tempInfluence) {
				maxInfluence = tempInfluence;
				_leaderID = tempAgent->_id;
				maxId = i;
			}
		}

		if (_influence >= maxInfluence) {
			_leaderID = -2;
			return -2;//��ǰagent��Ӱ�����ߣ���leader
		}
		Agent * leaderAgent = (Agent *)(_nearAgents[maxId].agent);
		leaderAgent->_influence += _influence;
		//�ҵ�������leader
		return maxId;

	}

	//������һ����Ŀ���  ���㷨�Ǽ����Ŷ���Ӱ��������agent��ΪĿ���
	Menge::Math::Vector2 Agent::computeNextGoal() {
		/*ORCAAgentTacticsFollow tAgent(this);
		return tAgent.computeNextGoal();*/
		/*
		Ĭ�Ϸ��� ��һ�� ȫ��Ŀ���
		�����һ�����ر��ʱ���Ƴ���һ���㣬�ٷ��ء��ڶ����㡱
		*/
		if (_globalGoals.size() > 0) {

			float dis = _pos.distance(_globalGoals[0]);

			if (dis < 5 && currentMapID >= 0 && currentMapID < _maps.size())
			{
				bool inOldMap = _maps[currentMapID]->pointInMap(_pos);
				if (!inOldMap) {
					for (int i = 1; i < _globalGoals.size(); i++) {
						_globalGoals[i - 1] = _globalGoals[i];
					}
				}
			}
			return _globalGoals[0];
		}
		else {
			//ִ�и�����Ϊ
			followLeaderBehavior();
		}

	}

	Menge::Math::Vector2 Agent::computeNextPrefSpeed() {

		if (_pos._y<=-25) {
			_prefSpeed = 0;
		}

		//Vector2 goalPoint = this->_nextGoal;
		////ʧȥleaderλ��
		//if (_missFollowing) {
		//	float tempDis = _leaderPath[0].distance(_pos);
		//	if (tempDis< 0.1) {
		//		for (int i = 1; i < _leaderPath.size(); i++) {
		//			_leaderPath[i - 1] = _leaderPath[i];
		//		}
		//	}
		//	else {
		//		this->_nextGoal = _leaderPath[0];
		//	}

		//}
		//else {
		//	//����Ǹ����ߣ���leader���ڸ��� ��leader������ͬ�ٶ�
		//	float dis = _pos.distance(_leaderPos);
		//	if (_isFollowing) {
		//		if(dis <= 3.5 && !_missFollowing)
		//		return _leaderPrefSpeed;
		//	}
		//	else {
		//		//�����Agent��Ϊleader 
		//		Vector2 groupPos(0, 0);
		//		for (int i = 0; i < _groupAgents.size(); i++) {
		//			Agent * currAgent = (Agent *)(_groupAgents[i]);
		//			groupPos += currAgent->_pos;
		//		}
		//		groupPos = groupPos / _groupAgents.size();
		//		Vector2 disp2 = groupPos - this->_pos;
		//		const float distSp2 = absSq(disp2);


		//		if (distSp2 > 15) {
		//			goalPoint = groupPos;
		//		}
		//	
		//	}
		//	
		//}


		//���ݵ�ǰλ�ú�Ŀ��λ�ã����������ٶ�
		// speed �����ٶ�ȷ��  ..���������ΪĬ�Ϸ���
		//�����Ŷӳ�Ա������λ��
		
		Vector2 goalPoint = this->_nextGoal;
		Vector2 disp = goalPoint - this->_pos;
		const float distSq = absSq(disp);
		float speed = this->_prefSpeed;
		if (distSq > 1e-8) {
			// Distant enough that I can normalize the direction.
			disp.set(disp / sqrtf(distSq));//��λ��
		}
		else {
			disp.set(0.f, 0.f);
		}

		Menge::Agents::PrefVelocity newVel;
		if (distSq <= 0.0001f) {
			// I've basically arrived -- speed should be zero.
			speed = 0.f;
		}
		else {
			const float speedSq = speed * speed;
			const float TS_SQD = Menge::SIM_TIME_STEP * Menge::SIM_TIME_STEP;
			if (distSq / speedSq < TS_SQD) {
				// The distance is less than I would travel in a single time step.
				speed = sqrtf(distSq) / Menge::SIM_TIME_STEP;
			}
		}


		newVel.setSingle(disp);
		newVel.setTarget(goalPoint);
		newVel.setSpeed(speed);
		this->setPreferredVelocity(newVel);

		return disp*speed;
	}

	//Menge::Math::Vector2 Agent::computeNextGoal() {
	//	//��Ҫ�ж��Ƿ���ɢ�ɹ�
	//	//���㵱ǰ����Map
	//	_currentMapIndex = -1;
	//	for (int i = 0; i < _maps.size(); i++) {
	//		bool agentInTheMap = _maps[i]->pointInMap(_pos);
	//		if (agentInTheMap) {
	//			_currentMapIndex = i;
	//			//if (_currentMapIndex!=_nextMapIndex) {
	//			//	return _nextGoal;
	//			//}
	//			break;
	//		}
	//	}
	//	if (_currentMapIndex == -1) return _pos;//�뿪��ʵ������
	//	//�жϵ�ǰλ����֮ǰ����Ŀ���ľ��룬С��һ��ֵ�ż�����Ŀ��	
	//	float disSq = computeDistanceSq_PosToGoal();
	//	if (disSq > 0.1) {
	//		return _nextGoal;
	//		//nextGoalIsTemp = false;
	//	}
	//	else {
	//		//����һ�νӽ�Ŀ���ʱ������ԭ�������ǰ��һС�ξ���
	//		//if (!_nextGoalIsTemp) {
	//		//	_nextGoalIsTemp = true;
	//		//	return Menge::Math::Vector2(_nextGoal._x * 2 - _pos._x, _nextGoal._y * 2 - _pos._y);
	//		//}
	//		//_nextGoalIsTemp = false;
	//		return followLeaderBehavior();
	//	}
	//	return Menge::Math::Vector2(0, -20);
	//}

	int Agent::findLeaderInNearAgent(size_t leaderID) {

		for (size_t i = 0; i < _nearAgents.size(); i++) {
			size_t currID = _nearAgents[i].agent->_id;
			if (leaderID == currID) {
				//�ڵ�ǰ�ھ��� �ҵ���֮ǰ��leader����������ǰleader
				return i;//���� leader��nearAgent�е��±�
			}
		}
		return -1;//��ʱ ��Ҫ����ѡ��leader

	}

	Menge::Math::Vector2 Agent::followLeaderBehavior() {
		//���ж��Ƿ�����leader��ǰleader �����ھ�
		//�ڸ����ھ��� �ҵ���leader
		int leaderIndex = findLeaderInNearAgent(_leaderID);
		if (leaderIndex == -1) {
			leaderIndex = getGoal();//����ѡ��leader
		}
		//ǰ���쵼��λ�ã�����ִ��̽����Ϊ
		if (leaderIndex >= 0 && leaderIndex < _nearAgents.size()) {
			const BaseAgent *temp = _nearAgents[leaderIndex].agent;
			Menge::Math::Vector2 leaderPos = temp->_pos;//ѡ��leader��Ŀ���Ϊ�Լ���Ŀ���
			_isFollowing = true;
			//�����ǰλ�ø�leader�ܽ�����ͣ�ƶ�
			if (_pos.distance(leaderPos)<2) {
							leaderPos = temp->_nextGoal;
			}
			//_leaderPath.push_back(leaderPos);
			_leaderPrefSpeed = temp->_nextPrefSpeed;
			_leaderPos = temp->_pos;
			//�ж�leader�Ƿ���ͬһ��Map
			for (int m = 0; m < _maps.size(); m++) {
				bool inMap = _maps[m]->pointInMap(_pos);
				if (inMap) {
					if (_maps[m]->pointInMap(leaderPos)) {
						_missFollowing = false;
					}
					else {
						float minDis =999;
						int minConIndex;
						for (int k = 0; k < _maps[m]->_connections.size(); k++) {
						//�ҵ���leader�������
							float temp = leaderPos.distance(_maps[m]->_connections[k].pos);
							if (temp < minDis) {
								minDis = temp;
								minConIndex = k;
							}
						}
						_leaderPath.clear();
						_leaderPath.push_back(_maps[m]->_connections[minConIndex].pos);
						_leaderPath.push_back(leaderPos);
						_missFollowing = true;
						break;
						
					}

				}
				
			}
			// std::cout <<"��"<<_id<<"����ѡ����leader"<<temp->_id<<"Ŀ��㣺("<<leaderPos._x<<","<<leaderPos._y<<")"<<std::endl;
			return leaderPos;
		}
		else {
			Vector2 groupPos(0, 0);
			for (int i = 0; i < _groupAgents.size(); i++) {
				Agent * currAgent = (Agent *)(_groupAgents[i]);
				groupPos += currAgent->_pos;
			}
			groupPos = groupPos / _groupAgents.size();
			return groupPos;
			//return exploreBehavior();
		}
	}
	Menge::Math::Vector2 Agent::exploreBehavior() {
		//ִ��̽����Ϊ
				//�ڵ�ǰ������ ȷ��ǰ������ ��Ҫ��¼�Ѿ�ȥ�����ţ�
				//��ǰ�����г��ڣ�ǰ������

		for (int m = 0; m < _maps.size(); m++) {
			bool isOut=true;
			bool inMap = _maps[m]->pointInMap(_pos);
			if (inMap) {
				isOut = false;
				_currentMapIndex = _maps[m]->_id;
				break;
			}
			if (isOut) {
				return _pos;
			}
		}
		if (_maps[_currentMapIndex]->_hasExist) {
			for (int j = 0; j < _maps[_currentMapIndex]->_nextMapsIndex.size(); j++) {
				if (_maps[_currentMapIndex]->_nextMapsIndex[j] == -1) {//����Map���±�
					Menge::Math::Vector2 goal = _maps[_currentMapIndex]->_connections[j].pos;//Ŀ�����Ϊ ����
					_nextMapIndex = -1;//��ʾ����
					_catchNextMap = false;
					return goal;
				}
			}
		}
		else {
			//��ǰMapû�г��ڣ����ѡ��һ���ţ���
			int index = (rand() % (_maps[_currentMapIndex]->_connections.size()));
			Menge::Math::Vector2 goal = _maps[_currentMapIndex]->_connections[index].pos;//Ŀ�����Ϊ �����һ����
			_nextMapIndex = _maps[_currentMapIndex]->_nextMapsIndex[index];
			_catchNextMap = false;
			return goal;


		}



	}
	//����Ϥ��Ϊ
	Menge::Math::Vector2 Agent::highEnvironmentFamiliarityBehavior() {
		/*
		�ܻ�ȡ���е�ͼ��Ϣ ��Agent��ǰλ��Ϊ����㣬�Ե�ͼ�����е� connectionΪ�ӽڵ�
		��������ͼ �����õϽ�˹�����㷨 �������·��

		*/
		return Menge::Math::Vector2(0, 0);

	}
	Menge::Math::Vector2 Agent::middleEnvironmentFamiliarityBehavior() {
		return Menge::Math::Vector2(0, 0);
	}
	Menge::Math::Vector2 Agent::lowEnvironmentFamiliarityBehavior() {
		return Menge::Math::Vector2(0, 0);
	}

#endif  // DOXYGEN_SHOULD_SKIP_THIS

}	// namespace ORCA
