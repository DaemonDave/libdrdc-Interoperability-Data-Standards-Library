/**	\file $Id: wrapper_cpp_tests.cc,v 1.7 2008/10/20 22:38:43 cvsuser Exp $
	wrapper cpp tests 
*/
/* librdc - A ROBOTICS SOFTWARE STANDARDS LIBRARY

 HER MAJESTYTHE QUEEN IN RIGHT OF CANADA AS REPRESENTED BY THE MINISTER
 OF NATIONAL DEFENCE, CANADA, 2007

 Developed by: Tie Peng and Erickson, D. (DRDC Suffield)

 This library is free software;.  You can redistribute it and/or modify
 it under the terms and conditions of the GNU Lesser General Public
 License as published by the Free Software Foundation; either

 Version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.

 	You should have received a copy of the GNU Lesser General Public
 	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 	USA

 Licence is located in license.txt in libdrdc source root
*/
/*
 * Description  : libdrdc - 
 * Author       : Tie Peng
 * Purpose      : wrapper test cases
 * Revision     : $Id: wrapper_cpp_tests.cc,v 1.7 2008/10/20 22:38:43 cvsuser Exp $
 */

/**
	\brief 	test cases for cpp wrapped functions
	
		  
	\todo Wrapper testing $RCSfile: wrapper_cpp_tests.cc,v $ contains many test cases under the wrapper banner.
	This needs to be broken down to separate tests for various components so that 
	diagnosis of the breakages is easier. Break out test cases by struct type and 
	function and isolate to make testing 	obvious   DRE 20080916
*/



#include <stdio.h>
#include <assert.h>
#include "wrapper.h"
#include "libdrdc.h"

extern "C" {
#include "coordinate.h"
#include "homogeneous.h"
#include "quaternion.h"
#include "time_conv.h"
#include "data_conv.h"
#include "unit_conv.h"
#include "test.h"
}



int test_1(void);
int test_2(void);
int test_3(void);
int test_4(void);
int test_5(void);





//! exception_context for try catch context
struct exception_context the_exception_context[1];

int main(void) 
{
  test_1();
/*  test_2();
  test_3();
  test_4();
  test_5();
*/
  return 0;
}


/** testing matrix values inside the homogeneous matrix, undergoing a 45 degree spin 
/ to see if the values coincide to a tolerance
*/
int test_1(void) 
{

  drdc_HMatrix m;

  double m_exp[16]; // expected values
  double m_a[16];


  // set m with rotation axis angle
  m.fromRotAxis(AXIS_X, PI/4);

/* approx. expected values
		1  		0    0  0
		0    0.7  0.7 0 
	  0   -0.7  0.7 0 
		0     0    0  1
*/


  // load precomputed values for comparison
  m_exp[0] = 1.0; /*0*/
  m_exp[1] = Hex2Double(0x00000000,0x00000000); /*1*/
  m_exp[2] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[3] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[4] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[5] = cos(PI/4); /*0.707107*/
  m_exp[6] = cos(PI/4); /*0.707107*/
  m_exp[7] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[8] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[9] = -cos(PI/4);/*-0.707107*/
  m_exp[10] = cos(PI/4);/*0.707107*/
  m_exp[11] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[12] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[13] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[14] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[15] = 1.0; /*1*/
	
	// output values to arrays															
  m.toArray(m_a);
	// check
  if (0 == doubleChecker(100, 16, m_a, m_exp)) return 0;
  return -1;
}

