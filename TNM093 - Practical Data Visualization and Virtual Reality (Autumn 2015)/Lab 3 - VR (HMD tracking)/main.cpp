#include <sgct.h>
#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_access.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

sgct::Engine * gEngine;

//-----------------------
// function declarations 
//-----------------------
void myInitOGLFun();
void myPreSyncFun();
void myPostSyncPreDrawFun();
void myDrawFun();

//for syncing variables across a cluster
void myEncodeFun();
void myDecodeFun();

void drawAxes(float size);
void drawWireCube(float size);
void drawUniverse(sgct::SharedFloat t);


//-----------------------
// variable declarations 
//-----------------------

//store each device's transform 4x4 matrix in a shared vector
sgct::SharedVector<glm::mat4> sharedTransforms;
sgct::SharedString sharedText;
sgct::SharedObject<size_t> sharedHeadSensorIndex(999);
sgct::SharedFloat t;
sgct::SharedVector<glm::vec3> sharedWandPos;
sgct::SharedVector<glm::vec3> sharedWandAng;
sgct::SharedVector<glm::vec4> sharedObjectData;

sgct_utils::SGCTSphere* sun;
sgct_utils::SGCTSphere* moon;
sgct_utils::SGCTSphere* earth;

float tid;
glm::mat4 transforms;
glm::mat4 wandtransforms;


//pointer to a device
sgct::SGCTTrackingDevice * devicePtr = NULL;
//pointer to a tracker
sgct::SGCTTracker * trackerPtr = NULL;

int main( int argc, char* argv[] )
{
	// Allocate
	gEngine = new sgct::Engine( argc, argv );

	// Bind your functions
	gEngine->setInitOGLFunction( myInitOGLFun );
	gEngine->setPreSyncFunction( myPreSyncFun );
	gEngine->setPostSyncPreDrawFunction( myPostSyncPreDrawFun );
	gEngine->setDrawFunction( myDrawFun );

	// Init the engine
	if( !gEngine->init() )
	{
		delete gEngine;
		return EXIT_FAILURE;
	}

	sgct::SharedData::instance()->setEncodeFunction( myEncodeFun );
	sgct::SharedData::instance()->setDecodeFunction( myDecodeFun );

	// Main loop
	gEngine->render();

	// Clean up
	delete gEngine;

	// Exit program
	exit( EXIT_SUCCESS );
}

void myInitOGLFun()
{
  
    sun = new sgct_utils::SGCTSphere(0.12f, 15);
	moon = new sgct_utils::SGCTSphere(0.01f, 15);
	earth = new sgct_utils::SGCTSphere(0.04f, 15);
	
	glEnable(GL_DEPTH_TEST);

	//only store the tracking data on the master node
	if( gEngine->isMaster() )
	{
		t = 0;
		size_t index = 0;
		
		
		//allocate shared data
		for(size_t i = 0; i < sgct::Engine::getTrackingManager()->getNumberOfTrackers(); i++)
		{
			trackerPtr = sgct::Engine::getTrackingManager()->getTrackerPtr(i);
			
			//init the shared vector with identity matrixes
			for(size_t j=0; j<trackerPtr->getNumberOfDevices(); j++)
			{
				devicePtr = trackerPtr->getDevicePtr(j);
			
				if( devicePtr->hasSensor() )
				{
					sharedTransforms.addVal( glm::mat4(1.0f) );
					
					//find the head sensor
					if( sgct::Engine::getTrackingManager()->getHeadDevicePtr() == devicePtr )
						sharedHeadSensorIndex.setVal(index);

					index++;
				}
			}
		}
	}
}

