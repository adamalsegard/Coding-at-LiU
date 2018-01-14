#extension GL_EXT_gpu_shader4 : enable

in vec3 in_position;

varying out float vertexId;

uniform mat4 viewMatrix_;
uniform mat4 projectionMatrix_;
uniform int nVertices;
uniform int iRender;

void main() {
	// Move the vertices from volume coordinates [0,1] to world coordinates [-1,1]
	vec3 pos = (in_position - 0.5) * 2.0;
    pos.z /= 5.0;

    gl_Position = projectionMatrix_ * viewMatrix_ * vec4(pos, 1.0);

    vertexId = float(gl_VertexID - iRender) / float(nVertices + 1 );

}
