/* Created by Marko Galesic
 * Referencing code from the book and slides
 */

uniform float fogDensity;
uniform vec4 fogColor;
uniform float stepsize;
uniform vec3 eye;

varying float fogDistance;
varying vec3 N;
varying vec3 L;

vec4 fog()
{
    float rayLength = fogDistance;
	vec4 Ov = vec4(0.0, 0.0, 0.0, 0.0);

    while (rayLength > 0.0)
	{
        Ov += (1.0 - Ov) * fogDensity;
        
        rayLength -= stepsize;
	}

    
    return Ov * fogColor * gl_FrontMaterial.diffuse  + (1.0 - Ov) * fogColor;
}

vec4 diffuseLighting()
{
    return dot(N, L) * gl_LightSource[0].diffuse;
}

void main()
{
    gl_FragColor = fog() + (0.0 * diffuseLighting());
}