#ifndef ARITHMETIC_H
#define ARITHMETIC_H
#include <stdint.h> 
#include "params.h"

#define zetas KYBER_NAMESPACE(zetas)
extern const int32_t zetas[128];

#define ntt KYBER_NAMESPACE(ntt)
void ntt(int32_t r[256]);

#define invntt KYBER_NAMESPACE(invntt)
void invntt(int32_t r[256]);

#define basemul KYBER_NAMESPACE(basemul)
void basemul(int32_t r[2], const int32_t a[2], const int32_t b[2], int32_t zeta);

#define poly_reduction KYBER_NAMESPACE(poly_reduction)
void poly_reduction(int32_t poly[256]);

#endif