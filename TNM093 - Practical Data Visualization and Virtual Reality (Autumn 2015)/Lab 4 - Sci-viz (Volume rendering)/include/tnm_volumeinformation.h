#ifndef VRN_TNM_VOLUMEINFORMATION_H
#define VRN_TNM_VOLUMEINFORMATION_H

#include "voreen/core/processors/processor.h"
#include "modules/tnm093/include/tnm_common.h"
#include "voreen/core/ports/volumeport.h"
#include "voreen/core/datastructures/volume/volumeatomic.h"

namespace voreen {

class TNMVolumeInformation : public Processor {
public:
    TNMVolumeInformation();
    ~TNMVolumeInformation();
    std::string getClassName() const   { return "TNMVolumeInformation";   }
    std::string getCategory() const    { return "tnm093"               ;  }
    CodeState getCodeState() const     { return CODE_STATE_EXPERIMENTAL;  }

    Processor* create() const          { return new TNMVolumeInformation; }

protected:
    void process();

private:
	void handleVolume(const VolumeFloat* volume, int index, std::string name);
	void handleVolume(const Volume3xFloat* volume, int index, std::string name);

    VolumePort _inport0; // Volume containing the first data value
	VolumePort _inport1; // Volume containing the second data value
	VolumePort _inport2; // Volume containing the third  data value
	VolumePort _inport3; // Volume containing the fourth data value
	VolumePort _inport4; // Volume containing the fifth data value
	VolumePort _inport5; // Volume containing the sixth data value

    DataPort _outport; // The outport containing the computed measures

    Data* _data; // The local copy of the computed data; ownership stays with this object at all times
};

} // namespace

#endif // VRN_TNM_VOLUMEINFORMATION_H
