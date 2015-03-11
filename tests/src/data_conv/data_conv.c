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
 * Revision     : $Id: data_conv.c,v 1.4 2008/09/03 22:04:39 cvsuser Exp $
 */



#ifndef DATA_CONV_H
#include "data_conv.h"
#endif

ieeeFpd32 ieeeFpd32FromFloat(const float value) {
  FloatUnion_t su;
  su.value=value;
  return su.word;
}


float ieeeFpd32ToFloat(const ieeeFpd32 input) {
  FloatUnion_t su;
  su.word=input;
  return su.value;
}

ieeeFpd64 ieeeFpd64FromDouble(const double value) {
  DoubleUnion_t du;
  du.value=value;
  return du.dWord;
}


double ieeeFpd64ToDouble(const ieeeFpd64 input) {
  DoubleUnion_t du;
  du.dWord=input;
  return du.value;
}

uint8_t jausByteFromDouble(double value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_BYTE_RANGE;
  double bias = min;
  
  // limit real number between min and max
  if(value < min) value = min;
  if(value > max) value = max;
                
  // return rounded integer value
  return (unsigned char) rint((value - bias)/scaleFactor);

}

double jausByteToDouble(const uint8_t value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_BYTE_RANGE;
  double bias = min;
  
  return value*scaleFactor + bias;

}
double jausIntegerToDouble(const sint32_t value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_INTEGER_RANGE;
  double bias = (max+min)/2.0; 
                
  return value*scaleFactor + bias;

}
sint32_t jausIntegerFromDouble(double value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_INTEGER_RANGE;
  double bias = (max+min)/2.0;
        
  // limit real number between min and max
  if(value < min) value = min;
  if(value > max) value = max;
                
  // return rounded integer value
  return (int) rint((value - bias)/scaleFactor);
}

double jausLongToDouble(const sint64_t value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_LONG_RANGE;
  double bias = (max+min)/2.0; 
                
  return value*scaleFactor + bias;

}
sint64_t jausLongFromDouble(double value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_LONG_RANGE;
  double bias = (max+min)/2.0;
        
  // limit real number between min and max
  if(value < min) value = min;
  if(value > max) value = max;
                
  // return rounded integer value
  return (long) rint((value - bias)/scaleFactor);

}
double jausShortToDouble(const sint16_t value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_SHORT_RANGE;
  double bias = (max+min)/2.0; 
    
  return value*scaleFactor + bias;

}
sint16_t jausShortFromDouble(double value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_SHORT_RANGE;
  double bias = (max+min)/2.0;
        
  // limit real number between min and max
  if(value < min) value = min;
  if(value > max) value = max;
                
  // calculate rounded integer value
  return (short) rint((value - bias)/scaleFactor);
}
double jausUnsignedIntegerToDouble(const uint32_t value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_UNSIGNED_INTEGER_RANGE;
  double bias = min;

  return value*scaleFactor + bias;

}
uint32_t jausUnsignedIntegerFromDouble(double value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_UNSIGNED_INTEGER_RANGE;
  double bias = min;
        
  // limit real number between min and max
  if(value < min) value = min;
  if(value > max) value = max;
                
  // calculate rounded integer value
  return (unsigned int) rint((value - bias)/scaleFactor);

}
double jausUnsignedLongToDouble(const uint64_t value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_UNSIGNED_LONG_RANGE;
  double bias = min; 

  return value*scaleFactor + bias;

}
uint64_t jausUnsignedLongFromDouble(double value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_UNSIGNED_LONG_RANGE;
  double bias = min;
        
  // limit real number between min and max
  if(value < min) value = min;
  if(value > max) value = max;
                
  // calculate rounded integer value
  return (unsigned long) rint((value - bias)/scaleFactor);

}
double jausUnsignedShortToDouble(const uint16_t value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_UNSIGNED_SHORT_RANGE;
  double bias = min;
            
  return value*scaleFactor + bias;

}
uint16_t jausUnsignedShortFromDouble(double value, const double min, const double max) {
  double scaleFactor = (max-min)/JAUS_UNSIGNED_SHORT_RANGE;
  double bias = min;
        
  // limit real number between min and max
  if(value < min) value = min;
  if(value > max) value = max;
                
  // calculate rounded integer value
  return (unsigned short) rint((value - bias)/scaleFactor);

}
