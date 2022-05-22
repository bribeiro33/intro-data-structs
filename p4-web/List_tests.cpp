// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"
#include <cassert>
#include <iostream>

using namespace std;

// Add your test cases here

// don't know how to test contructor with Node
TEST(test_contructors) {
    List<int> my_list;
    assert(my_list.empty());
    assert(my_list.size() == 0);
    my_list.push_back(42);
    assert(my_list.size() == 1);
    List<int> my_list2(my_list);
    assert(!my_list2.empty());
    assert(my_list2.size() == 1);
    assert(my_list2.front() == 42);
    assert(my_list2.back() == 42);
    my_list.pop_back();
    assert(my_list.empty());
    assert(my_list.size() == 0);
    
    my_list.push_back(12);
    my_list.push_back(13);
    my_list.push_back(14);
    my_list.push_back(15);
    int array[] = {12, 13, 14, 15};
    int count = 0;
    List<int> my_list3(my_list);
    assert(my_list3.front() == 12);
    assert(my_list.front() == 12);
    assert(my_list3.back() == 15);
    assert(my_list.back() == 15);
    for (List<int>::Iterator i = my_list3.begin(); i != my_list3.end(); ++i) {
        assert(*i == array[count]);
        count++;
    }
    assert(count == my_list3.size());
    
    my_list2 = my_list3;
    count = 0;
    for (List<int>::Iterator i = my_list2.begin(); i != my_list2.end(); ++i) {
        assert(*i == array[count]);
        count++;
    }
    assert(count == my_list3.size());
    assert(!my_list2.empty());
    assert(!my_list3.empty());
    assert(my_list2.front() == 12);
    assert(my_list2.back() == 15);
    
    my_list2.pop_back();
    assert(my_list2.size() == 3);
    my_list2.pop_back();
    assert(my_list2.size() == 2);
    my_list2.pop_back();
    assert(my_list2.size() == 1);
    my_list2.pop_back();
    assert(my_list2.size() == 0);
    assert(my_list2.empty());
    List<int> my_list4(my_list2);
    assert(my_list4.empty());
}

TEST(test_front_and_back) {
    List<int> my_list;
    my_list.push_back(2);
    assert(my_list.front() == 2);
    assert(my_list.back() == 2);
    my_list.push_front(4);
    assert(my_list.front() == 4);
    assert(my_list.back() == 2);
    List<int>::Iterator i = my_list.begin();
    assert(*i == 4);
    ++i;
    assert(*i == 2);
    my_list.push_back(11);
    ++i;
    assert(*i == 11);
    assert(my_list.front() == 4);
    assert(my_list.back() == 11);
    my_list.push_back(16);
    ++i;
    assert(*i == 16);
    assert(my_list.front() == 4);
    assert(my_list.back() == 16);
    my_list.push_front(17);
    assert(my_list.front() == 17);
    assert(my_list.back() == 16);
    my_list.pop_back();
    assert(my_list.front() == 17);
    assert(my_list.back() == 11);
    my_list.pop_front();
    assert(my_list.front() == 4);
    assert(my_list.back() == 11);
    my_list.pop_back();
    assert(my_list.front() == 4);
    assert(my_list.back() == 2);
    my_list.pop_front();
    assert(my_list.front() == 2);
    assert(my_list.back() == 2);
    my_list.pop_back();
    assert(my_list.empty());
    assert(my_list.size() == 0);
}

TEST (test_clear) {
    List<string> my_list;
    my_list.push_back("blue");
    my_list.push_front("pig");
    my_list.push_front("catan");
    assert(my_list.size() == 3);
    my_list.clear();
    assert(my_list.size() == 0);
    assert(my_list.empty());
}

TEST (test_iterator_operators) {
    List<int> my_list;
    my_list.push_back(12);
    my_list.push_back(8);
    my_list.push_back(11);
    my_list.push_back(37);
    my_list.push_back(42);
    my_list.push_back(22);
    int array[] = {12, 8, 11, 37, 42, 22};
    int count = 0;
    for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array[count]);
        count++;
    }
    assert(count == my_list.size());
    
    List<int>::Iterator i = my_list.begin();
    ++i; // 8
    ++i; // 11
    ++i; // 37
    ++i; // 42
    ++i; // 22
    
    count -= 1;
    while (i != my_list.begin()) {
        assert(*i == array[count]);
        --i;
        --count;
    }
    
    i = my_list.begin();
    ++i;
    List<int>::Iterator j = my_list.begin();
    assert(j != i);
    ++j;
    assert(j == j);
    --i;
    assert(j != i);
    --j;
    assert(j == i);
}

