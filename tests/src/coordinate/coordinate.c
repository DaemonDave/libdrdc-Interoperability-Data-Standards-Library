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
 * Revision     : $Id: coordinate.c,v 1.3 2008/09/03 22:04:39 cvsuser Exp $
 */


#include <math.h>
/* #include <stdio.h> */
/* #include <stdlib.h> */
#ifndef LIBDRDC_H
#include "libdrdc.h"
#endif
#include "coordinate.h"

static char UTMLetterDesignator(double Lat);



/*Reference ellipsoids derived from Peter H. Dana's website-
  http://www.utexas.edu/depts/grg/gcraft/notes/datum/elist.html
  Department of Geography, University of Texas at Austin
  Internet: pdana@mail.utexas.edu
  3/22/95

  Source
  Defense Mapping Agency. 1987b. DMA Technical Report: Supplement to Department of Defense World Geodetic System
  1984 Technical Report. Part I and II. Washington, DC: Defense Mapping Agency
*/
/* $Id: coordinate.c,v 1.3 2008/09/03 22:04:39 cvsuser Exp $ */



int LatLon_to_UTM(const double a, const double f, const double Lat, const double Long, double *UTMNorthing, double *UTMEasting, unsigned char *UTMZoneNum, char *UTMZoneCh) {
  //converts lat/long to UTM coords.  Equations from USGS Bulletin 1532
  //East Longitudes are positive, West longitudes are negative.
  //North latitudes are positive, South latitudes are negative
  //Lat and Long are in decimal degrees
  //Written by Chuck Gantz- chuck.gantz@globalstar.com


  double e2 = 1.0 - SQ(1.0 - f);
  //double a = ellipsoid_array[ReferenceEllipsoid].equat_radius;
  //printf("equat_radius %7.2f \n", a  );
  //double eccSquared = ellipsoid_array[ReferenceEllipsoid].sqr_eccentricity;
  //printf("square of eccentricity: %3.9f \n", eccSquared  );
  double k0 = 0.9996;

  double LongOrigin;
  double eccPrimeSquared;
  double N, T, C, A, M;

  //Make sure the longitude is between -180.00 .. 179.9
  // -180.00 .. 179.9;
  //double LongTemp = (LongDeg+180) - (int)((LongDeg+180)/360)*360-180;
  //printf("LongTemp %f \n", LongTemp);
  
  // convert longitude and latitude in degrees to radians
  //double LatRad = LatDeg*deg2rad;
  //double LongRad = LongTemp*deg2rad;
  
  double LatRad = Lat;
  double LongRad = Long;
  double LatDeg = LatRad * rad2deg;
  double LongDeg = LongRad * rad2deg;
  double LongTemp = (LongDeg+180) - (int)((LongDeg+180)/360)*360-180;

  double LongOriginRad;
  int    ZoneNumber;

  // computethe zone number
  ZoneNumber = (int)((LongTemp + 180)/6) + 1;
  //printf("ZoneNumber %d \n", ZoneNumber  );
  
  if( LatDeg >= 56.0 && LatDeg < 64.0 && LongTemp >= 3.0 && LongTemp < 12.0 )
    ZoneNumber = 32;

  // Special zones for Svalbard
  if( LatDeg >= 72.0 && LatDeg < 84.0 )
    {
      if(      LongTemp >= 0.0  && LongTemp <  9.0 ) ZoneNumber = 31;
      else if( LongTemp >= 9.0  && LongTemp < 21.0 ) ZoneNumber = 33;
      else if( LongTemp >= 21.0 && LongTemp < 33.0 ) ZoneNumber = 35;
      else if( LongTemp >= 33.0 && LongTemp < 42.0 ) ZoneNumber = 37;
    }

  // adjust origin to middle of zone
  LongOrigin = (ZoneNumber - 1)*6 - 180 + 3;              //+3 puts origin in middle of zone
  // convert origin to radians
  LongOriginRad = LongOrigin * deg2rad;

  //compute the UTM Zone from the latitude and longitude
  //sprintf(UTMZone, "%d%c", ZoneNumber, UTMLetterDesignator(LatDeg));
  *UTMZoneNum=ZoneNumber;
  *UTMZoneCh =UTMLetterDesignator(LatDeg);

  // compute eccentricity prime
  eccPrimeSquared = (e2)/(1-e2);

  N = a/sqrt(1-e2*sin(LatRad)*sin(LatRad));
  T = tan(LatRad)*tan(LatRad);
  C = eccPrimeSquared*cos(LatRad)*cos(LatRad);
  // compute A from centre of zone
  A = cos(LatRad)*(LongRad-LongOriginRad);
    
  M = a*((1   -e2/4      - 3*e2*e2/64    - 5*e2*e2*e2/256)*LatRad
	 - (3*e2/8   + 3*e2*e2/32    + 45*e2*e2*e2/1024)*sin(2*LatRad)
	 + (15*e2*e2/256 + 45*e2*e2*e2/1024)*sin(4*LatRad)
	 - (35*e2*e2*e2/3072)*sin(6*LatRad));

  *UTMEasting = (double)(k0*N*(A+(1-T+C)*A*A*A/6
			       + (5-18*T+T*T+72*C-58*eccPrimeSquared)*A*A*A*A*A/120)
			 + 500000.0);

  *UTMNorthing = (double)(k0*(M+N*tan(LatRad)*(A*A/2+(5-T+9*C+4*C*C)*A*A*A*A/24
					       + (61-58*T+T*T+600*C-330*eccPrimeSquared)*A*A*A*A*A*A/720)));
  if(LatDeg < 0)
    *UTMNorthing += 10000000.0;                         //10000000 meter offset for southern hemisphere

  return 0;
}


