////////////////////////////////////////
//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
////////////////////////////////////////
// Student Name: Â²¥ß­õ
// Student ID: 0316235
// Student Email: richad85014@hotmail.com
//
////////////////////////////////////////
// You can delete everything and start from scratch.
////////////////////////////////////////

#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace Ogre;

const float PI = 3.141592654;
float time_step = 0;
int pengiunState = 0; // 0 down  1 up
bool zero_flag = false;

BasicTutorial_00::BasicTutorial_00(void) {}

void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");
	mSceneMgrArr[1] = mRoot
		->createSceneManager(ST_GENERIC, "secondary");
}

void BasicTutorial_00::createCamera_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(120,300,600));
	mCamera->lookAt(Ogre::Vector3(120,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void)
{
	// add your own stuff
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("SceneTwoCam");
	mCamera->setPosition(Ogre::Vector3(0, 350, 0.001));
	mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	mCamera->setNearClipDistance(5);
}


void BasicTutorial_00::createViewport_00(void)
{
	mCamera = mCameraArr[0];
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0.0,1.0));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    mViewportArr[0] = vp;
}

void BasicTutorial_00::createViewport_01(void)
{
    // add your own stuff
	mCamera = mCameraArr[1];
	Ogre::Viewport* vp = mWindow->addViewport(mCamera,1,0.75,0,0.25,0.25);
	vp->setOverlaysEnabled(false);
	vp->setBackgroundColour(Ogre::ColourValue(0,0.0,1.0));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    mViewportArr[1] = vp;
}

void BasicTutorial_00::createScene_00(void) 
{
	mSceneMgr = mSceneMgrArr[0];
	int numCubes = 72;
	int L = 255;

    // add your own stuff
	Plane plane(Vector3::UNIT_Y, 0);
	Plane plane1(Vector3::UNIT_Z,0);

	MeshManager::getSingleton().createPlane(
		"ground",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500,1500, // width, height
		20,20, // x- and y-segments
		true, // normal
		1, // num texture sets
		5,5, // x- and y-tiles
		Vector3::UNIT_Z // upward vector
	); 

	 MeshManager::getSingleton().createPlane(
		"wall",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane1,
		1500,1500,
		20,20,
		true,
		1,
		5,5,
		Vector3::UNIT_Y
	);

	mSceneMgr->setAmbientLight(ColourValue(0.5,0.5,0.5));
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	Entity* entPenguin1 = mSceneMgr->createEntity("Pengiun1","penguin.mesh");
	Entity* entPenguin2 = mSceneMgr->createEntity("Pengiun2","penguin.mesh");
	
	Entity* cube1 = mSceneMgr->createEntity("Cube1","cube.mesh");
	Entity* cube2 = mSceneMgr->createEntity("Cube2","cube.mesh");
	Entity* fish = mSceneMgr->createEntity("Fish","fish.mesh");

	Entity* entPlane1 = mSceneMgr->createEntity("Ground","ground");
	Entity* entPlane2 = mSceneMgr->createEntity("Wall", "wall");
	entPlane2->setCastShadows(false);
	entPlane2->setMaterialName("Examples/Rockwall");

	SceneNode *node0 = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode();

	SceneNode *node1 = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(
			"PengiunNode",
            Vector3(100.0, 50.0, 100.0));

	SceneNode *node2 = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(
            Vector3(150.0, 20.0, 0.0));

	 SceneNode *node3 = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode();

	 SceneNode *node4 = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode("CubeNode");

	 SceneNode *node5 = node4
		->createChildSceneNode();
	 
	 SceneNode *node6 = node5
		->createChildSceneNode();
	 

	 node5 -> translate(Vector3(0,50,0));
	 node5->scale(Vector3(0.5,0.5,0.5));
	 node6->scale(Vector3(5,5,5));
	 
	 node6 -> translate(Vector3(0,100,0));

	 node4->attachObject(cube1);
	 node5->attachObject(cube2);
	 node6->attachObject(fish);

	node1 -> scale(2,3,2);
	node2 -> yaw(Degree(-90));
	node3 -> setPosition(0,0,-750);
	node0 -> attachObject(entPlane1);
	node1 -> attachObject(entPenguin1);
	node3 -> attachObject(entPlane2);
	node2 -> attachObject(entPenguin2);

    Light *light = mSceneMgr -> createLight("Light1");
	light->setType(Light::LT_POINT);
	light->setPosition(Vector3(150, 250, 100));
	light->setDiffuseColour(0.0, 1.0, 0.0);
	light->setSpecularColour(0.0, 1.0, 0.0);
	Light *light2 = mSceneMgr -> createLight("Light2");
	light2->setType(Light::LT_POINT);
	light2->setPosition(Vector3(-150, 300, 250));
	light2->setDiffuseColour(0.5, 0.5, 0.5);
	light2->setSpecularColour(0.5, 0.5, 0.5);

}

