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

#include "MengeVis/SceneGraph/GLScene.h"

#include "MengeVis/SceneGraph/graphCommon.h"
#include "MengeVis/SceneGraph/GLCamera.h"
#include "MengeVis/SceneGraph/Select.h"
#include <vector>

namespace MengeVis {

	namespace SceneGraph {

		///////////////////////////////////////////////////////////////////////////
		//				IMPLEMENTATION FOR GLScene
		///////////////////////////////////////////////////////////////////////////

		GLScene::GLScene():_uiContext(0x0) {
			firsttime = false;
		}

		///////////////////////////////////////////////////////////////////////////
		GLScene::~GLScene() {
			GLNodeListItr itr = _nodes.begin();
			for ( ; itr != _nodes.end(); ++itr ) {
				delete (*itr);
			}
			
			SystemListItr sItr = _systems.begin();
			for ( ; sItr != _systems.end(); ++sItr ) {
				delete (*sItr);
			}
			
			if ( _uiContext ) delete _uiContext;
		}

		///////////////////////////////////////////////////////////////////////////
		
		void GLScene::finish() {
			SystemListItr sItr = _systems.begin();
			for ( ; sItr != _systems.end(); ++sItr ) {
				(*sItr)->finish();
			}
		}
		
		///////////////////////////////////////////////////////////////////////////
		
		void GLScene::newGLContext() {
			GLNodeListItr itr = _nodes.begin();
			for ( ; itr != _nodes.end(); ++itr ) {
				(*itr)->newContext();
			}
			if ( _uiContext ) {
				_uiContext->newGLContext();
			}
		}

		///////////////////////////////////////////////////////////////////////////


		void GLScene::drawGLOgre(const GLCamera & camera, std::vector<agentOgre1>& NodePos)
		{
		
			GLNodeListItr itr = _nodes.begin();
			NodePos.clear();
			int i = 0;
			for (; itr != _nodes.end(); ++itr)
			{
				agentOgre1 node;
				(*itr)->drawGLOgre(false);

				if ((*itr)->agentID == 1)
				{
					char str[100];
					sprintf(str, "node%d", i);

					node.ID = (*itr)->agentID; 
					node.pos0[0] = (*itr)->x1;
					node.pos0[1] = (*itr)->x2;
					node.pos0[2] = (*itr)->x3;

					//printf("agents--x: %f,y:%f,z:%f\n", (*itr)->x1, (*itr)->x2, (*itr)->x3);
					NodePos.push_back(node);
					i++;
				}
				else{
					node.ID = (*itr)->agentID;
					node.pos0[0] = (*itr)->x1;
					node.pos0[1] = (*itr)->x2;
					node.pos0[2] = (*itr)->x3;

					node.pos1[0] = (*itr)->x4;
					node.pos1[1] = (*itr)->x5;
					node.pos1[2] = (*itr)->x6;

					//printf("others--x: %f,y:%f,z:%f\n", (*itr)->x1, (*itr)->x2, (*itr)->x3);
					NodePos.push_back(node);
					i++;
				}
			}

			GLNodeListItr itrGround = _grounds.begin();

			for (; itrGround != _grounds.end(); ++itrGround)
			{
				agentOgre1 node;
				(*itrGround)->drawGLOgre(false);

				if ((*itrGround)->agentID == 3)
				{
					char str[100];
					sprintf(str, "node%d", i);
					node.ID = 3;
					std::vector<float> x = (*itrGround)->x;
					for (int i = 0; i < x.size();i++){
						Ogre::Vector3 pos;
						//pos[0] = (*itrGround)->x[i++];
						//pos[1] = (*itrGround)->x[i++];
						//pos[2] = (*itrGround)->x[i];
						pos[0] = x[i++];
						pos[1] = x[i++];
						pos[2] = x[i];
						node.pos3.push_back(pos);
					}
					///node.pos3[0] = (*itr);
					NodePos.push_back(node);
					i++;
				}
			}
			//printf("total: %d\n", i);


			/*		int i=0;
			for ( ; itr != _nodes.end(); ++itr ) {
			if(i<NodePos.size()){
			float x1=0,x2=0,x3=0;
			(*itr)->drawGL(false);
			Ogre::Vector3 node;
			node[0]=(*itr)->x1;
			node[1]=(*itr)->x2;
			node[2]=(*itr)->x3;

			NodePos[i]=node;
			printf("total: %d\n", i);
			printf("x: %f,y:%f,z:%f\n", (*itr)->x1,(*itr)->x2,(*itr)->x3);
			i++;
			}
			}*/

			//if ( _uiContext ) {
			//	_uiContext->drawGL( vWidth, vHeight );
			//}
		}


		void GLScene::drawGL( const GLCamera & camera, const GLLightVector & lights,
							  int vWidth, int vHeight ) {
			glLoadIdentity();
			camera.setGLView();
			int LIGHT_COUNT = (int)lights.size();
			for ( int i = 0; i < LIGHT_COUNT; ++i ) {
				lights[ i ].initGL( i, GLLight::WORLD );
			}

			GLNodeListItr itr = _nodes.begin();
			
			for ( ; itr != _nodes.end(); ++itr ) {
				(*itr)->drawGL( false );
			}

			if ( _uiContext ) {
				_uiContext->drawGL( vWidth, vHeight );
			}
			
		}


		
		///////////////////////////////////////////////////////////////////////////

		bool GLScene::selectGL( const GLCamera & camera, int vWidth, int vHeight,
								int * selectPoint ) {	
			if ( _uiContext ) {
				return _uiContext->selectGL( this, camera, vWidth, vHeight, selectPoint );
			}
			return false;
		}

		///////////////////////////////////////////////////////////////////////////

		bool GLScene::updateScene( float time ) {
			bool redraw = false;
			SystemListItr itr = _systems.begin();
			for ( ; itr != _systems.end(); ++itr ) {
				redraw = (*itr)->updateScene( time ) || redraw;
			}
			if ( _uiContext ) _uiContext->update();
			return redraw;
		}

		///////////////////////////////////////////////////////////////////////////

		bool GLScene::addNode( GLNode * node, GLDagNode * parent ) {
			if ( !parent ) {
				_nodes.push_back( node );		
			} else {
				parent->addChild( node );
			}
			return true;
		}


		bool GLScene::addGround(GLNode * node) {

			_grounds.push_back(node);

			return true;
		}
		bool GLScene::clearNode() {

			_nodes.clear();

			return true;
		}
		///////////////////////////////////////////////////////////////////////////

		bool GLScene::addSystem( System * system ) {
			_systems.push_back( system );
			return true;
		}

		///////////////////////////////////////////////////////////////////////////

		void GLScene::setContext( Context * context ) {
			if ( _uiContext ) {
				_uiContext->deactivate();
				delete _uiContext;
			}
			_uiContext = context;
			_uiContext->activate();
		}

		///////////////////////////////////////////////////////////////////////////

		ContextResult GLScene::handleMouse( SDL_Event & e ) {
			if ( _uiContext ) return _uiContext->handleMouse( e );
			return ContextResult( false, false );
		}

		///////////////////////////////////////////////////////////////////////////

		ContextResult GLScene::handleKeyboard( SDL_Event & e ) {
			if ( _uiContext ) return _uiContext->handleKeyboard( e );
			return ContextResult( false, false );
		}

	}	// namespace SceneGraph
}	// namespace MengeVis
