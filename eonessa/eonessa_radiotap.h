
/*
 * Copyright (C) 2011 Dan White
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef EONESSA_RADIOTAP_H
#define EONESSA_RADIOTAP_H

#define EN_RT_TSFT              (1<<0)
#define EN_RT_FLAGS             (1<<1)
#define EN_RT_RATE              (1<<2)
#define EN_RT_CHANNEL           (1<<3)
#define EN_RT_FHSS              (1<<4)
#define EN_RT_ANTENNA_SIGNAL    (1<<5)
#define EN_RT_ANTENNA_NOISE     (1<<6)
#define EN_RT_LOCK_QUALITY      (1<<7)
#define EN_RT_TX_ATTENUATION    (1<<8)
#define EN_RT_DB_TX_ATTENUATION (1<<9)
#define EN_RT_DBM_TX_POWER      (1<<10)
#define EN_RT_ANTENNA           (1<<11)
#define EN_RT_DB_ANTENNA_SIGNAL (1<<12)
#define EN_RT_DB_ATENNA_NOISE   (1<<13)
#define EN_RT_RX_FLAGS          (1<<14)
#define EN_RT_MCS               (1<<19)
#define EN_RT_RESET_TO_RADIOTAP (1<<29)
#define EN_RT_VENDOR_NAMESPACE  (1<<30)
#define EN_RT_CONTINUATION      (1<<31)

#define EN_RT_CHAN_FLAG_TURBO   0x0010
#define EN_RT_CHAN_FLAG_CCK     0x0020
#define EN_RT_CHAN_FLAG_OFDN    0x0040
#define EN_RT_CHAN_FLAG_2GHZ    0x0080
#define EN_RT_CHAN_FLAG_5GHZ    0x0100
#define EN_RT_CHAN_FLAG_PASSIVE 0x0200
#define EN_RT_CHAN_FLAG_DYNAMIC 0x0400
#define EN_RT_CHAN_FLAG_GFSK    0x0800

#define EN_RT_FLAG_CFP            0x01
#define EN_RT_FLAG_SHORT_PREAMBLE 0x02
#define EN_RT_FLAG_WEP            0x04
#define EN_RT_FLAG_FRAGGED        0x08
#define EN_RT_FLAG_INCLUDES_FCS   0x10
#define EN_RT_FLAG_PADDED         0x20
#define EN_RT_FLAG_FAILED_FCS     0x40
#define EN_RT_FLAG_HT             0x80

#define EN_RT_MCS_KNOWN_BANDWIDTH 0x01
#define EN_RT_MCS_KNOWN_INDEX     0x02
#define EN_RT_MCS_KNOWN_INTERVAL  0x04
#define EN_RT_MCS_KNOWN_HT        0x08
#define EN_RT_MCS_KNOWN_FEC       0x10
#define EN_RT_MCS_KNOWN_RESERVED  0xe0

#define EN_RT_MCS_FLAG_BW_20           0x00
#define EN_RT_MCS_FLAG_BW_40           0x01
#define EN_RT_MCS_FLAG_BW_20L          0x02
#define EN_RT_MCS_FLAG_BW_20U          0x03
#define EN_RT_MCS_FLAG_BW_MASK         0x03
#define EN_RT_MCS_FLAG_GUARD_INT_LONG  0x00
#define EN_RT_MCS_FLAG_GUARD_INT_SHORT 0x04
#define EN_RT_MCS_FLAG_GUARD_MASK      0x04
#define EN_RT_MCS_FLAG_HT_FORMAT_MIXED 0x00
#define EN_RT_MCS_FLAG_HT_FORMAT_GREEN 0x08
#define EN_RT_MCS_FLAG_HT_FORMAT_MASK  0x08
#define EN_RT_MCS_FLAG_FEC_TYPE_BCC    0x00
#define EN_RT_MCS_FLAG_FEC_TYPE_LDPC   0x10
#define EN_RT_MCS_FLAG_FEC_TYPE_MASK   0x10
#define EN_RT_MCS_FLAG_RESERVED        0xe0

#define EN_RT_RX_FLAG_RESERVED          0x0001
#define EN_RT_RX_FLAG_PLCP_CRC_FAIL     0x0002
#define EN_RT_RX_FLAG_RESERVED_4_FUTURE 0xfffc

struct en_radiotap_header {
    u_int8_t        it_version;     /* set to 0 */
    u_int8_t        it_pad;
    u_int16_t       it_len;         /* entire length */
    u_int32_t       it_present;     /* fields present */
};

/*int eonessa_parse(const char* buf, unsigned n, int capture_type, struct eonessa*);*/

#endif // EONESSA_RADIOTAP_H