int test_2(void) 
{
  drdc_lPosn l1, l2, l3, l_fuzz;
  double l3_a[3], l2_a[3], l1_a[3];
  double l3_a_exp[3];
  int bResult, one=1, zero=0;
  double fResult, fResult_exp;


  l1_a[0] = Hex2Double(0xbbb017c5,0x3fd46f59); /*0.319296*/
  l1_a[1] = Hex2Double(0x78cd9159,0x3fd7fe59); /*0.374899*/
  l1_a[2] = Hex2Double(0x7bc47a28,0x3febc4fb); /*0.867796*/
  l2_a[0] = Hex2Double(0x4aea408d,0x3fd7d1bc); /*0.372176*/
  l2_a[1] = Hex2Double(0xfb29e97c,0x3fb2dd59); /*0.0736901*/
  l2_a[2] = Hex2Double(0x9c08467c,0x3fc9944a); /*0.199838*/

  l1.set(l1_a[0], l1_a[1], l1_a[2]);
  l2.set(l2_a);
  l_fuzz.set(FUZZ_3);
  bResult = l1.compare(l2, l_fuzz);
  assert(0 == intChecker(1, &bResult, &one));
  bResult = l1.compare(l1, l_fuzz);
  assert(0 == intChecker(1, &bResult, &zero));

  l3 = l1+l2;
  l3.toArray(l3_a);
  l3_a_exp[0] = Hex2Double(0x034d2c29,0x3fe6208b); /*0.691473*/
  l3_a_exp[1] = Hex2Double(0xf7980bb8,0x3fdcb5af); /*0.448589*/
  l3_a_exp[2] = Hex2Double(0x116345e4,0x3ff11507); /*1.06763*/
  assert(0 == doubleChecker(1, 3, l3_a, l3_a_exp));

  l3 = -l1;
  l3.toArray(l3_a);
  l3_a_exp[0] = Hex2Double(0xbbb017c5,0xbfd46f59); /*-0.319296*/
  l3_a_exp[1] = Hex2Double(0x78cd9159,0xbfd7fe59); /*-0.374899*/
  l3_a_exp[2] = Hex2Double(0x7bc47a28,0xbfebc4fb); /*-0.867796*/
  assert(0 == doubleChecker(1, 3, l3_a, l3_a_exp));
  
  l3 = l2-l1;
  l3.toArray(l3_a);
  l3_a_exp[0] = Hex2Double(0x79d14640,0x3fab1314); /*0.0528799*/
  l3_a_exp[1] = Hex2Double(0xfa0316fa,0xbfd34702); /*-0.301209*/
  l3_a_exp[2] = Hex2Double(0xd4c26889,0xbfe55fe8); /*-0.667958*/
  assert(0 == doubleChecker(1, 3, l3_a, l3_a_exp));

  l3 = l1*3.;
  l3.toArray(l3_a);
  l3_a_exp[0] = Hex2Double(0x998823a8,0x3feea706); /*0.957889*/
  l3_a_exp[1] = Hex2Double(0x1a9a2d03,0x3ff1fec3); /*1.1247*/
  l3_a_exp[2] = Hex2Double(0x9cd35b9e,0x4004d3bc); /*2.60339*/
  assert(0 == doubleChecker(1, 3, l3_a, l3_a_exp));

  fResult = l1.dot(l2);
  fResult_exp = Hex2Double(0x6d8ff7d1,0x3fd478e7); /*0.3198793954796858*/;
  assert(0 == doubleChecker(1, 1, &fResult, &fResult_exp));

  l3 = l1.cross(l2);
  l3.toArray(l3_a);
  l3_a_exp[0] = Hex2Double(0x08f196b8,0x3f867812); /*0.0109712*/
  l3_a_exp[1] = Hex2Double(0x820b87d9,0x3fd0962a); /*0.259165*/
  l3_a_exp[2] = Hex2Double(0xf1a3ee81,0xbfbdb226); /*-0.116*/
  assert(0 == doubleChecker(1, 3, l3_a, l3_a_exp));

  fResult = l2.magnitude();
  fResult_exp = Hex2Double(0x25c51169,0x3fdb71ac); /*0.42881301582772*/;
  assert(0 == doubleChecker(1, 1, &fResult, &fResult_exp));


  l2.normalize();
  l2.toArray(l3_a);
  l3_a_exp[0] = Hex2Double(0x4ee8d445,0x3febc604); /*0.867922*/
  l3_a_exp[1] = Hex2Double(0xb3c8e71c,0x3fc5ff11); /*0.171847*/
  l3_a_exp[2] = Hex2Double(0x882e7621,0x3fddd35e); /*0.466026*/
  assert(0 == doubleChecker(1, 3, l3_a, l3_a_exp));

  return 0;
}