void BasicTutorial_00::createScene_01(void) 
{
    // add your own stuff
	mSceneMgr = mSceneMgrArr[1];
	mSceneMgr->setAmbientLight(ColourValue(0,0,0));
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

	Light *light = mSceneMgr -> createLight("Light3");
	light->setType(Light::LT_POINT);
	light->setPosition(Vector3(100, 150, 250));
	light->setDiffuseColour(0.0, 0.0, 1.0); //blue
	light->setSpecularColour(0.0,0.0, 1.0); //blue

	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"plane",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500,1500, // width, height
		20,20, // x- and y-segments
		true, // normal
		1, // num texture sets
		5,5, // x- and y-tiles
		Vector3::UNIT_Z // upward vector
	); 
	Entity* entPlane = mSceneMgr->createEntity("Plane","plane");
	Entity* ent = mSceneMgr->createEntity("Cube","cube.mesh");
	ent->setMaterialName("Examples/green");

	SceneNode *node = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode();

	SceneNode *node1 = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(
            Vector3(50.0, 0.0, 0.0));

	node1 -> scale(0.5,0.5,0.5);
	node -> attachObject(entPlane);
	node1 -> attachObject(ent);
}

void BasicTutorial_00::createViewports(void)
{
    //Do not modify
	createViewport_00();
	createViewport_01();
}

void BasicTutorial_00::createCamera(void) {
    //Do not modify
	createCamera_00();
	createCamera_01();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
}

