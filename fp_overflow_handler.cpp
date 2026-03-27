#include <iostream>
#include <string>
#include <bitset>
#include <cstring>
#include <iomanip>

/** HW 2, Floating-point Overflow Handler. 
 * Program will detect when Floating-point increment has become too small
 */

class FpAnalyzer {
public:
    explicit FpAnalyzer(float val) : value(val) {
        uint32_t temp;
        std::memcpy(&temp, &value, sizeof(float));
        bits = std::bitset<32>(temp);
    }

    // returns the formatted string
    std::string getIEEE() const {
        std::string s = bits.to_string();
        return s.substr(0, 1) + " " + s.substr(1, 8) + " " + s.substr(9);
    }

    uint32_t getRaw() const {
        return static_cast<uint32_t>(bits.to_ulong());
    }

    float getValue() const { return value; }

private:
    float value;
    std::bitset<32> bits;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "usage:" << std::endl;
        std::cout << "./fp_overflow_checker loop_bound loop_counter" << std::endl;
        std::cout << "loop_bound is a positive floating-point value" << std::endl;
        std::cout << "loop_counter is a positive floating-point value" << std::endl;
        return 1;
    }

    float bound_in = std::stof(argv[1]);
    float inc_in = std::stof(argv[2]);

    FpAnalyzer bound(bound_in);
    FpAnalyzer inc(inc_in);

    std::cout << "Loop bound: " << bound.getIEEE() << std::endl;
    std::cout << "Loop counter: " << inc.getIEEE() << std::endl;

    // using single precision, a increment is lost if  difference is >= 24
    uint32_t inc_raw = inc.getRaw();
    uint32_t inc_exp = (inc_raw >> 23) & 0xFF;
    
    // the threshold for the increment is 24
    uint32_t thresh_exp = inc_exp + 24;
    
    if (thresh_exp >= 255) {
        // if increment is too large and approaches inf
        std::cout << "There is no overflow!" << std::endl;
        return 0;
    }

    uint32_t thresh_raw = (thresh_exp << 23);
    float thresh_val;
    std::memcpy(&thresh_val, &thresh_raw, sizeof(float));
    FpAnalyzer thresh(thresh_val);

    if (bound_in >= thresh_val) {
        std::cout << "Warning: Possible overflow!" << std::endl;
        std::cout << "Overflow threshold:" << std::endl;
        std::cout << thresh_val << std::endl;
        std::cout << thresh.getIEEE() << std::endl;
    } else {
        std::cout << "There is no overflow!" << std::endl;
    }

    return 0;
}