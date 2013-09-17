#pragma once
#include "protocol.h"

typedef enum {
    RTCP_SR   = 200,
    RTCP_RR   = 201,
    RTCP_SDES = 202,
    RTCP_BYE  = 203,
    RTCP_APP  = 204
} rtcp_type_t;

/*
 * RTCP common header word
 */
typedef struct {
   unsigned int version:2;   /* protocol version */
   unsigned int p:1;         /* padding flag */
   unsigned int count:5;     /* varies by packet type */
   unsigned int pt:8;        /* RTCP packet type */
   uint16 length;           /* pkt len in words, w/o this word */
} rtcp_common_t;

/*
 * Big-endian mask for version, padding bit and packet type pair
 */
#define RTCP_VALID_MASK (0xc000 | 0x2000 | 0xfe)
#define RTCP_VALID_VALUE ((RTP_VERSION << 14) | RTCP_SR)

/*
 * Reception report block
 */
typedef struct {
   uint32 ssrc;             /* data source being reported */
   unsigned int fraction:8;  /* fraction lost since last SR/RR */
   int lost:24;              /* cumul. no. pkts lost (signed!) */
   uint32 last_seq;         /* extended last seq. no. received */
   uint32 jitter;           /* interarrival jitter */
   uint32 lsr;              /* last SR packet from this source */
   uint32 dlsr;             /* delay since last SR packet */
} rtcp_rr_t;

/*
 * SDES item
 */
typedef struct {
   uint8 type;              /* type of item (rtcp_sdes_type_t) */
   uint8 length;            /* length of item (in octets) */
   char data[1];             /* text, not null-terminated */
} rtcp_sdes_item_t;

/*
 * One RTCP packet
 */
typedef struct {
   rtcp_common_t common;     /* common header */
   union {
      struct {
         uint32 ssrc;     /* sender generating this report */
         uint32 ntp_sec;  /* NTP timestamp */
         uint32 ntp_frac;
         uint32 rtp_ts;   /* RTP timestamp */
         uint32 psent;    /* packets sent */
         uint32 osent;    /* octets sent */
         rtcp_rr_t rr[1];  /* variable-length list */
       } sr;/* sender report (SR) */
       struct {
          uint32 ssrc;     /* receiver generating this report */
          rtcp_rr_t rr[1];  /* variable-length list */
       } rr;/* reception report (RR) */
       struct rtcp_sdes {
          uint32 src;      /* first SSRC/CSRC */
          rtcp_sdes_item_t item[1]; /* list of SDES items */
       } sdes;/* source description (SDES) */
       struct {
          uint32 src[1];   /* list of sources */
                           /* can't express trailing text for reason */
       } bye;/* BYE */
   } r;
} rtcp_t;

class RtcpNet :
	public Protocol
{
public:
	RtcpNet(void);

	virtual bool Parse();
	Protocol* GetUpperProtocol();
	Protocol* GetLowerProtocol();
	~RtcpNet(void);
protected:
	rtcp_type_t rtcp_type;
	rtcp_t* rtcp_packet;
};

