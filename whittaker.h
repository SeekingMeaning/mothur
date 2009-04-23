#ifndef WHITTAKER_H
#define WHITTAKER_H
/*
 *  whittaker.h
 *  Mothur
 *
 *  Created by Thomas Ryabin on 3/13/09.
 *  Copyright 2009 Schloss Lab UMASS Amherst. All rights reserved.
 *
 */
#include "calculator.h"

/*This class implements the Whittaker estimator on 2 groups. 
 It is a child of the calculator class.*/ 

/***********************************************************************/

class Whittaker : public Calculator  {
	
public:
	Whittaker() : Calculator("whittaker", 3) {};
	EstOutput getValues(SAbundVector*) {return data;};
	EstOutput getValues(SharedRAbundVector*, SharedRAbundVector*);

};

/***********************************************************************/

#endif