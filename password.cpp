#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <string>
#include <cstring>
#include <openssl/sha.h>

std::string generateSalt(size_t length = 8) {
    std::string saltCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    std::string salt;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> distribution(0, saltCharacters.length() - 1);
    
    for (size_t i = 0; i < length; ++i) {
        salt += saltCharacters[distribution(generator)];
    }
    
    return salt;
}

std::string hashPassword(const std::string& password, const std::string& salt) {
    std::string saltedPassword = password + salt;
    unsigned char hashedBytes[SHA256_DIGEST_LENGTH];
    
    SHA256(reinterpret_cast<const unsigned char*>(saltedPassword.c_str()), saltedPassword.length(), hashedBytes);
    
    std::stringstream ss;
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hashedBytes[i]);
    }
    
    return ss.str();
}

bool checkPassword(const std::string& password, const std::string& hashedPassword, const std::string& salt) {
    std::string saltedPassword = password + salt;
    unsigned char hashedBytes[SHA256_DIGEST_LENGTH];
    
    SHA256(reinterpret_cast<const unsigned char*>(saltedPassword.c_str()), saltedPassword.length(), hashedBytes);
    
    std::stringstream ss;
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hashedBytes[i]);
    }
    
    return ss.str() == hashedPassword;
}

int main() {
    std::ofstream passwordFile("passwords.txt");
    
    if (!passwordFile) {
        std::cerr << "Failed to open passwords.txt for writing." << std::endl;
        return 1;
    }
    
    int numUsers;
    std::cout << "Enter the number of users: ";
    std::cin >> numUsers;
    
    std::cin.ignore(); // Ignore newline character
    
    for (int i = 0; i < numUsers; ++i) {
        std::string username, password;
        std::cout << "Enter the username for User " << i + 1 << ": ";
        std::getline(std::cin, username);
        std::cout << "Enter the password for User " << i + 1 << ": ";
        std::getline(std::cin, password);
        
        passwordFile << username << ":" << password << std::endl;
    }
    
    passwordFile.close();
    
    std::ifstream passwordFileRead("passwords.txt");
    std::ofstream hashedPasswordFile("hashed_passwords.txt");
    
    if (!passwordFileRead) {
        std::cerr << "Failed to open passwords.txt for reading." << std::endl;
        return 1;
    }
    
    if (!hashedPasswordFile) {
        std::cerr << "Failed to open hashed_passwords.txt for writing." << std::endl;
        return 1;
    }
    
    std::string line;
    while (std::getline(passwordFileRead, line)) {
        std::stringstream ss(line);
        std::string username, password;
        std::getline(ss, username, ':');
        std::getline(ss, password);
        
        std::string salt = generateSalt();
        std::string hashedPassword = hashPassword(password, salt);
        
        hashedPasswordFile << username << ":" << hashedPassword << ":" << salt << std::endl;
    }
    
    passwordFileRead.close();
    hashedPasswordFile.close();
    
    std::string inputUsername, inputPassword;
    std::cout << "Enter username: ";
    std::getline(std::cin, inputUsername);
    std::cout << "Enter password: ";
    std::getline(std::cin, inputPassword);
    
    std::ifstream hashedPasswordFileRead("hashed_passwords.txt");
    
    if (!hashedPasswordFileRead) {
        std::cerr << "Failed to open hashed_passwords.txt for reading." << std::endl;
        return 1;
    }
    
    bool loginSuccessful = false;
    std::string storedUsername, storedHashedPassword, storedSalt;
    
    while (std::getline(hashedPasswordFileRead, line)) {
        std::stringstream ss(line);
        std::getline(ss, storedUsername, ':');
        std::getline(ss, storedHashedPassword, ':');
        std::getline(ss, storedSalt);
        
        if (storedUsername == inputUsername) {
            if (checkPassword(inputPassword, storedHashedPassword, storedSalt)) {
                loginSuccessful = true;
                break;
            }
        }
    }
    
    hashedPasswordFileRead.close();
    
    if (loginSuccessful) {
        std::cout << "Login successful." << std::endl;
    } else {
        std::cout << "Login failed. Invalid username or password." << std::endl;
    }
    
    return 0;
}
