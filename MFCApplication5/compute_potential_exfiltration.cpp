/*--------------------------------------------------------------*/
/* 								*/
/*			compute_potential_exfiltration		*/
/*								*/
/*								*/
/*	NAME							*/
/*	compute_potential_exfiltration - estimates maximum	*/
/*		poteential exfiltration  due to soil control	*/
/*								*/
/*	SYNOPSIS						*/
/*	double	compute_potential_exfiltration(			*/
/*			int	,				*/
/*			double	,				*/
/*			double	,				*/
/*			double	,				*/
/*			double	,				*/
/*			double	,				*/
/*			double	,				*/
/*			double	,				*/
/*			double	)				*/
/*								*/
/*	returns:						*/
/*	potential_exfiltration - (m water/ day ) maximum pot 	*/
/*		exfiltration due to soil control.		*/
/*								*/
/*	OPTIONS							*/
/*	int verbose_flag 					*/
/*	double	S (DIM) - relative saturation			*/
/*	double	sat_deficit_z (m) - depth to water table	*/
/*	double	Ksat_0 (m/day) - saturate hydraulic 		*/
/*			conductivity at the surface.		*/
/*	double	m_z (m-1) - decay parameter for Ksat_0		*/
/*	double	psi_air_entry (Pa) -  air entry pressure.	*/
/*	double	pore_size_index (DIM) - Brooks Corey pore size  */
/*			index parameter.			*/
/*	double 	p_0  (dim) - porosity  at surface 		*/
/*	double 	p  (m-1) - porosity  decay rate 		*/
/*								*/
/*	DESCRIPTION						*/
/*	Estimates the maximum possible rate of exfiltration of	*/
/*	soil water due to soil control only.  This rate should	*/
/*	be limited to the climatic potential evaporation.	*/
/*								*/
/*	Reference: 						*/
/*	Wigmosta,et.al. 1994 A distributed hydrology-vegetation */
/*	model for complex terrain.  WRR v. 30, no. 6.		*/
/*								*/
/*	Which is a somewhat modified result of the development:	*/
/*								*/
/*	Eagleson, P. S. (1978) "Climate, Soil and Vegetation 	*/
/*	3.  A simplified Model of Soil Moisture Movement in the	*/
/*	Liquid Phase.  WRR, Vol 14, No 5.			*/
/*								*/
/*	We use the geometric mean hydraulic conductivity	*/
/*		of the top and bottom of the unsat zone.	*/
/*								*/
/*								*/
/*	PROGRAMMER NOTES					*/
/*								*/
/*	RAF, Jan 21 1997 					*/
/*	New code for OJP.					*/
/*								*/
/*--------------------------------------------------------------*/
#include "stdafx.h"
#include <stdio.h>

#include <math.h>
#include "CHESS.h"
#include "Constants.h"

double	compute_potential_exfiltration(
	int 	verbose_flag,
	double	S,
	double 	sat_deficit_z,
	double	Ksat_0,
	double	m_z,
	double	psi_air_entry,
	double	pore_size_index,
	double 	p,
	double	p_0)
{
	/*--------------------------------------------------------------*/
	/*	Local function declaration				*/
	/*--------------------------------------------------------------*/

	/*--------------------------------------------------------------*/
	/*	Local variable definition.				*/
	/*--------------------------------------------------------------*/
	double	porosity_average;
	double	Ksat_average, wilting_point;
	double	potential_exfiltration;

	/*--------------------------------------------------------------*/
	/*	Estimate mean porosity.					*/
	/*--------------------------------------------------------------*/
	p = 1. / 1.2;
	//porosity_average =  p_0 *(1-exp(-1*sat_deficit_z/p));
	porosity_average = p_0 * p* (1 - min(exp(-1 * sat_deficit_z / p), 1.)); //modified by guoping
	//printf("porosity average is %12.8f %12.8f \n",porosity_average,p_0);
	//getchar();

	/*--------------------------------------------------------------*/
	/*	Estimate mean saturated conductivity.			*/
	/*--------------------------------------------------------------*/
	if (m_z > ZERO)
		Ksat_average = m_z * Ksat_0 *(1 - exp(-1 * sat_deficit_z / m_z));
	else
		Ksat_average = Ksat_0;

	S = max(0, min(S, 1));

	/*--------------------------------------------------------------*/
	/*	Plug everything into the equation for max infiltration  */
	/*--------------------------------------------------------------*/
	potential_exfiltration =
		pow(S, (1 / (2 * pore_size_index)) + 2) * sqrt((8 * porosity_average
			* Ksat_average * psi_air_entry) / (3 * (1 + 3 * pore_size_index)
				* (1 + 4 * pore_size_index)));


	wilting_point = exp(-1.0*log(2.5 / psi_air_entry)
		* pore_size_index)* porosity_average; //



//getchar();}
 //printf("wilting_point is %12.8f %12.8f %12.8f\n",wilting_point,porosity_average,Ksat_0);
	potential_exfiltration = min(max((S - wilting_point)*porosity_average, 0.0), potential_exfiltration);
	//if(wilting_point<1){
	//	printf("potential_exfiltration %10.8f %10.8f \n",potential_exfiltration,S);
	//	printf("porosity_average %f %f %f \n",porosity_average,p_0,wilting_point);
	//	getchar();
	//}	
	return(potential_exfiltration);
} /*potential_exfiltration*/
