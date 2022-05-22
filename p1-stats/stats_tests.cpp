/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <limits> 
using namespace std;

void test_sum_small_data_set();
void summarize_test();
void summarize_test_single();
void count_test();
void count_test_empty(); 
void sum_test();
void sum_test_single(); 
void mean_test();
void mean_test_single(); 
void median_test_even();
void median_test_odd();
void median_test_neg();
void median_test_single();
void mode_test();
void mode_test_equal();
void mode_test_single();
void mode_test_multiple();
void min_test();
void min_test_single();
void max_test();
void max_test_single(); 
void stdev_test();
void stdev_test_zeros();
void percentile0_test();
void percentile25_test();
void percentile50_test();
void percentile75_test();
void percentile100_test();
void percentile1_test();
void percentile73_test();


// Add prototypes for you test functions here.

int main()
{
  /*test_sum_small_data_set();
  // Call your test functions here
  */
  summarize_test();
  summarize_test_single();
  count_test();
  count_test_empty();
  sum_test();
  sum_test_single();
  mean_test();
  mean_test_single(); 
  median_test_even();
  median_test_odd();
  median_test_neg();
  median_test_single();
  mode_test();
  mode_test_equal();
  mode_test_single();
  mode_test_multiple();
  min_test();
  min_test_single();
  max_test();
  max_test_single();
  stdev_test();
  stdev_test_zeros();
  percentile0_test();
  percentile25_test();
  percentile50_test();
  percentile75_test();
  percentile100_test();
  percentile1_test();
  percentile73_test();

  return 0;
}

void test_sum_small_data_set()
{
  cout << "test_sum_small_data_set" << endl;
  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  assert(sum(data) == 6);
  cout << "PASS!" << endl;
}

void summarize_test(){
  // input: {-1, 0, 1, 2, 5.2, 2, 0, -1, -1, -1, 2, 0, -1}
  // expected: {{-1,5}, {0,3}, {1,2}, {2,3}, {5.2,1}}
  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;
  
  vector<double> summarize_t = {-1, 0, 1, 2, 5.2, 2, 0, -1, -1, -1, 2, 0, -1, 1}; 
  vector<vector<double> > expected = {{-1,5}, {0,3}, {1,2}, {2,3}, {5.2,1}};
  
  vector<vector<double> > result = summarize(summarize_t);

  for (size_t i = 0; i < result.size(); i++){
    for (size_t j = 0; j < result[i].size(); j++){
      if (abs(result[i][j] - expected[i][j]) < epsilon){
        assert(true);}
      else {assert(false);}
    }
  }
  cout << "PassA" << endl; 
}

void summarize_test_single(){
  // input: {0}
  // expected: {{0,1}}
  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;
  
  vector<double> summarize_t = {0}; 
  vector<vector<double> > expected2 = {{0,1}};
  
  vector<vector<double> > result2 = summarize(summarize_t);

  for (size_t i = 0; i < result2.size(); i++){
    for (size_t j = 0; j < result2[i].size(); j++){
      if (abs(result2[i][j] - expected2[i][j]) < epsilon){
        assert(true);}
      else {assert(false);}
    }
  }
  cout << "PassB" << endl; 
}

void count_test(){
  //input: {3,-4,2.4,0}
  //expected: 4
  vector<double> count_t = {3,-4,2.4,0};
  assert(count(count_t) == 4); 
  cout << "Pass1" << endl; 
}

void count_test_empty(){
  //input: {}
  //expected: 0
  vector<double> count_t = {};
  assert(count(count_t) == 0);
  cout << "Pass2" << endl; 
}

void sum_test(){
  //input: {3,-4,2.4,0}
  //expected: 1.4
  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;
  
  vector<double> sum_t = {3,-4,2.4,0};
  double result = sum(sum_t);
  
  if (abs(result - 1.4) < epsilon){assert(true);}
  
  else {assert(false);}

  cout << "Pass3" << endl;
}

void sum_test_single(){
  //input: {0}
  //expected: 0
  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;
  
  vector<double> sum_t = {0};
  double result = sum(sum_t);

  if (abs(result - 0) < epsilon){assert(true);}
  
  else {assert(false);}

  cout << "Pass4" << endl;
}

void mean_test(){
  //input: {3,-4,2.4,0}
  //expected: 0.35

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> mean_t = {3,-4,2.4,0};
  double result = mean(mean_t);
  
  if (abs(result - 0.35) < epsilon){assert(true);}
    
  else {assert(false);}

  cout << "Pass5" << endl;
}

void mean_test_single(){
  //input: {0}
  //expected: 0

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> mean_t = {0};
  double result = mean(mean_t);
  
  if (abs(result - 0) < epsilon){assert(true);}
    
  else {assert(false);}

  cout << "Pass6" << endl;
}

