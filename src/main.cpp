#include "include.hpp"

int main(int argc, char** argv)
{
    auto example = 1;
    std::cout << "Enter an example number: ";
    if (argc == 2)
        example = std::atoi(argv[1]);
    else
        std::cin >> example;

    auto begin = clock();

    switch (example) {
    case  1: TEST_1();  break;
    case  2: TEST_2();  break;
    case  3: TEST_3();  break;
    case  4: TEST_4();  break;
    case  5: TEST_5();  break;
    case  6: TEST_6();  break;
    case  7: TEST_7();  break;
    case  8: TEST_8();  break;
    case  9: TEST_9();  break;
    case 10: TEST_10(); break;
    case 11: TEST_11(); break;
    case 12: TEST_12(); break;
    case 13: TEST_13(); break;
    case 14: TEST_14(); break;
    case 15: TEST_15(); break;
    case 16: TEST_16(); break;
    case 17: TEST_17(); break;
    }

    auto end = clock();
    double elapsed_secs = double(end-begin)/(60*CLOCKS_PER_SEC);

    std::cout << " Time in second= " << double(end - begin) / (CLOCKS_PER_SEC) << "  \n";
    std::cout << " Time in minutes= " << elapsed_secs << "  \n";

    std::cout << " \n main() finished ";
    return 0;
}
