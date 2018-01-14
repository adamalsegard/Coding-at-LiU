in float vertexId;

void main() {
	float color = 1.0 - vertexId;
	color = vertexId * vertexId;
	color = clamp(vertexId, 0.1, 1.0);



	gl_FragData[0] = vec4(vec3(1.0 - color), 1.0);
}
