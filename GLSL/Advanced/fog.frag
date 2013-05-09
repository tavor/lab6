/* Created by Marko Galesic
 * Referencing code from the book and slides
 */
uniform float fudgeFactor;
uniform float fudgeExponent;
uniform vec3 eye;
uniform float stepsize;

varying float fogDistance;
varying vec3 N;
varying vec3 L;
varying vec3 V;

float mieScattering(float fudgeFactor, float fudgeExponent)
{
    float rayLength = fogDistance;
	float Ov = 0.0;
    
    while (rayLength > 0.0)
	{
        // Calculate the dust point along the ray we are "shooting"
        vec3 dustPoint = eye + normalize(V) * rayLength;
        
        // Get the vector from the light to the dust point
        vec3 dustIncidentLightVector = dustPoint - gl_LightSource[0].position.xyz;
        
        // Get the vector from the dust point to the eye
        vec3 dustPointViewVector = eye - dustPoint;
        
        // Calculate the angle between view and light vector
        float VdotL = dot(normalize(dustPointViewVector), normalize(dustIncidentLightVector));
        
        // Calculate Mie Scattering cos term and mie term itself
        float cosTerm = pow((1.0 + VdotL)/2.0, fudgeExponent);
        float mieTerm = 1.0 + fudgeFactor * cosTerm;
        
        // Use Mie term as fog density function
        Ov += (1.0 - Ov) * mieTerm;
        
        rayLength -= stepsize;
	}
    
    return Ov;
}

vec4 diffuseLighting()
{
    return dot(N, L) * gl_LightSource[0].diffuse;
}

vec4 specularLighting()
{
    vec3 R = reflect(-normalize(L), normalize(N));
    return pow( max(dot(R, -normalize(V)), 0.0), 4.0) * vec4(1.0, 1.0, 1.0, 1.0);
}

void main()
{
    float mieScattering = mieScattering(fudgeFactor, fudgeExponent);
    gl_FragColor = mieScattering * gl_FrontMaterial.diffuse * diffuseLighting() + mieScattering * specularLighting();
}