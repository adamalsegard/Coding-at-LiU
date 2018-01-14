#include "modules/tnm093/include/tnm_datareduction.h"

namespace voreen {

namespace {
	// We will sort the data using this function to ensure a strong ordering on the voxel indices
	bool sortByIndex(const VoxelDataItem& lhs, const VoxelDataItem& rhs) {
		return lhs.voxelIndex < rhs.voxelIndex;
	}

}

TNMDataReduction::TNMDataReduction()
    : _inport(Port::INPORT, "in.data")
    , _outport(Port::OUTPORT, "out.data")
    , _percentage("percentage", "Percentage of Dropped Data")
{
    addPort(_inport);
    addPort(_outport);
    addProperty(_percentage);
}

Processor* TNMDataReduction::create() const {
    return new TNMDataReduction;
}

void TNMDataReduction::process() {
    if (!_inport.hasData())
        return;

	// We have checked above that there is data, so the dereferencing is safe
    const Data& inportData = *(_inport.getData());
    const float percentage = _percentage.get();

	// Our new data
	Data* outportData = new Data;
	// Copy the names of the values for later usage
	outportData->valueNames = inportData.valueNames;
	outportData->minimumMaximumValues = inportData.minimumMaximumValues;

    for (size_t i = 0; i < inportData.data.size() ; ++i) {
      
	//int index = i/(1-percentage);
	const VoxelDataItem& item = inportData.data[i];
	float random = ((float)(rand())) / ((float)(RAND_MAX));
	//std::cout << random << std::endl;
	
	if(percentage < random)
	  outportData->data.push_back(item);

    }

	// sort the data by the voxel index for faster processing later
	std::sort(outportData->data.begin(), outportData->data.end(), sortByIndex);
	// Place the new data into the outport (and transferring ownership at the same time)
    _outport.setData(outportData);
}

} // namespace
