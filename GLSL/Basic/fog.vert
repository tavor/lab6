/* Created by Marko Galesic
 * Referencing code from the book and slides
 */

uniform float fogDensity;
uniform vec4 fogColor;
uniform vec3 eye;

varying float fogDistance;
varying vec3 N;
varying vec3 L;

void main()
{
    fogDistance = length((gl_ModelViewMatrix * gl_Vertex).xyz - eye);
    N = gl_NormalMatrix * gl_Normal;
    L = gl_LightSource[0].position.xyz - (gl_ModelViewMatrix * gl_Vertex).xyz;
    gl_Position = ftransform();
}