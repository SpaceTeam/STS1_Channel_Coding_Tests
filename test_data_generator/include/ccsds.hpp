/*
 *  AX5043 OS-independent driver
 *
 *  Copyright (C) 2019 Libre Space Foundation (https://libre.space)
 *
 *	Authors: surligas, ctriant
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DRIVERS_AX5043_INC_CCSDS_H_
#define DRIVERS_AX5043_INC_CCSDS_H_

#include <stdint.h>
#include <stddef.h>

void
ccsds_scrambler(uint8_t *data, size_t len);

void
ccsds_descrambler(uint8_t *data, size_t len);

#endif /* DRIVERS_AX5043_INC_CCSDS_H_ */

