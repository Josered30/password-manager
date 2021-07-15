#include <string>
#include <iostream>

#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/sha.h>
#include <cryptopp/eax.h>
#include <cryptopp/hex.h>

CryptoPP::SecByteBlock get_key(std::string key)
{
    CryptoPP::SecByteBlock derived(32);
    char purpose = 0;
    unsigned int iterations = 15000;

    CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA256> kdf;
    kdf.DeriveKey(derived.data(), derived.size(), purpose, (CryptoPP::byte *)key.data(), key.size(), NULL, 0, iterations);
    return derived;
}

std::string decrypt(std::string value, std::string aes_key)
{

    CryptoPP::SecByteBlock key = get_key(aes_key);

    std::string result;
    CryptoPP::EAX<CryptoPP::AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(key.data(), 16, key.data() + 16, 16);

    CryptoPP::AuthenticatedDecryptionFilter df(decryptor, new CryptoPP::StringSink(result));
    df.Put((CryptoPP::byte *)value.data(), value.size());
    df.MessageEnd();

    return result;
}

std::string encrypt(std::string value, std::string aes_key)
{
    CryptoPP::SecByteBlock key = get_key(aes_key);

    std::string result;
    CryptoPP::EAX<CryptoPP::AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(key.data(), 16, key.data() + 16, 16);

    CryptoPP::AuthenticatedEncryptionFilter ef(encryptor, new CryptoPP::StringSink(result));
    ef.Put((CryptoPP::byte *)value.data(), value.size());
    ef.MessageEnd();

    return result;
}

std::string from_hex(std::string hex_value)
{
    std::string value;
    CryptoPP::HexDecoder decoder;
    decoder.Detach(new CryptoPP::StringSink(value));
    decoder.Put((CryptoPP::byte *)hex_value.data(), hex_value.size());
    decoder.MessageEnd();

    return value;
}

std::string to_hex(std::string value)
{
    std::string hex_value;
    CryptoPP::HexEncoder encoder;
    encoder.Detach(new CryptoPP::StringSink(hex_value));
    encoder.Put((CryptoPP::byte *)value.data(), value.size());
    encoder.MessageEnd();

    return hex_value;
}
