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
int ballState = 0; // 0 stop 1 up 2 down 3 left 4 right
bool zero_flag = false;

BasicTutorial_00::BasicTutorial_00(void) {}

void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");
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
	Entity* entBigBall = mSceneMgr->createEntity("BigBall","sphere.mesh");
	Entity* entball1 = mSceneMgr->createEntity("ball1","sphere.mesh");
	Entity* entball2 = mSceneMgr->createEntity("ball2","sphere.mesh");

	Entity* entPlane1 = mSceneMgr->createEntity("Ground","ground");
	Entity* entPlane2 = mSceneMgr->createEntity("Wall", "wall");
	entPlane2->setCastShadows(false);
	entPlane2->setMaterialName("Examples/Rockwall");

	SceneNode *node0 = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode();

	SceneNode *node1 = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode();

	SceneNode *node2 = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(
		"BigBall");

	 SceneNode *node3 = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(
		"b1",
		Vector3(150, 0.0, 0.0));

	 SceneNode *node4 = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode( 
		"b2",
		Vector3(-150, 0.0, 0.0));
	 
	node1 -> setPosition(0,0,-750);
	node0 -> attachObject(entPlane1);
	node1 -> attachObject(entPlane2);

	node3->scale(0.1,0.1,0.1);
	node4->scale(0.1,0.1,0.1);

	node2->attachObject(entBigBall);
	node3->attachObject(entball1);
	node4->attachObject(entball2);

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

	if (arg.key == OIS::KC_I ) {
		if (ballState == 1)
			ballState = 0;
		else
		ballState = 1;
	}

	if (arg.key == OIS::KC_K ) {
		if (ballState == 2)
			ballState = 0;
		else
		ballState = 2;
	}
	
	if (arg.key == OIS::KC_J ) {
		if (ballState == 3)
			ballState = 0;
		else
		ballState = 3;
	}

	if (arg.key == OIS::KC_L ) {
		if (ballState == 4)
			ballState = 0;
		else
		ballState = 4;
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

		mSceneMgr = mSceneMgrArr[0];
		SceneNode *node1 = mSceneMgr
			->getSceneNode("BigBall");

		Vector3 position = node1->getPosition();

		if (ballState == 1){
			node1->setPosition(move_up(position));
			checkCollision(position);
		}
		else if (ballState == 2){
			node1->setPosition(move_down(position));
			checkCollision(position);
		}
		else if (ballState == 3){
			node1->setPosition(move_left(position));
			checkCollision(position);
		}
		else if (ballState == 4){
			node1->setPosition(move_right(position));
			checkCollision(position);
		}

    return flg;
}
void BasicTutorial_00::checkCollision(Vector3 pos){

	mSceneMgr = mSceneMgrArr[0];
	SceneNode *node1 = mSceneMgr
			->getSceneNode("b1");
	SceneNode *node2 = mSceneMgr
			->getSceneNode("b2");

	Vector3 dir1 = node1->getPosition() - pos;
	Vector3 dir2 = node2->getPosition() - pos;

	if (dir1.length() <= 110)
	{
		node1->setPosition(node1->getPosition() + dir1.normalisedCopy());
	}
	if (dir2.length() <= 110)
	{
		node2->setPosition(node2->getPosition() + dir2.normalisedCopy());
	}

}

Vector3 BasicTutorial_00::move_down(Vector3 pos){
	Vector3 velocity = Vector3(0,0,1);
	
	return pos + velocity;
}

Vector3 BasicTutorial_00::move_up(Vector3 pos){
	Vector3 velocity = Vector3(0,0,-1);
	
	return pos + velocity;
}

Vector3 BasicTutorial_00::move_left(Vector3 pos){
	Vector3 velocity = Vector3(-1,0,0);
	
	return pos + velocity;
}

Vector3 BasicTutorial_00::move_right(Vector3 pos){
	Vector3 velocity = Vector3(1,0,0);
	
	return pos + velocity;
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
