#include "BaseApplication.h"

class MyClass : public BaseApplication
{
public:
	MyClass(void) { }
	virtual ~MyClass(void) { }
protected:
	virtual void createScene(void);
};

void MyClass::createScene(void)
{
	// shadow
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));

	// light and light sphere
	Ogre::Light* pointLight1 = mSceneMgr->createLight("pointLight1");
	pointLight1->setType(Ogre::Light::LT_POINT);
	pointLight1->setDiffuseColour(Ogre::ColourValue::White);
	pointLight1->setSpecularColour(Ogre::ColourValue::White);

	Ogre::Entity* sphereEnt = mSceneMgr->createEntity("MyEntity", "sphere.mesh");
	Ogre::SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("LightNode");
	lightNode->attachObject(sphereEnt);
	lightNode->setScale(0.1f, 0.1f, 0.1f);
	sphereEnt->setMaterialName("BaseWhiteNoLighting");

	Ogre::Vector3 lightPosition(0, 500, 150);
	lightNode->setPosition(lightPosition);
	pointLight1->setPosition(lightPosition);

	// Ninja
	Ogre::Entity* entNinja = mSceneMgr->createEntity("Ninja", "ninja.mesh");
	entNinja->setCastShadows(true);
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);

	// ground
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("Examples/Rockwall");
	entGround->setCastShadows(false);

	// set camera position
	mCamera->setPosition(100, 200, -300);
	mCamera->lookAt(0, 100, 0);
}

int main(int argc, char *argv[])
{
	// Create application object
	MyClass app;

	try{
		app.go();
	}
	catch (Ogre::Exception& e){
		std::cerr << "An exception has occured: " <<
			e.getFullDescription().c_str() << std::endl;
	}
	return 0;
}