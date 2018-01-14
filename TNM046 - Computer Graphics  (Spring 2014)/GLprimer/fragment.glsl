
#version 330 core

in vec3 interpolatedNormal;
in vec2 st;
in vec3 L;
in vec3 interpolatedColor;

out vec4 finalcolor;


void main() {


    //finalcolor = vec4(interpolatedColor, 1.0);
    //finalcolor = abs(vec4(interpolatedNormal, 1.0));





    // Phong model

    // vec3 L is the light direction
    // vec3 V is the view direction - (0 ,0 ,1) in view space
    // vec3 N is the normal
    // vec3 R is the computed reflection direction
    // float n is the "shininess" parameter
    // vec3 ka is the ambient reflection color
    // vec3 Ia is the ambient illumination color
    // vec3 kd is the diffuse surface reflection color
    // vec3 Id is the illumination color
    // vec3 ks is the diffuse surface reflection color
    // vec3 Is is the illumination color

    vec3 V = vec3(0.0,0.0,1.0);
    vec3 N = interpolatedNormal;
    float n = 10;
    vec3 ka = vec3(0.2,0.2,0.2);
    vec3 Ia = vec3(0.5,0.5,0.5);
    vec3 kd = vec3(0.6,0.6,0.6);
    vec3 Id = vec3(1.0,1.0,1.0);
    vec3 ks = vec3(0.8,0.8,0.8);
    vec3 Is = vec3(1.0,1.0,1.0);



    // This assumes that N, L and V are normalized.
    vec3 R = 2.0*dot(N ,L) *N - L; // Could also have used the function reflect()
    float dotNL = max(dot(N , L) , 0.0) ; // If negative , set to zero
    float dotRV = max(dot(R , V) , 0.0) ;
    vec3 shadedcolor = Ia * ka + Id * kd * dotNL + Is * ks *pow( dotRV , n);
    finalcolor = vec4( shadedcolor , 1.0) ;


}
