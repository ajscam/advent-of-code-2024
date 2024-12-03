#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <assert.h>

using namespace std;

#define MAX_INCREASE 3

bool check_descending( const vector<int> &row ) {
  for( auto it = row.begin(); it != row.end() - 1; ++it ){
    auto next = it+1;
    if ( *next - *it >= 0 || *next - *it < -MAX_INCREASE ) {
      return false;
    }
  }
  return true;
}

bool check_ascending( const vector<int> &row ) {
  for( auto it = row.begin(); it != row.end() - 1; ++it ){
      auto next = it+1;
      if ( *next - *it <= 0 || *next - *it > MAX_INCREASE ) {
        return false;
      }
  }
  return true;
}

bool check_safety( const vector<int> &row ) {

  int len = row.size();

  if( len < 2 ) { return false; }

  // First, determine if the list is ascending or descending based
  // on the first 2 values in the vector
  
  int first = row[0];
  int second = row[1];

  if( second > first ) {
    return check_ascending( row );
  } else if( second < first ) {
    return check_descending( row );
  } else {
    // The levels are neither an increase or a decrease!
    return false;
  }
  return false;
}

int main() {
    ifstream inputFile("input.txt");  // Open the input file

    if (!inputFile) {
        cerr << "Unable to open file data.txt" << endl;
        return 1;  // Exit if file can't be opened
    }

    vector<vector<int>> data;  // 2D vector to store the numbers
    string line;  // To read each line from the file

    // Read each line of the file
    while (getline(inputFile, line)) {
        stringstream ss(line);  // Use stringstream to process the line
        vector<int> row;        // Temporary vector to hold numbers for each row
        int number;

        // Read numbers from the line and add them to the row
        while (ss >> number) {
            row.push_back(number);
        }

        // Add the row to the main data
        data.push_back(row);
    }

    inputFile.close();  // Close the file after reading

    int total = 0;
    for (const auto& row : data) {
      for (int num : row) {
        cout << num << " ";
      }
      if( check_safety( row ) ) {
        total ++;
        cout << ": Safe";
      } else {
        cout << ": Unsafe";
      }
      cout << endl;
    }
    cout << "Total number safe Part 1: " << total << endl;
    assert( total == 490 );  //  This is the actual, correct answer.  Assert it here to make sure we don't break anything

    total = 0;
    for (const auto& row : data) {
      for (int num : row) {
        cout << num << " ";
      }
        if( check_safety( row ) ) {
          total ++;
          cout << ": Safe";
        } else {
          // Try to make safe by removing a level
          //
          // Brute force.  Start at the beginning and remove each 
          bool safe = false;
          for( int n=0; n< row.size(); ++n ) {
            vector<int> copy( row );
            auto it = copy.begin()+n;
            auto erased = copy.erase( it ); // remove the n'th  
            if( check_safety( copy )  ) {
              total ++;
              cout << ": Safe removing " << n+1 << " level, " << *erased ;
              safe = true;
              break;
            }
          }
          if( ! safe ) { cout << ": Unsafe"; }
          
        }
      cout << endl;
    }
    cout << "Total number safe Part 2: " << total << endl;
    assert( total == 536 ); //  This is the actual, correct answer.  Assert it here to make sure we don't break anything

    return 0;
}
