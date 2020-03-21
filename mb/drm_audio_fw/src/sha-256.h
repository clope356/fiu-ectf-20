#ifndef SHA_H__
#define SHA_H__
void calc_sha_256(uint8_t hash[32], const void *input, size_t len);
#endif