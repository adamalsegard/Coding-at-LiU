#include "modules/tnm093/include/tnm_streamline.h"

namespace voreen {

TNMStreamlineRenderer::TNMStreamlineRenderer()
	: RenderProcessor()
	, _inport(Port::INPORT, "in.data")
	, _outport(Port::OUTPORT, "out.image")
	, _nSeedPoints("seedPoints", "# Seedpoints (per axis)", 5, 5, 1000)
	, _nSteps("nSteps", "# Integration Steps", 100, 1, 1000)
	, _stepLength("stepLength", "Integration Step Length", 0.001f, 0.f, 1.f)
	, _integrationMethod("integrationMethod", "Integration Method")
	, _camera("camera", "Camera", tgt::Camera(tgt::vec3(0.f, 0.f, 3.5f), tgt::vec3(0.f, 0.f, 0.f), tgt::vec3(0.f, 1.f, 0.f)))
	, _streamlinesDirty(true)
{
	_integrationMethod.addOption("euler", "Euler", IntegrationMethodEuler);
	_integrationMethod.addOption("rk4", "Runge Kutta 4th", IntegrationMethodRK4);

	addPort(_inport);
	addPort(_outport);

	addProperty(_nSeedPoints);
	addProperty(_nSteps);
	addProperty(_stepLength);
	addProperty(_integrationMethod);
	addProperty(_camera);

	_cameraHandler = new CameraInteractionHandler("cameraHandler", "Camera", &_camera);
	addInteractionHandler(_cameraHandler);

	_nSeedPoints.onChange(CallMemberAction<TNMStreamlineRenderer>(this, &TNMStreamlineRenderer::generateSeedpoints));
	_stepLength.onChange(CallMemberAction<TNMStreamlineRenderer>(this, &TNMStreamlineRenderer::invalidateStreamlines));
	_nSteps.onChange(CallMemberAction<TNMStreamlineRenderer>(this, &TNMStreamlineRenderer::invalidateStreamlines));
	_integrationMethod.onChange(CallMemberAction<TNMStreamlineRenderer>(this, &TNMStreamlineRenderer::invalidateStreamlines));
}

TNMStreamlineRenderer::~TNMStreamlineRenderer()	{
	delete _cameraHandler;
}

void TNMStreamlineRenderer::initialize() throw (tgt::Exception) {
	RenderProcessor::initialize();

	_shader = ShdrMgr.loadSeparate("streamline.vert", "streamline.frag");

	glGenBuffers(1, &_vbo);
}

void TNMStreamlineRenderer::deinitialize() throw (tgt::Exception) {
	glDeleteBuffers(1, &_vbo);
	ShdrMgr.dispose(_shader);

	RenderProcessor::deinitialize();
}

void TNMStreamlineRenderer::process() {
	// Activate the user-outport as the rendering target
	_outport.activateTarget();

	// Clear the buffer
	_outport.clearTarget();

	// During the first run, we might not have any seedpoints yet
	// In subsequent runs, we only want to generate the seed points if something has changed
	if (_seedPoints.empty())
		generateSeedpoints();

	// Bind the vertex buffer that contains (or will contain) the streamlines
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	// Similarly to the streamlines. If the seedpoints haven't changed, there is no need
	// to regenerate the streamlines and upload them
	if (_streamlinesDirty) {
		generateStreamlines(_seedPoints);
		int nValues = 0;
		for (size_t i = 0; i < _nPointsPerStreamline.size(); ++i) {
			// _nPointsPerStreamline stores one entry per streamline, denoting the
			// number of points that streamline has
			// we need to multiply it by 3 as each point contains 3 floats
			nValues += _nPointsPerStreamline[i] * 3;
		}
		LINFO("Total number of points in all streamlines: " << nValues);
		
		// Upload all streamline points into the Vertex Buffer Object
		glBufferData(GL_ARRAY_BUFFER, nValues * sizeof(float), &(_streamlines[0]), GL_STATIC_DRAW);

		// We uploaded the streamlines, so they are no longer dirty
		_streamlinesDirty = false;
	}

	// Declare the structure of the uploaded points: we have groups of 3 floats in the attribute location 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	_shader->activate();

	// Set the position and camera matrices so that we can move around the streamlines
	tgt::Camera cam = _camera.get();
	setGlobalShaderParameters(_shader, &cam);

	// The _nPointsPerStreamline vector contains one integer value per streamline denoting the number of points
	// that belong this is streamline
	// By iterating through this vector and keeping track of how many points we previously rendered (iRender)
	// we can step through all streamlines sequentially
	int iRender = 0;
	for (size_t i = 0; i < _nPointsPerStreamline.size(); ++i) {
		int currentNumber = _nPointsPerStreamline[i];
		_shader->setUniform("nVertices", currentNumber);
		_shader->setUniform("iRender", iRender);
		glDrawArrays(GL_LINE_STRIP, iRender, currentNumber);
		iRender += currentNumber;
	}
	_shader->deactivate();
	_outport.deactivateTarget();	
}

void TNMStreamlineRenderer::generateSeedpoints() {
	// We modified the seed points, so all previous streamlines are invalid
	_streamlinesDirty = true;

	// Remove all previous seed points
	_seedPoints.clear();

	// Create a uniform distribution of seed points spanning [-1, 1]
	int nSeed = _nSeedPoints.get();
	for (int iX = 0; iX < nSeed; ++iX) {
		for (int iY = 0; iY < nSeed; ++iY) {
			for (int iZ = 0; iZ < nSeed; ++iZ) {
				float x = static_cast<float>(iX) / static_cast<float>(nSeed - 1);
				float y = static_cast<float>(iY) / static_cast<float>(nSeed - 1);
				float z = static_cast<float>(iZ) / static_cast<float>(nSeed - 1);

				_seedPoints.push_back(tgt::vec3(x, y, z));
			}
		}
	}
}	


void TNMStreamlineRenderer::generateStreamlines(const std::vector<tgt::vec3>& seedpoints) {
	// Remove the previous streamlines
	_streamlines.clear();
	// Remove the number of previous streamlines
	_nPointsPerStreamline.clear();

	const Volume3xFloat* volume = dynamic_cast<const Volume3xFloat*>(_inport.getData()->getRepresentation<Volume>());
	if (!volume) {
		LERROR("Volume input to TNMStreamlineRenderer is not a vector volume");
		return;
	}
	
	// Create a new streamline for each seedpoint
	for (size_t i = 0; i < seedpoints.size(); ++i) {
		tgt::vec3 currentPoint = seedpoints[i];

		// Add the start point to our list of streamlines
		_streamlines.push_back(currentPoint.x);
		_streamlines.push_back(currentPoint.y);
		_streamlines.push_back(currentPoint.z);

		// nActualSteps measures how many steps were actually taken for the current stream line
		// which may or may not be different from _nSteps, the maximum number
		int nActualSteps = 1;
		for (int j = 0; j < _nSteps.get(); ++j) {
			// volume->getVoxelFloatLinear expects a position that is in [0, dim - 1], so we have to
			// convert the currentPoint from [0,1] into [0, dim - 1]
			tgt::vec3 samplePos = currentPoint * (tgt::vec3(volume->getDimensions()) - tgt::vec3(1.f));

			// Extract the three components from the vector field
			float dirX = volume->getVoxelFloatLinear(samplePos, 0) * (500.f/2139.f);
			float dirY = volume->getVoxelFloatLinear(samplePos, 1) * (500.f/2004.f);
			float dirZ = volume->getVoxelFloatLinear(samplePos, 2) * (100.f/19.8f);

			// Normalize the directions. Normalization factors are taken from:
			// http://vis.computer.org/vis2004contest/data.html#format

			const float dirMin = -79.47297f;
			const float dirMax = 85.17703f;
			float dirXNorm = (dirX - dirMin) / (dirMax - dirMin);
			float dirYNorm = (dirX - dirMin) / (dirMax - dirMin);
			float dirZNorm = (dirX - dirMin) / (dirMax - dirMin);

			// Invalid values in the dataset are represented by 1.0e35, so
			// they will be normalized to a value > 1.f
			if ((dirXNorm > 1.f) || (dirYNorm > 1.f) || (dirZNorm > 1.f))
				continue;

		
			
			// Implement your integration methods here
			switch (_integrationMethod.getValue()) {
				case IntegrationMethodEuler:
					{
						currentPoint.x += _stepLength.get() * dirX;
						currentPoint.y += _stepLength.get() * dirY;
						currentPoint.z += _stepLength.get() * dirZ;

						break;
					}
				case IntegrationMethodRK4:
					{
					  									  
						tgt::vec3 f1 = tgt::vec3(dirX, dirY, dirZ);
						tgt::vec3 f2 = currentPoint + _stepLength.get()*f1/2.0f;
						tgt::vec3 f3 = currentPoint + _stepLength.get()*f2/2.0f;
						tgt::vec3 f4 = currentPoint + _stepLength.get()*f3;
						currentPoint += _stepLength.get()*(f1 + 2.0f*f2 + 2.0f*f3 + f4)/6.0f;

						break;
					}
			}

			// Check if all of the values are still inside the volume
			// We have to bound all of the values to the boundary
			// (please note that this method slights changes the last step)
			bool outsideVolume = false;
			if (currentPoint.x < 0.f) {
				currentPoint.x = 0.f;
				outsideVolume = true;
			}
			if (currentPoint.x > 1.f) {
				currentPoint.x = 1.f;
				outsideVolume = true;
			}
			if (currentPoint.y < 0.f) {
				currentPoint.y = 0.f;
				outsideVolume = true;
			}
			if (currentPoint.y > 1.f) {
				currentPoint.y = 1.f;
				outsideVolume = true;
			}
			if (currentPoint.z < 0.f) {
				currentPoint.z = 0.f;
				outsideVolume = true;
			}
			if (currentPoint.z > 1.f) {
				currentPoint.z = 1.f;
				outsideVolume = true;
			}
			_streamlines.push_back(currentPoint.x);
			_streamlines.push_back(currentPoint.y);
			_streamlines.push_back(currentPoint.z);
			++nActualSteps;

			// If the point was outside the volume, we bail out
			if (outsideVolume)
				break;
		}
		_nPointsPerStreamline.push_back(nActualSteps);
	}
}

void TNMStreamlineRenderer::invalidateStreamlines() {
	_streamlinesDirty = true;
}

} // namespace