/** 
 * UTM Latitude Zone
 * 
 * @param Lat 
 * 
 * @return 
 */
char UTMLetterDesignator(double Lat)
{
    //This routine determines the correct UTM letter designator for the given latitude
    //returns 'Z' if latitude is outside the UTM limits of 84N to 80S
    //Written by Chuck Gantz- chuck.gantz@globalstar.com
    char LetterDesignator;

    if((84 >= Lat) && (Lat >= 72)) LetterDesignator = 'X';
    else if((72 > Lat) && (Lat >= 64)) LetterDesignator = 'W';
    else if((64 > Lat) && (Lat >= 56)) LetterDesignator = 'V';
    else if((56 > Lat) && (Lat >= 48)) LetterDesignator = 'U';
    else if((48 > Lat) && (Lat >= 40)) LetterDesignator = 'T';
    else if((40 > Lat) && (Lat >= 32)) LetterDesignator = 'S';
    else if((32 > Lat) && (Lat >= 24)) LetterDesignator = 'R';
    else if((24 > Lat) && (Lat >= 16)) LetterDesignator = 'Q';
    else if((16 > Lat) && (Lat >= 8))  LetterDesignator = 'P';
    else if(( 8 > Lat) && (Lat >= 0))  LetterDesignator = 'N';
    else if(( 0 > Lat) && (Lat >= -8)) LetterDesignator = 'M';
    else if((-8> Lat) && (Lat >= -16)) LetterDesignator = 'L';
    else if((-16 > Lat) && (Lat >= -24)) LetterDesignator = 'K';
    else if((-24 > Lat) && (Lat >= -32)) LetterDesignator = 'J';
    else if((-32 > Lat) && (Lat >= -40)) LetterDesignator = 'H';
    else if((-40 > Lat) && (Lat >= -48)) LetterDesignator = 'G';
    else if((-48 > Lat) && (Lat >= -56)) LetterDesignator = 'F';
    else if((-56 > Lat) && (Lat >= -64)) LetterDesignator = 'E';
    else if((-64 > Lat) && (Lat >= -72)) LetterDesignator = 'D';
    else if((-72 > Lat) && (Lat >= -80)) LetterDesignator = 'C';
    else LetterDesignator = 'Z';                            //This is here as an error flag to show that the Latitude is outside the UTM limits

    return LetterDesignator;
}


