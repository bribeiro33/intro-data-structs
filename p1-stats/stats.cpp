// stats.cpp
#include "stats.h"
#include <cassert>
#include <vector>
#include <cmath> 
#include <iostream> 
#include <limits>
#include "p1_library.h"
using namespace std;

vector<vector<double> > summarize(vector<double> v) 
{
  double c = 1;
  sort(v);
  vector<vector<double> > summary;
  for (int i = 0; i < static_cast<int>(v.size()); i++){
    if (v[i] == static_cast<int>(v.size()) - 1){
      vector<double> row = {v[i], c};
      summary.push_back(row); 
    }

    else{
      int j = i + 1; 
      if (v[i] == v[j]){
        c++;
      }
      else{
        vector<double> row = {v[i], c};
        summary.push_back(row);
        c = 1; 
      }
    }
  }
  return summary; 
}

int count(vector<double> v) {
  return static_cast<int>(v.size());
}

double sum(vector<double> v) {
  double s = 0;

  for (size_t i = 0; i < v.size(); i++)
  {
    s += v[i];
  }
  return s;
}

double mean(vector<double> v) {
  return sum(v)/(static_cast<int>(v.size()));
}

double median(vector<double> v) {
  sort(v);
  double med = 0;
  
  //  If the vector size is 1, median = v[0]
  if (count(v) == 1){
    med = v[0];
  }

  else{ //check
    int num = floor(count(v) / 2);
    int i = num;
    int j = i - 1; 

    
    if (count(v) % 2 == 0)
    {
      med = (v[i] + v[j])/2;
    }

    
    else {med = v[i];}
  }

  return med; 
}

double mode(vector<double> v) {
   sort(v);
  double mode = v[static_cast<int>(v.size())-1];
  double c = 1; 
  double c2 = 1; 
  int j = 0; 

  for (int i = static_cast<int>(v.size()) - 1; i >= 0; i--){
    if (i - 1 < 0){
      j = count(v) - 1; 
    }

    else {
      j = i - 1; 
    }
    if (v[i] == v[j]){
      c ++; 
    }
    else {
      c = 1; 
    }
    if (c >= c2){
      mode = v[i];
      c2 = c; 
    }
  }
  return mode;  
}


double min(vector<double> v) {
  sort(v);
  return v[0];
}

double max(vector<double> v) {
  sort(v);
  return v[count(v) -1];
}

double stdev(vector<double> v) {
  vector<double> sqrdiff; 
  double sum = 0; 
  for (int i = 0; i < count(v); i++){
    double temp = (v[i] - mean(v)) * (v[i] - mean(v)); 
    sqrdiff.push_back(temp);
    sum += temp; 
  } 
  double variance = sum/(count(v) - 1); 
  return sqrt(variance); 
}

double percentile(vector<double> v, double p) {
  sort(v); 
  double pform = 0; 

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;
  
  if (abs(0.01 - p) < epsilon){
    pform = v[0];
  }

  else if (p == 1){
    pform = v[count(v) - 1]; 
  }

  else{
    //rank of the percentile
    double n = (p * (count(v) - 1)) + 1;

    //separation of n
    double k = 0; 
    double d = modf(n, &k);

    //plugging in 
    pform = v[k-1] + (d * (v[k] - v[k-1]));
  }
  
  return pform; 
}