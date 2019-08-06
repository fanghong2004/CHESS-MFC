//------------------------------------------------------------------------------------------------------------------------------
// open daily-step input files
// created by Guoping Tang
//------------------------------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include "CHESS.h"

#include "Constants.h"

struct	input_Clim_Files open_Clim_Files(char *inClimFile, char *prefix)
{
	//------------------------------------------------------------------------------------------------------------------------------
	//	local variable declarations 							
	//------------------------------------------------------------------------------------------------------------------------------
	char  inPrec[MAXSTR], inTmin[MAXSTR], inTmax[MAXSTR], inCO2[MAXSTR];
	struct input_Clim_Files inClimFiles;


	//fang
	errno_t err;

	//------------------------------------------------------------------------------------------------------------------------------
	//	Attempt to open the daily clim sequence file for each critical clim parameter and read them in.		
	//------------------------------------------------------------------------------------------------------------------------------
	//strcpy_s(file_name, file_prefix);
	strcat_s(inClimFile,sizeof(inClimFile)+100, prefix);
	strcpy_s(inPrec, inClimFile);
	strcpy_s(inTmin, inClimFile);
	strcpy_s(inTmax, inClimFile);
	strcpy_s(inCO2, inClimFile);
	strcat_s(inPrec, "_daily.rain");
	strcat_s(inTmin, "_daily.tmin");
	strcat_s(inTmax, "_daily.tmax");
	strcat_s(inCO2, "_annual.CO2");

	//if ((inClimFiles.pPrec = fopen(inPrec, "r")) == NULL) {
	if (err = fopen_s(&inClimFiles.pPrec, inPrec, "r")) {
		printf("can not open input precipitation file \n");
		exit(0);
	}
	//if ((inClimFiles.pTmin = fopen(inTmin, "r")) == NULL) {
	if (err = fopen_s(&inClimFiles.pTmin, inTmin, "r")) {
		printf("can not open input minimum temperature file \n");
		exit(0);
	}

	//if ((inClimFiles.pTmax = fopen(inTmax, "r")) == NULL) {
	if (err = fopen_s(&inClimFiles.pTmax, inTmax, "r")) {
		printf("can not open input maximum temperature file \n");
		exit(0);
	}

	//if ((inClimFiles.pCO2 = fopen(inCO2, "r")) == NULL) {
	if (err = fopen_s(&inClimFiles.pCO2, inCO2, "r")) {
		printf("can not open input annual CO2 concentration file \n");
		exit(0);
	}

	return(inClimFiles);
}
