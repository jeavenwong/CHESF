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

#ifndef __GLVIEWER_H__
#define __GLVIEWER_H__

#include "thirdParty/SDL/SDL.h"
#include <string>
#include <vector>

#include "MengeVis/VisConfig.h"
#include "MengeVis/SceneGraph/GLCamera.h"
#include "MengeVis/SceneGraph/GLGroundPlane.h"
#include "MengeVis/SceneGraph/GLScene.h"
#include "MengeVis/Viewer/Profiler.h"
#include "MengeVis/Viewer/ScreenGrab.h"

#include "Ogre.h"
#include "ExampleApplication.h"
#include "OIS.h"

namespace MengeVis {

	// Forward declarations
	class Image;

	/*! 
	 *	@namespace	MengeVis::Viewer
	 *	@brief		The namespace containing visualization functionality for the
	 *				pedestrian simulation.
	 */
	namespace Viewer {

		// Forward declarations
		class ViewConfig;
		class Watermark;

		/*!
		 *	@brief		Class for defining an OpenGL Viewer.
		 */
		class MENGEVIS_API GLViewer {
		public:

			std::vector<agentOgre1> _NodePos;
			/*!
			 *	@brief		. .
			 *
			 *	@param		width		The width of the view window, in pixels.
			 *	@param		height		The height of the view window, in pixels.
			 */
			GLViewer( int width, int height );

			/*!
			 *	@brief		Constructor based on configuration in a ViewConfig instance.
			 *
			 *	@param		cfg		A fully specified view configuration.
			 */
			GLViewer( ViewConfig & cfg );

			/*!
			 *	@brief		Destructor.
			 */
			~GLViewer(void);

			/*!
			 *	@brief		Runs the main loop -- including advancing the scene
			 *				in time.  Exiting this function means the main event
			 *				loop is no longer running.
			 */
			virtual void run();

	     	//static	GLViewer* getViewer(ViewConfig & cfg);
			void drawOgre();

			/*!
			 *	@brief		Sets the optional background image to the viewer.
			 *
			 *	@param		imgName		A valid path to a valid image to load.
			 *	@returns	A boolean reporting success (true) or failure (false).
			 */
			bool setBGImage( const std::string & imgName );

			/*!
			 *	@brief		Reports if the viewer has a background image.
			 *
			 *	@returns	True if there is a background image, false otherwise.
			 */
			bool hasBGImage() const { return _bgImg != 0x0; }

			/*!
			 *	@brief		Sets the watermark to the viewer.
			 *
			 *	@param		imgName		A valid path to a valid image to load.
			 *	@returns	A boolean reporting success (true) or failure (false).
			 */
			bool setWatermark( const std::string & imgName );

			/*!
			 *	@brief		Reports if the viewer has a watermark.
			 *
			 *	@returns	True if there is a watermark, false otherwise.
			 */
			bool hasWatermark() const { return _waterMark != 0x0; }

			/*!
			 *	@brief		Clears the background image from the viewer.
			 */
			void clearBGImage();

			/*!
			 *	@brief		Initializes the viewer with the given title.
			 *
			 *	@param		title		The name displayed at the top of the window.
			 *	@returns	True if initialization was successful, false otherwise.
			 */
		    virtual	bool initViewer( const std::string & title );

			/*!
			 *	@brief		Resizes the window to the indicated size.
			 *
			 *	@param		w		The new width of the viewer window.
			 *	@param		h		The new height of the viewer window.
			 */
			void resizeGL( int w, int h );

			/*!
			 *	@brief		Initializes the opengl mechanism.
			 */
			void initGL();

			/*!
			 *	@brief		Sets the GLScene to be drawn.
			 *				A viewer can only draw a single scene; all drawn 
			 *				elements belong either to the GLScene or a GLContext.
			 *
			 *	@param		scene	The GLScene to be rendered and temporally advanced.
			 */
			void setScene( SceneGraph::GLScene * scene );

			/*!
			 *	@brief		Causes the viewer to recognize that a new OpenGL context has been
			 *				created (such as window resizes).
			 */
			void newGLContext();

			/*!
			 *	@brief		Main drawing function -- draws scene and context as available.
			 */
			void drawGL();

			/*!
			 *	@brief		Processes a mouse event.
			 *
			 *	@param		e		An SDL_Event corresponding with an appropriate SDL mouse event (button up/down, move).
			 *	@returns	A boolean indicating if a scene redraw is necessary (true)
			 *				or not (false).
			 */
			bool handleMouse( SDL_Event & e );
			
			/*!
			 *	@brief		Processes a keyboard event.
			 *
			 *	@param		e		An SDL_Event corresponding with an appropriate SDL keyboard event (key up/down).
			 *	@returns	A boolean indicating if a scene redraw is necessary (true)
			 *				or not (false).
			 */
			bool handleKeyboard( SDL_Event & e );

			/*!
			 *	@brief		Sets whether the world axis is drawn or not.
			 *
			 *	@param		state	A boolean controlling whether the world axis is drawn (true)
			 *						or not (false).
			 */
			void setDrawWorldAxis( bool state ) { _drawWorldAxis = state; }

			/*!
			 *	@brief		Reports the state of whether the world axis is drawn or not.
			 *
			 *	@returns	A boolean indicating if the world axis is drawn (true) or not (false).
			 */
			bool getDrawWorldAxis() const { return _drawWorldAxis; }

			/*!
			 *	@brief		Draws a red frame around the viewer, indicating that images
			 *				are being saved.
			 */
			void drawRecordingFrame() const;

			/*!
			 *	@brief		Sets the horizontal field of view for the ith camera.
			 *
			 *	@param		i		The index of the camera - index value is NOT checked.
			 *	@param		fov		The horizontal field of view for the indicated camera.
			 *						Value is not validated.
			 */
			void setCameraFOV( int i, float fov ) { _cameras[i].setFOV( fov ); }

			/*!
			 *	@brief		Sets the distance to the camera's far clipping plane.
			 *
			 *	@param		i		The index of the camera - index value is NOT checked.
			 *	@param		dist	The distance, from the camera, to its far clipping plane.
			 *						Value is not validated.
			 */
			void setCameraFarPlane( int i, float dist ) { _cameras[i].setFarPlane( dist ); }

