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

void main()
{
    V = (gl_ModelViewMatrix * gl_Vertex).xyz - eye;
    fogDistance = length(V);
    N = gl_NormalMatrix * gl_Normal;
    L = gl_LightSource[0].position.xyz - (gl_ModelViewMatrix * gl_Vertex).xyz;
    gl_Position = ftransform();
}