#include "php2stl.h"

string CGIpair::decodeURLString(string URLstr) {
    const int len = URLstr.length();
    string result;
    for(int i = 0; i < len; i++) {
		if(URLstr[i] == '+')
			result += ' ';
		else if(URLstr[i] == '%') {
			result +=
			translateHex(URLstr[i + 1]) * 16 +
			translateHex(URLstr[i + 2]);
			i += 2; // Move past hex code
		} else // An ordinary character
			result += URLstr[i];
    }
    result=str_replace(":@:", "=", result);
    return result;
}
// Translate a single hex character; used by
// decodeURLString():
char CGIpair::translateHex(char hex) {
    if(hex >= 'A')
		return (hex & 0xdf) - 'A' + 10;
    else
		return hex - '0';
}