			/*!
			 *	@brief		Change the scene time by the given offset.
			 *	
			 *	@param		delta	The amount of time change.  Can be negative, but only 
			 *						meaningful if the GLScene can support negative time changes.
			 */
			void offsetTime( float delta );
			/*!
			 *	@brief		Sets the current time.
			 *
			 *	@param		t		The current time for the viewer and its GLScene.
			 */
			void setTime( float t ) { _viewTime = t; };

			/*!
			 *	@brief		Sets the view's background color.
			 *				This must be called AFTER the view has been initialized.
			 *
			 *	@param		r		The red component of the background color (must be in the range [0, 1]).
			 *	@param		g		The green component of the background color (must be in the range [0, 1]).
			 *	@param		b		The blue component of the background color (must be in the range [0, 1]).
			 */
			void setBGColor( float r, float g, float b );

			/*!
			 *	@brief		Gets a pointer to the ith camera.
			 *
			 *	@param		i		The index of the desired camera.  The index value
			 *						is not checked.
			 *	@returns	A pointer to the ith camera.
			 */
			SceneGraph::GLCamera * getCamera( int i=0 ) { return &_cameras[i]; }

			/*!
			 *	@brief		Sets the simulator to use a fixed time step, with the given value.
			 *
			 *	@param		stepSize		The size of the fixed step the viewer should advance
			 *								its GLScene.
			 */
			void setFixedStep( float stepSize );
			
			/*!
			 *	@brief		Sets the path for when outputting screen capture images.
			 *
			 *	@param		path		The path to which output images should be written.
			 */
			void setDumpPath( const std::string & path );

		protected:

			//GLViewer *_view;
			/*!
			 *	@brief		The various SDL flags which determine the view.
			 */
			static Uint32 FLAGS;

			////////////////////////////////////////////////////////////////
			// members

			/*!
			 *	@brief		The SDL window for this view.
			 */
			SDL_Window * _window;

			/*!
			 *	@brief		The width of the viewer window (in pixels).
			 */
			int	_width;
			
			/*!
			 *	@brief		The height of the viewer window (in pixels).
			 */
			int _height;

			/*!
			 *	@brief		The GLScene to draw.
			 */
			SceneGraph::GLScene *	_scene;

			/*!
			 *	@brief		A set of cameras from which to draw the scene.
			 */
			std::vector< SceneGraph::GLCamera > _cameras;

			/*!
			 *	@brief		The index of camera currently being used to draw the scene.
			 */
			size_t		_currCam;

			/*!
			 *	@brief		The x-position of the mouse when a
			 *				mouse button was depressed (in screen space).
			 */
			int _downX;			
			
			/*!
			 *	@brief		The y-position of the mouse when a
			 *				mouse button was depressed (in screen space).
			 */
			int _downY;			

			// HUD/UI components

			/*!
			 *	@brief		Determines if the GLScene needs to update.
			 */
			bool	_update;

			/*!
			 *	@brief		Determines whether a world-aligned axis is drawn
			 */
			bool	_drawWorldAxis;

			/*!
			 *	@brief		Determines whether the frame rate is displayed in the viewer.
			 */
			bool	_showFPS;

			/*!
			 *	@brief		A timer to determine the displayed frame rate value.
			 */
			SampleTimer	_fpsDisplayTimer;			

			/*!
			 *	@brief		Controls whether the viewer advances the GLScene (true) or not (false).
			 */
			bool	_pause;

			/*!
			 *	@brief		Determines if the viewer should still operate -- as long as it is true, it will
			 *				continue its main loop (@see GLViewer::run).  
			 */
			bool _running;

			/*!
			 *	@brief		The current time at which the viewer is running.  Modified by calls to GLViewer::setTime and
			 *				GLViewer::offsetTime.
			 */
			float _viewTime;

			/*!
			 *	@brief		The viewer's background color.
			 */
			Menge::Math::Vector3	_bgColor;

			/*!
			 *	@brief		The step size for fixed-step simulation.
			 */
			float	_stepSize;

			/*! 
			 *	@brief		A pointer to the optional background image.
			 */
			Image	*	_bgImg;

			/*!
			 *	@brief		An optional watermark.
			 */
			Watermark	* _waterMark;

			/*!
			 *	@brief		Determines if screen capture images will be output at each time advance.
			 */
			bool	_dumpImages;

			/*!
			 *	@brief		Reports if the screen capture output path is valid.
			 */
			bool	_validDumpPath;

			/*!
			 *	@brief		The path to the folder in which to write screen capture images.
			 */
			std::string _dumpPath;

			/*!
			 *	@brief		The number of images which have been output.  Used for 
			 *				labeling the image file names into a sequential order.
			 */
			size_t _imgCount;

			/*!
			 *	@brief		The set of lights to use in rendering.
			 */
			std::vector< SceneGraph::GLLight > _lights;

			/*!
			 *	@brief		Initizlies the OpenGL lighting based on the set of lights.
			 */
			void initLighting();

			////////////////////////////////////////////////////////////////
			// methods

			/*!
			 *	@brief		Initializes the SDL mechanism for event handling and context creation.
			 */
			bool initSDL( const std::string & title );

			/*!
			 *	@brief		Draws a simple, three-color world axis at the origin of world space.
			 */
			void drawWorldAxis() const;
		};
	}	// namespace Viewer
}	// namespace MengeVis



class ExampleCameraListener : public Ogre::FrameListener
{
public:
	Ogre::Camera* _Cam;//������Ϣ
	OIS::Mouse* _mouse;//���
	OIS::InputManager* _man;
	OIS::Keyboard* _key;//����
	Ogre::Entity* _ent;//ʵ��
	Ogre::AnimationState* _aniState;//ģ�Ͷ���
	Ogre::AnimationState* _aniStateTop;

	std::vector<Ogre::AnimationState*> _aniStateArr;//�洢��ͬangent�Ķ���״̬
	std::vector<Ogre::AnimationState*> _aniStateTopArr;
	std::vector<Ogre::Entity*> _entArr; //�洢��ͬangent��ʵ��


