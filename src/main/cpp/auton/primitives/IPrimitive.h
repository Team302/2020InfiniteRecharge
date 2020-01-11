/*
 * IPrimitive.h
 *
 *  Created on: Jan 12, 2017
 *      Author: The Realest of Authors
 */

#ifndef SRC_INTERFACES_IPRIMITIVE_H_
#define SRC_INTERFACES_IPRIMITIVE_H_

#include <auton/PrimitiveParams.h>

class IPrimitive
{
    public:
         const float LOOP_LENGTH = 0.020; //Program loop duration in seconds

        IPrimitive() = default;
        virtual ~IPrimitive() = default;
        virtual void Init(PrimitiveParams*	Parms) = 0;
        virtual void Run() = 0;
        virtual bool IsDone() = 0;

};

#endif /* SRC_IPrimitive_H_ */
