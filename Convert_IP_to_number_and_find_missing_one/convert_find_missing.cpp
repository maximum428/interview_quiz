#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>
#include <stdexcept>


using namespace std;

uint32_t convertToUint32(const string&  ip) {
  vector<uint8_t> ip_sections;
  size_t start = 0;
  for (size_t i = 0; i < ip.size(); i++) {
    if (ip[i] == '.') {
      if (i == start) {
        throw invalid_argument("Invalid IP format");
      }
      int value = stoi(ip.substr(start, i - start));
      if (value < 0 || value > 255) {
        throw out_of_range("IP section out of range");
      }
      ip_sections.push_back(static_cast<uint32_t>(value));
      start = i+1;
    }
  }
  
  if (start >= ip.size()) {
    throw invalid_argument("Invalid IP format");
  }

  int value = stoi(ip.substr(start));
  if (value < 0 || value > 255) {
    throw out_of_range("IP section out of range");
  }
  ip_sections.push_back(static_cast<uint32_t>(value));

  if (ip_sections.size() != 4) {
    throw invalid_argument("IP must have exactly 4 sections");
  }

  return ip_sections[0] << 24 | ip_sections[1] << 16 | ip_sections[2] << 8 | ip_sections[3];
}

string convertToIpString(uint32_t value) {
  return to_string((value >> 24) & 0xFF) + "." + to_string((value >> 16) & 0xFF) + "." + to_string((value >> 8) & 0xFF) + "." + to_string(value & 0xFF);
}

uint32_t findMissingIp(const string& filename) {
  /* Range from 0.0.0.0 to 255.255.255.255.
   Use XOR bitwise operation to find Missing IP from a file which store each IP address per line.
   For example, we have numbers (afer converting ip to numbers) in a file:
      00
      01
      10
      11
  after convert ip address to number, sum: 00 ^ 01 ^ 10 ^ 11 = 0

   if 01 is missing, then 00 ^ 10 ^ 11 = 01 is missing number and convert the number back to IP address */

   ifstream fin(filename);
   if (!fin) {
    throw runtime_error("Failed to open file: " + filename);
   }

   uint32_t xor_all = 0;
   string line;

   // XOR all IPs from file
   while (getline(fin, line)) {
    if (line.empty()) {
      continue;
    }
    xor_all ^= convertToUint32(line);
   }
   // Since XOR of all values from 0 to 2^32-1 is 0,
   // if exactly one IP is missing, the remaing XOR is the missing one.
   return xor_all;
}

int main() {
  try {
    string ip = "192.168.10.1";
    uint32_t value = convertToUint32(ip);

    cout << "IP: " << ip << endl;
    cout << "Uint32: " << value << endl;
    cout << "Back to IP: " << convertToIpString(value) << endl;

    // Example:
    // uint32_t missing = findMissingIp("ips.txt");
    // cout << "Missing IP number: " << missing << endl;
    // cout << "Missing IP string: " << convertToIpString(missing) << endl;
  } catch (const exception& e) {
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}

