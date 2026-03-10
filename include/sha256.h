#ifndef SHA256_H
#define SHA256_H

#define RIGHTROTATE(var, n) (var>>n|var<<32-n)
#define SWAP_ENDIANNESS_32(n) ((n<<24)|((n<<8)&0x00FF0000)|((n>>8)&0x0000FF00)|(n>>24))
#define SWAP_ENDIANNESS_64(n) ((n<<56)|((n<<40)&0x00FF000000000000)|((n<<24)&0x0000FF0000000000)|((n<<8)&0x000000FF00000000)|((n>>8)&0x00000000FF000000)|((n>>24)&0x0000000000FF0000)|((n>>40)&0x000000000000FF00)|(n>>56))

#include <string>
using namespace std;

string hash_sha256(const char *input);

#endif
