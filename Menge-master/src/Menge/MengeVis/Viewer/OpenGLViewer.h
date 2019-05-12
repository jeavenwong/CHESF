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
*	@file		GLViewer.h
*	@brief		Specification for an OpenGL based 3D viewer.
*
*				Can draw a SceneGraph GLScene, perform view
*				manipulation and overlay text on the scene.
*/


#include "MengeVis/Viewer/GLViewer.h"

#include "thirdParty/SDL/SDL.h"
#include <string>
#include <vector>

#include "MengeVis/VisConfig.h"
#include "MengeVis/SceneGraph/GLCamera.h"
#include "MengeVis/SceneGraph/GLGroundPlane.h"
#include "MengeVis/SceneGraph/GLScene.h"
#include "MengeVis/Viewer/Profiler.h"
#include "MengeVis/Viewer/ScreenGrab.h"



namespace MengeVis {

	// Forward declarations
	class Image;

	/*!
	*	@namespace	MengeVis::Viewer
	*	@brief		The namespace containing visualization functionality for the
	*				pedestrian simulation.
	*/
	namespace Viewer{

		// Forward declarations
		class ViewConfig;
		class Watermark;

		/*!
		*	@brief		Class for defining an OpenGL Viewer.
		*/
		class MENGEVIS_API OpenGLViewer :public MengeVis::Viewer::GLViewer {
		public:

	
			/*!
			*	@brief		. .
			*
			*	@param		width		The width of the view window, in pixels.
			*	@param		height		The height of the view window, in pixels.
			*/
			//OpenGLViewer();
			OpenGLViewer(int width, int height);

			/*!
			*	@brief		Constructor based on configuration in a ViewConfig instance.
			*
			*	@param		cfg		A fully specified view configuration.
			*/
			OpenGLViewer(ViewConfig & cfg);

			/*!
			*	@brief		Destructor.
			*/
			~OpenGLViewer(void);

			/*!
			*	@brief		Runs the main loop -- including advancing the scene
			*				in time.  Exiting this function means the main event
			*				loop is no longer running.
			*/
			virtual	void run();
			//void drawOgre();
			virtual	bool initViewer(const std::string & title);
			

			/*!
			*	@brief		Main drawing function -- draws scene and context as available.
			*/
			//void drawGL();



			
		};
	}	// namespace Viewer
}	// namespace MengeVis