void BasicTutorial_00::createScene( void ) {
    //Do not modify
	createScene_00();
	createScene_01();
	//mSceneMgr = mSceneMgrArr[0]; // active SceneManager
	mSceneMgr = mSceneMgrArr[1]; // active SceneManager
    //
    mCamera = mCameraArr[0];
    //mCamera = mCameraArr[1];
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
//
// To find out the answer:
// Go to see the definition of KeyEvent
//
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyPressed ***\n";
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    
    if (arg.key == OIS::KC_C ) {
        
        ss.str("");
        ss.clear();
        
        Vector3 pos = mCameraMan->getCamera()->getPosition(); 
        ss << std::fixed << std::setprecision(2) 
            << "CameraPosition:" 
            << pos.x << "\t" 
            << pos.y << "\t" 
            << pos.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        //
        ss.str("");
        ss.clear();
        Vector3 dir = mCameraMan->getCamera()->getDirection();
        ss << std::fixed << std::setprecision(2) 
            << "CameraDirection:" 
            << dir.x << "\t" 
            << dir.y << "\t" 
            << dir.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
    }

    if (arg.key == OIS::KC_1 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(98.14,	450.69,	964.20));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.01,	-0.30,	-0.95));
    }

    if (arg.key == OIS::KC_2 ) {
        // add your own stuff
		mCameraMan->getCamera()
            ->setPosition(Vector3(-1463.00,	606.45,	-513.24));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.88, -0.47,	0.10));
    }

    if (arg.key == OIS::KC_3 ) {
        // add your own stuff
		mCameraMan->getCamera()
            ->setPosition(Vector3(-1356.16,	634.32,	-964.51));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.71,	-0.44,	0.55));
    }

    if (arg.key == OIS::KC_4 ) {
         // add your own stuff
		mCameraMan->getCamera()
            ->setPosition(Vector3(40.39,	155.23,	251.20));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.02,	-0.41,	-0.91));
    }

    if (arg.key == OIS::KC_5 ) {
        // add your own stuff
		mCameraMan->getCamera()
            ->setPosition(Vector3(19.94,	822.63,	30.79));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.00,	-0.99,	-0.11));
    }

    if (arg.key == OIS::KC_M ) {
        
       Camera *cam1 = mCameraArr[0];
	   Camera *cam2 = mCameraArr[1];

       mWindow->removeViewport(mViewportArr[0]->getZOrder());
	   mWindow->removeViewport(mViewportArr[1]->getZOrder());
	Ogre::Viewport* vp = mWindow->addViewport(cam2);
	vp->setOverlaysEnabled(false);
	vp->setBackgroundColour(Ogre::ColourValue(0,0.0,1.0));
	cam2->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    mViewportArr[1] = vp;

	vp = mWindow->addViewport(
		cam1,
		1,
		0,
		0,
		0.5,
		0.2);
	vp->setBackgroundColour(Ogre::ColourValue(0,0.5,0.0));
	cam1->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	    mViewportArr[0] = vp;          
    }

    if (arg.key == OIS::KC_N ) {
        // add your own stuff
	   Camera *cam1 = mCameraArr[0];
	   Camera *cam2 = mCameraArr[1];

       mWindow->removeViewport(mViewportArr[0]->getZOrder());
	   mWindow->removeViewport(mViewportArr[1]->getZOrder());
	Ogre::Viewport* vp = mWindow->addViewport(cam2,
		1,
		0.5,
		0.3,
		0.5,
		0.2);
	vp->setOverlaysEnabled(false);
	vp->setBackgroundColour(Ogre::ColourValue(0,0.0,1.0));
	cam2->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    mViewportArr[1] = vp;    

	vp = mWindow->addViewport(cam1);
	vp->setBackgroundColour(Ogre::ColourValue(1.0,0.0,0.0));
	cam1->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	mViewportArr[0] = vp;     
    }

	if (arg.key == OIS::KC_0 ) {
		switch(zero_flag){
			case true:
				zero_flag = false;
				break;
			case false:
				zero_flag = true;
				break;
		}
	}

    // Do not delete this line
    BaseApplication::keyPressed(arg);

    return flg;
}


bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyReleased ***\n";
    
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    BaseApplication::keyReleased(arg);

    return flg;
}

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
    // add your own stuff
	if (zero_flag){
		mSceneMgr = mSceneMgrArr[0];
		Entity* pengiun = mSceneMgr->getEntity("Pengiun1");
		SceneNode *node1 = mSceneMgr
			->getSceneNode("PengiunNode");

		SceneNode *node2 = mSceneMgr
			->getSceneNode("CubeNode");

		node2->yaw(Degree(0.1));

		Vector3 position = node1->getPosition();

		if (!pengiunState){
			position = move_down(position, time_step);
			if (position.y < 0){
				time_step = 0;
				pengiunState = 1;
			}
		}

		else if (pengiunState){
			position = move_up(position, time_step);
			if (position.y > 280){
				time_step = 0;
				pengiunState = 0;
			}
		}

		node1->setPosition(position);
		time_step += 0.002;
	}
    return flg;
}

Vector3 BasicTutorial_00::move_down(Vector3 pos, float time_step){
	Vector3 velocity = Vector3(0.0,0.0,0.0);
	Vector3 acceleration = Vector3(0.0, -50.8, 0.0);
	
	velocity += acceleration*time_step;
	return pos + velocity*time_step;
}

Vector3 BasicTutorial_00::move_up(Vector3 pos, float time_step){
	Vector3 velocity = Vector3(0,0,0);
	Vector3 acceleration = Vector3(0.0, 20.8, 0.0);
	
	if (velocity.y <= 80)
	velocity += acceleration*time_step;
	return pos + velocity*time_step;
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