void median_test_even(){
  //input: {3,-4,2.4,0}
  //expected: 1.2

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> median_t = {3,-4,2.4,0};
  double result = median(median_t);
  
  if (abs(result - 1.2) < epsilon){assert(true);}
    
  else {assert(false);}

  cout << "Pass7" << endl;
}

void median_test_odd(){
  //input: {5,-3.3,7,4.2,0}
  //expected: 4.2

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> median_t = {5,-3.3,7,4.2,0};
  double result = median(median_t);
  
  if (abs(result - 4.2) < epsilon){assert(true);}
    
  else {assert(false);}

  cout << "Pass8" << endl;
}

void median_test_neg(){
  //input: {-3,-3.3,-3.6,0}
  //expected: -3.15

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> median_t = {-3,-3.3,-3.6,0};
  double result = median(median_t);
  
  if (abs(result - (-3.15)) < epsilon){assert(true);}
    
  else {assert(false);}

  cout << "Pass9" << endl;
}

void median_test_single(){
  //input: {0}
  //expected: 0

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> median_t = {0};
  double result = median(median_t);
  
  if (abs(result - (0)) < epsilon){assert(true);}
    
  else {assert(false);}

  cout << "Pass10" << endl;
}

void mode_test(){
  //input: {-1,-1,-2,0}
  //expected: -1

  vector<double> mode_t = {-1,-1,-2};
  assert(mode(mode_t) == -1);
  cout << "Pass11" << endl; 
}

void mode_test_equal(){
  //input: {2,2, 2.2, 1.5, 1.5, 0}
  //expected: 1.5

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> mode_t = {2,2, 2.2, 1.5, 1.5};
  double result = mode(mode_t);
  
  if (abs(result - 1.5) < epsilon){assert(true);}
    
  else {assert(false);}
  
  cout << "Pass12" << endl; 
}

void mode_test_single(){
  //input: {0}
  //expected: 0

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> mode_t = {0};
  double result = mode(mode_t);
  
  if (abs(result - (0)) < epsilon){assert(true);}
    
  else {assert(false);}
  
  cout << "Pass13" << endl; 
}

void mode_test_multiple(){
  //input: {1, 2, 3, 3, 2, 1, 3, 0}
  //expected: 3

  vector<double> mode_t = {1, 2, 3, 3, 2, 1, 3, 0};
  
  assert(mode(mode_t) == 3);
  
  cout << "Pass14" << endl; 
}

void min_test(){
  //input: {0,5,-3.1,-2.8}
  //expected: -3.1

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> min_t = {0,5,-3.1,-2.8}; 
  double result = min(min_t);

  if (abs(result - (-3.1)) < epsilon){assert(true);}

  else {assert(false);}
  
  cout << "Pass15" << endl; 
}

void min_test_single(){
  //input: {0}
  //expected: 0

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> min_t = {0};
  double result = min(min_t);

  if (abs(result - (0)) < epsilon){assert(true);}

  else {assert(false);}
  
  cout << "Pass16" << endl; 
}

void max_test(){
  //input: {0,5,-3.1,5.5}
  //expected: 5.5

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> max_t = {0,5,-3.1,5.5}; 
  double result = max(max_t);

  if (abs(result - (5.5)) < epsilon){assert(true);}

  else {assert(false);}
  
  cout << "Pass17" << endl; 
}

void max_test_single(){
  //input: {0}
  //expected: 0

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> max_t = {5.5}; 
  double result = max(max_t);

  if (abs(result - (5.5)) < epsilon){assert(true);}

  else {assert(false);}
  
  cout << "Pass18" << endl; 
}

void stdev_test(){
  //input: {0,5,-3.1,5.5}
  //expected: 4.1299717513158

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> stdev_t = {0,5,-3.1,5.5}; 
  double result = stdev(stdev_t);

  if (abs(result - (4.1299717513158)) < epsilon){assert(true);}

  else {assert(false);}
  
  cout << "Pass19" << endl; 
}

void stdev_test_zeros(){
  //input: {0,0}
  //expected: 0

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;

  vector<double> stdev_t = {0,0}; 
  double result = stdev(stdev_t);

  if (abs(result - (0)) < epsilon){assert(true);}

  else {assert(false);}
  
  cout << "Pass20" << endl; 
}

void percentile0_test(){
  //input1: {2.2, -3.5, 50, 4, 0}
    //e: -3.5
  //input2: {0,0}
    //e: 0
  //input3: {1,1,1,1}
    //e: 1

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;
  
  vector<double> per_t1 = {2.2, -3.5, 50, 4, 0};
  vector<double> per_t2 = {0,0};
  vector<double> per_t3 = {1, 1, 1, 1};

  double result1 = percentile(per_t1, 0);
  double result2 = percentile(per_t2, 0);
  double result3 = percentile(per_t3, 0);

  if ((result1 - (-3.5)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result2 - (0)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result3 - (1)) < epsilon){assert(true);}
  else {assert(false);}

  cout << "Pass21" << endl; 
}