int UTM_to_LatLon(const double a, const double f, const double UTMNorthing, const double UTMEasting, const unsigned char UTMZoneNum, const char UTMZoneCh, double *Lat, double *Long) {
    //converts UTM coords to lat/long.  Equations from USGS Bulletin 1532
    //East Longitudes are positive, West longitudes are negative.
    //North latitudes are positive, South latitudes are negative
    //Lat and Long are in decimal degrees.
    //Written by Chuck Gantz- chuck.gantz@globalstar.com

    double k0 = 0.9996;
    double e2 = 1.0 - SQ(1.0 - f);
    double eccPrimeSquared;
    double e1 = (1-sqrt(1-e2))/(1+sqrt(1-e2));
    double N1, T1, C1, R1, D, M;
    double LongOrigin, LongOriginRad;
    double mu, phi1, phi1Rad;
    double x, y;
    int ZoneNumber;
    char ZoneLetter;
    int NorthernHemisphere;                                 //1 for northern hemispher, 0 for southern

    x = UTMEasting - 500000.0;                              //remove 500,000 meter offset for longitude
    y = UTMNorthing;

    //ZoneNumber = strtoul(UTMZone, &ZoneLetter, 10);
    ZoneNumber=UTMZoneNum;
    ZoneLetter=UTMZoneCh;
    if((ZoneLetter - 'N') >= 0)
        NorthernHemisphere = 1;                             //point is in northern hemisphere
    else
    {
        NorthernHemisphere = 0;                             //point is in southern hemisphere
        y -= 10000000.0;                                    //remove 10,000,000 meter offset used for southern hemisphere
    }

    LongOrigin = (ZoneNumber - 1)*6 - 180 + 3;              //+3 puts origin in middle of zone
    LongOriginRad = LongOrigin * deg2rad;

    eccPrimeSquared = (e2)/(1-e2);

    M = y / k0;
    mu = M/(a*(1-e2/4-3*e2*e2/64-5*e2*e2*e2/256));

    phi1Rad = mu    + (3*e1/2-27*e1*e1*e1/32)*sin(2*mu)
        + (21*e1*e1/16-55*e1*e1*e1*e1/32)*sin(4*mu)
        +(151*e1*e1*e1/96)*sin(6*mu);
    phi1 = phi1Rad*rad2deg;

    N1 = a/sqrt(1-e2*sin(phi1Rad)*sin(phi1Rad));
    T1 = tan(phi1Rad)*tan(phi1Rad);
    C1 = eccPrimeSquared*cos(phi1Rad)*cos(phi1Rad);
    R1 = a*(1-e2)/pow(1-e2*sin(phi1Rad)*sin(phi1Rad), 1.5);
    D = x/(N1*k0);

    *Lat = phi1Rad - (N1*tan(phi1Rad)/R1)*(D*D/2-(5+3*T1+10*C1-4*C1*C1-9*eccPrimeSquared)*D*D*D*D/24
        +(61+90*T1+298*C1+45*T1*T1-252*eccPrimeSquared-3*C1*C1)*D*D*D*D*D*D/720);
    *Lat = *(Lat);

    *Long = (D-(1+2*T1+C1)*D*D*D/6+(5-2*C1+28*T1-3*C1*C1+8*eccPrimeSquared+24*T1*T1)
        *D*D*D*D*D/120)/cos(phi1Rad);
    *Long = LongOriginRad + *(Long);

    return 0;
}


int WUTMPosn_to_WPosn(const double a, const double f, const unsigned char zoneNumber, const char zoneLetter, const double *worldUTMPosition, double *worldPosition) {
  double lat, lon;
  UTM_to_LatLon(a,f,worldUTMPosition[1],worldUTMPosition[0],zoneNumber,zoneLetter,&lat,&lon);
  worldPosition[0]=lon; worldPosition[1]=lat; worldPosition[2]=worldUTMPosition[2];

  return 0;
}

