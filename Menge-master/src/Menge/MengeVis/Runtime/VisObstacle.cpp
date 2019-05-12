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

#include "MengeVis/Runtime/VisObstacle.h"

#include "MengeVis/SceneGraph/graphCommon.h"
#include <vector>
using namespace std;
namespace MengeVis {
	namespace Runtime {

		using Menge::Math::Vector3;
		using SceneGraph::GLNode;

		////////////////////////////////////////////////////////////////////////////
		//			Implementation of VisObstacle
		////////////////////////////////////////////////////////////////////////////

		VisObstacle::VisObstacle( const Vector3 & p0, const Vector3 & p1 ) : GLNode(), _p0( p0 ),
			                                                                 _p1( p1 ) {
		}

		////////////////////////////////////////////////////////////////////////////

		void VisObstacle::drawGL( bool select ) {
			// TODO: remove this from here place it somewhere where it gets called upon
			//	context initialization
			if ( !select ) {
				glPushAttrib( GL_LINE_BIT | GL_ENABLE_BIT );
				glDisable( GL_LIGHTING );
				glLineWidth( 3.f );
				glColor3f( 0.75f, 0.75f, 0.75f );

				//Vector2 p0 = _obst->getP0();
				//Vector2 p1 = _obst->getP1();
				glBegin( GL_LINES );
				glVertex3f( _p0.x(), _p0.y(), _p0.z() );
				glVertex3f( _p1.x(), _p1.y(), _p1.z() );
				glEnd();
				glPopMatrix();
				glPopAttrib();
			}
		}

		void VisObstacle::drawGLOgre(bool select) {

			agentID = 0;
			x1 = -_p0.x();
			x2 = _p0.z();
			x3 = _p0.y();

			x4 = -_p1.x();
			x5 = _p1.z();
			x6 = _p1.y();

		}
		////////////////////////////////////////////////////////////////////////////
		//			Implementation of VisObstacle
		////////////////////////////////////////////////////////////////////////////

		VisSpecialArea::VisSpecialArea(const std::vector<Menge::Math::Vector2> vertexs) : GLNode()
		{
			_vertexs = vertexs;
		}

		////////////////////////////////////////////////////////////////////////////

		void VisSpecialArea::drawGL(bool select) {
			// TODO: remove this from here place it somewhere where it gets called upon
			//	context initialization
			if (!select) {
				glPushAttrib(GL_LINE_BIT | GL_ENABLE_BIT);
				glDisable(GL_LIGHTING);
				glLineWidth(3.f);
				glColor3f(0.75f, 0.75f, 0.75f);

				//Vector2 p0 = _obst->getP0();
				//Vector2 p1 = _obst->getP1();
				glBegin(GL_POLYGON);
				for (int i = 0; i < _vertexs.size(); i++)
				{
					glVertex2f(_vertexs[i]._x, _vertexs[i]._y);
				}
				glEnd();
				glPopMatrix();
				glPopAttrib();
			}
		}
		void VisSpecialArea::drawGLOgre(bool select) {
			// TODO: remove this from here place it somewhere where it gets called upon
			//	context initialization
			if (!select) {
				glPushAttrib(GL_LINE_BIT | GL_ENABLE_BIT);
				glDisable(GL_LIGHTING);
				glLineWidth(3.f);
				glColor3f(0.75f, 0.75f, 0.75f);

				//Vector2 p0 = _obst->getP0();
				//Vector2 p1 = _obst->getP1();
				glBegin(GL_POLYGON);
				for (int i = 0; i < _vertexs.size(); i++)
				{
					glVertex2f(_vertexs[i]._x, _vertexs[i]._y);
				}
				glEnd();
				glPopMatrix();
				glPopAttrib();
			}
		}

		////////////////////////////////////////////////////////////////////////////
		//			Implementation of VisGround
		////////////////////////////////////////////////////////////////////////////

		VisGround::VisGround(std::vector<Menge::Math::Vector3> &p, int count) : GLNode(), _p(p), _count(count)
		{

		}

		////////////////////////////////////////////////////////////////////////////

		void VisGround::drawGL(bool select) {

			agentID = 3;
			for (int i = 0; i < _count;i++){

				x.push_back(-_p[i].x());
				x.push_back(_p[i].z());
				x.push_back(_p[i].y());
				/*
				*x = -_p[i].x(); x++;
				*x = _p[i].z(); x++;
				*x = _p[i].y(); x++;
				*x = '\0';
				*/
			}
		}

		void VisGround::drawGLOgre(bool select) {

			agentID = 3;
			for (int i = 0; i < _count; i++){

				x.push_back(-_p[i].x());
				x.push_back(_p[i].z());
				x.push_back(_p[i].y());
				/*
				*x = -_p[i].x(); x++;
				*x = _p[i].z(); x++;
				*x = _p[i].y(); x++;
				*x = '\0';
				*/
			}
		}


	}	// namespace Runtime
}	// namespace MengeVis