TEST (test_erase) {
    List<int> my_list;
    my_list.push_back(12);
    my_list.push_back(8);
    my_list.push_back(11);
    my_list.push_back(37);
    my_list.push_back(42);
    my_list.push_back(22);
    int array[] = {8, 11, 37, 42, 22};
    List<int>::Iterator first = my_list.begin();
    my_list.erase(first);
    int count = 0;
    for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array[count]);
        count++;
    }
    assert(count == my_list.size());
    
    int array1[] = {8, 37, 42, 22};
    List<int>::Iterator second = my_list.begin();
    ++second;
    my_list.erase(second);
    count = 0;
    for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array1[count]);
        count++;
    }
    assert(count == my_list.size());
    
    int array2[] = {8, 37, 42};
    List<int>::Iterator last = my_list.begin(); // 8
    ++last; // 37
    ++last; // 42
    ++last; // 22
    my_list.erase(last);
    assert(my_list.back() == 42);
    count = 0;
    for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array2[count]);
        count++;
    }
    assert(count == my_list.size());
    
    int array3[] = {8, 42};
    List<int>::Iterator second1 = my_list.begin();
    ++second1;
    my_list.erase(second1);
    count = 0;
    for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array3[count]);
        count++;
    }
    assert(count == my_list.size());
    
    int array4[] = {8};
    List<int>::Iterator last1 = my_list.begin();
    ++last1;
    my_list.erase(last1);
    count = 0;
    for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array4[count]);
        count++;
    }
    assert(count == my_list.size());
    
    List<int>::Iterator first1 = my_list.begin();
    my_list.erase(first1);
    assert(my_list.empty());
    assert(my_list.size() == 0);
}

TEST (test_insert) {
    List<int> my_list;
    my_list.push_back(12);
    my_list.push_back(8);
    my_list.push_back(11);
    my_list.push_back(37);
    my_list.push_back(42);
    my_list.push_back(22);
    int array[] = {12, 15, 8, 11, 37, 42, 22};
    List<int>::Iterator second = my_list.begin();
    ++second;
    my_list.insert(second, 15);
    int count = 0;
    for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array[count]);
        count++;
    }
    assert(count == my_list.size());
    
    int array1[] = {26, 12, 15, 8, 11, 37, 42, 22};
    List<int>::Iterator first = my_list.begin();
    my_list.insert(first, 26);
    count = 0;
    for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array1[count]);
        count++;
    }
    assert(count == my_list.size());
    
    int array2[] = {26, 12, 15, 8, 11, 37, 42, 58, 22};
    List<int>::Iterator last = my_list.begin();
    ++last; // 12
    ++last; // 15
    ++last; // 8
    ++last; // 11
    ++last; // 37
    ++last; // 42
    ++last; // 22
    my_list.insert(last, 58);
    count = 0;
    for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array2[count]);
        count++;
    }
    assert(count == my_list.size());
}

TEST (test_intert2) {
    List<char> my_list;
    my_list.push_back('b');
    List<char>::Iterator first = my_list.begin();
    my_list.insert(first, 'a');
    char array[] = {'a', 'b'};
    int count = 0;
    for (List<char>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array[count]);
        count++;
    }
    assert(count == my_list.size());
    assert(my_list.front() == 'a');
    assert(my_list.back() == 'b');
}

TEST (test_pop_functions) {
    List<int> my_list;
    my_list.push_back(20);
    my_list.push_back(21);
    my_list.push_back(22);
    my_list.push_back(23);
    my_list.push_back(24);
    List<int>::Iterator last = my_list.begin();
    ++last; // 21
    ++last; // 22
    ++last; // 23
    ++last; // 24
    int array[] = {20, 21, 22, 23, 24};
    int count = 4;
    assert(my_list.size() == 5);
    while (count > 0) {
        assert(*last == array[count]);
        count--;
        --last;
    }
    
    my_list.pop_back();
    int array1[] = {20, 21, 22, 23};
    assert(my_list.size() == 4);
    count = 0;
    for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array1[count]);
        count++;
    }
    assert(count == my_list.size());
    
    my_list.pop_front();
    int array2[] = {21, 22, 23};
    count = 0;
    for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array2[count]);
        count++;
    }
    assert(count == my_list.size());
    
    my_list.pop_front();
    int array3[] = {22, 23};
    count = 0;
    for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array3[count]);
        count++;
    }
    assert(count == my_list.size());
    
    my_list.pop_back();
    int array4[] = {22};
    count = 0;
    for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) {
        assert(*i == array4[count]);
        count++;
    }
    assert(count == my_list.size());
}

TEST (test_iterators) {
    List<int> my_list;
    List<int>::Iterator empty;
    List<int>::Iterator past_last = my_list.end();
    assert(empty == past_last);
    List<int>::Iterator first = my_list.begin();
    assert(empty == first);
    my_list.push_back(12);
    first = my_list.begin();
    assert(first != empty);
    --first;
    assert(first == empty);
    first = my_list.begin();
    assert(*first == 12);
    ++first;
    assert(first == empty);
    
    List<int> my_list2;
    List<int>::Iterator add = my_list2.end();
    my_list2.insert(add, 1);
    assert(my_list2.front() == 1);
    assert(my_list2.back() == 1);
    assert(my_list2.size() == 1);
    List<int>::Iterator first2 = my_list2.begin();
    assert(*first2 == 1);
}

TEST_MAIN()
