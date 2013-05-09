/* Created by Marko Galesic
 * Referencing (heavily) code from the book and slides
 */

// Distance fog shader
volume
myfog 	(	
		float distance = 1;
		color background = color (0.5, 0.5, 0.5);
        float fogDensity = 0.8;
        
	)
{
    float d = 1 - exp (-length(I)/distance);

	Ci = mix (Ci, background, d * fogDensity);
	Oi = mix (Oi, color(1, 1, 1), d * fogDensity);
}
