#include "modules/tnm093/include/tnm_volumeinformation.h"
#include "voreen/core/datastructures/volume/volumeatomic.h"

namespace voreen {

	const std::string loggerCat_ = "TNMVolumeInformation";
	
namespace {
	// This ordering function allows us to sort the Data vector by the voxelIndex
	// The extraction *should* produce a sorted list, but you never know
	bool sortByIndex(const VoxelDataItem& lhs, const VoxelDataItem& rhs) {
		return lhs.voxelIndex < rhs.voxelIndex;
	}

}

TNMVolumeInformation::TNMVolumeInformation()
    : Processor()
    , _inport0(Port::INPORT, "in.volume.0")
	, _inport1(Port::INPORT, "in.volume.1")
	, _inport2(Port::INPORT, "in.volume.2")
	, _inport3(Port::INPORT, "in.volume.3")
	, _inport4(Port::INPORT, "in.volume.4")
	, _inport5(Port::INPORT, "in.volume.5")
    , _outport(Port::OUTPORT, "out.data")
    , _data(0)
{
	addPort(_inport0);
    addPort(_inport1);
	addPort(_inport2);
	addPort(_inport3);
	addPort(_inport4);
	addPort(_inport5);
    addPort(_outport);

	setExpensiveComputationStatus(Processor::COMPUTATION_STATUS_PROGRESSBAR);
}

TNMVolumeInformation::~TNMVolumeInformation() {
    delete _data;
}


void TNMVolumeInformation::handleVolume(const VolumeFloat* volume, int index, std::string name) {
	static const float CutoffValue = 10e10;

	std::pair<float, float>& p = _data->minimumMaximumValues[index];
	p.first = std::numeric_limits<float>::max();
	p.second = -std::numeric_limits<float>::max();

	const tgt::svec3 dimensions = volume->getDimensions();

	_data->valueNames[index] = name;

	// iX is the index running over the 'x' dimension
	// iY is the index running over the 'y' dimension
	// iZ is the index running over the 'z' dimension
	for (size_t iX = 0; iX < dimensions.x; ++iX) {
		for (size_t iY = 0; iY < dimensions.y; ++iY) {
			for (size_t iZ = 0; iZ < dimensions.z; ++iZ) {
				// i is a unique identifier for the voxel calculated by the following
				// (probably one of the most important) formulas:
				// iZ*dimensions.x*dimensions.y + iY*dimensions.x + iX;
				const size_t i = VolumeFloat::calcPos(volume->getDimensions(), tgt::svec3(iX, iY, iZ));

				float value = volume->voxel(i);
				if (value > CutoffValue)
					value = 0.f;

				_data->data.at(i).dataValues[index] = value;
				p.first = std::min(p.first, value);
				p.second = std::max(p.second, value);
			}
		}
	}
}

void TNMVolumeInformation::handleVolume(const Volume3xFloat* volume, int index, std::string name) {
	static const float CutoffValue = 1e10;

	std::pair<float, float>& p = _data->minimumMaximumValues[index];
	p.first = std::numeric_limits<float>::max();
	p.second = -std::numeric_limits<float>::max();

	const tgt::svec3 dimensions = volume->getDimensions();

	_data->valueNames[index] = name;

	// iX is the index running over the 'x' dimension
	// iY is the index running over the 'y' dimension
	// iZ is the index running over the 'z' dimension
	for (size_t iX = 0; iX < dimensions.x; ++iX) {
		for (size_t iY = 0; iY < dimensions.y; ++iY) {
			for (size_t iZ = 0; iZ < dimensions.z; ++iZ) {
				// i is a unique identifier for the voxel calculated by the following
				// (probably one of the most important) formulas:
				// iZ*dimensions.x*dimensions.y + iY*dimensions.x + iX;
				const size_t i = Volume3xFloat::calcPos(volume->getDimensions(), tgt::svec3(iX, iY, iZ));

				tgt::vec3 val = volume->voxel(i);

				if ((val.x > CutoffValue) || (val.y > CutoffValue) || (val.z > CutoffValue))
					val = tgt::vec3(0.f);

				float value = val.x * val.x + val.y * val.y + val.z * val.z;
				_data->data.at(i).dataValues[index] = value;
				p.first = std::min(p.first, value);
				p.second = std::max(p.second, value);
			}
		}
	}
}



void TNMVolumeInformation::process() {
	if (_data == 0) {
		_data = new Data;

		_data->valueNames.resize(6);
		tgt::svec3 dim = _inport0.getData()->getDimensions();

		// This line assumes that all volumes have the same dimensions
		_data->data.resize(dim.x * dim.y * dim.z);

		// We have six values, so we need six pairs of min/max values
		_data->minimumMaximumValues.resize(6);
	}

	const tgt::svec3 dimensions = _inport0.getData()->getDimensions();
	// iX is the index running over the 'x' dimension
	// iY is the index running over the 'y' dimension
	// iZ is the index running over the 'z' dimension
	for (size_t iX = 0; iX < dimensions.x; ++iX) {
		for (size_t iY = 0; iY < dimensions.y; ++iY) {
			for (size_t iZ = 0; iZ < dimensions.z; ++iZ) {
				// i is a unique identifier for the voxel calculated by the following
				// (probably one of the most important) formulas:
				// iZ*dimensions.x*dimensions.y + iY*dimensions.x + iX;
				const size_t i = Volume3xFloat::calcPos(dimensions, tgt::svec3(iX, iY, iZ));
				_data->data.at(i).voxelIndex = i;
			}
		}
	}

	setProgress(0.f);
	handleVolume(
		dynamic_cast<const VolumeFloat*>(_inport0.getData()->getRepresentation<Volume>()),
		0,
		"Cloud moisture mixing ratio"
	);
	setProgress(1.f / 6.f);
	handleVolume(
		dynamic_cast<const VolumeFloat*>(_inport1.getData()->getRepresentation<Volume>()),
		1,
		"Water vapor mixing ratio"
	);
	setProgress(2.f / 6.f);
	handleVolume(
		dynamic_cast<const VolumeFloat*>(_inport2.getData()->getRepresentation<Volume>()),
		2,
		"Total cloud moisture mixing ratio"
	);
	setProgress(3.f / 6.f);
	handleVolume(
		dynamic_cast<const VolumeFloat*>(_inport3.getData()->getRepresentation<Volume>()),
		3,
		"Pressure"
	);
	setProgress(4.f / 6.f);
	handleVolume(
		dynamic_cast<const VolumeFloat*>(_inport4.getData()->getRepresentation<Volume>()),
		4,
		"Temperature"
	);
	setProgress(5.f / 6.f);
	handleVolume(
		dynamic_cast<const Volume3xFloat*>(_inport5.getData()->getRepresentation<Volume>()),
		5,
		"Wind Speed"
	);
	setProgress(6.f / 6.f);


	// sort the data by the voxel index for faster processing later
	std::sort(_data->data.begin(), _data->data.end(), sortByIndex);

	// And provide access to the data using the outport
    _outport.setData(_data, false);
}

} // namespace