int test_3(void) 
{
  drdc_lPose lpose, lpose1;
  drdc_lePose lepose, lepose1;
  drdc_lPosn posn;
  drdc_Orient orient;
  drdc_eOrient rpy;
  
  double rpy_a[3], posn_a[3];
  double lpose_a[7], lpose1_a[7], lepose_a[6], lepose1_a[6], lpose_a_exp[7], lepose_a_exp[6];
  
  posn_a[0] = Hex2Double(0xe30dfbf5,0x3fa9572e); /*0.0494933*/
  posn_a[1] = Hex2Double(0x8bf51c60,0x3fe2227c); /*0.56671*/
  posn_a[2] = Hex2Double(0xdd28ba56,0x3fbf3675); /*0.121925*/
  rpy_a[0] = Hex2Double(0xbaab6730,0x3fe0b523); /*0.522112*/
  rpy_a[1] = Hex2Double(0x75ef5c21,0x3fbdf7a7); /*0.11706*/
  rpy_a[2] = Hex2Double(0x1339dab6,0x3fe8a32c); /*0.769918*/
  lpose_a_exp[0] = Hex2Double(0xe30dfbf5,0x3fa9572e); /*0.0494933*/
  lpose_a_exp[1] = Hex2Double(0x8bf51c60,0x3fe2227c); /*0.56671*/
  lpose_a_exp[2] = Hex2Double(0xdd28ba56,0x3fbf3675); /*0.121925*/
  lpose_a_exp[3] = Hex2Double(0x65b0c3a8,0x3fecc918); /*0.899548*/
  lpose_a_exp[4] = Hex2Double(0x413100d2,0x3fcbd9a3); /*0.217579*/
  lpose_a_exp[5] = Hex2Double(0xd9579a4d,0x3fc316da); /*0.149135*/
  lpose_a_exp[6] = Hex2Double(0xf4334d7a,0x3fd648a3); /*0.348184*/
  lepose_a_exp[0] = Hex2Double(0xe30dfbf5,0x3fa9572e); /*0.0494933*/
  lepose_a_exp[1] = Hex2Double(0x8bf51c60,0x3fe2227c); /*0.56671*/
  lepose_a_exp[2] = Hex2Double(0xdd28ba56,0x3fbf3675); /*0.121925*/
  lepose_a_exp[3] = Hex2Double(0xbaab6730,0x3fe0b523); /*0.522112*/
  lepose_a_exp[4] = Hex2Double(0x75ef5c21,0x3fbdf7a7); /*0.11706*/
  lepose_a_exp[5] = Hex2Double(0x1339dab6,0x3fe8a32c); /*0.769918*/

  rpy.set(rpy_a[0], rpy_a[1], rpy_a[2]);
  orient = rpy.to_Orient();
  posn.set(posn_a);
  lpose.set(posn,orient);
  lpose.toArray(lpose_a);
  assert(0 == doubleChecker(1, 7, lpose_a, lpose_a_exp));

  lepose.set(posn, rpy);


  lpose1 = lepose.to_lPose();
  lpose1.toArray(lpose1_a);
  assert(0 == doubleChecker(1, 7, lpose1_a, lpose_a_exp));
  
  lepose1=lpose.to_lePose();
  lepose1.toArray(lepose1_a);
  assert(0 == doubleChecker(1, 6, lepose1_a, lepose_a_exp));
  

  printf ("Testing Homogeneous ... \n");
  drdc_HMatrix hmat;
  double hmat_a[16];
  double hmat_a_exp[16];
  drdc_lPosn posn1;
  double posn1_a[3];
  drdc_HMatrix hmat2;
  double hmat2_a[16];
  double hmat2_a_exp[16];
  double rpy1_a[3];

  hmat = lpose.to_HMatrix();
  hmat.toArray(hmat_a);
  posn1 = hmat.getPosition();
  posn1.toArray(posn1_a);

  hmat_a_exp[0] = Hex2Double(0x4ef7d0ee,0x3fe6d156); /*0.713054*/
  hmat_a_exp[1] = Hex2Double(0x59a6605b,0x3fe61f3c); /*0.691313*/
  hmat_a_exp[2] = Hex2Double(0x2ff609bf,0xbfbde625); /*-0.116793*/
  hmat_a_exp[3] = Hex2Double(0x00000000,0x00000000); /*0*/
  hmat_a_exp[4] = Hex2Double(0x17f5d484,0xbfe1f7f5); /*-0.561518*/
  hmat_a_exp[5] = Hex2Double(0x5fa64c70,0x3fe5361b); /*0.662855*/
  hmat_a_exp[6] = Hex2Double(0xf62e00cc,0x3fdfb2f8); /*0.495299*/
  hmat_a_exp[7] = Hex2Double(0x00000000,0x00000000); /*0*/
  hmat_a_exp[8] = Hex2Double(0xe941986e,0x3fdade61); /*0.419823*/
  hmat_a_exp[9] = Hex2Double(0x46411f28,0xbfd267ed); /*-0.287593*/
  hmat_a_exp[10] = Hex2Double(0x037795d4,0x3feb8bf8); /*0.860836*/
  hmat_a_exp[11] = Hex2Double(0x00000000,0x00000000); /*0*/
  hmat_a_exp[12] = Hex2Double(0xe30dfbf5,0x3fa9572e); /*0.0494933*/
  hmat_a_exp[13] = Hex2Double(0x8bf51c60,0x3fe2227c); /*0.56671*/
  hmat_a_exp[14] = Hex2Double(0xdd28ba56,0x3fbf3675); /*0.121925*/
  hmat_a_exp[15] = Hex2Double(0x00000000,0x3ff00000); /*1*/
  assert(0 == doubleChecker(1, 16, hmat_a, hmat_a_exp));
  assert(0 == doubleChecker(1, 3, posn1_a, posn_a));

  hmat2_a_exp[0] = Hex2Double(0x2f2d4e76,0x3fc4481b); /*0.158451*/
  hmat2_a_exp[1] = Hex2Double(0x932c12da,0x3fe67168); /*0.701344*/
  hmat2_a_exp[2] = Hex2Double(0x74c24ba3,0xbfe63d5a); /*-0.694989*/
  hmat2_a_exp[3] = Hex2Double(0x00000000,0x00000000); /*0*/
  hmat2_a_exp[4] = Hex2Double(0xbd6f63e2,0xbfd0e4d8); /*-0.263968*/
  hmat2_a_exp[5] = Hex2Double(0xfb8c8faa,0x3fe6aace); /*0.708351*/
  hmat2_a_exp[6] = Hex2Double(0x9d1f9b8e,0x3fe4f2da); /*0.654645*/
  hmat2_a_exp[7] = Hex2Double(0x00000000,0x00000000); /*0*/
  hmat2_a_exp[8] = Hex2Double(0x503aa159,0x3fee7218); /*0.951428*/
  hmat2_a_exp[9] = Hex2Double(0x4eed7d70,0x3fb468ea); /*0.0797259*/
  hmat2_a_exp[10] = Hex2Double(0xcd482f00,0x3fd3081e); /*0.297371*/
  hmat2_a_exp[11] = Hex2Double(0x00000000,0x00000000); /*0*/
  hmat2_a_exp[12] = Hex2Double(0xe30dfbf5,0x3fa9572e); /*0.0494933*/
  hmat2_a_exp[13] = Hex2Double(0x8bf51c60,0x3fe2227c); /*0.56671*/
  hmat2_a_exp[14] = Hex2Double(0xdd28ba56,0x3fbf3675); /*0.121925*/
  hmat2_a_exp[15] = Hex2Double(0x00000000,0x3ff00000); /*1*/
  rpy1_a[0] = Hex2Double(0x073507fb,0x3fd800ea); /*0.375056*/
  rpy1_a[1] = Hex2Double(0x1ef3ede1,0x3fea5930); /*0.823387*/
  rpy1_a[2] = Hex2Double(0x5faabc74,0x3fa7e0b1); /*0.0466361*/

  rpy.set(rpy1_a);
  hmat2 = hmat * rpy.to_HMatrix();
  hmat2.toArray(hmat2_a);  
  printf ("Testing Homogeneous mult... \n");
  assert(0 == doubleChecker(1, 16, hmat2_a, hmat2_a_exp));

  return 0;
}


