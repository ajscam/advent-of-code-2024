#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

// Function to sort an array
// using insertion sort
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        // Move elements of arr[0..i-1],
        // that are greater than key, to one
        // position ahead of their
        // current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
 
int part_two( vector<int>& first, vector<int>& second ) {
  int total = 0, winner = 0, similarity = 0;

  auto sec_it = second.begin();
  int count = 0;
  for( auto it = first.begin(); it != first.end(); ++it ) {
    //cout << "Starting with " << *it << ", second is " << *sec_it << endl;
    if( *it > winner ) {
      count = 0;
    }
    else if( *it == winner ) {
      // Another one, add the similarity
      total += similarity;
    }
    while( sec_it != second.end() && *sec_it <= *it ) {
      if( *sec_it == *it ) {
        count++;
      }
      sec_it++;
    }
    if( count > 0 ) {
      similarity = *it * count;
      //cout << "Winner! " << *it << " was found " << count << " times, similarity: " << similarity << endl;
      winner = *it; 
      total += similarity;
    } else {
      //cout << "reset" << endl;
      count = 0;
    }
  }

  return total;
}

int part_one( vector<int>& first, vector<int>& second ) {
  int total=0; 

  auto sec_it = second.begin();
  for( auto it = first.begin(); it != first.end(); ++it ) {
    int diff = abs(*sec_it - *it);
    //cout << "one=" << *it << ", two=" << *sec_it << ", difference=" << diff << endl;
    total += diff;
    sec_it++;
  }
  return total;
}


int main(void)
{
  string line;
  ifstream myfile;
  myfile.open("input.txt");

  if(!myfile.is_open()) {
      perror("Error open");
      exit(EXIT_FAILURE);
  }

  int total=0;
  int one, two;

  vector<int> first, second;

  cout << "Reading input.txt" << endl;
  while(getline(myfile, line)) {
    sscanf(line.data(), "%d %d", &one, &two ); 
    cout << "one=" << one << ", two=" << two << endl;
    first.push_back( one );
    second.push_back( two );
  }
  cout << "Done reading input.txt" << endl;
  insertionSort(first.data(), first.size());
  insertionSort(second.data(), second.size());

  cout << "Part One total=" << part_one( first, second ) << endl;

  cout << "Part Two. total=" << part_two( first, second ) << endl;

  return 0;
}

