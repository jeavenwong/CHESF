

#include "HelbingPlugin.h"

#include "MengeCore/Agents/SimulatorBase.h"	
#include "MengeCore/Math/consts.h"
#include "MengeCore/Core.h"
#include <algorithm>
#include <cassert>
#include <limits>


namespace Menge {

	namespace Agents {

		//using Menge::Math::Vector2;
		//using Menge::Math::sqr;
		//float	AGENT_SCALE = 2000.f;
		//float	OBST_SCALE = 2000.f;
		//float	REACTION_TIME = 0.5f;
		//float	BODY_FORCE = 1.2e5f;
		//float	FRICTION = 2.4e5f;
		//float	FORCE_DISTANCE = 0.08f;
		//const std::string OperationORCAPlan::NAME = "orca";
		float TIME_STEP;

		////////////////////////////////////////////////////////////////////////////
		//			Implementation of 
		////////////////////////////////////////////////////////////////////////////
		PLUGCLASS::PLUGCLASS() {
			_planName = PLUGNAME;
			/*AGENT_SCALE = 4000.f;
			OBST_SCALE = 2000.f;
			REACTION_TIME = 0.2f;
			BODY_FORCE = 1200.f;
			FRICTION = 2400.f;
			FORCE_DISTANCE = 0.02f;*/

		}


		/////////////////////////////////////////////////////////////////////////////

		
		/////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////

		void PLUGCLASS::computeNewVelocity(float timesetp) {
			TIME_STEP = timesetp;
			Vector2 force(drivingForce());
			for (size_t i = 0; i < _baseAgent->_nearAgents.size(); ++i) {
				const BaseAgent * otherBase = _baseAgent->_nearAgents[i].agent;
				//const Agent * const other = static_cast< const Agent *>(otherBase);

				force += agentForce(otherBase);
			}

			for (size_t obs = 0; obs < _baseAgent->_nearObstacles.size(); ++obs) {
				const Obstacle * obst = _baseAgent->_nearObstacles[obs].obstacle;
				force += obstacleForce(obst);
			}
			Vector2 acc = force / _mass;
			_baseAgent->_velNew = _baseAgent->_vel + acc * TIME_STEP;

		}

		/////////////////////////////////////////////////////////////////////////////

		Vector2 PLUGCLASS::agentForce(const BaseAgent * other) const {
			/* compute right of way */
			float rightOfWay = fabs(_baseAgent->_priority - other->_priority);
			if (rightOfWay >= 1.f) {
				rightOfWay = 1.f;
			}

			const float D = FORCE_DISTANCE;
			Vector2 normal_ij = _baseAgent->_pos - other->_pos;
			float distance_ij = abs(normal_ij);
			normal_ij /= distance_ij;
			float Radii_ij = _baseAgent->_radius + other->_radius;

			float AGENT_SCALE2 = AGENT_SCALE;
			float D_AGT = D;

			// Right of way-dependent calculations
			// Compute the direction perpinduclar to preferred velocity (on the side 
			//		of the normal force.

			Vector2 avoidNorm(normal_ij);
			if (rightOfWay) {
				Vector2 perpDir;
				if (_baseAgent->_priority < other->_priority) {
					// his advantage
					D_AGT += (rightOfWay * rightOfWay) * _baseAgent->_radius * .5f;	// Note: there is no symmetric reduction on 
																		// the other side
																		// modify normal direction
																		//	The perpendicular direction should always be in the direction that gets the
																		//	agent out of the way as easily as possible
					float prefSpeed = other->_velPref.getSpeed();
					if (prefSpeed < 0.0001f) {
						// he wants to be stationary, accelerate perpinduclarly to displacement
						perpDir.set(-normal_ij.y(), normal_ij.x());
						if (perpDir * _baseAgent->_vel < 0.f) perpDir.negate();
					}
					else {
						// He's moving somewhere, accelerate perpindicularly to his preferred direction
						// of travel.  
						const Vector2 prefDir(other->_velPref.getPreferred());
						perpDir.set(-prefDir.y(), prefDir.x());	// perpendicular to preferred velocity
						if (perpDir * normal_ij < 0.f) perpDir.negate();
					}
					// spherical linear interpolation
					float sinTheta = det(perpDir, normal_ij);
					if (sinTheta < 0.f) {
						sinTheta = -sinTheta;
					}
					if (sinTheta > 1.f) {
						sinTheta = 1.f;	// clean up numerical error arising from determinant
					}
					avoidNorm.set(slerp(rightOfWay, normal_ij, perpDir, sinTheta));
				}
			}
			float mag = (AGENT_SCALE2 * expf((Radii_ij - distance_ij) / D_AGT));
			const float MAX_FORCE = 1e15f;
			if (mag >= MAX_FORCE) {
				mag = MAX_FORCE;
			}
			Vector2 force(avoidNorm * mag);

			if (distance_ij < Radii_ij) {
				Vector2 f_pushing(0.f, 0.f);
				Vector2 f_friction(0.f, 0.f);
				// pushing
				Vector2 tangent_ij(normal_ij.y(), -normal_ij.x());

				f_pushing = normal_ij * (BODY_FORCE * (Radii_ij - distance_ij));
				f_friction = tangent_ij * (FRICTION * (Radii_ij - distance_ij)) * fabs((other->_vel - _baseAgent->_vel) * tangent_ij);// / distance_ij;
				force += f_pushing + f_friction;
			}
			return force;
		}

