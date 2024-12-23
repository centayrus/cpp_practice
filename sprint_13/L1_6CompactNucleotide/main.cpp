#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>

using namespace std;

struct Nucleotide {
    char symbol;
    size_t position;
    int chromosome_num;
    int gene_num;
    bool is_marked;
    char service_info;
};

struct CompactNucleotide {
    uint32_t position : 32;     // от 0 до 3,3 млрд
    uint16_t gene_num : 15;     // от 1 до 25 тыс. + значение 0
    uint8_t is_marked : 1;      // 1 бит
    uint8_t service_info : 8;   // любой символ
    uint8_t chromosome_num : 6; // от 1 до 46
    uint8_t symbol : 2;         // нуклеотиды: A, T, G или С

};

CompactNucleotide Compress(const Nucleotide &n) {
    CompactNucleotide result;
    result.position = n.position;
    result.gene_num = n.gene_num;
    result.is_marked = n.is_marked;
    result.service_info = n.service_info;
    result.chromosome_num = n.chromosome_num;

        switch (n.symbol) {
        case 'A': result.symbol = 0; break;
        case 'T': result.symbol = 1; break;
        case 'G': result.symbol = 2; break;
        case 'C': result.symbol = 3; break;
        default: assert(false && "Invalid symbol");
    }
    return result;

    return result;
}

Nucleotide Decompress(const CompactNucleotide &cn) {
    Nucleotide result;
       switch (cn.symbol) {
        case 0: result.symbol = 'A'; break;
        case 1: result.symbol = 'T'; break;
        case 2: result.symbol = 'G'; break;
        case 3: result.symbol = 'C'; break;
        default: assert(false && "Invalid compressed symbol");
    }

    result.position = cn.position;
    result.chromosome_num = cn.chromosome_num;
    result.gene_num = cn.gene_num;
    result.is_marked = cn.is_marked;
    result.service_info = cn.service_info;
    return result;
}

static_assert(sizeof(CompactNucleotide) <= 8, "Your CompactNucleotide is not compact enough");
static_assert(alignof(CompactNucleotide) == 4, "Don't use '#pragma pack'!");
bool operator==(const Nucleotide &lhs, const Nucleotide &rhs) {
    return (lhs.symbol == rhs.symbol) &&
           (lhs.position == rhs.position) &&
           (lhs.chromosome_num == rhs.chromosome_num) &&
           (lhs.gene_num == rhs.gene_num) &&
           (lhs.is_marked == rhs.is_marked) &&
           (lhs.service_info == rhs.service_info);
}
void TestSize() {
    assert(sizeof(CompactNucleotide) <= 8);
}
void TestCompressDecompress() {
    Nucleotide source;
    source.symbol = 'T';
    source.position = 1'000'000'000;
    source.chromosome_num = 48;
    source.gene_num = 1'000;
    source.is_marked = true;
    source.service_info = '!';

    CompactNucleotide compressedSource = Compress(source);
    Nucleotide decompressedSource = Decompress(compressedSource);

    assert(source == decompressedSource);
}

int main() {
    TestSize();
    TestCompressDecompress();
}