//
// Created by nbollom on 12/11/18.
//

#include "namegenerator.h"
#include <vector>

using namespace std;

std::string GenerateRandomName(std::shared_ptr<std::mt19937_64> engine) {
    static vector<string> parts1 = {"br", "cr", "dr", "fr", "gr", "j", "kr", "l", "m", "n", "pr", "r", "sh", "tr", "v", "wh", "x", "y", "z"};
    static vector<string> parts2 = {"a", "a", "e", "e", "i", "i", "o", "o", "u", "u", "ae", "ie", "oo", "ou"};
    static vector<string> parts3 = {"b", "ck", "d", "g", "k", "m", "n", "p", "t", "v", "x", "z"};
    static uniform_int_distribution<unsigned long> distribution1(0, parts1.size() - 1);
    static uniform_int_distribution<unsigned long> distribution2(0, parts2.size() - 1);
    static uniform_int_distribution<unsigned long> distribution3(0, parts3.size() - 1);
    string result;
    for (int i = 0; i < 6; ++i) {
        string part;
        switch (i % 3) {
            case 0:
                part = parts1[distribution1(*engine)];
                break;
            case 1:
                part = parts2[distribution2(*engine)];
                break;
            case 2:
                part = parts3[distribution3(*engine)];
                break;
            default:break;
        }
        result.append(part);
    }
    result[0] = result[0] - (char)32;
    return result;
}
