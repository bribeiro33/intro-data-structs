//main.cpp
#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <vector>

using namespace std;

int main() 
{
  
  //  Asks user for file name and stores it in var "filename"
  string filename;
  cout << "enter a filename\n";
  cin >> filename;

  //  Asks user for coulumn name and stores it in var "column_name"
  string column_name;
  cout << "enter a column name\n";
  cin >> column_name; 

  //  Print informational message about the column and file
  cout << "reading column " << column_name << " from " << filename << endl;

  // Extracts data out of desired file and column and assigns to vector "v"
  vector<double> v; 
  v = extract_column(filename, column_name);
  
  //  Prints a summary of the vector
  cout << "Summary (value: frequency)" << endl; 
  for (int i = 0; i < count(v); i++){
    if (i == count(v) - 1) {
      cout << summarize(v)[i][0] << ": " << summarize(v)[i][1] << endl << endl;
    }

    else{
      cout << summarize(v)[i][0] << ": " << summarize(v)[i][1] << endl; 
    }
  }

  //  Prints a count of the number of elements in the vactor
  cout << "count = " << count(v) << endl; 

  //  Prints a sum of all the elements in the vector
  cout << "sum = " << sum(v) << endl;

  //  Prints the mean value of the elements in the vector 
  cout << "mean = " << mean(v) << endl; 

  //  Prints the standard deviation of the elements in v
  cout << "stdev = " << stdev(v) << endl; 

  // Prints the median of the elements in v
  cout << "median = " << median(v) << endl;

  //  Prints the mode of the elements in v 
  cout << "mode = " << mode(v) << endl; 

  //  Prints the minimum value in v 
  cout << "min = " << min(v) << endl; 

  //  Prints the maximum value in v 
  cout << "max = " << max(v) << endl;

  // Prints the common percentiles of the values in v
  cout << "  0th percentile = " << percentile(v, 0) << endl; 
  cout << " 25th percentile = " << percentile(v, .25) << endl; 
  cout << " 50th percentile = " << percentile(v, .5) << endl; 
  cout << " 75th percentile = " << percentile(v, .75) << endl; 
  cout << "100th percentile = " << percentile(v, 1) << endl; 

}