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

uniform sampler2D vfColor;
uniform sampler2D noiseColor;

uniform int steps;
uniform float stepSize;

in vec3 texCoord_;

/*
* Traverse the vector field and sample the noise image
* @param posF Starting position
* @param stepSize length of each step
* @param steps the number of steps to traverse
* @param v the accumulated value from sampling the noise image
* @param c the number of samples used for v
*
*/
void traverse(vec2 posF, float stepSize, int steps, inout float v, inout int c){
    
	// TASK 5 - Implement LIC
	// Traverse the vectorfield starting at `posF for `steps` with using `stepSize` and sample the noiseColor texture for each position.
    // Store the accumulated value in v and the amount of samples in c.

	int currentStep = 0;

	while( currentStep < steps) {
		// Sample the noise texture at current position.
		v += texture2D(noiseColor, posF).r;

		// Update the sample position by figure out what direction the input is heading (Euler)
		//posF += normalize(texture2D(vfColor, posF).xy) * stepSize;

		// TASK 8 (optional): Update position with Runge Kutta-4 instead
		vec2 k1 = texture2D(vfColor, posF).xy;
		vec2 k2 = texture2D(vfColor, posF + (normalize(k1)*stepSize/2.f)).xy;
		vec2 k3 = texture2D(vfColor, posF + (normalize(k2)*stepSize/2.f)).xy;
		vec2 k4 = texture2D(vfColor, posF + normalize(k3)*stepSize).xy;
		posF += (stepSize / 6.f) * normalize(k1 + 2*k2 + 2*k3 + k4);

		currentStep++;
	}
	// Add number of samples (could use steps*2 in the end as well...).
	c += currentStep;
}


void main(void) {
    float v = texture(noiseColor,texCoord_.xy).r;
    int c = 1;
    
    // TASK 5 - Traverse the vector field both forward and backwards to calculate the output color.
	traverse(texCoord_.xy, stepSize, steps, v, c);
	traverse(texCoord_.xy, -stepSize, steps, v, c);
	
	// Take the avarage.
	v /= c;

    FragData0 = vec4(v,v,v,1);
}