		////////////////////////////////////////////////////////////////
		Vector2 PLUGCLASS::obstacleForce(const Obstacle * obst) const {
			const float D = FORCE_DISTANCE;
			const float OBST_MAG = OBST_SCALE;
			Vector2 nearPt;	// set by distanceSqToPoint
			float distSq;	// set by distanceSqToPoint
			if (obst->distanceSqToPoint(_baseAgent->_pos, nearPt, distSq) ==
				Obstacle::LAST) return Vector2(0.f, 0.f);
			float dist = sqrtf(distSq);
			Vector2 forceDir((_baseAgent->_pos - nearPt) / dist);

			Vector2 force = forceDir * (OBST_MAG * exp((_baseAgent->_radius - dist) / D));

			// pushing, friction
			if (dist <  _baseAgent->_radius) { // intersection has occurred
				Vector2 f_pushing(0.f, 0.f);
				Vector2 f_friction(0.f, 0.f);

				Vector2 tangent_io(forceDir.y(), -forceDir.x());

				// make sure direction is opposite i's velocity
				if ((tangent_io * _baseAgent->_vel) < 0.f) {
					tangent_io.negate();
				}

				f_pushing = forceDir * (BODY_FORCE * (_baseAgent->_radius - dist));

				// friction
				f_friction = tangent_io * FRICTION * (_baseAgent->_radius - dist) * (_baseAgent->_vel * tangent_io);
				force += f_pushing - f_friction;
			}
			return force;
		}

		////////////////////////////////////////////////////////////////

		Vector2 PLUGCLASS::drivingForce() const {
			return (_baseAgent->_velPref.getPreferredVel() - _baseAgent->_vel) * (_mass / REACTION_TIME);
		}

		////////////////////////////////////////////////////////////////



		void  PLUGCLASS::initAgentInfo() const {
			return;
		}

		FACTORYPLUGCLASS::FACTORYPLUGCLASS() : OperationPlanFactory() {
			_nameID = _attrSet.addStringAttribute("type", true, "");
		}
		////////////////////////////////////////////////////////////////////////////

		bool FACTORYPLUGCLASS::setFromXML(PLUGCLASS * sel, TiXmlElement * node,
			const std::string & specFldr) const {
			PLUGCLASS * op = dynamic_cast< PLUGCLASS * >(sel);
			assert(op != 0x0 && "Trying to set attributes of a const state selector element on "
				"an incompatible object");
			//这里可以添加一些必要的参数
			if (!OperationPlanFactory::setFromXML(op, node, specFldr)) return false;
			op->setPlanName(_attrSet.getString(_nameID));
			return true;
		}
	}	// namespace Agents
}	// namespace Menge
extern "C" {

	OperationPlanPlugin_API	Menge::Agents::OperationPlanFactory * Export(void) {//只有此处的API无法替换宏

		return new Menge::Agents::FACTORYPLUGCLASS();

	}

}