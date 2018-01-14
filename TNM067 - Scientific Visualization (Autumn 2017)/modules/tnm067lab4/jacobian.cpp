/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2016 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#include <modules/tnm067lab4/jacobian.h>

namespace inviwo {

namespace util {

mat2 jacobian(const ImageSampler &sampler, vec2 position, vec2 offset) { 
    vec2 ox(offset.x,0);
    vec2 oy(0,offset.y);
    mat2 J; 
	// TASK 1: Calculate the Jacobian J
	vec4 v_deltaPosX = sampler.sample(position + ox);
	vec4 v_deltaNegX = sampler.sample(position - ox);
	vec4 v_deltaPosY = sampler.sample(position + oy);
	vec4 v_deltaNegY = sampler.sample(position - oy);

	vec2 V_x = (v_deltaPosX - v_deltaNegX) / (2 * offset.x);
	vec2 V_y = (v_deltaPosY - v_deltaNegY) / (2 * offset.y);

	J = mat2(vec2(V_x.x, V_x.y), vec2(V_y.x, V_y.y));

    return J;
}

}

}  // namespace
