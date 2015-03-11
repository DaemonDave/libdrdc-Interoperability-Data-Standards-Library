// librdc - A ROBOTICS SOFTWARE STANDARDS LIBRARY

// HER MAJESTYTHE QUEEN IN RIGHT OF CANADA AS REPRESENTED BY THE MINISTER
// OF NATIONAL DEFENCE, CANADA, 2007

// Developed by:  Erickson, D. (DRDC Suffield)

// This library is free software;.  You can redistribute it and/or modify
// it under the terms and conditions of the GNU Lesser General Public
// License as published by the Free Software Foundation; either

// Version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA

// Licence is located in license.txt in libdrdc source root

/*
 * Description  : libdrdc - 
 * Author       : Tie Peng
 * Purpose      :
 * Revision     : $Id: coordinate.h,v 1.5 2008/09/15 14:05:13 cvsuser Exp $
 */


#ifndef COORDINATE_H
#define COORDINATE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#define WGS84_A   6378137.0
#define WGS84_F   (1.0 / 298.257223563)


/*!
	\brief
	
	Coordinate contains functions to convert various pose representations. 
	
	The functions located here are: 
	- Local Coordinate Frame	
		- Latitude / Longitude (2D Spherical) to/from  Universal Trans Mercator (UTM)  	
	
	- World Coordinate Frame
		- Latitude / Longitude (2D Spherical) to/from  Universal Trans Mercator (UTM) 
	
		
	using the World Geodetic Survey WGS 84 datum 		
			
					
		 	
*/ 


/**
 * @addtogroup Coordinate Coordinate Reference Frame API
 */
/** @{ */


/** 
 * Lat/Lon to %UTM Northing/Easting Conversion
 *
 * This function converts the specified lat/lon coordinate to %UTM coordinate.
 *
 * @param a Input. Ellipsoid semi-major axis, in meters. (For WGS84 datum, use 6378137.0).
 * @param f Input. Ellipsoid flattening. (For WGS84 datum, use 1 / 298.257223563).
 * @param Lat Input. Latitude in radians.
 * @param Long Input. Longtitude in radians.
 * @param UTMNorthing Output. %UTM Northing in meters. 
 * @param UTMEasting Output. %UTM Easting in meters. 
 * @param UTMZoneNum Output. %UTM zone number.
 * @param UTMZoneCh Output. %UTM zone character.
 * 
 * @return It returns zero if successful. Otherwise, it returns one if
 * errors occur.
 */
int LatLon_to_UTM(const double a, const double f, const double Lat, const double Long, double *UTMNorthing, double *UTMEasting, unsigned char *UTMZoneNum, char *UTMZoneCh);
/** 
 * %UTM to Lat/Lon Conversion
 * 
 * This function converts the specified %UTM coordinate lat/lon coordinate.
 *
 * @param a Input. Ellipsoid semi-major axis, in meters. (For WGS84 datum, use 6378137.0).
 * @param f Input. Ellipsoid flattening. (For WGS84 datum, use 1 / 298.257223563).
 * @param UTMNorthing Input. %UTM Northing in meters. 
 * @param UTMEasting Input. %UTM Easting in meters.
 * @param UTMZoneNum  Input. %UTM zone number.
 * @param UTMZoneCh Input. %UTM zone character.
 * @param Lat Output. Latitude in radians.
 * @param Long Output. Longtitude in radians.
 * 
 * @return 
 */
int UTM_to_LatLon(const double a, const double f, const double UTMNorthing, const double UTMEasting, const unsigned char UTMZoneNum, const char UTMZoneCh, double *Lat, double *Long);


/** 
 * %UTM Position to World Position 
 *
 * This function is a wrapper of UTM_to_LatLon.
 * 
 * @param a Input. Ellipsoid semi-major axis, in meters. (For WGS84 datum, use 6378137.0).
 * @param f Input. Ellipsoid flattening. (For WGS84 datum, use 1 / 298.257223563).
 * @param zoneNumber Input. %UTM zone number.
 * @param zoneLetter Input. %UTM zone character.
 * @param worldUTMPosition Input.  %UTM position vector - [easting, northing, elevation].
 * @param worldPosition Output. %World position vector- [longtiude, latitude, elevation].
 * 
 * @return It returns zero if successful. Otherwise, it returns one if
 * errors occur.
 */
