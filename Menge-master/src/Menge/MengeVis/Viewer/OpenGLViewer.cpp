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


#ifdef _MSC_VER
#include "windows.h"
#endif

#include "MengeVis/Viewer/GLViewer.h"
#include "MengeVis/Viewer/OpenGLViewer.h"

#include "MengeCore/Runtime/os.h"
#include "MengeVis/SceneGraph/Context.h"
#include "MengeVis/SceneGraph/GLContextManager.h"
#include "MengeVis/SceneGraph/image.h"
#include "MengeVis/SceneGraph/Select.h"
#include "MengeVis/SceneGraph/shapes.h"
#include "MengeVis/SceneGraph/TextWriter.h"
#include "MengeVis/SceneGraph/XformMatrix.h"
#include "MengeVis/Viewer/ViewConfig.h"
#include "MengeVis/Viewer/ScreenGrab.h"
#include "MengeVis/Viewer/Profiler.h"
#include "MengeVis/Viewer/Watermark.h"

#include <iostream>
#include <sstream>
#include <iomanip>

namespace MengeVis {

	namespace Viewer {

		using Menge::logger;
		using Menge::Logger;

		///////////////////////////////////////////////////////////////////////////
		//				IMPLEMENTATION FOR OpenGLViewer
		///////////////////////////////////////////////////////////////////////////

	

		///////////////////////////////////////////////////////////////////////////

		OpenGLViewer::OpenGLViewer(int width, int height) : GLViewer(width, height)
		{

		}

		///////////////////////////////////////////////////////////////////////////

		OpenGLViewer::OpenGLViewer(ViewConfig & cfg) : GLViewer(cfg)
		{
			
		}

		///////////////////////////////////////////////////////////////////////////

		OpenGLViewer::~OpenGLViewer() {
			if (_scene != 0x0) {
				//delete _scene;	TODO: Figure out why navigation mesh causes problems here
				_scene = 0x0;
			}

			if (_bgImg != 0x0) {
				delete _bgImg;
			}
			if (_window) SDL_DestroyWindow(_window);
			SDL_Quit();
		}

		///////////////////////////////////////////////////////////////////////////

		bool OpenGLViewer::initViewer(const std::string & title) {
				if ( ! initSDL( title ) ) return false;//可视化窗口此时出现了
				initGL();
				SceneGraph::initShapes();//初始化了两个 GLNode ，，能画圆和圆柱
			/*
			绘制圆圈的GLNode。 这个圆是围绕世界空间的起源，躺在x-z平面上。
			绘制圆柱体的GLNode。 气缸有单位半径和单位高度，气缸底部位于原点。 高度沿着y轴。
			*/
				resizeGL( _width, _height );

			return true;
		}


	
		///////////////////////////////////////////////////////////////////////////

		void OpenGLViewer::run() {
			std::string useMessage("\nViewer controls:\n" \
				"  Quit the program ............ Ctrl + q\n"\
				"  Camera controls:\n" \
				"    Ctrl + Left Mouse ......... ROTATION\n" \
				"    Ctrl + Shift + Left Mouse.. MOVE\n" \
				"    Shift + Left Mouse ........ ZOOM\n" \
				"    'o' ....................... Orthographic view\n" \
				"    'p' ....................... Perspective view\n" \
				"    'x' ....................... Look along x-axis\n" \
				"    Shift + 'x'................ Look along negative x-axis\n"\
				"    'y' ....................... Look along y-axis\n" \
				"    Shift + 'y'................ Look along negative y-axis\n"\
				"    'z' ....................... Look along z-axis\n" \
				"    Shift + 'z'................ Look along negative z-axis\n"\
				"    Ctrl + 'c'................. Display camera parameters to the console\n"\
				"    Ctrl + '1'-'9'............. Switch cameras (if a camera exists)\n"\
				"  Playback:\n" \
				"    spacebar .................. Stop/start playback\n" \
				"    RIGHT arrow ............... Advance one frame (when stopped)\n" \
				"  Output images ............... Ctrl + o\n"\
				);

			size_t FULL_FRAME = 0;
			size_t SCENE_UPDATE = 0;
			size_t FULL_DRAW = 0;
			size_t BUFFER_SWAP = 0;


			bool redraw = true;
			float time = 0.f;
			_fpsDisplayTimer.start();

			while ( _running ) {
				SDL_Event e;
				while ( SDL_PollEvent( &e ) ) {
					if( e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
						redraw = handleKeyboard( e ) || redraw;
					} else if( e.type == SDL_QUIT ) {
						_running = false;
						redraw = false;
						break;
					} else if (e.type == SDL_WINDOWEVENT) {
						if (e.window.event == SDL_WINDOWEVENT_SHOWN) {
							redraw = true;
						} else if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
							resizeGL(e.window.data1, e.window.data2);
							redraw = true;
						}
					}
					else if (e.type == SDL_MOUSEMOTION ||
						e.type == SDL_MOUSEBUTTONDOWN ||
						e.type == SDL_MOUSEBUTTONUP ||
						e.type == SDL_MOUSEWHEEL ) {
						redraw = handleMouse(e) || redraw;
					}
				}
				if ( !_pause ) startTimer( FULL_FRAME );
				if ( redraw || _update || !_pause ) {
					// draw stuff
					if ( _scene && ( !_pause || _update ) ) {
						startTimer( SCENE_UPDATE );
						try {
							redraw = _scene->updateScene( _viewTime );
						} catch ( SceneGraph::SystemStopException ) {
							// When a system sends an exception that things are over
							// pause everything
							std::cout << "System stopped!\n";
							_pause = true;	
						}
						if (!_update ) {
							 offsetTime( _stepSize );
						}
						stopTimer( SCENE_UPDATE );	
					}
					if ( redraw ) {
						startTimer( FULL_DRAW );
						drawGL();			
						stopTimer( FULL_DRAW );

						startTimer( BUFFER_SWAP );
						SDL_GL_SwapWindow(_window);
						stopTimer( BUFFER_SWAP );
						redraw = false;
					}
					if ( !_pause ) lapTimer( FULL_FRAME );			
				}

				if ( ( !_pause || _update ) && _dumpImages ) {
					std::stringstream fullPath;				
					fullPath << _dumpPath << "img";
					fullPath << std::setfill( '0' ) << std::setw( 6 ) << ++_imgCount << ".png";
					snapshotPNG( _width, _height, fullPath.str().c_str() );
				}
				_update = false;
			}
			printAverages();

			_scene->finish();
		}

		

		///////////////////////////////////////////////////////////////////////////

	}	// namespace Viewer
}	// namespace MengeVis