int test_4(void) {
  drdc_WPosn wposn, wposn1;
  drdc_WUTMPosn wutmposn;
  double Lon=-106.6278;
  double Lat= 52.1208;
  double el=473;
  drdc_UTMZone_t  zone;
  double UTMNorthing;
  double UTMNorthing_exp;
  double UTMEasting;
  double UTMEasting_exp;
  double UTMElevation;
  int UTMZoneNum;
  int UTMZoneNum_exp;
  char UTMZoneCh;
  char UTMZoneCh_exp;
  double wposn_a[3], wposn1_a[3];
  drdc_eOrient rpy;
  double rpy_a[3];
  drdc_Orient orient;
  drdc_WPose wpose;
  drdc_WUTMPose wutmpose;
  double wpose_a_exp[7],  wutmpose_a_exp[7];
  double wpose_a[7],  wutmpose_a[7];

  wposn.set(Lon*deg2rad, Lat*deg2rad, el);
  wutmposn=wposn.to_WUTMPosn();
  zone = wutmposn.getZone();
  UTMZoneNum = zone.zoneNumber;
  UTMZoneCh = zone.zoneLetter;
  UTMEasting = wutmposn.getEasting();
  UTMNorthing =  wutmposn.getNorthing();
  UTMElevation = wutmposn.getElevation();

  UTMNorthing_exp = Hex2Double(0xf04c92c8,0x4156085a); /*5775723.754673667*/;
  UTMEasting_exp = Hex2Double(0x75f3d9bf,0x4117b72d); /*388555.3651880286*/;
  UTMZoneNum_exp = 13;
  UTMZoneCh_exp = 'U';

  assert(0 == doubleChecker(1.0e+14, 1, &UTMEasting, &UTMEasting_exp));
  assert(0 == doubleChecker(1.0e+14, 1, &UTMNorthing, &UTMNorthing_exp));
  assert(0 == doubleChecker(1, 1, &UTMElevation, &el));
  assert(0 == intChecker(1, &UTMZoneNum, &UTMZoneNum_exp));
  assert(0 == charChecker(1, &UTMZoneCh, &UTMZoneCh_exp));

  wposn.toArray(wposn_a);
  wposn1= wutmposn.to_WPosn();
  wposn1.toArray(wposn1_a);
  assert(0 == doubleChecker(1.0e+6, 3, wposn1_a, wposn_a));

  rpy_a[0] = Hex2Double(0xfe0e09c8,0x3fe3221a); /*0.597913*/
  rpy_a[1] = Hex2Double(0xa5ea4d37,0x3fee5f70); /*0.94915*/
  rpy_a[2] = Hex2Double(0x2673721d,0x3fd27ba9); /*0.288798*/
  wpose_a_exp[0] = Hex2Double(0x6ba9cc69,0xbffdc6ae); /*-1.86101*/
  wpose_a_exp[1] = Hex2Double(0x53b715ac,0x3fed1c18); /*0.90968*/
  wpose_a_exp[2] = Hex2Double(0x00000000,0x407d9000); /*473*/
  wpose_a_exp[3] = Hex2Double(0x70715407,0x3feb89a6); /*0.860553*/
  wpose_a_exp[4] = Hex2Double(0x2eeb7134,0x3fc923f0); /*0.196409*/
  wpose_a_exp[5] = Hex2Double(0xa6a17a86,0x3fde11ee); /*0.469844*/
  wpose_a_exp[6] = Hex2Double(0xb9691aaa,0xbf864188); /*-0.0108672*/
  wutmpose_a_exp[0] = Hex2Double(0x75f3d9bf,0x4117b72d); /*388555*/
  wutmpose_a_exp[1] = Hex2Double(0xf04c92c8,0x4156085a); /*5.77572e+006*/
  wutmpose_a_exp[2] = Hex2Double(0x00000000,0x407d9000); /*473*/
  wutmpose_a_exp[3] = Hex2Double(0x70715407,0x3feb89a6); /*0.860553*/
  wutmpose_a_exp[4] = Hex2Double(0x2eeb7134,0x3fc923f0); /*0.196409*/
  wutmpose_a_exp[5] = Hex2Double(0xa6a17a86,0x3fde11ee); /*0.469844*/
  wutmpose_a_exp[6] = Hex2Double(0xb9691aaa,0xbf864188); /*-0.0108672*/

  rpy.set(rpy_a[0], rpy_a[1], rpy_a[2]);
  orient = rpy.to_Orient();
  wpose.set(wposn, orient);
  wutmpose = wpose.to_WUTMPose();
  wpose.toArray(wpose_a);
  wutmpose.toArray(wutmpose_a);

  zone = wutmpose.getZone();
  UTMZoneNum = zone.zoneNumber;
  UTMZoneCh = zone.zoneLetter;

  assert(0 == doubleChecker(1, 7, wpose_a, wpose_a_exp));
  assert(0 == doubleChecker(1.0e+14, 7, wutmpose_a, wutmpose_a_exp));
  assert(0 == intChecker(1, &UTMZoneNum, &UTMZoneNum_exp));
  assert(0 == charChecker(1, &UTMZoneCh, &UTMZoneCh_exp));

  return 0;

}


