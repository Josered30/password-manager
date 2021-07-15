#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <string>
#include <iostream>

#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/sha.h>
#include <cryptopp/eax.h>

CryptoPP::SecByteBlock get_key(std::string key);
std::string decrypt(std::string value, std::string aes_key);
std::string encrypt(std::string value, std::string aes_key);
std::string from_hex(std::string hex_value);
std::string to_hex(std::string value);

#endif