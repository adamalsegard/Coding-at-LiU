// variables for storing compositing results
vec4 result = vec4(0.0);

#define SAMPLING_BASE_INTERVAL_RCP 200.0

struct VOLUME_STRUCT {
    sampler3D volume_;              // the actual dataset normalized
    vec3 datasetDimensions_;        // the dataset's resolution, e.g. [ 256.0, 128.0, 128.0]
    vec3 datasetDimensionsRCP_;     // Reciprocal of the dataset dimension (= 1/datasetDimensions_)
};

struct TEXTURE_PARAMETERS {
    vec2 dimensions_;        // the texture's resolution, e.g. [256.0, 128.0]
    vec2 dimensionsRCP_;
};

struct LIGHT_SOURCE {
    vec3 position_;        // light position in world space
    vec3 ambientColor_;    // ambient color (r,g,b)
    vec3 diffuseColor_;    // diffuse color (r,g,b)
    vec3 specularColor_;   // specular color (r,g,b)
    vec3 attenuation_;     // attenuation (constant, linear, quadratic)
};

// uniforms needed for shading
uniform vec3 cameraPosition_;   // in world coordinates
uniform float shininess_;       // material shininess parameter
uniform LIGHT_SOURCE lightSource_;

// Settings for the raycaster
uniform float samplingStepSize_;
uniform float samplingRate_; 

// declare entry and exit parameters
uniform sampler2D entryPoints_;            // ray entry points
uniform TEXTURE_PARAMETERS entryParameters_;
uniform sampler2D exitPoints_;             // ray exit points
uniform TEXTURE_PARAMETERS exitParameters_;

// declare volume
uniform VOLUME_STRUCT volumeStruct_;    // volume data with parameters

// delcare transfer function
uniform sampler1D transferFunc_;

/////////////////////////////////////////////////////

vec3 calculateGradient(in vec3 samplePosition) {
    const vec3 h = volumeStruct_.datasetDimensionsRCP_;
    // Implement central differences
    vec3 grad;
    vec3 hx = vec3(h.x, 0.0f, 0.0f);
    vec3 hy = vec3(0.0f, h.y, 0.0f);
    vec3 hz = vec3(0.0f, 0.0f, h.z);
    grad.x = (texture(volumeStruct_.volume_, samplePosition + hx).a - texture(volumeStruct_.volume_, samplePosition - hx).a);///(2*h.x);
    grad.y = (texture(volumeStruct_.volume_, samplePosition + hy).a - texture(volumeStruct_.volume_, samplePosition - hy).a);///(2*h.y);
    grad.z = (texture(volumeStruct_.volume_, samplePosition + hz).a - texture(volumeStruct_.volume_, samplePosition - hz).a);///(2*h.z);
        
    return grad;
}

vec3 applyPhongShading(in vec3 pos, in vec3 gradient, in vec3 ka, in vec3 kd, in vec3 ks) {
    
    vec3 V = -normalize(cameraPosition_ - pos);
    vec3 N = normalize(gradient);
    float n = shininess_;
    vec3 L = normalize(lightSource_.position_ - pos);
    vec3 Ia = lightSource_.ambientColor_;
    vec3 Id = lightSource_.diffuseColor_;
    vec3 Is = lightSource_.specularColor_;


    // This assumes that N, L and V are normalized.
    vec3 R = 2.0*dot(N ,L) *N - L; // Could also have used the function reflect()
    float dotNL = abs(dot(N , L)); 
    float dotRV = abs(dot(R , V));
    vec3 finalcolor = Ia * ka + Id * kd * dotNL + Is * ks *pow( dotRV , n);
    
    return finalcolor;
}

void rayTraversal(in vec3 first, in vec3 last) {
    // calculate the required ray parameters
    float t     = 0.0;
    float tIncr = 0.0;
    float tEnd  = 1.0;
    vec3 rayDirection = last - first;
    tEnd = length(rayDirection);
    rayDirection = normalize(rayDirection);
    tIncr = 1.0/(samplingRate_ * length(rayDirection*volumeStruct_.datasetDimensions_));
    
    bool finished = false;
    while (!finished) {
        vec3 samplePos = first + t * rayDirection;
        float intensity = texture(volumeStruct_.volume_, samplePos).a;
        
        vec3 gradient = calculateGradient(samplePos);

        vec4 color = texture(transferFunc_, intensity);
        color.rgb = applyPhongShading(samplePos, gradient, color.rgb, color.rgb, vec3(1.0,1.0,1.0));
  
        // if opacity greater zero, apply compositing
        if (color.a > 0.0 && length(gradient)>0.00001 ) {
            color.a = 1.0 - pow(1.0 - color.a, samplingStepSize_ * SAMPLING_BASE_INTERVAL_RCP);
            result.rgb = result.rgb + (1-result.a)*color.rgb*color.a;
            result.a = result.a + (1-result.a)*color.a;

        }

        // early ray termination
        if (result.a > 1.0)
            finished = true;
        
        t += tIncr;
        finished = finished || (t > tEnd);
    }
}

void main() {
    vec3 frontPos = texture(entryPoints_, gl_FragCoord.xy * entryParameters_.dimensionsRCP_).rgb;
    vec3 backPos = texture(exitPoints_, gl_FragCoord.xy * exitParameters_.dimensionsRCP_).rgb;

    // determine whether the ray has to be casted
    if (frontPos == backPos)
        // background needs no raycasting
        discard;
    else
        // fragCoords are lying inside the bounding box
        rayTraversal(frontPos, backPos);

    FragData0 = result;
}