int test_5(void) {
  int exception;

  Try {

    double longtitudeDeg;
    double longtitudeRad;
    ieeeFpd64 fpd;
    unsigned char *buf=(unsigned char*) &fpd;
    int i;
    sint32_t longtitudeJausInteger;

    longtitudeDeg = -106.6278;
    longtitudeRad = -106.6278*deg2rad;

    fpd=ieeeFpd64FromDouble(longtitudeRad);

    printf("IEEE 754 Representaion: ");
    for(i=0; i < 8; i++)
      printf("%02X", buf[i]);

    //If endian conversion is required, use as follows
    printf("\nIEEE 754 Representaion: ");
    for(i=0; i < 8; i++)
      printf("%02X", buf[8-i-1]);

    longtitudeJausInteger = jausIntegerFromDouble(longtitudeDeg, -180., 180.);
    printf("\n");

    struct timeval utcTime, gpsTime;
    JausTime_t jausGpsTime;
    char jausGpsTimeString[80];
    uint32_t timeStamp;
    uint16_t dateStamp;

    gettimeofday(&utcTime, NULL);
    gpsTime=timeUtcToGps(14, &utcTime);
    jausTimeConvert(&gpsTime, &jausGpsTime);
    jausTimeToString(&jausGpsTime, jausGpsTimeString);
    printf("%s", jausGpsTimeString);
    timeStamp = jausGpsTime.timeStamp;
    dateStamp = jausGpsTime.dateStamp;

#define OOC_DEMO
#ifdef OOC_DEMO
    drdc_WPosn_t *GPSPosn = new_WPosn();
    drdc_WUTMPosn_t *UTMPosn = new_WUTMPosn();
    drdc_lPosn_t    *localPosn = new_lPosn();
    double localPosn_a[3];
    drdc_UTMZone_t zone;

    GPSPosn->set(GPSPosn, -106.6278*deg2rad, 52.1208*deg2rad, 473);
    GPSPosn->to_WUTMPosn(GPSPosn, UTMPosn);
    UTMPosn->to_lPosn(UTMPosn, localPosn);
    UTMPosn->getZone(UTMPosn, &zone);
    wp_print(GPSPosn);
    wp_print(UTMPosn);
    printf("%d %c\n", zone.zoneNumber, zone.zoneLetter);
    localPosn->to_WUTMPosn(localPosn, zone, UTMPosn);
    UTMPosn->to_WPosn(UTMPosn, GPSPosn);
    wp_print(GPSPosn);
    wp_print(UTMPosn);

    wp_print(localPosn);
    localPosn-> scale(localPosn, unitConvertDistance("m", "km"), localPosn);
    localPosn->toArray(localPosn, localPosn_a);
    printVector(3, localPosn_a);

    GPSPosn->destroy(GPSPosn);
    UTMPosn->destroy(UTMPosn);
    localPosn->destroy(localPosn);
#else

    drdc_WPosn GPSPosn;
    drdc_WUTMPosn UTMPosn;
    drdc_lPosn    localPosn;
    double localPosn_a[3];

    GPSPosn.set(-106.6278*deg2rad, 52.1208*deg2rad, 473);
    UTMPosn = GPSPosn.to_WUTMPosn();
    localPosn = UTMPosn.to_lPosn();
    wp_print(&localPosn);
    localPosn = localPosn * unitConvertDistance("m", "km");
    localPosn.toArray(localPosn_a);
    printVector(3, localPosn_a);
#endif

    drdc_HMatrix puma560[6], manipulatorTransform;
    drdc_lPose manipulatorPose;
    drdc_LinkSpecs_t linkSpecs[] = {
      {JOINT_REVOLUTE, 0, PI/2, 0},
      {JOINT_REVOLUTE, 0.4318, 0, 0},
      {JOINT_REVOLUTE, 0.0203, -PI/2, 0.1505},
      {JOINT_REVOLUTE, 0, PI/2, 0.4318},
      {JOINT_REVOLUTE, 0, -PI/2, 0},
      {JOINT_REVOLUTE, 0, 0, 0},
    };

    double jointOffsetOrAngle[] = {PI/8, 0, PI/4, 0, 0, 0};

    for(i=0; i < 6; i++) {
      puma560[i].fromLink(linkSpecs[i], jointOffsetOrAngle[i]);
    }

    manipulatorTransform = puma560[0] * puma560[1] * puma560[2] * puma560[3] *puma560[4] * puma560[5];

    wp_print(&manipulatorTransform);
    //Use Local Pose to represent manipulatr end effort pose
    manipulatorPose = manipulatorTransform.to_lPose();
    wp_print(&manipulatorPose);
    //Linked list can be used too.


  } Catch(exception) {
    fprintf(stderr, "***Exception = %d\n", exception);
  } 


  return 0;
}
