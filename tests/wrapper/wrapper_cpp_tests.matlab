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

struct exception_context the_exception_context[1];

int main(void) {
  test_1();
  test_2();
  test_3();
  test_4();
  test_5();
  return 0;
}



int test_1(void) {

  drdc_HMatrix m;
  drdc_Orient q;
  drdc_eOrient rpy;

  double m_exp[16];
  double q_exp[4];
  double rpy_exp[3];

  double m_a[16];
  double q_a[4];


  m.fromRotAxis(AXIS_X, PI/4);
  q=m.to_Orient();

  //& m_exp=rotx(pi/4);
  //& prnval m_exp;
  //& q_tmp=quaternion(m_exp);
  //& q_exp=q_tmp.d;
  //& prnval q_exp;

  m.toArray(m_a);
  q.toArray(q_a);

  assert(0 == doubleChecker(1, 16, m_a, m_exp));
  assert(0 == doubleChecker(1, 4, q_a, q_exp));

  return 0;
}



int test_2(void) {
  drdc_lPosn l1, l2, l3, l_fuzz;
  double l3_a[3], l2_a[3], l1_a[3];
  double l3_a_exp[3];
  int bResult, one=1, zero=0;
  double fResult, fResult_exp;


  //& l1_a = rand(3,1);
  //& prnval l1_a;
  //& l2_a = rand(3,1);
  //& prnval l2_a;

  l1.set(l1_a[0], l1_a[1], l1_a[2]);
  l2.set(l2_a);
  l_fuzz.set(FUZZ_3);
  bResult = l1.compare(l2, l_fuzz);
  assert(0 == intChecker(1, &bResult, &one));
  bResult = l1.compare(l1, l_fuzz);
  assert(0 == intChecker(1, &bResult, &zero));

  l3 = l1+l2;
  l3.toArray(l3_a);
  //& l3_a_exp = l1_a + l2_a;
  //& prnval l3_a_exp;
  assert(0 == doubleChecker(1, 3, l3_a, l3_a_exp));

  l3 = -l1;
  l3.toArray(l3_a);
  //& l3_a_exp = -l1_a;
  //& prnval l3_a_exp;
  assert(0 == doubleChecker(1, 3, l3_a, l3_a_exp));

 l3 = l2-l1;
  l3.toArray(l3_a);
  //& l3_a_exp = l2_a - l1_a;
  //& prnval l3_a_exp;
  assert(0 == doubleChecker(1, 3, l3_a, l3_a_exp));

  l3 = l1*3.;
  l3.toArray(l3_a);
  //& l3_a_exp = 3*l1_a;
  //& prnval l3_a_exp;
  assert(0 == doubleChecker(1, 3, l3_a, l3_a_exp));

  fResult = l1.dot(l2);
  //& fResult_exp = dot(l1_a, l2_a);
  //& prnval fResult_exp;
  assert(0 == doubleChecker(1, 1, &fResult, &fResult_exp));

  l3 = l1.cross(l2);
  l3.toArray(l3_a);
  //& l3_a_exp = cross(l1_a, l2_a);
  //& prnval l3_a_exp;
  assert(0 == doubleChecker(1, 3, l3_a, l3_a_exp));

  fResult = l2.magnitude();
  //& fResult_exp = norm(l2_a);
  //& prnval fResult_exp;
  assert(0 == doubleChecker(1, 1, &fResult, &fResult_exp));


  l2.normalize();
  l2.toArray(l3_a);
  //& l3_a_exp = l2_a / norm(l2_a);
  //& prnval l3_a_exp;
  assert(0 == doubleChecker(1, 3, l3_a, l3_a_exp));

  return 0;
}


int test_3(void) {
  drdc_lPose lpose, lpose1;
  drdc_lePose lepose, lepose1;
  drdc_lPosn posn;
  drdc_Orient orient;
  drdc_eOrient rpy;

  double rpy_a[3], posn_a[3];
  double lpose_a[7], lpose1_a[7], lepose_a[6], lepose1_a[6], lpose_a_exp[7], lepose_a_exp[6];

  //& posn_a=rand(3,1);
  //& rpy_a=rand(3,1);
  //& tr=rpy2tr(rpy_a(3), rpy_a(2), rpy_a(1));
  //& q_m=quaternion(tr);
  //& q_m_a=q_m.d;
  //& lpose_a_exp=cat(1,posn_a,q_m_a');
  //& lepose_a_exp=cat(1,posn_a,rpy_a);
  //& prnval posn_a;
  //& prnval rpy_a;
  //& prnval lpose_a_exp;
  //& prnval lepose_a_exp;

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

  //& hmat_a_exp = transl(posn_a) * tr;
  //& prnval hmat_a_exp;
  assert(0 == doubleChecker(1, 16, hmat_a, hmat_a_exp));
  assert(0 == doubleChecker(1, 3, posn1_a,posn_a));

  //& rpy1_a=rand(3,1);
  //& tr1=rpy2tr(rpy1_a(3), rpy1_a(2), rpy1_a(1));
  //& hmat2_a_exp = hmat_a_exp * tr1;
  //& prnval hmat2_a_exp;
  //& prnval rpy1_a;

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

  //& Lat = 52.1208; Lon=-106.6278; el=473;
  //& [UTMEasting_exp, UTMNorthing_exp, UTMZoneNum_exp, UTMZoneCh_exp] = deg2utm(Lat, Lon);
  //& UTMZoneNum_exp=int32(UTMZoneNum_exp);
  //& UTMZoneCh_exp=char(UTMZoneCh_exp);
  //& prnval UTMNorthing_exp;
  //& prnval UTMEasting_exp;
  //& prnval UTMZoneNum_exp;
  //& prnval UTMZoneCh_exp;

  assert(0 == doubleChecker(1, 1, &UTMEasting, &UTMEasting_exp));
  assert(0 == doubleChecker(1, 1, &UTMNorthing, &UTMNorthing_exp));
  assert(0 == doubleChecker(1, 1, &UTMElevation, &el));
  assert(0 == intChecker(1, &UTMZoneNum, &UTMZoneNum_exp));
  assert(0 == charChecker(1, &UTMZoneCh, &UTMZoneCh_exp));

  wposn.toArray(wposn_a);
  wposn1=wutmposn.to_WPosn();
  wposn1.toArray(wposn1_a);
  assert(0 == doubleChecker(1, 3, wposn1_a, wposn_a));

  //& rpy_a=rand(3,1);
  //& tr=rpy2tr(rpy_a(3), rpy_a(2), rpy_a(1));
  //& q_m=quaternion(tr);
  //& q_m_a=q_m.d;
  //& wpose_a_exp=cat(1,deg2rad(Lon),deg2rad(Lat),el,q_m_a');
  //& wutmpose_a_exp=cat(1, UTMEasting_exp, UTMNorthing_exp, el, q_m_a');
  //& prnval rpy_a;
  //& prnval wpose_a_exp;
  //& prnval wutmpose_a_exp;

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
  assert(0 == doubleChecker(1, 7, wutmpose_a, wutmpose_a_exp));
  assert(0 == intChecker(1, &UTMZoneNum, &UTMZoneNum_exp));
  assert(0 == charChecker(1, &UTMZoneCh, &UTMZoneCh_exp));

  return 0;

}
