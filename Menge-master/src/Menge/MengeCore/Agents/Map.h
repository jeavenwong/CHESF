/*
 Menge Crowd Simulation Framework

 Copyright and trademark 2012-17 University of North Carolina at Chapel Hill

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
 or
    LICENSE.txt in the root of the Menge repository.

 Any questions or comments should be sent to the authors menge@cs.unc.edu

 <http://gamma.cs.unc.edu/Menge/>
*/

/*!
 *  @file       Map.h
 *  @brief      Contains the Map class.
 */

#ifndef __MAP_H__
#define __MAP_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/Agents/MapSets/MapVertexList.h"
namespace Menge {

	namespace Agents {

		/*!
		*  @brief      Defines static Maps in the simulation.
		*/
		class MENGE_API Map {
		public:
			/*!
			 *	@brief		An enumeration to define the type of nearest point - first, middle,
			 *				last.
			 */
			enum NearTypeEnum {
				FIRST,
				MIDDLE,
				LAST
			};

			/*!
			 *  @brief      Constructs a static Map instance.
			 */
			Map();

			/*!
			 *  @brief      Destroys this static Map instance.
			 */
			~Map();

			/*!
			 *	@brief		Retrieves the normal of the Map
			 *	@returns	The normal
			 */
			inline Math::Vector2 normal() const {
				return Math::Vector2( _unitDir.y(), -_unitDir.x() );
			}

			/*!
			 *	@brief		Retrieve the first point on the Map.
			 */
			inline const Math::Vector2 & getP0() const { return _point; }

			/*!
			 *	@brief		Retrieve the Map's mid-point.
			 */
			inline const Math::Vector2 midPt() const {
				return _point + ( 0.5f * _length ) * _unitDir;
			}

			/*!
			 *	@brief		Retrieve the second point on the Map.
			 */
			Math::Vector2 getP1() const;

			/*!
			 *	@brief		Returns the next Map in sequence
			 */
			const Map * next() const { return _nextMap; }
			bool pointInMap(Math::Vector2 point);
			/*!
			 *	@brief		Computes the squared distance from the Map to the given point.
			 *				Also sets the value of the point in the provided Vector2
			 *
			 *	@param		pt			The point whose distance is to be evaluated
			 *	@param		nearPt		The position on the Map which is nearest to the
			 *							test point will be set here.
			 *	@param		distSq		The squared distance to the line (i.e. ||pt - nearPt||^2)
			 *							is placed inside this parameter.
			 *	@returns	The classificaiton of what the nearest point is - first, middle, or
			 *				last.
			 */
			NearTypeEnum distanceSqToPoint( const Math::Vector2 & pt, Math::Vector2 & nearPt,
											float & distSq ) const;

			/*!
			 *	@brief		Determines if a circle, moving along a ray, will intersect
			 *				the Map.
			 *
			 *	@param		dir		The direction of motion
			 *	@param		start	The starting point of the circle
			 *	@param		radius	The radius of the circle
			 *	@returns	The time to collision (a large value representing infinity
			 *					if no collision is possible.)
			 */
			float circleIntersection( const Math::Vector2 & dir, const Math::Vector2 & start,
									  float radius ) const;

			/*!
			 *	@brief		Returns the length of the Map
			 *
			 *	@returns	The length.
			 */
			inline float length() const { return _length; }

			/*!
			 *	@brief		Reports if the given point lies on the Map
			 *
			 *	@param		pt		The point to test
			 *	@returns	True if pt is on the Map, false otherwise
			 */
			bool pointOnMap( const Math::Vector2 & pt ) const;

			/*!
			 *	@brief		Reports if the given point is on the "outside" of
			 *				the Map.  This definition depends on whether the
			 *				Map is double-sided or not.
			 *
			 *	@param		point		The point to test.
			 *	@returns	A boolean reporting if the point lies on the outside of this
			 *				Map (true) or not (false).
			 */
			// NOTE: This test is "safe" because if _doubleSided is true, the leftOf test doesn't
			//		get performed.  If it is false, then _nextMap must point to a valid
			//		Map.
			inline bool pointOutside( const Math::Vector2 & point ) const {
				return _doubleSided || ( leftOf( _point, getP1(), point ) < 0.f );
			}

