#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"

using namespace Ogre;

/*!
\brief 3D Game Programming
\n
My Name: Li-Che Chien
\n
My ID: 0316235
\n
My Email: richard@hotmail.com
*/

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
	virtual void createViewports(void);
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void chooseSceneManager(void);
	/*!
	\brief In the requirement of animation with key:0

	I use several flags to indicates the state

	first I use zero_flag to check whether key:0 being click so animation starts

	then I use time_step as a counter to count the stage during animation

	every fram time_step will increase by 0.002, which is the appropriate value I figured out from repeating tests

	and then I use a pengiunState flag to indicate whether its moving up or down

	if up, it couldnt exceed 280, if down, it couldnt be lower than 0.
	*/
    virtual bool frameStarted(const Ogre::FrameEvent& evt);
	/*!
	\brief this function is for the key:0 animation
	
	which calculates the new position when pengiun move down.
	*/
	virtual Vector3 move_down(Vector3);
	/*!
	\brief this function is for the key:0 animation
	
	which calculates the new position when pengiun move up.
	*/
	virtual Vector3 move_up(Vector3);
	virtual Vector3 move_left(Vector3);
	virtual Vector3 move_right(Vector3);
protected:
	void checkCollision(Vector3);
	/*!
	\brief Set the viewport with camera[0]
	
	Set the background blue(0,0,1) and Z-order with default 0 (at the bottom)
	
	and add it to the viewport arr.
	*/
	void createViewport_00(void);
	/*!
	\brief Set the viewport with camera[1]
	
	Set the background blue(0,0,1) and Z-order with 1 (at the top)
	
	and add it to the viewport arr.
	*/
	void createViewport_01(void);
	void createCamera_00();
	void createCamera_01();

	/*!
	\brief First specify the scene manager by assign

	I create the plane with given attributes

	also set the ambient light and shadow with given number

	Then I start to create two pengiuns and ground and cubes and wall
	1. Create objects entity .
	2. Create scene node in scene manager meanwhile set its position or angle.
	3. Attach entity to scene node.

	for 72 cubes using a for loop with given values and set its meterial with chrome and SphereMappedRustySteel.

	After all objects created, I set two point light with different position.
	*/
	void createScene_00();
	/*!
	\brief In the second scene
	I've done the following things:

	1. Set Ambient light black(0,0,0) and shadow
	2. Create point light
	3. Create a plane and a cube entity with new material - green  
	4. Scale the cube with (0.5,0.5,0.5) and attach to scene node
	*/
	void createScene_01();
	/*!
	\brief Handle the key event

	From 1~5, just change the position and direction of camera

	for M,N , I have to reset the viewport to new position and ratio, also change the z-order
	*/
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
protected:
    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
};


#endif // #ifndef __BasicTutorial_00_h_