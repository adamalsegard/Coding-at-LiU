/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Created between 2005 and 2012 by The Voreen Team                   *
 * as listed in CREDITS.TXT <http://www.voreen.org>                   *
 *                                                                    *
 * This file is part of the Voreen software package. Voreen is free   *
 * software: you can redistribute it and/or modify it under the terms *
 * of the GNU General Public License version 2 as published by the    *
 * Free Software Foundation.                                          *
 *                                                                    *
 * Voreen is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * in the file "LICENSE.txt" along with this program.                 *
 * If not, see <http://www.gnu.org/licenses/>.                        *
 *                                                                    *
 * The authors reserve all rights not expressly granted herein. For   *
 * non-commercial academic use see the license exception specified in *
 * the file "LICENSE-academic.txt". To get information about          *
 * commercial licensing please contact the authors.                   *
 *                                                                    *
 **********************************************************************/

#include "modules/tnm093/include/tnm_volume3xcombiner.h"

#include "voreen/core/datastructures/volume/volumeatomic.h"

namespace voreen {

Volume3xCombiner::Volume3xCombiner()
    : Processor()
	, _inportX(Port::INPORT, "in.x")
	, _inportY(Port::INPORT, "in.y")
	, _inportZ(Port::INPORT, "in.z")
	, _outport(Port::OUTPORT, "out")
{
	addPort(_inportX);
	addPort(_inportY);
	addPort(_inportZ);
	addPort(_outport);
}

void Volume3xCombiner::process() {
	const VolumeFloat* x = _inportX.getData()->getRepresentation<VolumeFloat>();
	const VolumeFloat* y = _inportY.getData()->getRepresentation<VolumeFloat>();
	const VolumeFloat* z = _inportZ.getData()->getRepresentation<VolumeFloat>();

	Volume3xFloat* volume = new Volume3xFloat(x->getDimensions());

	VRN_FOR_EACH_VOXEL(i, tgt::svec3(0, 0, 0), volume->getDimensions()) {
		volume->voxel(i) = tgt::vec3(
			x->voxel(i),
			y->voxel(i),
			z->voxel(i)
		);
	}

	VolumeHandle* handle = new VolumeHandle(volume, tgt::vec3(1.f), tgt::vec3(0.f));
	_outport.setData(handle);
	//_outport.setData(new VolumeHandle(volume, tgt::vec3(1.f)));
}

} // namespace
