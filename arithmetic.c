#include <stdint.h> 
#include "params.h"
#include "arithmetic.h"

const int32_t zetas[128] = {1, -1600, -749, -40, -687, 630, -1432, 848, 
1062, -1410, 193, 797, -543, -69, 569, -1583, 296, -882, 1339, 1476, -283, 
56, -1089, 1333, 1426, -1235, 535, -447, -936, -450, -1355, 821, 289, 331, 
-76, -1573, 1197, -1025, -1052, -1274, 650, -1352, -816, 632, -464, 33, 1320, 
-1414, -1010, 1435, 807, 452, 1438, -461, 1534, -927, -682, -712, 1481, 648, 
-855, -219, 1227, 910, 17, -568, 583, -680, 1637, 723, -1041, 1100, 1409, 
-667, -48, 233, 756, -1173, -314, -279, -1626, 1651, -540, -1540, -1482, 952, 
1461, -642, 939, -1021, -892, -941, 733, -992, 268, 641, 1584, -1031, -1292, 
-109, 375, -780, -1239, 1645, 1063, 319, -556, 757, -1230, 561, -863, -735, 
-525, 1092, 403, 1026, 1143, -1179, -554, 886, -1607, 1212, -1455, 1029, 
-1219, -394, 885, -1175};

static int32_t barrett_reduce(int32_t a) {
  int32_t t;
  const int32_t v = ((1LL<<37) + KYBER_Q/2)/KYBER_Q;

  t  = ((int64_t)v*a + (1LL << 36)) >> 37;
  t *= KYBER_Q;
  return a - t;
}

void ntt(int32_t r[256])
{
    unsigned int len, start, j, k;
    int32_t t;
    int32_t zeta;
    k = 1;
    for(len = 128; len >= 2; len >>= 1) {
        for(start = 0; start < 256; start = j + len) {
            zeta = zetas[k++];
            for(j = start; j < len; j++) {
                t = barrett_reduce((int32_t)r[j + len]*zeta);
                r[j + len] = r[j] - t;
                r[j] = r[j] + t;      
            }
        }
    }
  
  for (int i = 0; i < 256; i++)
  {
    r[i] = barrett_reduce(r[i]);
  } 
}

void invntt(int32_t r[256]) {
  unsigned int start, len, j, k;
  int32_t zeta;
  int32_t t;
  const int16_t f = -26; // 128**(-1) % KYBER_Q

  k = 127;
  for(len = 2; len <= 128; len <<= 1) {
    for(start = 0; start < 256; start = j + len) {
      zeta = zetas[k--];
      for(j = start; j < start + len; j++) {
        t = r[j];
        r[j] = t + r[j + len];
        r[j + len] = r[j + len] - t;
        r[j + len] = barrett_reduce((int32_t)zeta*r[j + len]);
      }
    }
  }

  for (int i = 0; i < 256; i++)
  {
    r[i] *= f;
    r[i] = barrett_reduce(r[i]);
  }
}

void basemul(int32_t r[2], const int32_t a[2], const int32_t b[2], int32_t zeta)
{
  r[0] = barrett_reduce((int32_t)a[1]*b[1]);
  r[0] = (int32_t)r[0]*zeta;
  r[0] += a[0]*b[0];
  r[1] = (int32_t)(a[0]*b[1]);
  r[1] += (int32_t)(a[1]*b[0]);
}

void poly_reduction(int32_t poly[256]){
    for (int i = 0; i < 256; i++)
    {
        poly[i] = barrett_reduce(poly[i]);
    }
}