			/*!
			 *	@brief		Reports if the Map is convext at _point. 
			 *
			 *	Takes into account the double-sidedness of the Map and the side 
			 *	of the Map the agent is on.
			 *
			 *	@param		agtOnRight		Indicate if the agent is on the right side of
			 *								the Map (true) or the left (false).
			 *	@returns	True if the Map is convex, false otherwise.
			 */
			inline bool p0Convex( bool agtOnRight) const {
				return agtOnRight ? _isConvex : _doubleSided && !_isConvex;
			}

			/*!
			 *	@brief		Reports if the Map is convext at _point + _length * _unitDir. 
			 *
			 *	Takes into account the double-sidedness of the Map and the side 
			 *	of the Map the agent is on.
			 *
			 *	@param		agtOnRight		Indicate if the agent is on the right side of
			 *								the Map (true) or the left (false).
			 *	@returns	True if the Map is convex, false otherwise.
			 */
			// NOTE: The only way for _nextMap to be NULL is for this to be double sided.
			//		And end points of double-sided Maps are always convex.
			inline bool p1Convex( bool agtOnRight) const {
				return _nextMap == 0x0 ? 
					true : 
					( agtOnRight ? 
						_nextMap->_isConvex : 
						_doubleSided && _nextMap->_isConvex
					);
			}

			/*!
			 *	@brief		Sets the Map's closed state.  
			 *
			 *	If closed, it is part of a sequence of Maps that form a closed polygon.  
			 *	If open, it is part of a polyline.
			 *
			 *	@param		closed		Defines the Map as part of a closed polygon (true),
			 *							or a closed polygon (false).
			 */
			inline void setClosedState( bool closed ) { _doubleSided = !closed; }

			/*!
			 *	@brief		Reports if the Map is double sided.
			 *
			 *	If double sided (true) then the Map should be included in the 
			 *	nearby Maps, *regardless* of which side of the line the agent lies.
			 */
			bool _doubleSided;

			/*!
			 *	@brief		Reports if the Map is convex around the Map's
			 *				point (_point).
			 */
			bool _isConvex;
			bool _hasExist;
			/*!
			 *	@brief		Pointer to the next Map in the greater Map structure.
			 *				If the Map is open, it could be NULL.
			 */
			Map* _nextMap;
			std::vector<int> _nextMapsIndex;//可以不要了
			std::vector<Connection> _connections;
			std::vector<Path> _paths;
			/*!
			 *	@brief		The point from which the Map is defined.
			 */
			Math::Vector2 _point;
			std::vector<Math::Vector2> _points;
			/*!
			 *	@brief		Pointer to the previous Map in the greater Map structure.
			 *				If the Map is open, it could be NULL.
			 */
			Map* _prevMap;

			/*!
			 *	@brief		The direction the Map extends from the originating point.
			 */
			Math::Vector2 _unitDir;

			/*!
			 *	@brief		The distance in the direction the Map extends.
			 */
			float _length;

			/*!
			 *	@brief		A unique identifier for this Map.	
			 */
			size_t _id;

			/*!
			 *	@brief The class of Map, used so agents can ignore/include Maps
			 */
			size_t _class;
		};

		/*!
		   *  @brief      Computes the squared distance from a line segment with the
		   *              specified endpoints to a specified point.
		   *
		   *  @param      a               The first endpoint of the line segment.
		   *  @param      b               The second endpoint of the line segment.
		   *  @param      c               The point to which the squared distance is to
		   *                              be calculated.
		   *  @returns    The squared distance from the line segment to the point.
		   */
		 /* inline MENGE_API float distSqPointLineSegment( const Math::Vector2& a, 
														 const Math::Vector2& b,
														 const Math::Vector2& c)
		  {
			const float r = ((c - a) * (b - a)) / absSq(b - a);

			if (r < 0.0f) {
			  return absSq(c - a);
			} else if (r > 1.0f) {
			  return absSq(c - b);
			} else {
			  return absSq(c - (a + r * (b - a)));
			}
		  }*/
	}	// namespace Agents
}	// namespace Menge
#endif	// __Map_H__
