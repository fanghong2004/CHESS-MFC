
/*--------------------------------------------------------------*/
/* 								*/
/*		recompute_gamma			*/
/*								*/
/*	NAME							*/
/*	recompute_gamma - recomputes total and individual 	*/
/*	gamma values for subsurface routing to replace		*/
/*	tographic gradients by water table gradients		*/
/*								*/
/*								*/
/*	SYNOPSIS						*/
/*	recompute_gamma(					*/
/*			 struct  patch_object *,		*/
/*				double)				*/
/*								*/
/*								*/
/*	OPTIONS							*/
/*								*/
/*	DESCRIPTION						*/
/*								*/
/*								*/
/*	PROGRAMMER NOTES					*/
/*								*/
/*								*/
/*--------------------------------------------------------------*/
#include "stdafx.h"
#include <stdio.h>
#include <math.h>

#include "CHESS.h"
#include "Constants.h"

double recompute_gamma(struct patch_object *patch,
	double total_gamma)
{
	/*--------------------------------------------------------------*/
	/*	Local variable definition.				*/
	/*--------------------------------------------------------------*/
	int i, d;
	double adjustment, revised_total_gamma;
	double z1, z2, water_table_z1, water_table_z2;
	/*--------------------------------------------------------------*/
	/*	for now, if water table is above the surface we		*/
	/*	we set saturation deficit to zero, since return flow	*/
	/*	is modelled separately and should not be taken into	*/
	/*	account in modelling surface gradients			*/
	/*--------------------------------------------------------------*/

	adjustment = 0.0;
	z1 = patch->z;
	if (patch->sat_deficit_z > ZERO)
		water_table_z1 = (z1 - patch->sat_deficit_z);
	else
		water_table_z1 = z1;
	d = 0;

	if (patch->num_neighbours > 0)
		for (i = 0; i < patch->num_neighbours; i++) {
			z2 = patch->neighbours[i].patch->z;
			if (patch->neighbours[i].patch->sat_deficit_z > 0)
				water_table_z2 = (z2 - patch->neighbours[i].patch->sat_deficit_z);
			else
				water_table_z2 = z2;
			if (fabs(z1 - z2) > ZERO) {
				adjustment += max(((water_table_z1 - water_table_z2) / (z1 - z2) *
					patch->neighbours[i].gamma), 0.0);
			}
			else adjustment = 0.0;
		}
	else
		adjustment = 1.0;
	revised_total_gamma = adjustment * total_gamma;

	return(revised_total_gamma);
} /*recompute_gamma*/