int WUTMPosn_to_WPosn(const double a, const double f, const unsigned char zoneNumber, const char zoneLetter, const double *worldUTMPosition, double *worldPosition);

/** 
 * World Position to UTM Position
 * 
 * This function is a wrapper of LatLon_to_UTM.
 *
 * @param a Input. Ellipsoid semi-major axis, in meters. (For WGS84 datum, use 6378137.0).
 * @param f Input. Ellipsoid flattening. (For WGS84 datum, use 1 / 298.257223563).
 * @param worldPosition Input. World position vector - [longtiude, latitude, elevation].
 * @param zoneNumber Output. %UTM zone number.
 * @param zoneLetter Output. %UTM zone character.
 * @param worldUTMPosition Output.  UTM vector - [easting, northing, elevation].
 * 
 * @return It returns zero if successful. Otherwise, it returns one if
 * errors occur.
 */
int WPosn_to_WUTMPosn(const double a, const double f, const double *worldPosition, unsigned char *zoneNumber, char *zoneLetter, double *worldUTMPosition);


/** 
 * %Cartesian to %Spherical Conversion
 * 
 * This function converts ECEF XYZ coordinate spherical coordinate.
 *
 * @param cartesian %Cartesian vector - [x, y, z].
 * @param spherical Spherical vector - [Azimuth, Zenith, Radius].
 * 
 * @return It returns zero if successful. Otherwise, it returns one if
 * errors occur.
 */
int cartesian_to_spherical(const double *cartesian, double *spherical);

/** 
 * %Spherical to %Cartesian Conversion
 *
 * This function converts spherical coordinate to ECEF XYZ coordinate.
 * 
 * @param cartesian %Cartesian vector -[x, y, z].
 * @param spherical %Spherical vector - [Azimuth, Zenith, Radius].
 * 
 * @return It returns zero if successful. Otherwise, it returns one if
 * errors occur.
 */
int spherical_to_cartesian(const double *spherical, double *cartesian);

/** 
 * World Position to Cartesian Conversion
 * 
 * This function converts global geographical coordinate to ECEF XYZ coordinate.
 *
 * @param a Input. Ellipsoid semi-major axis, in meters. (For WGS84 datum, use 6378137.0).
 * @param f Input. Ellipsoid flattening. (For WGS84 datum, use 1 / 298.257223563).
 * @param falseElevation False elevation. 
 * @param worldPosition World position vector - [longtitude, latitude, elevation].
 * @param cartesian Cartesian vector - [x, y, z]. 
 * 
 * @return It returns zero if successful. Otherwise, it returns one if
 * errors occur.
 */
int WPosn_to_lPosn(const double a, const double f, const double falseElevation, const double *worldPosition, double *cartesian);

/** 
 * %Cartesian to World Position Conversion
 * 
 * This function converts ECEF XYZ coordinate to global geographical coordinate.
 *
 * @param a Input. Ellipsoid semi-major axis, in meters. (For WGS84 datum, use 6378137.0).
 * @param f Input. Ellipsoid flattening. (For WGS84 datum, use 1 / 298.257223563).
 * @param falseElevation False elevation.
 * @param cartesian %Cartesian vector - [x, y, z].
 * @param worldPosition World position vector - [longtitude, latitude, elevation]. 
 * 
 * @return It returns zero if successful. Otherwise, it returns one if
 * errors occur.
 */
int lPosn_to_WPosn(const double a, const double f, const double falseElevation, const double *cartesian, double *worldPosition);


/** 
 * Degree-Minute-Second to Decimal Degree Conversion
 * 
 * @param degrees Degree value. 
 * @param minutes Minute value.
 * @param seconds Second value.
 * 
 * @return Decimal degree value.
 */
double  DMS_to_DecimalDegree(const double degrees, const double minutes, const double seconds);


/** @} */

#endif
