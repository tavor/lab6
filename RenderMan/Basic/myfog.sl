// Distance fog shader
volume
myfog 	(	
		float distance = 1;
		color background = color (0.5, 0.5, 0.5);
	)
{
	float d = 1 - exp (-length(I)/distance);
	Ci = mix (Ci, background, d);
	Oi = mix (Oi, color(1, 1, 1), d);
}
