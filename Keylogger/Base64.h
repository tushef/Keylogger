#ifndef BASE64_H
#define BASE64_H
#include <vector>
#include <string>

//lib for pair data structure 
#include <utility>

namespace Base64 {
	std::string base64_encode(const std::string&);

	const std::string& SALT1 = "LM::TB::";
	const std::string& SALT2 = "12_22_32";
	const std::string& SALT3 = "13901420";

	std::pair <int, int> getSmallestFactorPair(int num) {

		// O(sqrt(n))

		std::pair <int, int> ret;
		for (int i = 1; i * i <= num; i++)
			if (num % i == 0) {
				ret.first = i;
				ret.second = num / i;
			}
		return ret;
	}

	std::string EncryptB64(std::string str)
	{
		/*
			My Encryption Algorithm - O(n)

			Hello World -> Hore llwdlo

			   0   1   2   3
			0| H | e | l | l |
			1| o |   | W | o |
			2| r | l | d |NUL|

			String:  Hello World -> Hore llWdlo
			Indexes: 0,1,2,3,4,5,6,7,8,9,10 -> 0,4,8,1,5,9,2,6,10,3,7,10
			Rule: ch1 = ch0 + ROW; 
			ROW = getSmallestFactorPair(str.length()+str.length()%2).first
			COLUMN = getSmallestFactorPair(str.length()+str.length()%2).second


			***SALTS
				Before the Encryption algorithm is executed
				we add 3 Salts to the original string

		*/

		int layers = 1;
		std::string ret = "";
		std::pair<int, int> table = getSmallestFactorPair(str.length() + str.length() % 2);

		while (layers != 0) {

			
			str.insert((str.length() + str.length() % 2) / 2, SALT2);
			str.insert(0, SALT1);
			str.insert(str.length()-1, SALT3);

			for (int i = 0; i < table.second; i++) {
				for (int j = i; j < signed(str.length()); j += table.second) {
					if (str[j] == '\0') {
						continue;
					}
					ret += str[j];
				}
			}

			ret = base64_encode(ret);

			layers--;
		}

		return base64_encode(str);
	}

	const std::string& BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	std::string base64_encode(const std::string& s)
	{
		std::string ret;
		// index we use map to table
		int val = 0; 
		// used to represent number of bits in a subgroup (of six)
		int bits = -6; 
		const unsigned int b63 = 0x3F; // decimal value is 63

		//c is assign every character from s string
		for (const auto& c : s) 
		{
			// left binary shift by 8, same as val * 2^8 + c
			val = (val << 8) + c; 
			// add 8 to numbers of bits when extracting info (octets)
			bits += 8; 

			while (bits >= 0)
			{
				// does binary right shift + binary AND comparison
				ret.push_back(BASE64_CODES[(val >> bits) & b63]); 
				bits -= 6;
			}
		}

		if (bits > -6) // means at least one character has been insert
			ret.push_back(BASE64_CODES[((val << 8) >> (bits + 8)) & b63]);

		while (ret.size() % 4)
			ret.push_back('=');

		return ret;
	}

}

#endif // !BASE64_H