void percentile25_test(){
  //input1: {2.2, -3.5, 50, 4, 0}
    //e: -1.75
  //input2: {0,0}
    //e: 0
  //input3: {1,1,1,1}
    //e: 1

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;
  
  vector<double> per_t1 = {2.2, -3.5, 50, 4, 0};
  vector<double> per_t2 = {0,0};
  vector<double> per_t3 = {1, 1, 1, 1};

  double result1 = percentile(per_t1, .25);
  double result2 = percentile(per_t2, .25);
  double result3 = percentile(per_t3, .25);

  if ((result1 - (0)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result2 - (0)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result3 - (1)) < epsilon){assert(true);}
  else {assert(false);}

  cout << "Pass22" << endl; 
}

void percentile50_test(){
  //input1: {2.2, -3.5, 50, 4, 0}
    //e: 0
  //input2: {0,0}
    //e: 0
  //input3: {1,1,1,1}
    //e: 1

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;
  
  vector<double> per_t1 = {2.2, -3.5, 50, 4, 0};
  vector<double> per_t2 = {0,0};
  vector<double> per_t3 = {1, 1, 1, 1};

  double result1 = percentile(per_t1, .5);
  double result2 = percentile(per_t2, .5);
  double result3 = percentile(per_t3, .5);

  if ((result1 - (2.2)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result2 - (0)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result3 - (1)) < epsilon){assert(true);}
  else {assert(false);}

  cout << "Pass23" << endl; 
}
  
  void percentile75_test(){
  //input1: {2.2, -3.5, 50, 4, 0}
    //e: 4
  //input2: {0,0}
    //e: 0
  //input3: {1,1,1,1}
    //e: 1

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;
  
  vector<double> per_t1 = {2.2, -3.5, 50, 4, 0};
  vector<double> per_t2 = {0,0};
  vector<double> per_t3 = {1, 1, 1, 1};

  double result1 = percentile(per_t1, .75);
  double result2 = percentile(per_t2, .75);
  double result3 = percentile(per_t3, .75);

  if ((result1 - (4)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result2 - (0)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result3 - (1)) < epsilon){assert(true);}
  else {assert(false);}

  cout << "Pass24" << endl; 
}

void percentile100_test(){
  //input1: {2.2, -3.5, 50, 4, 0}
    //e: 50
  //input2: {0,0}
    //e: 0
  //input3: {1,1,1,1}
    //e: 1

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;
  
  vector<double> per_t1 = {2.2, -3.5, 50, 4, 0};
  vector<double> per_t2 = {0,0};
  vector<double> per_t3 = {1, 1, 1, 1};

  double result1 = percentile(per_t1, 1);
  double result2 = percentile(per_t2, 1);
  double result3 = percentile(per_t3, 1);

  if ((result1 - (50)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result2 - (0)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result3 - (1)) < epsilon){assert(true);}
  else {assert(false);}

  cout << "Pass25" << endl; 
}

void percentile1_test(){
  //input1: {2.2, -3.5, 50, 4, 0}
    //e: -3.36
  //input2: {0,0}
    //e: 0
  //input3: {1,1,1,1}
    //e: 1

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;
  
  vector<double> per_t1 = {2.2, -3.5, 50, 4, 0};
  vector<double> per_t2 = {0,0};
  vector<double> per_t3 = {1, 1, 1, 1};

  double result1 = percentile(per_t1, .01);
  double result2 = percentile(per_t2, .01);
  double result3 = percentile(per_t3, .01);

  if ((result1 - (-3.36)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result2 - (0)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result3 - (1)) < epsilon){assert(true);}
  else {assert(false);}

  cout << "Pass26" << endl; 
}

void percentile73_test(){
  //input1: {2.2, -3.5, 50, 4, 0}
    //e: 3.856
  //input2: {0,0}
    //e: 0
  //input3: {1,1,1,1}
    //e: 1

  cout.precision(std::numeric_limits<double>::max_digits10);
  const double epsilon = 0.00001;
  
  vector<double> per_t1 = {2.2, -3.5, 50, 4, 0};
  vector<double> per_t2 = {0,0};
  vector<double> per_t3 = {1, 1, 1, 1};

  double result1 = percentile(per_t1, .73);
  double result2 = percentile(per_t2, .73);
  double result3 = percentile(per_t3, .73);

  if ((result1 - (3.856)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result2 - (0)) < epsilon){assert(true);}
  else {assert(false);}

  if ((result3 - (1)) < epsilon){assert(true);}
  else {assert(false);}

  cout << "Pass27" << endl; 
}

  
