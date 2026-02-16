#include "hash.h"
#include <openssl/sha.h>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace hash {

std::string sha256_file(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return "";

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    char buf[8192];
    while (file.good()) {
        file.read(buf, sizeof(buf));
        SHA256_Update(&ctx, buf, file.gcount());
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &ctx);

    std::ostringstream out;
    for (unsigned char c : hash)
        out << std::hex << std::setw(2) << std::setfill('0') << (int)c;

    return out.str();
}

}
