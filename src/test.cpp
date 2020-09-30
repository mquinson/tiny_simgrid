#include "main_include.hpp"

int main(int argc, char **argv)
{
  auto test_number = 1;
  
  if (argc == 2)
  {
    test_number = std::atoi(argv[1]);
    std::cout << "Running test " + std::to_string(test_number) + " ..." << std::endl;
  }
  else
  {
    std::cout << "Enter test number: ";
    std::cin >> test_number;
  }

  auto elapsed_time = run_test(test_number);

  std::cout << "Elapsed time in seconds = " << elapsed_time.first << std::endl;  
  std::cout << "Elapsed time in minutes = " << elapsed_time.second << std::endl;
  std::cout << "\n* FINISHED *\n";
  return 0;
}
