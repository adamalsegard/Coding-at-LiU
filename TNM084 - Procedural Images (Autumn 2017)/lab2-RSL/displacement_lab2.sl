// Adam Alsegård 17/11 - 2017

#include "voronoi.sl"

// A simple RSL displacement shader for a Rambutan fruit
// The 'hairHeight' varying variable will be sent to the surface shader
displacement displacement_rambutan(output varying float hairHeight = 0.0) {
	
	// Fruit body - only small displacement
	float fruitBody = 0.1 * noise(P) + 0.2 * noise(5*P);
	
	// Get hair strand "spikes" from cellular noise
	point Ptex = transform("object", P+8); // Shift texture coords slightly for a better variance 
	float freq = 12.0; // How many hair stems
	float jitter = 1.9; // "Variance" of hair roots
	float feat1, feat2;
	point pt1, pt2;
	voronoi_f2_3d(Ptex, freq, jitter, feat1, feat2, pt1, pt2);
	
	// Calculate spikes in the center of first feature 
	// and clamp values to resonable values
	float hair = 0.1 / feat1;
	hair = clamp(hair, 0.0, 1.2);
	
	// Get a smooth transition of colors in the surface shader
	hairHeight = hair > fruitBody ? hair : fruitBody;
		
	// Apply noise to position
	P = P + N * 0.5 * (fruitBody + hair);
	
	// Add curls to hair strands
	vector curls = noise(P) - 0.5;
	if(hair > 0.7) {
		P += 0.5*hair*curls;
	}
	
	// Calculate new normals
	N = calculatenormal(P);

}


	