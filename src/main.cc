#include <chrono>
#include <iostream>

int main()
{
  const std::chrono::time_point<std::chrono::system_clock> start
    = std::chrono::system_clock::now();

  // code

  const std::chrono::time_point<std::chrono::system_clock> end
    = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "Execution time : " << elapsed_seconds.count()
	    << " sec." << std::endl;

}
