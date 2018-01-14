// Adam Alsegård 17/11 - 2017

// A simple RSL surface shader for a Rambutan fruit
surface surface_rambutan() {

	// Init colors
	color Cd;
	color yellowRed = color( 255/255, 150/255, 0/255);
	color pinkRed = color( 220/255, 20/255, 60/255);
	color greenRed = color( 198/255, 255/255, 26/255);
	
	// Initialize the "hair strand height" variable
	float hairHeight = 0.0;

	// Check if variable was successfully obtained from displacement shader
	if(displacement("hairHeight", hairHeight) == 1) {
    
		// Give fruit body a yellowRed hue, and then as the strands get higher we
		// go to pinkRed and later greenRed at the edges.
		float minYellow = 0.08;
		float maxYellow = 0.25;
		float minGreen = 0.5;
		float maxGreen = 0.7;
		if(hairHeight < maxYellow) {
			if(hairHeight > minYellow) {
				float alpha = (hairHeight - minYellow) / (maxYellow-minYellow);
				Cd = mix( yellowRed, pinkRed, alpha);
			} else {
				Cd = yellowRed;
			}
		}
		else if (hairHeight > minGreen) {
			if(hairHeight < maxGreen) {
				float alpha = (hairHeight - minGreen) / (maxGreen-minGreen);
				Cd = mix( pinkRed, greenRed, alpha);
			} 
			else {
				Cd = greenRed;
			}
		}
		else {
			Cd = pinkRed;
		}
		
	} else {
		// Variable not received: give it the same color as the body 
		Cd = yellowRed;
	};
	
	// Apply the color and take light sources into account
	Ci = Cd * diffuse(N);
}
