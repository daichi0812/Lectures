/*
 * Copyright 1996-2018 Cyberbotics Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*******************************************************************************************************/
/* Description:  Header file of the accelerometer API for the e-puck crosscompilation                  */
/*******************************************************************************************************/

#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "types.h"

void          wb_accelerometer_enable(WbDeviceTag,int sampling_period);
void          wb_accelerometer_disable(WbDeviceTag);
const double *wb_accelerometer_get_values(WbDeviceTag);

#endif /* ACCELEROMETER_H */
