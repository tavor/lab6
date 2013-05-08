volume
myfog(	float smokedensity = 0.01, stepsize = 0.1;)
{
    float len = length(I);
	color Ov = 0, Cv = 0;

	while (len > 0)
	{
        Ov += (1 - Ov) * smokedensity;
        Cv += (1 - Ov) * smokedensity;

        len -= stepsize;
	}
	
	Ci = Cv + (1 - Ov) * Ci;
	Oi = Ov + (1 - Ov) * Oi;
}
