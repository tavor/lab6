#include "noises.h"

void
smokedensity(	point Pcur; output color Lscatter; output float smokedensity)
{
	Lscatter = 0;
	illuminance (Pcur)
	{
		extern color Cl;
		float foglight = 1;
		lightsource("__foglight", foglight);
		if (foglight > 0)
			Lscatter += Cl;
	}
}

volume
myfog(	float opacdensity = 1, lightdensity = 1;
        float stepsize = 0.1;)
{
    float len = length(I);
    Pcur = P - I;
	color Cv = 0, Ov = 0; /* color & opacity of volume that we accumulate */
    

	while (len > 0)
	{
		smokedensity(Pcur, smokedensity, Lscatter);
        
        Cv += (1 - Ovol) * stepsize * Lscatter;
        Ov += (1 - Ovol) * stepsize * smokedensity;
        
        Pcur += stepsize * normalize(I);

        len -= stepsize;
	}
	
	Ci = Cv + (1 - Ov) * Ci;
	Oi = Ov + (1 - Ov) * Oi;
}
