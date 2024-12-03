#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <regex>

using namespace std;


unsigned long long int perform_operation( const string &oper, const string &f1, const string &f2 ) {
  if( oper == "mul" ) {
    return atoi( f1.c_str() ) * atoi(f2.c_str());
  }
}

void process_line( string &line ) {

    std::regex mul_regex("(mul)\\(([[:digit:]]{1,3}),([[:digit:]]{1,3})\\)");

    auto words_begin =
        std::sregex_iterator(line.begin(), line.end(), mul_regex);
    auto words_end = std::sregex_iterator();

#if 0
    std::cout << "Found "
              << std::distance(words_begin, words_end)
              << " words\n";
#endif

    long double total = 0;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
      std::smatch match = *i;
      //std::cout << match.size() << " submatches found!" ;

      int result = perform_operation( match[1], match[2], match[3] );
      cout << match[0] << " = " << result << endl;

      total += result;

#if 0
      for (auto Submatch : match) {
              std::cout << "\nSubmatch: " << Submatch;
      }
      std::cout << endl;
#endif
    }

    std::cout << "That adds up to " << total << endl;
}


int main() {
    ifstream inputFile("input.txt");  // Open the input file

    if (!inputFile) {
        cerr << "Unable to open file data.txt" << endl;
        return 1;  // Exit if file can't be opened
    }

    string line;  // To read each line from the file

    // Read each line of the file
    while (getline(inputFile, line)) {
      process_line( line );
    }

    inputFile.close();  // Close the file after reading



    return 0;
}
