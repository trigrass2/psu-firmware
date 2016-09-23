/*
 * EEZ PSU Firmware
 * Copyright (C) 2015 Envox d.o.o.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
/** @file conf_user.h
@brief Configuration overrided by the user.
Use this header file to override anything from conf.h or conf_advanced.h.
*/

#pragma once

//#undef CHANNELS
//#define CHANNELS \
//    CHANNEL(1, CH_BOARD_REVISION_R4B43A_PARAMS, CH_PINS_1, CH_PARAMS_50V_3A), \
//    CHANNEL(2, CH_BOARD_REVISION_R4B43A_PARAMS, CH_PINS_2, CH_PARAMS_50V_3A)

/// Is Ethernet present?
#undef OPTION_ETHERNET
#define OPTION_ETHERNET 0

/// This is the delay period, after the channel output went OFF,
/// after which we shall turn DP off.
/// Value is given in seconds.
#undef DP_OFF_DELAY_PERIOD
#define DP_OFF_DELAY_PERIOD 30

// Pre-regulator's PMOS SOA:
//
// SUD19P06-60  Imax=0.8 A

#undef CH_PARAMS_40V_5A
#define CH_PARAMS_40V_5A    CH_PARAMS_U_40V, CH_PARAMS_I_5A, true, CH_PARAMS_OPP_DELAY, 10.0f, 150.0f, 160.0f, 48.0f, 0.8f, 20.0f, 160.0f


