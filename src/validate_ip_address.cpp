#include "../inc.hpp"

class LC_ValidateIPAddress {
public:
    int ipv4_section(string IP, int start) {
        bool leading_zero = false;
        int val = 0;
        int i;
        for (i = start; i < start + 3 && i < IP.size(); i++) {
            if (IP[i] >= '0' && IP[i] <= '9') {
                if (leading_zero) return -1;
                int n = IP[i] - '0';
                if (n == 0 && i == start) {
                    leading_zero = true;
                }
                val *= 10;
                val += n;
            } else {
                break;
            }
        }
        return i == start || val > 255 ? -1 : i;
    }
    bool ipv4(string IP) {
        int i = 0;
        i = ipv4_section(IP, i);
        if (i == -1 || i == IP.size() || IP[i++] != '.') return false;
        i = ipv4_section(IP, i);
        if (i == -1 || i == IP.size() || IP[i++] != '.') return false;
        i = ipv4_section(IP, i);
        if (i == -1 || i == IP.size() || IP[i++] != '.') return false;
        i = ipv4_section(IP, i);
        if (i == -1 || i != IP.size()) return false;
        return true;
    }
    int ipv6_section(string IP, int start) {
        int i;
        for (i = start; i < start + 4 && i < IP.size(); i++) {
            if ((IP[i] >= '0' && IP[i] <= '9') ||
                (IP[i] >= 'a' && IP[i] <= 'f') ||
                (IP[i] >= 'A' && IP[i] <= 'F')) {
                } else {break;}
        }
        return i == start ? -1 : i;
    }
    bool ipv6(string IP) {
        int i = 0;
        i = ipv6_section(IP, i);
        if (i == -1 || i == IP.size() || IP[i++] != ':') return false;
        i = ipv6_section(IP, i);
        if (i == -1 || i == IP.size() || IP[i++] != ':') return false;
        i = ipv6_section(IP, i);
        if (i == -1 || i == IP.size() || IP[i++] != ':') return false;
        i = ipv6_section(IP, i);
        if (i == -1 || i == IP.size() || IP[i++] != ':') return false;
        i = ipv6_section(IP, i);
        if (i == -1 || i == IP.size() || IP[i++] != ':') return false;
        i = ipv6_section(IP, i);
        if (i == -1 || i == IP.size() || IP[i++] != ':') return false;
        i = ipv6_section(IP, i);
        if (i == -1 || i == IP.size() || IP[i++] != ':') return false;
        i = ipv6_section(IP, i);
        if (i == -1 || i != IP.size()) return false;
        return true;
    }
    string validIPAddress(string IP) {
        return ipv4(IP) ? "IPv4" : ipv6(IP) ? "IPv6" : "Neither";
    }
};

TEST_CASE("LC: Validate IP Address") {
    auto s = make_shared<LC_ValidateIPAddress>();
    CHECK(s->ipv4_section("018", 0) == -1);
    CHECK(s->ipv4_section("18", 0) == 2);
    CHECK(s->ipv4_section("180", 0) == 3);
    CHECK(s->ipv4_section("100", 0) == 3);
    CHECK(s->ipv4_section("1", 0) == 1);
    CHECK(s->ipv4_section("", 0) == -1);
    CHECK(s->ipv4_section("256", 0) == -1);
    CHECK(s->ipv4_section("255", 0) == 3);
    CHECK(s->ipv4_section("01", 0) == -1);
    CHECK(s->ipv4_section("11", 0) == 2);
    CHECK(s->ipv4("127.0.0.1"));
    CHECK(s->validIPAddress("127.1.1.1") == "IPv4");
    CHECK(s->validIPAddress("00.1.1.1") == "Neither");
    CHECK(s->validIPAddress("255.255.255.255") == "IPv4");
    CHECK(s->ipv6_section("2001", 0) == 4);
    CHECK(s->ipv6_section("aaaa", 0) == 4);
    CHECK(s->ipv6_section("FFFF", 0) == 4);
    CHECK(s->ipv6_section("F", 0) == 1);
    CHECK(s->ipv6_section("", 0) == -1);
    CHECK(s->ipv6_section("1a", 0) == 2);
    CHECK(s->ipv6("2001:0db8:85a3:0:0:8A2E:0370:7334"));
    CHECK(s->ipv6("2001:db8:85a3:0:0:8A2E:0370:FFFF"));
    CHECK(s->validIPAddress("2001:db8:85a3:0:0:8A2E:0370:FFFF") == "IPv6");
}