/*
	This callback is called once per render loop iteration.
*/
void myPreSyncFun()
{
	/*
	Store all transforms in the array by looping through all trackers and all devices.

	Storing values from the tracker in the pre-sync callback will guarantee
	that the values are equal for all draw calls within the same frame.
	This prevents the application from getting different tracked data for
	left and right draws using a stereoscopic display. Remember to get
	all sensor, button and analog data that will affect the rendering in this stage.
	*/

	//only store the tracking data on the master node
	if( gEngine->isMaster() )
	{
		size_t index = 0;
		std::stringstream ss;
		
		/*
			Loop trough all trackers (like intersense IS-900, Microsoft Kinect, PhaseSpace etc.)
		*/
		for(size_t i = 0; i < sgct::Engine::getTrackingManager()->getNumberOfTrackers(); i++)
		{
			trackerPtr = sgct::Engine::getTrackingManager()->getTrackerPtr(i);
		
			
			/*
				Loop trough all tracking devices (like headtracker, wand, stylus etc.)
			*/
			for(size_t j = 0; j < trackerPtr->getNumberOfDevices(); j++)
			{
				devicePtr = trackerPtr->getDevicePtr(j);
				
				ss << "Device " << i <<  "-" << j << ": " << devicePtr->getName() << "\n";
				
				if( devicePtr->hasSensor() )
				{
					sharedTransforms.setValAt( index, devicePtr->getWorldTransform() );
					index++;

					double trackerTime = devicePtr->getTrackerDeltaTime();
					ss << "     Sensor id: " << devicePtr->getSensorId()
						<< " freq: " << (trackerTime <= 0.0 ? 0.0 : 1.0/trackerTime) << " Hz\n";

					ss << "\n     Pos\n"
						<< "          x=" << devicePtr->getPosition().x << "\n"
						<< "          y=" << devicePtr->getPosition().y << "\n"
						<< "          z=" << devicePtr->getPosition().z << "\n";

					ss << "\n     Rot\n"
						<< "          rx=" << devicePtr->getEulerAngles().x << "\n"
						<< "          ry=" << devicePtr->getEulerAngles().y << "\n"
						<< "          rz=" << devicePtr->getEulerAngles().z << "\n";
						
					sharedWandPos.addVal( glm::vec3(devicePtr->getPosition().x,devicePtr->getPosition().y,devicePtr->getPosition().z) );
					
					sharedWandAng.addVal( glm::vec3(devicePtr->getEulerAngles().x, devicePtr->getEulerAngles().y, devicePtr->getEulerAngles().z));
				}

				if( devicePtr->hasButtons() )
				{
					ss << "\n     Buttons\n";
					
					for(size_t k=0; k < devicePtr->getNumberOfButtons(); k++)
					{
						ss << "          Button " << k << ": " << (devicePtr->getButton(k) ? "pressed" : "released") << "\n";
					}
				}

				if( devicePtr->hasAnalogs() )
				{
					ss << "\n     Analog axes\n";sgct::SharedVector<glm::vec4> sharedObjectData;
					
					for(size_t k=0; k < devicePtr->getNumberOfAxes(); k++)
					{
						ss << "          Axis " << k << ": " << devicePtr->getAnalog(k) << "\n";
					}
				}

				ss << "\n";
			}
		}

		//store the string stream into the shared string
		sharedText.setVal( ss.str() );
	}
}

/*
  This callback is called once just before rendering data. It is here
  you may use the shared states to estimate internal states to be used
  for rendering the graphics.getEulerAngles getEulerAnglese
*/
void myPostSyncPreDrawFun()
{
	//Intersection calculations are done in draw universe
	
  
}

/*
	This callback can be called several times per render loop iteration.
	Using a single viewport in stereo (3D) usually results in refresh rate of 120 Hz.
*/
void myDrawFun()
{
	if( gEngine->isMaster() )
	{
	  //if ( t> 360)
	  //  t = 0;
	  
	  t = t + 1;
	  //sgct::MessageHandler::instance()->print("Tid: ", t.getVal());
	  //std::cout << t.getVal() << std::endl;
	}

	//draw a cube and axes around each wand
	for(size_t i = 0; i < sharedTransforms.getSize(); i++)
	{

		size_t wandindex = 0;
		wandtransforms = sharedTransforms.getValAt(wandindex);

		if(i != sharedHeadSensorIndex.getVal()) 
		{
			transforms =  sharedTransforms.getValAt( i );
		  
			glLineWidth(2.0);

			glPushMatrix();

			glMultMatrixf( glm::value_ptr( sharedTransforms.getValAt( i ) ) );

			glColor3f(0.5f,0.5f,0.5f);
			drawWireCube(0.1f);
			
			drawAxes(0.1f);

			//draw pointer line
			glBegin(GL_LINES);
			glColor3f(1.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, -5.0f);
			glEnd();

			glPopMatrix();
		}
	}
	
	drawUniverse(t);

	//draw text
	float textVerticalPos = static_cast<float>(gEngine->getCurrentWindowPtr()->getYResolution()) - 100.0f;
	int fontSize = 12;
	
	glColor3f(1.0f, 1.0f, 1.0f);
	sgct_text::print(sgct_text::FontManager::instance()->getFont( "SGCTFont", fontSize ),
		120.0f, textVerticalPos,
		sharedText.getVal().c_str() );
	

}

void myEncodeFun()
{
	sgct::SharedData::instance()->writeVector( &sharedTransforms );
	sgct::SharedData::instance()->writeString( &sharedText );
	sgct::SharedData::instance()->writeObj( &sharedHeadSensorIndex );
	
	sgct::SharedData::instance()->writeFloat( &t );
	sgct::SharedData::instance()->writeVector( &sharedWandPos );
	sgct::SharedData::instance()->writeVector( &sharedWandAng );
}

