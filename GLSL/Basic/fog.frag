/* Created by Marko Galesic
 * Referencing code from the book and slides
 */

uniform float fogDensity;
uniform vec4 fogColor;
uniform vec3 eye;

varying float fogDistance;
varying vec3 N;
varying vec3 L;

vec4 fog()
{
    float d = -log2(1.0 - fogDensity);
    float f = exp2(-1.0 * d * fogDistance * fogDistance);
    
    return f * gl_FrontMaterial.diffuse  + (1.0 - f) * fogColor;
}

vec4 diffuseLighting()
{
    return dot(N, L) * gl_LightSource[0].diffuse;
}

void main()
{
    gl_FragColor = fog() + (0.0 * diffuseLighting());
}