int WPosn_to_WUTMPosn(const double a, const double f, const double *worldPosition, unsigned char *zoneNumber, char *zoneLetter, double *worldUTMPosition) {
  double northing, easting;
  LatLon_to_UTM(a,f,worldPosition[1],worldPosition[0],&northing,&easting,zoneNumber,zoneLetter);
  worldUTMPosition[0]=easting; worldUTMPosition[1]=northing; worldUTMPosition[2]=worldPosition[2];
  return 0;
}


int cartesian_to_spherical(const double *cartesian, double *spherical) {
  double _r;

  spherical[0]   = atan2(cartesian[1], cartesian[0]);
  spherical[2]   = sqrt(SQ(cartesian[0]) + SQ(cartesian[1]) + SQ(cartesian[2]));
  _r     = sqrt(SQ(cartesian[0]) + SQ(cartesian[1]));
  spherical[1]   = atan2(_r,cartesian[2]);
  return 0;
}

int spherical_to_cartesian(const double *spherical, double *cartesian) {
  double _r;
  _r     = spherical[2] * sin(spherical[1]);
  cartesian[2]   = spherical[2] * cos(spherical[1]);
  cartesian[0]   = _r * cos(spherical[0]);
  cartesian[1]   = _r * sin(spherical[0]);
  return 0;
}

int WPosn_to_lPosn(const double a, const double f, const double falseElevation, const double *worldPosition, double *cartesian) {
  double e2 = 1.0 - SQ(1.0 - f);
  double N;
  double height = falseElevation + worldPosition[2];

  N  = a / sqrt(1 - e2 * SQ(sin(worldPosition[1])));
  cartesian[0] = (N + height) * cos(worldPosition[1]) * cos(worldPosition[0]);
  cartesian[1] = (N + height) * cos(worldPosition[1]) * sin(worldPosition[0]);
  cartesian[2] = ((1 - e2) * N + height) * sin(worldPosition[1]);
  return 0;
}

int lPosn_to_WPosn(const double a, const double f, const double falseElevation, const double *cartesian, double *worldPosition) {

  double e2 = 1.0 - SQ(1.0 - f);
  double b, ep, p, th, N, t, height;

  b     = sqrt(SQ(a) * (1 - e2));
  ep    = sqrt((SQ(a) - SQ(b)) / SQ(b));
  p     = sqrt(SQ(cartesian[0]) + SQ(cartesian[1]));
  th    = atan2(a*cartesian[2], b*p);
  worldPosition[0]  = atan2(cartesian[1], cartesian[0]);
  worldPosition[1]  = atan2( (cartesian[2] + SQ(ep) * b * pow(sin(th),3)), (p - e2 * a * pow(cos(th),3)));
  N     = a / sqrt(1 - e2 * SQ(sin(worldPosition[1])));

  height   = p * cos(worldPosition[1]) + cartesian[2]*sin(worldPosition[1]) - (a*a)/N;
  height   = p/cos(worldPosition[1]) - N;
  t    = 2* PI;
  worldPosition[0] = fmod( worldPosition[0], t);
  
  if (fabs(cartesian[0]) < 1.0 && fabs(cartesian[1]) < 1.0) {
    height = fabs(cartesian[2]) - b;
  }
  worldPosition[2] = height-falseElevation;
  return 0;
}



// convert the DMS number to a decimal verion
double  DMS_to_DecimalDegree(const double degrees, const double minutes, const double seconds) {
  double decimalDegree;

  decimalDegree = degrees;

  // solve for negative value of degrees
  if ( degrees >= 0) {
    decimalDegree += minutes/60;
  }
  else {
    decimalDegree -= minutes/60;
  }

  // solve for negative value of degrees
  if ( degrees >= 0) {
    decimalDegree += seconds/3600;
  }
  else {
    decimalDegree -= seconds/3600;
  }

  return decimalDegree;
}
