#include <iostream>
#include <string>
#include <bitset>
#include <array>
#include <vector>
#include <algorithm>
#include <iomanip>


uint32_t leftShift(const uint32_t &num,int shift)
  {
 return (num<<shift) | (num>>(32-shift) ) ;
  }

void convertStrToBinary(const std::string& str, std::vector<int>& converted)
{
    for(char c :str)
    {
        for(int i=7 ; i>=0 ; i--) converted.push_back( (c>>i)&1) ;
    }
}

void addBinaryStrSize(const uint32_t strSize, std::vector<int>& converted)
{
    std::array<int, 64> binary;

    for (int i = 31; i >= 0; i--) {
        binary[63 - i] = ((strSize >> i) & 1);
    }

    for (int i = 31; i >= 0; i--) {
        binary[i] = 0;
    }

    for (int i = 0; i < 64; i++) converted.push_back(binary[i]);
}

inline uint32_t f1(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (~x & z);
}

inline uint32_t f2(uint32_t x, uint32_t y, uint32_t z) {
    return x ^ y ^ z;
}

inline uint32_t f3(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

void wordsProcess(const std::vector<int>& converted, std::array<uint32_t, 80>& Words, int processed512)
{
    Words.fill(0);

    for (int i = 0; i < 80; i++) {

        if (i < 16) {
            for(int j=0 ; j<=31 ; j++) Words[i] |= converted[512 * processed512 + i*32+j]<<(31-j);
        }
        else {
            Words[i] =leftShift( Words[i - 3] ^ Words[i - 8] ^ Words[i - 14] ^ Words[i - 16] , 1) ;
        }
    }
}

std::string sha1(const std::string& str)
{
    std::vector<int> converted;

    convertStrToBinary(str, converted);

    converted.push_back(1);

    while ( converted.size() % 512 != 448) {
        converted.push_back(0);
    }

    addBinaryStrSize(str.size(), converted);

    std::array<uint32_t, 80> Words;
    int nBlocks512 = converted.size() / 512 , processed512 = 0;
    uint32_t H0 = 0x67452301, H1 = 0xEFCDAB89, H2 = 0x98BADCFE, H3 = 0x10325476, H4 = 0xC3D2E1F0;
    uint32_t A, B, C, D, E;

    while (processed512!=nBlocks512) {

        wordsProcess(converted, Words, processed512);

        A = H0;
        B = H1;
        C = H2;
        D = H3;
        E = H4;

        uint32_t K1 = 0x5A827999, K2 = 0x6ED9EBA1, K3 = 0x8F1BBCDC, K4 = 0xCA62C1D6;
        uint32_t temp{};

        for (int i = 0; i < 80; i++) {

            if (i <= 19)
                temp = leftShift(A,5) + f1(B, C, D) + E + Words[i] + K1;
            else if (i <= 39)
                temp = leftShift(A,5) + f2(B, C, D) + E + Words[i] + K2;
            else if (i <= 59)
                temp = leftShift(A,5) + f3(B, C, D) + E + Words[i] + K3;
            else if (i <= 79)
                temp = leftShift(A,5) + f2(B, C, D) + E + Words[i] + K4;

            E = D;
            D = C;
            C = leftShift(B,30);
            B = A;
            A = temp;

            H0 += A;
            H1 += B;
            H2 += C;
            H3 += D;
            H4 += E;
        }
        processed512++;
    }

   std::stringstream ss;

    ss << std::hex << H0 << H1 << H2 << H3 << H4;

    return ss.str() ;
}

int main()
{
    std::string str="abc" ;
    std::cout<<sha1(str) ;

    return 0;
}
