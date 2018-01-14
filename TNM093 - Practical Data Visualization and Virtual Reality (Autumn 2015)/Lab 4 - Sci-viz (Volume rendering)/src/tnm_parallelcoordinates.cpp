#include "modules/tnm093/include/tnm_parallelcoordinates.h"
#include <sstream>

namespace voreen {
    
TNMParallelCoordinates::AxisHandle::AxisHandle(AxisHandlePosition location, int index, const tgt::vec2& position)
    : _location(location)
    , _index(index)
    , _position(position)
{}

void TNMParallelCoordinates::AxisHandle::setPosition(const tgt::vec2& position) {
    _position = position;
}

tgt::vec2 TNMParallelCoordinates::AxisHandle::position() const {
	return _position;
}

int TNMParallelCoordinates::AxisHandle::index() const {
    return _index;
}

void TNMParallelCoordinates::AxisHandle::render() const {
	renderInternal(tgt::vec3(0.8f, 0.8f, 0.8f));
}

void TNMParallelCoordinates::AxisHandle::renderPicking() const {
	// Mapping the integer index to a float value between 1/255 and 1
    const float color = (_index + 1) / 255.f;
	// The picking information is rendered only in the red channel
	renderInternal(tgt::vec3(color, 0.f, 0.f));
}

void TNMParallelCoordinates::AxisHandle::setVertexBufferObjectAndShader(GLuint vbo, tgt::Shader* shader) {
	_vbo = vbo;
	_shader = shader;
}

void TNMParallelCoordinates::AxisHandle::renderInternal(const tgt::vec3& color) const {
	_shader->activate();

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0 ,0);

	_shader->setUniform("_position", _position);
	_shader->setUniform("_location", _location);
	_shader->setUniform("_color", color);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	_shader->deactivate();
}

TNMParallelCoordinates::AxisHandle::AxisHandlePosition TNMParallelCoordinates::AxisHandle::location() const {
	return _location; 
}

TNMParallelCoordinates::TNMParallelCoordinates()
    : RenderProcessor()
    , _inport(Port::INPORT, "in.data")
	, _outport(Port::OUTPORT, "out.image")
	, _privatePort(Port::OUTPORT, "private.image", false, Processor::INVALID_RESULT, GL_RGBA32F)
    , _pickedHandle(-1)
	, _font("font", "Font")
	, _colorMethod("colorMethod", "Coloring Method")
	, _brushingIndices("brushingIndices", "Brushing Indices")
	, _linkingIndices("linkingIndices", "Linking Indices")
{
    addPort(_inport);
    addPort(_outport);
    addPrivateRenderPort(_privatePort);

	addProperty(_font);
	addProperty(_colorMethod);

	addProperty(_brushingIndices);
	addProperty(_linkingIndices);

    _mouseClickEvent = new EventProperty<TNMParallelCoordinates>(
        "mouse.click", "Mouse Click",
        this, &TNMParallelCoordinates::handleMouseClick,
        tgt::MouseEvent::MOUSE_BUTTON_LEFT, tgt::MouseEvent::CLICK, tgt::Event::MODIFIER_NONE);
    addEventProperty(_mouseClickEvent);

    _mouseMoveEvent = new EventProperty<TNMParallelCoordinates>(
        "mouse.move", "Mouse Move",
        this, &TNMParallelCoordinates::handleMouseMove,
        tgt::MouseEvent::MOUSE_BUTTON_LEFT, tgt::MouseEvent::MOTION, tgt::Event::MODIFIER_NONE);
    addEventProperty(_mouseMoveEvent);

    _mouseReleaseEvent = new EventProperty<TNMParallelCoordinates>(
        "mouse.release", "Mouse Release",
        this, &TNMParallelCoordinates::handleMouseRelease,
        tgt::MouseEvent::MOUSE_BUTTON_LEFT, tgt::MouseEvent::RELEASED, tgt::Event::MODIFIER_NONE);
    addEventProperty(_mouseReleaseEvent);

	
    // Create AxisHandles here with a unique id
    int id = 0;
    for( float i = 0; i< 6; i++)
    {
      _handles.push_back(AxisHandle(AxisHandle::AxisHandlePositionTop, id, tgt::vec2((i/3)-0.83 ,1) ));
      _handles.push_back(AxisHandle(AxisHandle::AxisHandlePositionBottom, id+1, tgt::vec2((i/3)-0.83 ,-1) ));
      id += 2;
    }
  
    

}

