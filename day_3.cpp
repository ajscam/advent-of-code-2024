#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <assert.h>

#include <regex>

using namespace std;

const std::string DO = "do()";
const std::string DONT = "don't()";


unsigned int process_line( string &line, bool part2 = false ) {

  std::cout << "line=" << line << endl << endl;

  static bool enable = true;  // wow!  This is tricky.  This static declaration preservese the state of enable  
                              // variable across calls to this method.  This means from one line to the next of input 
                              // So a don't() at the very end of line 1 applies to the beginning of line 2.
                              // I missed this initially....
  std::string s2("don't()");
  std::string s3("do()");

  // This regex finds instructions like mul(X,Y), where X and Y are each 1-3 digit numbers. 
  // For instance, mul(44,46)
  // std::regex mul_regex("mul\\(([[:digit:]]{1,3}),([[:digit:]]{1,3})\\)");

  // And this is the regex for Part 2
  std::regex mul_regex("mul\\(([[:digit:]]{1,3}),([[:digit:]]{1,3})\\)|don't\\(\\)|do\\(\\)");

  // Using the regex above, get iterators to the matching results
  auto words_begin = std::sregex_iterator(line.begin(), line.end(), mul_regex);
  auto words_end =   std::sregex_iterator();

  std::cout << "Found "
            << std::distance(words_begin, words_end)
            << " expressions\n";

    unsigned int total = 0;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
      std::smatch match = *i;

      if( match[0] == DONT ) {
        cout << "match is " << match[0] << endl;
        enable = false;
      }
      else if( match[0] == DO ) {
        cout << "match is " << match[0] << endl;
        enable = true;
      } else {
        int product = 0;
        if( enable ) {
          product = atoi((match[1].str()).c_str()) * atoi((match[2].str()).c_str());
        }
        cout << match[0] << " = " << product << endl;
        total += product;
        //cout << "running total = " << total << endl;
      }

    }

    std::cout << "That adds up to " << total << endl;

    return total;
}


int main() {
    ifstream inputFile("input.txt");  // Open the input file

    if (!inputFile) {
        cerr << "Unable to open file data.txt" << endl;
        return 1;  // Exit if file can't be opened
    }

    string line;  // To read each line from the file

    int total = 0;

    // Read each line of the file
    while (getline(inputFile, line)) {
      total += process_line( line, true );
      //cout << "Running total = " << total << endl;
    }
    inputFile.close();  // Close the file after reading

    cout << "Total = " << total << endl;
    
    // I get the correct answer, then hard-code it here to make sure I get the right answer after cleanup
    // part 1
    //assert ( total == 167650499 );
    // part 2
    assert ( total == 95846796 ); 


    return 0;
}
