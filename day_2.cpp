#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


bool check_descending( const vector<int> &row, int tolerate = 0 ) {

  int num_errors = 0;

  for( auto it = row.begin(); it != row.end() - 1; ++it ){
    auto next = it+1;

    if ( *next - *it >= 0 || *next - *it < -3 ) {
      return false;
    }
  }
  return true;
}
bool check_ascending( const vector<int> &row, int tolerate = 0 ) {

  int num_errors = 0;
  for( auto it = row.begin(); it != row.end() - 1; ++it ){
      auto next = it+1;

      if ( *next - *it <= 0 || *next - *it > 3 ) {
        return false;
      }
  }
  if( num_errors > tolerate ) {
      cout << "Not safe!" <<  endl;
  }
  return true;
}

bool check_safety( const vector<int> &row, const int &tolerate = 0 ) {

#if 1
  for (int num : row) {
    cout << num << " ";
  }
  cout << endl;
#endif

  int len = row.size();

  if( len < 2 ) { return false; }

  if( row[1] > row[0] ) {
    return check_ascending( row, tolerate );
  } else if( row[1] < row[0] ) {
    return check_descending( row, tolerate );
  } else {
    if( row[2] > row[1] ) {
      return check_ascending( row, tolerate );
    } else if( row[2] < row[1] ) {
      return check_descending( row, tolerate );
    } else {
      cout << "Wait a minute.  The levels are equal!" << endl;
#if 0
      cout << "Contents of the file:" << endl;
      for (int num : row) {
        cout << num << " ";
      }
      cout << endl;
#endif
      return false;
    }
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
    // Output the contents of the 2D vector
    for (const auto& row : data) {
        if( check_safety( row ) ) {
          total ++;
        }
    }
    cout << "Total number safe: " << total << endl;

    total = 0;
    int tolerate = 1; // The number of levels to allow to tolerate
    for (const auto& row : data) {
        if( check_safety( row, tolerate ) ) {
          total ++;
        }
    }
    cout << "Total number safe: " << total << endl;


    return 0;
}