void myDecodeFun()
{
	sgct::SharedData::instance()->readVector( &sharedTransforms );
	sgct::SharedData::instance()->readString( &sharedText );
	sgct::SharedData::instance()->readObj( &sharedHeadSensorIndex );
	
	sgct::SharedData::instance()->readFloat( &t );
	sgct::SharedData::instance()->readVector( &sharedWandPos );
	sgct::SharedData::instance()->readVector( &sharedWandAng );
}

void drawAxes(float size)
{
	glLineWidth(2.0);
	glBegin(GL_LINES);

	//x-axis
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);

	//y-axis
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);

	//z-axis
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, size);

	glEnd();
}

void drawWireCube(float size)
{
	//bottom
	glBegin(GL_LINE_STRIP);
	glVertex3f( -size, -size, -size);
	glVertex3f( size, -size, -size);
	glVertex3f( size, -size, size);
	glVertex3f( -size, -size, size);
	glVertex3f( -size, -size, -size);
	glEnd();

	//top
	glBegin(GL_LINE_STRIP);
	glVertex3f( -size, size, -size);
	glVertex3f( size, size, -size);
	glVertex3f( size, size, size);
	glVertex3f( -size, size, size);
	glVertex3f( -size, size, -size);
	glEnd();

	//sides
	glBegin(GL_LINES);
	glVertex3f( -size, -size, -size);
	glVertex3f( -size, size, -size);

	glVertex3f( size, -size, -size);
	glVertex3f( size, size, -size);

	glVertex3f( size, -size, size);
	glVertex3f( size, size, size);

	glVertex3f( -size, -size, size);
	glVertex3f( -size, size, size);
	glEnd();
}

void drawUniverse(sgct::SharedFloat t)
{
	//size_t wandindex = 0;

	//wandtransforms = sharedTransforms.getValAt(wandindex);
    // Intersection Sun
  //glm::rotate(50.0f, glm::vec3(1.0f, 0.0f, 0.0f)) *
	glm::vec4 w = wandtransforms * glm::vec4(0, 0, 0, 1.0f);
  glm::vec4 o = ( glm::translate(glm::vec3(0.0f, 0.0f, 0.25f)))* glm::vec4(0, 0, 0, 1.0f);
  //glm::mat4 test = glm::rotate(50.0f, glm::vec3(1.0f, 0.0f, 0.0f)) ;
  //glm::vec4 o = glm::vec4(0.0f, 0.0f, -0.4f, 0.0f); 
  glm::vec4 v2 = (wandtransforms * glm::vec4(0, 0, -1.0f, 0));
  glm::vec4 v1 = o - w;
  glm::vec4 a = (glm::dot(v2, v1)/glm::dot(v2,v2)) * v2;
  float d = glm::length(v1-a);
  
  
  //Intersection Earth
  //50.0f, glm::vec3(1.0f, 0.0f, 0.0f)) *
   glm::vec4 o2 = (glm::translate(glm::vec3(0.5f, 0.0f, 0.0f)) * glm::rotate((t*0.5f *2.0f* 3.14f)/360, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate((50.0f*2.0f* 3.14f)/360, glm::vec3(1.0f, 0.0f, 0.0f)) *  glm::translate(glm::vec3(0.0f, 0.0f, -0.4f)))* glm::vec4(0, 0, 0, 1.0f);
  glm::vec4 v12 = o2 - w;
  glm::vec4 a2 = (glm::dot(v2, v12)/glm::dot(v2,v2)) * v2;
  float d2 = glm::length(v12-a2);
  
  
  glPushMatrix();
    //Translate the whole scene
    glTranslatef(0,0, 0.25f);
    glRotatef(50, 1, 0, 0);
    glPushMatrix();
    //Suns rotation
      glRotatef(t*2.0f, 0, 1, 0);
      
       if(d < 0.17f)
	glColor3f(1,0,0);
      else
	glColor3f(1,1,0);
      sun->draw();
    glPopMatrix();
    
    // Orbit from sun
    glPushMatrix();
      glRotatef(t * 0.5f, 0, 1, 0);
      glTranslatef(0.5f,0 ,0 );
      
      //Earths rotation
      glPushMatrix();
	glRotatef(t* 2.0f, 0, 1, 0);
	if(d2 < 0.05f)
	glColor3f(1,0,0);
      else
	glColor3f(0,1,0);
	earth->draw();
      glPopMatrix();
      
      //Orbit from Earth
      glPushMatrix();
	glRotatef(t*2.0f, 0, 1, 0);
	glTranslatef(0.1f, 0, 0);
	glPushMatrix();
	  glRotatef(t*3.0f, 0,1,0);
	  glColor3f(1,1,1);
	  moon->draw();
	glPopMatrix();
      glPopMatrix();
    glPopMatrix();  
  glPopMatrix();

  
  
}
