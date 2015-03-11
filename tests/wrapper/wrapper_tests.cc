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
 * Description  : libdrdc - wrapper_tests.cc
 * Author       : Tie Peng
 * Purpose      : This file exercises various wrapped data representations 
 * Revision     : $Id: wrapper_tests.cc,v 1.2 2008/09/09 15:22:53 cvsuser Exp $
 */


#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "wrapper.h"


extern "C" {
#include "test.h"
#include "data_conv.h"
#include "unit_conv.h"
#include "time_conv.h"
}

struct exception_context the_exception_context[1];

int swapBytes(int size, unsigned char *srcBuffer, unsigned char *destBuffer) 
{
  unsigned int i;
  unsigned char tempBuffer[8];
  memcpy(tempBuffer, srcBuffer, size);
  for(i=0; i< size; i++) {
    destBuffer[i] = tempBuffer[size - i - 1];
  }
  return 0;
}

int main(void) 
{
  HMatrix hmat;
  Quaternion q;

  double m_exp[16];
  double q_exp[4];
  Axis_t axis=AXIS_X;

  ieeeFpd64 fpd;
  unsigned char *buf=(unsigned char*) &fpd;
  int i;
  int exception;

  Datum_t reference;
  GlobPosition gpsPosition;
  UTM utmPosition, utmPositionKm;
  
  struct timeval utcTime, gpsTime;
  JausTime_t jausGpsTime, jausUtcTime;
  char jausGpsTimeString[80], jausUtcTimeString[80];

  HMatrix puma560[6];
  LinkSpecs_t linkSpecs[] = {
    {JOINT_REVOLUTE, 0, PI/2, 0},
    {JOINT_REVOLUTE, 0.4318, 0, 0},
    {JOINT_REVOLUTE, 0.0203, -PI/2, 0.1505},
    {JOINT_REVOLUTE, 0, PI/2, 0.4318},
    {JOINT_REVOLUTE, 0, -PI/2, 0},
    {JOINT_REVOLUTE, 0, 0, 0},
    };

  double jointOffsetOrAngle[] = {0, 0, 0, 0, 0, 0};

  for(i=0; i < 6; i++) {
    puma560[i]=HMatrix(linkSpecs[i], jointOffsetOrAngle[i]);
    printMatrix(puma560[i].matrix);
  }



  reference.a = WGS84_A;
  reference.f = WGS84_F;


  Try {
    gpsPosition=GlobPosition(-106.6278*deg2rad, 52.1208*deg2rad, 473);
    utmPosition=UTM(reference, gpsPosition);
    utmPositionKm = utmPosition * unitConvertDistance("m", "mmkm");
  } Catch (exception) fprintf(stderr, "***exception %d\n", exception);
  
  printVector(3, u2v(utmPosition).v);
  printVector(3, u2v(utmPositionKm).v);


  gettimeofday(&utcTime, NULL);
  gpsTime=timeUtcToGps(14, &utcTime);
  
  jausTimeConvert(&gpsTime, &jausGpsTime);
  jausTimeConvert(&utcTime, &jausUtcTime);

  jausTimeToString(&jausGpsTime, jausGpsTimeString);
  jausTimeToString(&jausUtcTime, jausUtcTimeString);

  printf("%s%s\n", jausGpsTimeString, jausUtcTimeString);

  hmat=HMatrix(AXIS_X, PI/4);
  q=Quaternion(hmat);

  m_exp[0] = Hex2Double(0x00000000,0x3ff00000); /*1*/
  m_exp[1] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[2] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[3] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[4] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[5] = Hex2Double(0x667f3bcd,0x3fe6a09e); /*0.707107*/
  m_exp[6] = Hex2Double(0x667f3bcc,0x3fe6a09e); /*0.707107*/
  m_exp[7] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[8] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[9] = Hex2Double(0x667f3bcc,0xbfe6a09e); /*-0.707107*/
  m_exp[10] = Hex2Double(0x667f3bcd,0x3fe6a09e); /*0.707107*/
  m_exp[11] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[12] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[13] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[14] = Hex2Double(0x00000000,0x00000000); /*0*/
  m_exp[15] = Hex2Double(0x00000000,0x3ff00000); /*1*/
  q_exp[0] = Hex2Double(0xcf328d46,0x3fed906b); /*0.92388*/
  q_exp[1] = Hex2Double(0xa6aea964,0x3fd87de2); /*0.382683*/
  q_exp[2] = Hex2Double(0x00000000,0x00000000); /*0*/
  q_exp[3] = Hex2Double(0x00000000,0x00000000); /*0*/

  assert(0 == doubleChecker(1, 16, hmat.matrix, m_exp));
  assert(0 == doubleChecker(1, 4, q2v(q).v, q_exp));
  //PrintMatrix(hmat.m);


  fpd=ieeeFpd64FromDouble(3.14159);
  //buf=(char *)&fpd;
  
  for(i=0; i < 8; i++)
    printf("%02X", buf[i]);

  printf ("\n");
  for(i=0; i < 8; i++) {
    //buf[i] = ((fpd >> (8 - i - 1)*8) & 0xFF);
    printf("%02X", buf[8-i-1]);
  }

  printf ("\n");
  swapBytes(8, buf, buf);
  for(i=0; i < 8; i++)
    printf("%02X", buf[i]);


 
  return 0;
}
