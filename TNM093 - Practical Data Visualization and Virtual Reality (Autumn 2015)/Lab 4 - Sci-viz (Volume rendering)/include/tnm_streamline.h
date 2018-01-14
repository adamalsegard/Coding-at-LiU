#ifndef VRN_TNM_STREAMLINE_H
#define VRN_TNM_STREAMLINE_H

#include "voreen/core/processors/renderprocessor.h"

#include "voreen/core/ports/volumeport.h"
#include "voreen/core/datastructures/volume/volumeatomic.h"
#include "voreen/core/interaction/camerainteractionhandler.h"
#include "voreen/core/properties/cameraproperty.h"
#include "voreen/core/properties/intproperty.h"
#include "voreen/core/properties/floatproperty.h"

namespace voreen {


class TNMStreamlineRenderer : public RenderProcessor {
public:
    TNMStreamlineRenderer();
    ~TNMStreamlineRenderer();
    std::string getClassName() const   { return "TNMStreamlineRenderer";   }
    std::string getCategory() const    { return "tnm093"               ;  }
    CodeState getCodeState() const     { return CODE_STATE_EXPERIMENTAL;  }

    Processor* create() const          { return new TNMStreamlineRenderer; }

	void initialize() throw (tgt::Exception);
	void deinitialize() throw (tgt::Exception);

protected:
	enum IntegrationMethod {
		IntegrationMethodEuler = 0,
		IntegrationMethodRK4
	};
	void generateSeedpoints();

	void generateStreamlines(const std::vector<tgt::vec3>& seedpoints);
	void invalidateStreamlines();

    void process();

    VolumePort _inport; // The incoming vector data
	RenderPort _outport; // The rendered output

	IntProperty _nSeedPoints; // Determines how many seedpoints exist per axis
	IntProperty _nSteps; // Determines the number of integration steps
	FloatProperty _stepLength; // Determines the integration steplength
	IntOptionProperty _integrationMethod; // Determines the integration method that is used

	CameraProperty _camera;
	CameraInteractionHandler* _cameraHandler;
	tgt::Shader* _shader; // The shader object that will do the rendering for us

	GLuint _vbo;
	GLuint _selectionVbo;

	std::vector<tgt::vec3> _seedPoints;
	bool _streamlinesDirty;
	std::vector<float> _streamlines;
	std::vector<int> _nPointsPerStreamline;
};

} // namespace

#endif // VRN_TNM_VOLUMEINFORMATION_H