TNMParallelCoordinates::~TNMParallelCoordinates() {
    delete _mouseClickEvent;
    delete _mouseMoveEvent;
}

void TNMParallelCoordinates::initialize() throw (tgt::Exception){
	RenderProcessor::initialize();
	const float xDiff = 0.05f;
	const float yDiff = 0.05f;
	glGenBuffers(1, &_handleVBO);

	// Specifying the triangle
	float data[6] = {
		0.f, -yDiff / 2.f,
		-xDiff, yDiff / 2.f,
		xDiff, yDiff / 2.f
	};

	glBindBuffer(GL_ARRAY_BUFFER, _handleVBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	_handleShader = ShdrMgr.loadSeparate("parallelcoordinates_handle.vert", "parallelcoordinates_handle.frag");

	for (std::vector<AxisHandle>::iterator it = _handles.begin();
		 it != _handles.end();
		 ++it)
	{ 
		it->setVertexBufferObjectAndShader(_handleVBO, _handleShader);
	}

}

void TNMParallelCoordinates::deinitialize() throw (tgt::Exception) {
	glDeleteBuffers(1, &_handleVBO);
	ShdrMgr.dispose(_handleShader);
	RenderProcessor::deinitialize();
}

void TNMParallelCoordinates::process() {
	if (!_inport.hasData())
		return;

	// If the underlying data has changed, we need to extract the names of the data values
	// and make them available in the combobox for the coloring options
	if (_inport.hasChanged()) {
        _colorMethod.setOptions(std::vector<Option<int> >());
		for (size_t i = 0; i < _inport.getData()->valueNames.size(); ++i) {
			std::stringstream s;
			s << i;
			_colorMethod.addOption(s.str(), _inport.getData()->valueNames[i], i);
			s.str("");
		}
		_colorMethod.updateWidgets();
	}

	// Activate the user-outport as the rendering target
    _outport.activateTarget();
	// Clear the buffer
    _outport.clearTarget();

	// Render the handles
    renderHandles();
	// Render the parallel coordinates lines
    renderLines();
	// Render text
	renderText(); 

	// We are done with the visual part
    _outport.deactivateTarget();

	// Activate the internal port used for picking
    _privatePort.activateTarget();
	// Clear that buffer as well
    _privatePort.clearTarget();
	// Render the handles with the picking information encoded in the red channel
    renderHandlesPicking();
	// Render the lines with the picking information encoded in the green/blue/alpha channel
	renderLinesPicking();
	// We are done with the private render target
    _privatePort.deactivateTarget();
}

void TNMParallelCoordinates::handleMouseClick(tgt::MouseEvent* e) {
	// The picking texture is the result of the previous rendering in the private render port
    tgt::Texture* pickingTexture = _privatePort.getColorTexture();
	// Retrieve the texture from the graphics memory and get it to the RAM
	pickingTexture->downloadTexture();

	// The texture coordinates are flipped in the y direction, so we take care of that here
    const tgt::ivec2 screenCoords = tgt::ivec2(e->coord().x, pickingTexture->getDimensions().y - e->coord().y);
	// And then go from integer pixel coordinates to [-1,1] coordinates
    const tgt::vec2& normalizedDeviceCoordinates = (tgt::vec2(screenCoords) / tgt::vec2(_privatePort.getSize()) - 0.5f) * 2.f;

	// The picking information for the handles is stored in the red color channel
    int handleId = static_cast<int>(pickingTexture->texelAsFloat(screenCoords).r * 255 - 1);

    LINFOC("Picking", "Picked handle index: " << handleId);
    // Use the 'id' and the 'normalizedDeviceCoordinates' to move the correct handle
    // The id is the id of the AxisHandle that has been clicked (the same id you assigned in the constructor)
    // id == -1 if no handle was clicked
    // Use the '_pickedHandle' member variable to store the picked index
	_pickedHandle = handleId;

    const Data* data = _inport.getData();
    
    int lineId = static_cast<int>(pickingTexture->texelAsFloat(screenCoords).b * data->data.size() - 1);;
    // Derive the id of the line that was clicked based on the color scheme that you devised in the
    // renderLinesPicking method


    LINFOC("Picking", "Picked line index: " << lineId);
    if (lineId != -1)
    {
	    _linkingList.insert(lineId);    
    } else 
    {
	    _linkingList.clear();
    }
	    


    // Make the list of selected indices available to the Scatterplot
    _linkingIndices.set(_linkingList);
}

void TNMParallelCoordinates::handleMouseMove(tgt::MouseEvent* e) {
    tgt::Texture* pickingTexture = _privatePort.getColorTexture();
    const tgt::ivec2 screenCoords = tgt::ivec2(e->coord().x, pickingTexture->getDimensions().y - e->coord().y);
    const tgt::vec2& normalizedDeviceCoordinates = (tgt::vec2(screenCoords) / tgt::vec2(_privatePort.getSize()) - 0.5f) * 2.f;

    
    const Data* data = _inport.getData();
    
    // Move the stored index along its axis (if it is a valid picking point)
	if (_pickedHandle != -1) {
	  
	  
	  
	  for(int i = 0; i < _handles.size(); i++)
	  {
	    if(_handles.at(i).index() == _pickedHandle )
	    {
	      switch(_handles.at(i).index()%2 ) 
	      {
		case 0:
		  //Handtaget är på övre raden
		  if(normalizedDeviceCoordinates[1] > _handles.at(i+1).position()[1] && normalizedDeviceCoordinates[1] < 1)
		    _handles.at(i).setPosition( tgt::vec2( _handles.at(i).position()[0]  ,normalizedDeviceCoordinates[1] ) );
		  
		  break;
		  
		case 1:
		  //Handtaget är på undre raden
		  if(normalizedDeviceCoordinates[1] < _handles.at(i-1).position()[1] && normalizedDeviceCoordinates[1] > -1)
		    _handles.at(i).setPosition( tgt::vec2( _handles.at(i).position()[0]  ,normalizedDeviceCoordinates[1] ) );
		  
		  break;
		
	      }
	    }
	  }
	}

	// update the _brushingList with the indices of the lines that are not rendered anymore
	_brushingList.clear();
	for(int i = 0; i < data->data.size() ; i++)
	{
	  //Ska vi rita ut linje i?
	  for(int k = 0; k < 6; k++)
	  {
	    if(_handles.at(k*2).position()[1] < 2*(data->data[i].dataValues[k]-data->minimumMaximumValues[k].first)/(data->minimumMaximumValues[k].second - data->minimumMaximumValues[k].first) - 1 ||
	       _handles.at(k*2+1).position()[1] > 2*(data->data[i].dataValues[k]-data->minimumMaximumValues[k].first)/(data->minimumMaximumValues[k].second - data->minimumMaximumValues[k].first) - 1)
	    {
	     _brushingList.insert(data->data[i].voxelIndex);        
	    }
	  }
	}

	_brushingIndices.set(_brushingList);

    // This re-renders the scene (which will call process in turn)
    invalidate();
}

void TNMParallelCoordinates::handleMouseRelease(tgt::MouseEvent* e) {

}



void TNMParallelCoordinates::renderLines() {
  
	const Data* data = _inport.getData();
	
	for(float i = 0; i < 6; i++)
	{
	  glBegin(GL_LINE_STRIP);
	  glColor3f(1.0f, 1.0f, 1.0f); 
	  glVertex2f((i/3)-0.83, 1);
	  glVertex2f((i/3)-0.83,-1);
	  glEnd();
	  
	}
	
	
	for(int i = 0; i < data->data.size() ; i++)
	{
	  
	  if (_brushingList.find(data->data[i].voxelIndex) != _brushingList.end())
	  {
	      continue;
	  }
	  else
	  {  
	    //Ritar ut linje i
	    
	    if(_linkingList.find(i) != _linkingList.end())
	      renderLinesInternal(tgt::vec3(1.0f, 0.0f, 0.0f),i);  
	    else
	    {
	      float p = (data->data[i].dataValues[_colorMethod.getValue()]-data->minimumMaximumValues[_colorMethod.getValue()].first)/(data->minimumMaximumValues[_colorMethod.getValue()].second - data->minimumMaximumValues[_colorMethod.getValue()].first);
	      renderLinesInternal(tgt::vec3(0.0f, p, 0.0f),i); 
	    }
	      
	    
	    
	    
	  }
	}
}

void TNMParallelCoordinates::renderLinesInternal(const tgt::vec3& color, int i) const {
  const Data* data = _inport.getData();
  
  glBegin(GL_LINE_STRIP);
  glColor3f(color[0],color[1],color[2]);
    for(int j = 0; j < 6; j++)
    {
      float p = j;
      glVertex2f((p/3)-0.83, 
		2*(data->data[i].dataValues[j]-data->minimumMaximumValues[j].first)/(data->minimumMaximumValues[j].second - data->minimumMaximumValues[j].first) - 1);
    
    }
  glEnd();
}

void TNMParallelCoordinates::renderLinesPicking() {
	// Use the same code to render lines (without duplicating it), but think of a way to encode the
	// voxel identifier into the color. The red color channel is already occupied, so you have 3
	// channels with 32-bit each at your disposal (green, blue, alpha)
  
      const Data* data = _inport.getData();
  
      for(int i = 0; i < data->data.size() ; i++)
	{
	  
	  if (_brushingList.find(data->data[i].voxelIndex) != _brushingList.end())
	  {
	      continue;
	  }
	  else
	  {  
	    float color = data->data.size();
	    renderLinesInternal(tgt::vec3(0.0f, 0.0f, (i + 1) / color),i); 
	  }
	}
}

void TNMParallelCoordinates::renderText() {
	const Data* data = _inport.getData();
	tgt::ivec2 size = _outport.getSize();

	if (_handles.empty())
		return;

	if (_handles.size() != 2 * data->valueNames.size()) {
		LERROR("Wrong number of registered handles. Expected: " << 2 * data->valueNames.size() << " got " << _handles.size());
		return;
	}

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-1,-1,0);
	float scaleFactorX = 2.0f / size.x;
	float scaleFactorY = 2.0f / size.y;
	glScalef(scaleFactorX, scaleFactorY, 1);

	glColor3f(1.0, 1.0, 1.0);

	for (size_t i = 0; i < data->valueNames.size(); ++i) {
		_font.get()->render(
			tgt::vec3(
				(((_handles[i*2].position().x + 1) / 2.f) - 0.025f) * size.x,
				0.0125f * size.y,
				0.0
			),
			data->valueNames[i]
		);
	}

	for (size_t i = 0; i < _handles.size(); ++i) {
		std::stringstream str;
		const AxisHandle& handle = _handles[i];
		if (handle.location() == AxisHandle::AxisHandlePositionTop) {
			float t = ((handle.position().y + 1) / 2.f);
			str << t * (data->minimumMaximumValues[i/2].second - data->minimumMaximumValues[i/2].first) + data->minimumMaximumValues[i/2].first;
			_font.get()->render(
				tgt::vec3(
					(((handle.position().x + 1) / 2.f) - 0.0125f) * size.x,
					(((handle.position().y + 1) / 2.f) + 0.025f) * size.y,
					0.0
				),
				str.str()
			);
		}
		else {
			float t = ((handle.position().y + 1) / 2.f);
			str << t * (data->minimumMaximumValues[i/2].second - data->minimumMaximumValues[i/2].first) + data->minimumMaximumValues[i/2].first;
			_font.get()->render(
				tgt::vec3(
					(((handle.position().x + 1) / 2.f) - 0.0125f) * size.x,
					(((handle.position().y + 1) / 2.f) - 0.025f) * size.y,
					0.0
				),
				str.str()
			);
		}
	}
	glPopMatrix();
}

void TNMParallelCoordinates::renderHandles() {
    for (size_t i = 0; i < _handles.size(); ++i) {
        const AxisHandle& handle = _handles[i];
        handle.render();
    }
}

void TNMParallelCoordinates::renderHandlesPicking() {
    for (size_t i = 0; i < _handles.size(); ++i) {
        const AxisHandle& handle = _handles[i];
        handle.renderPicking();
    }
}


} // namespace
