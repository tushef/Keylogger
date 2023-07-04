#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

const string& SALT1 = "LM::TB::";
const string& SALT2 = "12_22_32";
const string& SALT3 = "13901420";
const string& BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

pair <int, int> getSmallestFactorPair(int num) {

    // O(sqrt(n))

    pair <int, int> ret;
    for (int i = 1; i * i <= num; i++)
        if (num % i == 0) {
            ret.first = i;
            ret.second = num / i;
        }
    return ret;
}

string base64_decode(const string& s)
{
    string ret;
    vector<int> vec(256, -1);
    for (int i = 0; i < 64; i++)
        vec[BASE64_CODES[i]] = i;
    int val = 0, bits = -8;
    for (const auto& c : s)
    {
        if (vec[c] == -1) break;
        val = (val << 6) + vec[c];
        bits += 6;

        if (bits >= 0)
        {

            ret.push_back(char((val >> bits) & 0xFF));
            bits -= 8;
        }
    }
    return ret;
}

string Decrypt(string str) {

    str = base64_decode(str);
    string ret = "";
    pair<int, int> table = getSmallestFactorPair(str.length() + str.length() % 2);

    for (int i = 0; i < table.first; i++) {
        for (int j = i; j < signed(str.length()); j += table.first) {
            if (str[j] == '\0') {
                continue;
            }

            ret += str[j];
        }
    }

    ret.erase(0, SALT1.length());
    ret.erase(ret.length() - 1 - SALT3.length(), SALT3.length());
    ret.erase((ret.length() + ret.length() % 2) / 2, SALT2.length());
    

    return ret;
}

int main(int argc, char* argv[]) {
    
    if (argc != 3) {
        return cout << "Program needs 2 arguments, input file and output file" << endl, 3;
    }

    string inputFile(argv[1]), outputFile(argv[2]);
    ifstream readFile(inputFile);

    if (!readFile) {
        return cout << "Cannot read " << inputFile << " file" << endl, 4;
    }

    string encryptedData;

    readFile >> encryptedData; 

    if (!readFile) {
        return cout << "File " << inputFile << " corrupted" << endl, 5;
    }

    encryptedData = Decrypt(encryptedData);

    ofstream writeFile(outputFile);
    if (!writeFile)
        return cout << "Cannot write to output file '" << outputFile << "'" << endl, 6;
    writeFile << encryptedData;
    cout << "Decoding was successful" << endl;

    return 0;
}