	bool _run;//�ж��Ƿ�ֹͣ
	bool _pause = false;//��ͣ
	ExampleCameraListener(Ogre::SceneNode* node, Ogre::Entity* ent, RenderWindow* win, Ogre::Camera* cam)
	{
		//���캯��1��������ʼ��
		_run = true;
		_ent = ent;
		_aniState = _ent->getAnimationState("Walk");//����ģ��ΪWalk�Ķ���
		//_aniState = _ent->getAnimationState("RunBase");

		_aniState->setEnabled(true);//���ø�״̬
		_aniState->setLoop(true);//���ö���ѭ��

		_Cam = cam;
		size_t windowHnd = 0;
		std::stringstream windowHndStr;//���ô��ڶ���
		win->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		OIS::ParamList pl;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		//�������ͼ��̷���Ϸ��ռ(��������ʾ����Ļ�ϲ������ƶ���������)
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

		_man = OIS::InputManager::createInputSystem(pl); //�����������
		_key = static_cast<OIS::Keyboard*>(_man->createInputObject(OIS::OISKeyboard, false));//��ü��̶���
		_mouse = static_cast<OIS::Mouse*>(_man->createInputObject(OIS::OISMouse, false));//���������
	}

	ExampleCameraListener(std::vector<Ogre::Entity*>&  entARR, RenderWindow* win, Ogre::Camera* cam)
	{
		//���캯��2��ʵ����ʹ�õ��������������������ʼ��
		_run = true;
		_aniStateArr.clear();  //ÿ��ogre����֡��ʱ�����øú���
		for (int i = 0; i<entARR.size(); i++)
		{
			//ģ�Ͷ�������
			Ogre::AnimationState* n_aniState;
			//Ogre::AnimationState* n_aniStateTop;

			//n_aniState = entARR[i]->getAnimationState("RunBase");
			n_aniState = entARR[i]->getAnimationState("Walk");//��ͬ��ģ�� ����Ч��Ҳ��һ����ʳ��ħ�Ķ�����run,robot����Walk;ʳ��ħ��run��Ϊ�����������������
			n_aniState->setEnabled(true);
			n_aniState->setLoop(true);
			_aniStateArr.push_back(n_aniState);

			/*n_aniStateTop = entARR[i]->getAnimationState("RunTop");
			n_aniStateTop->setEnabled(true);
			n_aniStateTop->setLoop(true);
			_aniStateTopArr.push_back(n_aniStateTop);*/

		}
		_Cam = cam;
		size_t windowHnd = 0;
		std::stringstream windowHndStr;//���ô��ڶ���
		win->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		OIS::ParamList pl;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		//�������ͼ��̷���Ϸ��ռ(��������ʾ����Ļ�ϲ������ƶ���������)
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

		_man = OIS::InputManager::createInputSystem(pl);	//�����������
		_key = static_cast<OIS::Keyboard*>(_man->createInputObject(OIS::OISKeyboard, false));//���ü��̶���
		_mouse = static_cast<OIS::Mouse*>(_man->createInputObject(OIS::OISMouse, false));//����������
	}

	bool frameStarted(const Ogre::FrameEvent &evt)
	{   //ogreÿ�θ���֡��ʱ�򣬻���øú���������ģ�Ͷ������Լ����ܼ��̺��������
		for (int i = 0; i<_aniStateArr.size(); i++)
		{
			_aniStateArr[i]->addTime(evt.timeSinceLastFrame);//����ģ�Ͷ���
			//_aniStateTopArr[i]->addTime(evt.timeSinceLastFrame);
		}


		_mouse->capture();
		_key->capture();
		Ogre::Vector3 translate(0, 0, 0);
		if (_key->isKeyDown(OIS::KC_ESCAPE))//��������Ϊ  Esc��
		{
			_run = false;
			return false;
		}
		//if (_key->isKeyDown(OIS::KC_SPACE))//��������Ϊ  Space��
		//{
		//	_pause = TRUE;
		//}

 		if (_key->isKeyDown(OIS::KC_W))//��������Ϊ  W��
		{  
			translate += Ogre::Vector3(0, 0, -10);
		}

		if (_key->isKeyDown(OIS::KC_S))//S
		{
			translate += Ogre::Vector3(0, 0, 10);
		}
		if (_key->isKeyDown(OIS::KC_A))//A
		{
			translate += Ogre::Vector3(-10, 0, 0);
		}
		if (_key->isKeyDown(OIS::KC_D))//D
		{
			translate += Ogre::Vector3(10, 0, 0);
		}

		if (_key->isKeyDown(OIS::KC_Q))//Q
		{
			translate += Ogre::Vector3(0, 10, 0);
		}
		if (_key->isKeyDown(OIS::KC_E))//E
		{
			translate += Ogre::Vector3(0, -10, 0);
		}

		//�����������ӽ�
		float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
		float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
		_Cam->yaw(Ogre::Radian(rotX)/15);
		_Cam->pitch(Ogre::Radian(rotY)/15);
		_Cam->moveRelative(translate*evt.timeSinceLastFrame);


	}
	~ExampleCameraListener()
	{   //�ͷŶ���
		_man->destroyInputObject(_mouse);

		/*for (int i = 0; i<_aniStateTopArr.size(); i++)
			delete _aniStateTopArr[i];*/
		for (int i = 0; i<_aniStateArr.size(); i++)
			delete _aniStateArr[i];
		for (int i = 0; i<_entArr.size(); i++)
			delete _entArr[i];
		/*_aniStateTopArr.clear();*/
		_aniStateArr.clear();
		_entArr.clear();
	}
};




class ExampleOgre : public ExampleApplication
{
private:
	Ogre::SceneNode* m_Node;// �����ڵ㣺ogre �������ó����������������������������������ڵ㣬ÿ�������ڵ��Ӧogre�����һ��ģ��
	Ogre::Entity* ent;//ogre����ģ��
	ExampleCameraListener* FrameListener1; // ����֡�����࣬������������³�������ģ�͵���Ϊ��ʵ�ֶ������任�����ӽ�
public:
	Ogre::Vector3 pos;//������ �����洢 λ����Ϣ
	Ogre::Vector3 pos1;//�����������
	Ogre::Vector3 pos2;//�����������
	float nearFace;   //�����������

	std::vector<Ogre::SceneNode*> agentNode;//������ ��̬�������ڵ� agent
	std::vector<Ogre::SceneNode*> obstacleNode;//������ ��̬�������ڵ� obstacle
	std::vector<agentOgre1> NodePos;		//����������Ľṹ�����Ҵ�������������agent���ϰ���Ľṹ�壬������¼��agent���ϰ����λ����Ϣ��������GLScene.h����
	std::vector<agentOgre1> lastNodePos;	//����Ǵ洢ǰһ֡����agent��λ����Ϣ
	std::vector<Ogre::Entity*>  entARR;		//�������洢ogre���洴����ģ��
	bool run;								//�����Ƿ�ֹͣ����
	bool pause;								//�����Ƿ���ͣ����

	float Obstacle_thickness = 0.32;
	float Obstacle_hight =1.6;
public:

	ExampleOgre()
	{
		m_Node = NULL;	// ������ʼ��
		FrameListener1 = NULL;
		run = true;
	}
	~ExampleOgre()
	{
		destroyScene();// �ͷų������������	
	}
	Ogre::SceneManager* getSceneMgr(){
		return mSceneMgr;//���� ������������ָ�� 
	}
	void createScene()
	{
		//������ʼ��
		lastNodePos.clear();

		agentNode.clear();
		obstacleNode.clear();
		entARR.clear();
		// set background and some fog
		//mSceneMgr->setFog(Ogre::FOG_LINEAR, ColourValue(1.0f, 1.0f, 0.8f), 0, 15, 100);

		// set shadow properties
		mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);
		mSceneMgr->setShadowColour(ColourValue(0.5, 0.5, 0.5));
		mSceneMgr->setShadowTextureSize(1024);
		mSceneMgr->setShadowTextureCount(1);
		mSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));//���ñ�����ɫ,������

		Ogre::Vector3 _pos0 = Ogre::Vector3(0, 0, 0);//��ʼ��λ����Ϣ
		Ogre::Vector3 _pos1 = Ogre::Vector3(0, 0, 0);
		int count = 0;

		//ManualObject * circle = mSceneMgr->createManualObject("circle");

		//float const radius = 4; 
		//float const accuracy = 35;

		//circle->begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);

		//unsigned point_index = 0;

		//for (float theta = 0; theta <= 2 * Math::PI; theta += Math::PI / accuracy)

		//{

		//	circle->position(radius * cos(theta), 0, radius * sin(theta));
		//	circle->colour(4.0, 1.0, 1.0);
		//	circle->index(point_index++);

		//}

		//circle->index(0); // Rejoins the last point to the first.         

		//circle->end();

		//mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(circle);



		for (int i = 0; i<NodePos.size(); i++)// NodePos��������ݻ�������menge������£�Ȼ�������������agent���ϰ���
		{
			char str[100];
			sprintf(str, "node%d", i);
			if (NodePos[i].ID == 1)
			{	//����ģ��
				Ogre::SceneNode* node = mSceneMgr->createSceneNode();//���������ڵ�
				mSceneMgr->getRootSceneNode()->addChild(node);//�ڳ�������������ӳ������
				Ogre::Entity* ent = mSceneMgr->createEntity(str, "robot.mesh");//����ģ��  (robot.mesh)(Sinbad)
				node->attachObject(ent);//��ģ���볡�����
				node->setScale(0.018, 0.028, 0.016);//��ģ�ͽ��г߶ȱ任
				node->setPosition(NodePos[i].pos0);//����ģ��λ��
				//printf("agent[%d]λ��;x %f, y %f ,z %f\n", i, NodePos[i].pos0.x, NodePos[i].pos0.y, NodePos[i].pos0.z);
				//node->setDirection(1.0f,0.0f,0.0f);
				//node->yaw(Ogre::Degree(90.0f));
				//node->roll(Ogre::Degree(90.0f));
				
				agentNode.push_back(node);//��������ģ����ӵ�������
				entARR.push_back(ent);//��������ʵ����ӵ�������
			}
			else if (NodePos[i].ID == 0){
				//�����ϰ��� ��Ҫ������
				_pos0 = NodePos[i].pos0;// (x,Z,y)
				_pos1 = NodePos[i].pos1;
				ManualObject* cube; //�����ϰ���
				char str1[300];
				sprintf(str1, "cube%d", i);
				cube = mSceneMgr->createManualObject(str1);//�����ϰ���
				cube->begin("BaseWhiteNoLighting");//������

				// ����
				if (_pos0[0] != _pos1[0]){
					cube->position(_pos0[0], _pos0[1], _pos0[2] + Obstacle_thickness);   //0
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0], _pos1[1], _pos1[2] + Obstacle_thickness);    //1
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0], _pos1[1], _pos1[2] - Obstacle_thickness);    //2
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos0[0], _pos0[1], _pos0[2] - Obstacle_thickness);    //3
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos0[0], _pos0[1] + Obstacle_hight, _pos0[2] + Obstacle_thickness);    //4
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0], _pos1[1] + Obstacle_hight, _pos1[2] + Obstacle_thickness);    //5
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0], _pos1[1] + Obstacle_hight, _pos1[2] - Obstacle_thickness);    //6
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos0[0], _pos0[1] + Obstacle_hight, _pos0[2] - Obstacle_thickness);    //7
					cube->colour(1.0, 1.0, 1.0);
				}
				else{
				
					cube->position(_pos0[0] + Obstacle_thickness, _pos0[1], _pos0[2]);   //0
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0] + Obstacle_thickness, _pos1[1], _pos1[2]);    //1
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0] - Obstacle_thickness, _pos1[1], _pos1[2]);    //2
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos0[0] - Obstacle_thickness, _pos0[1], _pos0[2]);    //3
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos0[0] + Obstacle_thickness, _pos0[1] + Obstacle_hight, _pos0[2]);    //4
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0] + Obstacle_thickness, _pos1[1] + Obstacle_hight, _pos1[2]);    //5
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0] - Obstacle_thickness, _pos1[1] + Obstacle_hight, _pos1[2]);    //6
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos0[0] - Obstacle_thickness, _pos0[1] + Obstacle_hight, _pos0[2]);    //7
					cube->colour(1.0, 1.0, 1.0);
		
				}
				//// ����
				//cube->quad(0, 1, 2, 3);
				//cube->quad(4, 5, 6, 7);
				//cube->quad(0, 1, 7, 5);
				//cube->quad(0, 5, 4, 3);
				//cube->quad(4, 3, 2, 6);
				//cube->quad(6, 2, 1, 7);
				cube->triangle(0, 2, 1);
				cube->triangle(0, 2, 3);
				cube->triangle(3, 4, 0);
				cube->triangle(3, 7, 4);
				cube->triangle(4, 7, 6);
				cube->triangle(4, 6, 5);
				cube->triangle(5, 2, 1);
				cube->triangle(5, 6, 2);
				cube->triangle(0, 4, 1);
				cube->triangle(5, 1, 4);
				cube->triangle(3, 6, 7);
				cube->triangle(3, 2, 6);

				//ƽ���ϰ���
				//cube->position(_pos0[0], _pos0[1], _pos0[2]);    //0
				//cube->colour(1.0, 3.0, 1.0);
				//cube->position(_pos1[0], _pos1[1], _pos1[2]);    //1
				//cube->colour(1.0, 3.0, 1.0);
				//cube->position(_pos1[0], _pos1[1] + Obstacle_hight, _pos1[2]);    //2
				//cube->colour(1.0, 3.0, 1.0);
				//cube->position(_pos0[0], _pos0[1] + Obstacle_hight, _pos0[2]);    //3
				//cube->colour(1.0, 3.0, 1.0);
				//cube->quad(0, 1, 2, 3);
				
				cube->end();//�ϰ��ﴴ�����
				char str[300];
				sprintf(str, "wall%d", i);
				cube->convertToMesh(str);//�ϰ�������ת��,ת����mesh�ļ�
				Ogre::Entity * entw = mSceneMgr->createEntity(str);//����mesh�ļ�����ʵ��
				entw->setMaterialName("Examples/Rockwall");//����ʵ�����
				SceneNode* sn = mSceneMgr->getRootSceneNode()->createChildSceneNode();//���������������������
				sn->attachObject(entw);//�󶨽���ʵ��

			
				count = 0;
				obstacleNode.push_back(sn);
			}
			else if (NodePos[i].ID == 3){

				//�������������Ҫ�����
				std::vector<Ogre::Vector3> pos = NodePos[i].pos3;
				int size = pos.size();
				if (size==4){
					for (int j = 0; j< size - 3; j++){

						//MaterialPtr material = MaterialManager::getSingletonPtr()->create("q", "General");
						//material->getTechnique(0)->getPass(0)->createTextureUnitState("Dirt.jpg");
						ManualObject* cube; //�����ϰ���
						char str1[300];
						sprintf(str1, "cube%d+%d", i, j);
						cube = mSceneMgr->createManualObject(str1);//�����ϰ���
						//cube->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_FAN);//������
						cube->begin("cubeMaterial");
						cube->position(pos[j][0], pos[j][1], pos[j][2]);   //0
						cube->colour(0.0, 0.0, 0.0);

						cube->position(pos[j + 1][0], pos[j + 1][1], pos[j + 1][2]);   //1
						cube->colour(0.0, 0.0, 0.0);

						cube->position(pos[j + 2][0], pos[j + 2][1], pos[j + 2][2]);   //2
						cube->colour(0.0, 0.0, 0.0);

						cube->position(pos[j + 3][0], pos[j + 3][1], pos[j + 3][2]);   //3
						cube->colour(0.0, 0.0, 0.0);

						cube->position(pos[j][0], pos[j][1] + 0.01, pos[j][2]);   //4
						cube->colour(0.0, 0.0, 0.0);
						cube->position(pos[j + 1][0], pos[j + 1][1] + 0.01, pos[j + 1][2]);   //5
						cube->colour(0.0, 0.0, 0.0);
						cube->position(pos[j + 2][0], pos[j + 2][1] + 0.01, pos[j + 2][2]);   //6
						cube->colour(0.0, 0.0, 0.0);
						cube->position(pos[j + 3][0], pos[j + 3][1] +0.01, pos[j + 3][2]);   //7
						cube->colour(0.0, 0.0, 0.0);
						////// ����
						//cube->triangle(0, 1, 2);
						//cube->triangle(0, 2, 3);
						//cube->triangle(3, 4, 0);
						//cube->triangle(3, 7, 4);
						//cube->triangle(4, 7, 6);
						//cube->triangle(4, 6, 5);
						//cube->triangle(5, 2, 1);
						//cube->triangle(5, 6, 2);
						//cube->triangle(0, 4, 1);
						//cube->triangle(5, 1, 4);
						//cube->triangle(3, 6, 7);
						//cube->triangle(3, 2, 6);
						cube->quad(0, 1, 2, 3);
						cube->quad(0, 4, 7, 3);
						cube->quad(4, 5, 6, 7);
						cube->quad(5, 1, 2, 6);
						cube->quad(4, 5, 1, 0);
						cube->quad(7, 6, 2, 3);
						cube->end();//���洴�����
						char str[300];
						sprintf(str, "wall%d+%d", i, j);
						cube->convertToMesh(str);//�ϰ�������ת��,ת����mesh�ļ�
						Ogre::Entity * entw = mSceneMgr->createEntity(str);//����mesh�ļ�����ʵ��
						SceneNode* sn = mSceneMgr->getRootSceneNode()->createChildSceneNode();//���������������������
						sn->attachObject(cube);//�󶨽���ʵ��

						entw->setMaterialName("Examples/Rockwall");//����ʵ�����

					}
				}
				else if (size==3)
				{
					for (int j = 0; j< size - 2; j++){
						ManualObject* cube; //�����ϰ���
						char str1[300];
						sprintf(str1, "cube%d+%d", i, j);
						cube = mSceneMgr->createManualObject(str1);//�����ϰ���
						cube->begin("cubeMaterial");//������

						cube->position(pos[j][0], pos[j][1], pos[j][2]);   //0
						cube->colour(0.0, 0.0, 0.0);

						cube->position(pos[j + 1][0], pos[j + 1][1], pos[j + 1][2]);   //1
						cube->colour(0.0, 0.0, 0.0);

						cube->position(pos[j + 2][0], pos[j + 2][1], pos[j + 2][2]);   //2
						cube->colour(0.0, 0.0, 0.0);

						cube->triangle(0, 1, 2);
						//cube->position(pos[j][0], pos[j][1] + 1, pos[j][2]);   //3
						//cube->colour(0.0, 0.0, 0.0);
						//cube->position(pos[j + 1][0], pos[j + 1][1] + 1, pos[j + 1][2]);   //4
						//cube->colour(0.0, 0.0, 0.0);
						//cube->position(pos[j + 2][0], pos[j + 2][1] + 1, pos[j + 2][2]);   //5
						//cube->colour(0.0, 0.0, 0.0);				
						////// ����
						//cube->triangle(2, 5, 1);
						//cube->triangle(2, 1, 4);
						//cube->triangle(3, 5, 4);
						//cube->triangle(0, 2, 1);
						//cube->triangle(0, 5, 3);
						//cube->triangle(0, 5, 2);
						//cube->triangle(0, 4, 1);
						//cube->triangle(0, 3, 4);

						cube->end();//���洴�����
						char str[300];
						sprintf(str, "wall%d+%d", i, j);
						cube->convertToMesh(str);//�ϰ�������ת��,ת����mesh�ļ�
						Ogre::Entity * entw = mSceneMgr->createEntity(str);//����mesh�ļ�����ʵ��
						SceneNode* sn = mSceneMgr->getRootSceneNode()->createChildSceneNode();//���������������������
						sn->attachObject(cube);//�󶨽���ʵ��

						entw->setMaterialName("Examples/Rockwall");//����ʵ�����

					}

				}
				


			}

		}

		//�������汳��
		Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -0.001);//����ƽ�����

		Ogre::MeshManager::getSingleton().createPlane("plane",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			plane, 200, 200, 20, 20, true, 1, 40, 40, Ogre::Vector3::UNIT_Z);//����ƽ�����Ϣ

		Ogre::Entity* ent1 = mSceneMgr->createEntity("LightPlaneEntity", "plane");//����ƽ�����,����ƽ��ʵ��
		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent1);//��ģ���볡�����,�����˵�����������
		//ent1->setMaterialName("Examples/Rockwall");//���ò���
		
		ent1->setMaterialName("Examples/GrassFloor");//���ò���


		////����ʮ��·�������·
		//Ogre::Plane plane1(Ogre::Vector3::UNIT_Y, 0.006);//Y �Ƿ���
		//Ogre::MeshManager::getSingleton().createPlane("plane1",
		//	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		//	plane1, 4, 200, 50, 50, true, 1, 10, 150, Ogre::Vector3::UNIT_Z);//Z ��ƽ�����췽��
		//Ogre::Entity* ent2 = mSceneMgr->createEntity("LightPlaneEntity1", "plane1");
		//ent2->setMaterialName("Examples/RustySteel");
		//Ogre::SceneNode* node2 = mSceneMgr->createSceneNode();
		//mSceneMgr->getRootSceneNode()->addChild(node2);
		//node2->attachObject(ent2);
		//node2->setPosition(0, 0.006, 0);

		////����ʮ��·�ں����·
		//Ogre::Plane plane2(Ogre::Vector3::UNIT_Y, 0.015);
		//Ogre::MeshManager::getSingleton().createPlane("plane2",
		//	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		//	plane1, 200, 4, 50, 50, true, 1, 150, 10, Ogre::Vector3::UNIT_Z);
		//Ogre::Entity* ent3 = mSceneMgr->createEntity("LightPlaneEntity2", "plane2");
		//Ogre::SceneNode* node3 = mSceneMgr->createSceneNode();
		//mSceneMgr->getRootSceneNode()->addChild(node3);
		//node3->attachObject(ent3);
		//ent3->setMaterialName("Examples/RustySteel");
		//node3->setPosition(0, 0.015, 0);
		//  ��ת��
		//pitch --- X
		//yaw   --- Y
		//roll  --- Z

		//����ʮ��·��O-G��·
		//Ogre::Plane plane3(Ogre::Vector3::UNIT_Y, 0.008);
		//Ogre::MeshManager::getSingleton().createPlane("plane3",
		//	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		//	plane1, 4, 200, 50, 50, true, 1, 10, 150, Ogre::Vector3::UNIT_Z);
		//Ogre::Entity* ent4 = mSceneMgr->createEntity("LightPlaneEntity3", "plane3");
		//ent4->setMaterialName("Examples/RustySteel");
		//Ogre::SceneNode* node4 = mSceneMgr->createSceneNode();
		//node4->yaw(Ogre::Degree(45.0f));
		//mSceneMgr->getRootSceneNode()->addChild(node4);
		//node4->attachObject(ent4);
		//node4->setPosition(0, 0.008, 0);
		


		//�����ƹ�Ч��
		Ogre::Light* light = mSceneMgr->createLight("Light1");//������Դ
		light->setType(Ogre::Light::LT_DIRECTIONAL);//���ù�Դ����
		light->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
		light->setDirection(Ogre::Vector3(1, -1, 0));

		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);//������ӰЧ��

		//�������
		mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
		//mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox", 5000, false);//�������Ч��
	}

	void createCamera()
	{//�������
		mCamera = mSceneMgr->createCamera("MyCamera1");
		//mCamera->setPosition(Ogre::Vector3(pos[0], pos[1], pos[2]));
		//mCamera->lookAt(Ogre::Vector3(pos1[0], pos1[1], pos1[2]));
		mCamera->setNearClipDistance(nearFace);
		mCamera->setPosition(Ogre::Vector3(0, 0, 0));
		mCamera->lookAt(Ogre::Vector3(0, 0, -300));
		//mCamera->setNearClipDistance(1);
	}


	void createFrameListener()
	{//����֡����
		if (mCamera == NULL)  printf("\n\n pause");

		FrameListener1 = new ExampleCameraListener(entARR, mWindow, mCamera); //����֡��������ogreÿ�θ���֡��ʱ�򣬶������֡��������ĺ���
		mRoot->addFrameListener(FrameListener1);//��֡��������뵽���ڵ�����
	}


	void show()
	{//ogre��ʼ��
		if (!setup())//ogre��ʼ��,����������Դ�ļ�
			return;
	}

	void repeatRun()
	{	//����agent��λ�ã����»��Ƴ���
		if (!(FrameListener1->_run))
			run = false;//�ж��Ƿ�ֹͣ����ͼ��
		//pause = FrameListener1->_pause;//�ж��Ƿ�ֹͣ����ͼ��
		//if (pause)return;
		for (int i = 0; i<NodePos.size(); i++)
		if (NodePos[i].ID == 1)
		{
			agentNode[i]->setPosition(NodePos[i].pos0);//����ģ��λ����Ϣ
			//printf("����agent[%d]λ��;x %f, y %f ,z %f\n", i, NodePos[i].pos0.x, NodePos[i].pos0.y, NodePos[i].pos0.z);
		}
		//int newObstacleCount = NodePos.size() - lastNodePos.size();
		Ogre::Vector3 _pos0 = Ogre::Vector3(0, 0, 0);//��ʼ��λ����Ϣ
		Ogre::Vector3 _pos1 = Ogre::Vector3(0, 0, 0);
		int i = agentNode.size() + obstacleNode.size();
		for ( ; i<NodePos.size(); i++)// NodePos��������ݻ�������menge������£�Ȼ�������������agent���ϰ���
		{
			char str[100];
			sprintf(str, "node%d", i);
			if (NodePos[i].ID == 1)
			{	//����ģ��
				Ogre::SceneNode* node = mSceneMgr->createSceneNode();//���������ڵ�
				mSceneMgr->getRootSceneNode()->addChild(node);//�ڳ�������������ӳ������
				Ogre::Entity* ent = mSceneMgr->createEntity(str, "robot.mesh");//����ģ��  (robot.mesh)(Sinbad)
				node->attachObject(ent);//��ģ���볡�����
				node->setScale(0.018, 0.028, 0.016);//��ģ�ͽ��г߶ȱ任
				node->setPosition(NodePos[i].pos0);//����ģ��λ��
				//printf("agent[%d]λ��;x %f, y %f ,z %f\n", i, NodePos[i].pos0.x, NodePos[i].pos0.y, NodePos[i].pos0.z);
				//node->setDirection(1.0f,0.0f,0.0f);
				//node->yaw(Ogre::Degree(90.0f));
				//node->roll(Ogre::Degree(90.0f));

				agentNode.push_back(node);//��������ģ����ӵ�������
				entARR.push_back(ent);//��������ʵ����ӵ�������
			}
			else if (NodePos[i].ID == 0){
				//�����ϰ��� ��Ҫ������
				_pos0 = NodePos[i].pos0;// (x,Z,y)
				_pos1 = NodePos[i].pos1;
				ManualObject* cube; //�����ϰ���
				char str1[300];
				sprintf(str1, "cube%d", i);
				cube = mSceneMgr->createManualObject(str1);//�����ϰ���
				cube->begin("BaseWhiteNoLighting");//������

				// ����
				if (_pos0[0] != _pos1[0]){
					cube->position(_pos0[0], _pos0[1], _pos0[2] + Obstacle_thickness);   //0
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0], _pos1[1], _pos1[2] + Obstacle_thickness);    //1
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0], _pos1[1], _pos1[2] - Obstacle_thickness);    //2
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos0[0], _pos0[1], _pos0[2] - Obstacle_thickness);    //3
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos0[0], _pos0[1] + Obstacle_hight, _pos0[2] + Obstacle_thickness);    //4
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0], _pos1[1] + Obstacle_hight, _pos1[2] + Obstacle_thickness);    //5
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0], _pos1[1] + Obstacle_hight, _pos1[2] - Obstacle_thickness);    //6
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos0[0], _pos0[1] + Obstacle_hight, _pos0[2] - Obstacle_thickness);    //7
					cube->colour(1.0, 1.0, 1.0);
				}
				else{

					cube->position(_pos0[0] + Obstacle_thickness, _pos0[1], _pos0[2]);   //0
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0] + Obstacle_thickness, _pos1[1], _pos1[2]);    //1
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0] - Obstacle_thickness, _pos1[1], _pos1[2]);    //2
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos0[0] - Obstacle_thickness, _pos0[1], _pos0[2]);    //3
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos0[0] + Obstacle_thickness, _pos0[1] + Obstacle_hight, _pos0[2]);    //4
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0] + Obstacle_thickness, _pos1[1] + Obstacle_hight, _pos1[2]);    //5
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos1[0] - Obstacle_thickness, _pos1[1] + Obstacle_hight, _pos1[2]);    //6
					cube->colour(1.0, 1.0, 1.0);
					cube->position(_pos0[0] - Obstacle_thickness, _pos0[1] + Obstacle_hight, _pos0[2]);    //7
					cube->colour(1.0, 1.0, 1.0);

				}
				//// ����
				//cube->quad(0, 1, 2, 3);
				//cube->quad(4, 5, 6, 7);
				//cube->quad(0, 1, 7, 5);
				//cube->quad(0, 5, 4, 3);
				//cube->quad(4, 3, 2, 6);
				//cube->quad(6, 2, 1, 7);
				cube->triangle(0, 2, 1);
				cube->triangle(0, 2, 3);
				cube->triangle(3, 4, 0);
				cube->triangle(3, 7, 4);
				cube->triangle(4, 7, 6);
				cube->triangle(4, 6, 5);
				cube->triangle(5, 2, 1);
				cube->triangle(5, 6, 2);
				cube->triangle(0, 4, 1);
				cube->triangle(5, 1, 4);
				cube->triangle(3, 6, 7);
				cube->triangle(3, 2, 6);

				//ƽ���ϰ���
				//cube->position(_pos0[0], _pos0[1], _pos0[2]);    //0
				//cube->colour(1.0, 3.0, 1.0);
				//cube->position(_pos1[0], _pos1[1], _pos1[2]);    //1
				//cube->colour(1.0, 3.0, 1.0);
				//cube->position(_pos1[0], _pos1[1] + Obstacle_hight, _pos1[2]);    //2
				//cube->colour(1.0, 3.0, 1.0);
				//cube->position(_pos0[0], _pos0[1] + Obstacle_hight, _pos0[2]);    //3
				//cube->colour(1.0, 3.0, 1.0);
				//cube->quad(0, 1, 2, 3);

				cube->end();//�ϰ��ﴴ�����
				char str[300];
				sprintf(str, "wall%d", i);
				cube->convertToMesh(str);//�ϰ�������ת��,ת����mesh�ļ�
				Ogre::Entity * entw = mSceneMgr->createEntity(str);//����mesh�ļ�����ʵ��
				entw->setMaterialName("Examples/Rockwall");//����ʵ�����
				SceneNode* sn = mSceneMgr->getRootSceneNode()->createChildSceneNode();//���������������������
				sn->attachObject(entw);//�󶨽���ʵ��
				obstacleNode.push_back(sn);
			}
			else if (NodePos[i].ID == 3){

				//�������������Ҫ�����
				std::vector<Ogre::Vector3> pos = NodePos[i].pos3;
				int size = pos.size();
				if (size == 4){
					for (int j = 0; j< size - 3; j++){

						//MaterialPtr material = MaterialManager::getSingletonPtr()->create("q", "General");
						//material->getTechnique(0)->getPass(0)->createTextureUnitState("Dirt.jpg");
						ManualObject* cube; //�����ϰ���
						char str1[300];
						sprintf(str1, "cube%d+%d", i, j);
						cube = mSceneMgr->createManualObject(str1);//�����ϰ���
						//cube->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_FAN);//������
						cube->begin("cubeMaterial");
						cube->position(pos[j][0], pos[j][1], pos[j][2]);   //0
						cube->colour(0.0, 0.0, 0.0);

						cube->position(pos[j + 1][0], pos[j + 1][1], pos[j + 1][2]);   //1
						cube->colour(0.0, 0.0, 0.0);

						cube->position(pos[j + 2][0], pos[j + 2][1], pos[j + 2][2]);   //2
						cube->colour(0.0, 0.0, 0.0);

						cube->position(pos[j + 3][0], pos[j + 3][1], pos[j + 3][2]);   //3
						cube->colour(0.0, 0.0, 0.0);

						cube->position(pos[j][0], pos[j][1] + 0.01, pos[j][2]);   //4
						cube->colour(0.0, 0.0, 0.0);
						cube->position(pos[j + 1][0], pos[j + 1][1] + 0.01, pos[j + 1][2]);   //5
						cube->colour(0.0, 0.0, 0.0);
						cube->position(pos[j + 2][0], pos[j + 2][1] + 0.01, pos[j + 2][2]);   //6
						cube->colour(0.0, 0.0, 0.0);
						cube->position(pos[j + 3][0], pos[j + 3][1] + 0.01, pos[j + 3][2]);   //7
						cube->colour(0.0, 0.0, 0.0);
						////// ����
						//cube->triangle(0, 1, 2);
						//cube->triangle(0, 2, 3);
						//cube->triangle(3, 4, 0);
						//cube->triangle(3, 7, 4);
						//cube->triangle(4, 7, 6);
						//cube->triangle(4, 6, 5);
						//cube->triangle(5, 2, 1);
						//cube->triangle(5, 6, 2);
						//cube->triangle(0, 4, 1);
						//cube->triangle(5, 1, 4);
						//cube->triangle(3, 6, 7);
						//cube->triangle(3, 2, 6);
						cube->quad(0, 1, 2, 3);
						cube->quad(0, 4, 7, 3);
						cube->quad(4, 5, 6, 7);
						cube->quad(5, 1, 2, 6);
						cube->quad(4, 5, 1, 0);
						cube->quad(7, 6, 2, 3);
						cube->end();//���洴�����
						char str[300];
						sprintf(str, "wall%d+%d", i, j);
						cube->convertToMesh(str);//�ϰ�������ת��,ת����mesh�ļ�
						Ogre::Entity * entw = mSceneMgr->createEntity(str);//����mesh�ļ�����ʵ��
						SceneNode* sn = mSceneMgr->getRootSceneNode()->createChildSceneNode();//���������������������
						sn->attachObject(cube);//�󶨽���ʵ��

						entw->setMaterialName("Examples/Rockwall");//����ʵ�����

					}
				}
				else if (size == 3)
				{
					for (int j = 0; j< size - 2; j++){
						ManualObject* cube; //�����ϰ���
						char str1[300];
						sprintf(str1, "cube%d+%d", i, j);
						cube = mSceneMgr->createManualObject(str1);//�����ϰ���
						cube->begin("cubeMaterial");//������

						cube->position(pos[j][0], pos[j][1], pos[j][2]);   //0
						cube->colour(0.0, 0.0, 0.0);

						cube->position(pos[j + 1][0], pos[j + 1][1], pos[j + 1][2]);   //1
						cube->colour(0.0, 0.0, 0.0);

						cube->position(pos[j + 2][0], pos[j + 2][1], pos[j + 2][2]);   //2
						cube->colour(0.0, 0.0, 0.0);

						cube->triangle(0, 1, 2);
						//cube->position(pos[j][0], pos[j][1] + 1, pos[j][2]);   //3
						//cube->colour(0.0, 0.0, 0.0);
						//cube->position(pos[j + 1][0], pos[j + 1][1] + 1, pos[j + 1][2]);   //4
						//cube->colour(0.0, 0.0, 0.0);
						//cube->position(pos[j + 2][0], pos[j + 2][1] + 1, pos[j + 2][2]);   //5
						//cube->colour(0.0, 0.0, 0.0);				
						////// ����
						//cube->triangle(2, 5, 1);
						//cube->triangle(2, 1, 4);
						//cube->triangle(3, 5, 4);
						//cube->triangle(0, 2, 1);
						//cube->triangle(0, 5, 3);
						//cube->triangle(0, 5, 2);
						//cube->triangle(0, 4, 1);
						//cube->triangle(0, 3, 4);

						cube->end();//���洴�����
						char str[300];
						sprintf(str, "wall%d+%d", i, j);
						cube->convertToMesh(str);//�ϰ�������ת��,ת����mesh�ļ�
						Ogre::Entity * entw = mSceneMgr->createEntity(str);//����mesh�ļ�����ʵ��
						SceneNode* sn = mSceneMgr->getRootSceneNode()->createChildSceneNode();//���������������������
						sn->attachObject(cube);//�󶨽���ʵ��

						entw->setMaterialName("Examples/Rockwall");//����ʵ�����

					}

				}



			}

		}
			

		if (lastNodePos.size() != 0)
		{
			
			for (int i = 0; i<NodePos.size(); i++)
			if (NodePos[i].ID == 1){ //����ģ�͵��˶�����,��ģ����ת,��֤�˶�������ģ�ͳ���һ��
				Ogre::Vector3 mDirection = NodePos[i].pos0 - lastNodePos[i].pos0;
				mDirection.y = 0;//��ֹ��ά��ת,ֻ��ˮƽ������ת
				//modelNode[i]->setDirection(1.0f, 0.0f, 0.0f);
				//Ogre::Vector3 src = modelNode[i]->getOrientation() * Ogre::Vector3::UNIT_X;
				//Ogre::Quaternion quat = src.getRotationTo(mDirection);
				//modelNode[i]->rotate(quat);
				//modelNode[i]->yaw(Ogre::Degree(90.0f));


				Ogre::Vector3 src = agentNode[i]->getOrientation() * Ogre::Vector3::UNIT_X;

				if ((1.0 + src.dotProduct(mDirection)) < 0.0001)
				{
					agentNode[i]->yaw(Ogre::Degree(180));
				}
				else
				{
					Ogre::Quaternion quat = src.getRotationTo(mDirection);
					agentNode[i]->rotate(quat);
				}
			}
			lastNodePos.assign(NodePos.begin(), NodePos.end());//��ģ�� �ɵ�λ����Ϣ�洢��lastNodePos����
		}
		else lastNodePos.assign(NodePos.begin(), NodePos.end());
		mRoot->renderOneFrame();//���»���һ֡
	}
};





#endif  // __GLVIEWER_H__
