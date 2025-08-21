 #include <math.h>
 #include <string>
 #include <sstream>
 #include "heap/Heap.h"
 #include "util/Point.h"
 #include "util/sampleFunc.h"
 #include "list/XArrayList.h"



 int minHeapComparator(int*& lhs, int*& rhs) {
    if (*lhs < *rhs) {
      return -1;
    } else if (*lhs > *rhs) {
      return +1;
    } else {
      return 0;
    }
  }
  void deleteInt(int* a) { delete a; }
 int maxHeapComparator(int*& lhs, int*& rhs) {
    if (*lhs < *rhs) {
      return +1;
    } else if (*lhs > *rhs) {
      return -1;
    } else {
      return 0;
    }
  }
  string strInt(int*& str) { return to_string(*str); }
 
 int myIntComparator(int& lhs, int& rhs){
     if(lhs < rhs) return +1;
     else if(lhs > rhs) return -1;
     else return 0;
 }
 void anotherHeap(){
     Heap<int> heap;
     int array[] = {50, 20, 15, 10, 8, 6, 7, 23}; 
     for(int idx =0; idx < 8; idx++) heap.push(array[idx]);
     heap.println();
     heap.pop();
     heap.println();
     heap.push(5);
     heap.println();
     
     Heap<int> maxHeap(&myIntComparator);
     for(int idx =0; idx < 8; idx++) maxHeap.push(array[idx]);
     maxHeap.println();
     maxHeap.pop();
     maxHeap.println();
     maxHeap.push(70);
     maxHeap.println();
     
     
 }
 void simpleMinHeap(){
     int array[] = {50, 20, 15, 10, 8, 6, 7, 23}; 
               //    0   1   2   3  4  5  6   7
     //min heap: [6, 10, 7, 23, 15, 20, 8, 50]
     //[6,10,7,23,15,20,8,50]
 
     cout << "Input array: ";
     for(int idx =0; idx < 8; idx++) cout << array[idx]  << "  ";
     cout << endl;
     
     Heap<int> minHeap;
     for(int idx =0; idx < 8; idx++){
         minHeap.clear();
         minHeap.heapify(array, idx+1);
         cout << "Min heap: " << minHeap.toString() << endl;
     }
     const int& a = minHeap.peek();
     cout << "a = " << a << endl;
 }
 
 void heapDemo1(){
    cout << "Heap Demo 1" << endl;
     int array[] = {50, 20, 15, 10, 8, 6, 7, 23}; 
     //min heap: [6, 10, 7, 23, 15, 20, 8, 50]
     //max heap: [50, 23, 15, 20, 8, 6, 7, 10]
     Heap<int> minHeap1;
     cout << "Min Heap: ";
     minHeap1.heapify(array, 8);
     cout << minHeap1.toString() << endl;
     
     Heap<int> minHeap2(minHeapComparator);
     cout << "Min Heap: ";
     minHeap2.heapify(array, 8);
     cout << minHeap2.toString() << endl;
     
     Heap<int> maxHeap(maxHeapComparator);
     cout << "Max Heap: ";
     maxHeap.heapify(array, 8);
     cout << maxHeap.toString() << endl;
 }
 
 void heapDemo2(){
    cout << "Heap Demo 2" << endl;
     Point array[] = {
         Point(13.1, 12.4), Point(5.5, 4.5), Point(15.5, 14.5),
         Point(23.1, 12.4), Point(35.5, 14.5), Point(5.5, 34.5)
     };
     Heap<Point> minHeap1(minHeapComparator);
     cout << "Min Heap: ";
     minHeap1.heapify(array, 6);
     cout << minHeap1.toString(&point2str) << endl;
     
     Heap<Point> maxHeap(maxHeapComparator);
     cout << "Max Heap: ";
     maxHeap.heapify(array, 6);
     cout << maxHeap.toString(&point2str) << endl;
 }
 
 int myPointComparator(Point*&  lhs, Point*& rhs){
     if(lhs->radius() < rhs->radius()) return -1;
     else if(lhs->radius() > rhs->radius()) return +1;
     else return 0;
 }
 int myPointComparatorMAX(Point*&  lhs, Point*& rhs){
     if(lhs->radius() < rhs->radius()) return +1;
     else if(lhs->radius() > rhs->radius()) return -1;
     else return 0;
 }
 
 string myPoint2Str(Point*& point){
     stringstream os;
     os << "["   << setw(6) << setprecision(2) << point->getX() 
                 << ", "
                 << setw(6) << setprecision(2) << point->getY()
        << "]";
     return os.str();
 }
 void heapDemo3(){
    cout << "Heap Demo 3" << endl;
     Point* array[] = {
         new Point(13.1, 12.4), new Point(5.5, 4.5), new Point(15.5, 14.5),
         new Point(23.1, 12.4), new Point(35.5, 14.5), new Point(5.5, 34.5)
     };
     Heap<Point*> heap(&myPointComparatorMAX, &Heap<Point*>::free);
     for(int idx=0; idx < 6; idx++) heap.push(array[idx]);
     heap.println(&myPoint2Str);
     
     for(Heap<Point*>::Iterator it = heap.begin(); it != heap.end(); it++){
         Point* point = *it;
         cout << point->radius() << ", ";
     }
     cout << endl;
 }

 void heapDemo4(){
    cout << "Heap Demo 4" << endl;
     
    int array[] = {50, 20, 15, 10, 8, 6, 7, 23}; 
     //min heap: [6, 10, 7, 23, 15, 20, 8, 50]
     //max heap: [50, 23, 15, 20, 8, 6, 7, 10]
     Heap<int> minHeap1;
     cout << "Min Heap: ";
     minHeap1.heapify(array, 8);
     cout << minHeap1.toString() << endl;
     
     Heap<int> minHeap2(minHeapComparator);
     cout << "Min Heap: ";
     minHeap2.heapify(array, 8);
     cout << minHeap2.toString() << endl;
     
     Heap<int> maxHeap(maxHeapComparator);
     cout << "Max Heap: ";
     maxHeap.heapify(array, 8);
     cout << maxHeap.toString() << endl;

     cout << "Deleting 15 of max Heap:" << endl;
     maxHeap.remove(15);
     cout << "After deleting 15: " << maxHeap.toString() << endl;
     cout << "Deleting 15 of min Heap:" << endl;
        minHeap1.remove(50);
        cout << "After deleting 15: " << minHeap1.toString() << endl;
 }

 void heapDemo5(){
    cout << "Heap Demo 5" << endl;
     
    int array[] = {50, 20, 15, 10, 8, 6, 7, 23}; 
    XArrayList<int> xArrayList;
    for(int idx =0; idx < 8; idx++) xArrayList.add(array[idx]); 
     //min heap: [6, 10, 7, 23, 15, 20, 8, 50]
     //max heap: [50, 23, 15, 20, 8, 6, 7, 10]
     Heap<int> minHeap1;
     cout << "Min Heap: ";
     minHeap1.heapify(array, 8);
     cout << minHeap1.toString() << endl;

     //Heap<int> minHeap2;
     //minHeap2 = minHeap1;
     //cout << "minHeap2 copy from minHeap1: " << minHeap2.toString() << endl;
     
     Heap<int> maxHeap(maxHeapComparator);
     cout << "Max Heap: ";
     maxHeap.heapify(array, 8);
     cout << maxHeap.toString() << endl;
     cout <<"Sorting ascending order: " << endl;
     maxHeap.heapsort(xArrayList);
     cout << "Sorted array: " << xArrayList.toString() << endl;

     cout << "Sorting descending order: " << endl;
     minHeap1.heapsort(xArrayList);
        cout << "Sorted array: " << xArrayList.toString() << endl;
 }

void heapDemo6(){
    cout << "Heap Demo 6" << endl;
    XArrayList<int> list;
    int values[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    for (int v : values) {
        list.add(v);
    }

    cout << "Before heapsort: ";
    list.println();

    Heap<int> heap;
    heap.heapsort(list);

    cout << "After heapsort: ";
    list.println();
}

     
 void test_Heap01() {
    cout << "\nHeap Test 01\n";
    //! data
    Heap<int> heap;

    //! expect
    string expect = "size=0;empty=1;[]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap02() {
    cout << "\nHeap Test 02\n";
    //! data
    Heap<int> heap;
    Heap<int> copy(heap);

    //! expect
    string expect = "size=0;empty=1;[]";

    //! output
    stringstream ss;
    ss << "size=" << copy.size() << ";empty=" << copy.empty() << ";" << copy.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap03() {
    cout << "\nHeap Test 03\n";
    //! data
    Heap<int> heap;
    Heap<int> copy;
    copy = heap;

    //! expect
    string expect = "size=0;empty=1;[]";

    //! output
    stringstream ss;
    ss << "size=" << copy.size() << ";empty=" << copy.empty() << ";" << copy.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap04() {
    cout << "\nHeap Test 04\n";
    //! data
    Heap<int> heap;
    heap.push(4);
    heap.push(2);
    heap.push(1);

    //! expect
    string expect = "size=3;empty=0;[1,4,2]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap05() {
    cout << "\nHeap Test 05\n";
    //! data
    Heap<int> heap;
    heap.push(4);
    heap.push(2);
    heap.push(1);
    heap.push(7);
    heap.push(3);
    heap.push(9);
    heap.push(10);
    heap.push(6);
    heap.push(8);
    heap.push(5);
    heap.push(12);
    heap.push(11);
    heap.push(14);
    heap.push(13);
    heap.push(15);

    //! expect
    string expect = "size=15;empty=0;[1,3,2,6,4,9,10,7,8,5,12,11,14,13,15]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap06() {
    cout << "\nHeap Test 06\n";
    //! data
    Heap<int> heap;
    heap.push(4);
    heap.push(2);
    heap.push(1);

    //! expect
    string expect = "size=3;empty=0;[1,4,2]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap07() {
    cout << "\nHeap Test 07\n";
    //! data
    Heap<int> heap;

    //! expect
    string expect = "Caught exception: Calling to peek with the empty heap.";

    //! output
    stringstream ss;
    try {
        ss << heap.pop();
    } catch (const underflow_error& e) {
        ss << "Caught exception: " << e.what();
    }
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap08() {
    cout << "\nHeap Test 08\n";
    //! data
    Heap<int> heap;
    stringstream ss;
    heap.push(4);
    ss << heap.pop() << endl;

    //! expect
    string expect = "4\nsize=0;empty=1;[]";

    //! output
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap09() {
    cout << "\nHeap Test 09\n";
    //! data
    Heap<int> heap;
    stringstream ss;
    heap.push(4);
    heap.push(2);
    heap.push(1);
    heap.push(7);
    heap.push(3);
    heap.push(9);
    heap.push(10);
    heap.push(6);
    heap.push(8);
    heap.push(5);
    heap.push(12);
    heap.push(11);
    heap.push(14);
    heap.push(13);
    heap.push(15);

    ss << heap.pop() << heap.pop() << heap.pop() << endl;
    // int val1 = heap.pop();
    // int val2 = heap.pop();
    // int val3 = heap.pop();
    // cout << "val1=" << val1 << ", val2=" << val2 << ", val3=" << val3 << endl;
    // ss << val1 << val2 << val3 << endl;

    //! expect
    string expect = "123\nsize=12;empty=0;[4,5,9,6,12,11,10,7,8,13,14,15]";

    //! output
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap10() {
    cout << "\nHeap Test 10\n";
    //! data
    Heap<int> heap;

    //! expect
    string expect = "Caught exception: Calling to peek with the empty heap.";

    //! output
    stringstream ss;
    try {
        ss << heap.peek();
    } catch (const underflow_error& e) {
        ss << "Caught exception: " << e.what();
    }
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap11() {
    cout << "\nHeap Test 11\n";
    //! data
    Heap<int> heap;
    heap.push(4);
    heap.push(2);
    heap.push(1);
    heap.push(7);
    heap.push(3);
    heap.push(9);
    heap.push(10);
    heap.push(6);
    heap.push(8);
    heap.push(5);
    heap.push(12);
    heap.push(11);
    heap.push(14);
    heap.push(13);
    heap.push(15);

    //! expect
    string expect =
        "111\n"
        "size=15;empty=0;[1,3,2,6,4,9,10,7,8,5,12,11,14,13,15]";

    //! output
    stringstream ss;
    ss << heap.peek() << heap.peek() << heap.peek() << endl;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
       << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap12() {
    cout << "\nHeap Test 12\n";
    //! data
    Heap<int> heap;
    heap.push(4);
    heap.push(2);
    heap.push(1);
    heap.remove(2);

    //! expect
    string expect = "size=2;empty=0;[1,4]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
       << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap13() {
    cout << "\nHeap Test 13\n";
    //! data
    Heap<int> heap;
    heap.push(4);
    heap.push(2);
    heap.push(1);
    heap.push(7);
    heap.push(3);
    heap.push(9);
    heap.push(10);
    heap.push(6);
    heap.push(8);
    heap.push(5);
    heap.push(12);
    heap.push(11);
    heap.push(14);
    heap.push(13);
    heap.push(15);

    heap.remove(11);
    heap.remove(20);
    heap.remove(15);

    //! expect
    string expect = "size=13;empty=0;[1,3,2,6,4,9,10,7,8,5,12,13,14]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
       << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap14() {
    cout << "\nHeap Test 14\n";
    //! data
    Heap<int> heap;
    heap.push(4);
    heap.push(2);
    heap.push(1);

    //! expect
    string expect = "True\nsize=3;empty=0;[1,4,2]";

    //! output
    stringstream ss;
    ss << (heap.contains(2) ? "True" : "False") << endl;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
       << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap15() {
    cout << "\nHeap Test 15\n";
    //! data
    Heap<int> heap;
    heap.push(4);
    heap.push(2);
    heap.push(1);

    //! expect
    string expect = "False\nsize=3;empty=0;[1,4,2]";

    //! output
    stringstream ss;
    ss << (heap.contains(0) ? "True" : "False") << endl;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
       << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap16() {
    cout << "\nHeap Test 16\n";
    //! data
    Heap<int*> heap(maxHeapComparator, Heap<int*>::free);
    heap.push(new int(4));
    heap.push(new int(2));
    heap.push(new int(1));

    //! expect
    string expect = "size=3;empty=0;[4,2,1]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
       << heap.toString(&strInt);
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap17() {
    cout << "\nHeap Test 17\n";
    //! data
    Heap<int*> heap(maxHeapComparator, Heap<int*>::free);
    heap.push(new int(4));
    heap.push(new int(2));
    heap.push(new int(1));
    heap.push(new int(8));
    heap.push(new int(6));
    heap.push(new int(9));
    heap.push(new int(12));
    heap.push(new int(7));
    heap.push(new int(5));
    heap.push(new int(3));
    heap.push(new int(10));
    heap.push(new int(14));
    heap.push(new int(15));
    heap.push(new int(11));
    heap.push(new int(13));
    heap.push(new int(16));
    heap.push(new int(18));
    heap.push(new int(17));

    Heap<int*> copy(heap);

    //! expect
    string expect =
        "size=18;empty=0;[18,17,14,16,7,12,13,10,15,3,4,1,9,8,11,2,6,5]";

    //! output
    stringstream ss;
    ss << "size=" << copy.size() << ";empty=" << copy.empty() << ";"
       << copy.toString(&strInt);
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap18() {
    cout << "\nHeap Test 18\n";
    //! data
    Heap<int*> heap(maxHeapComparator, Heap<int*>::free);
    heap.push(new int(4));
    heap.push(new int(2));
    heap.push(new int(1));
    heap.push(new int(8));
    heap.push(new int(6));
    heap.push(new int(9));
    heap.push(new int(12));
    heap.push(new int(7));
    heap.push(new int(5));
    heap.push(new int(3));
    heap.push(new int(10));
    heap.push(new int(14));
    heap.push(new int(15));
    heap.push(new int(11));
    heap.push(new int(13));
    heap.push(new int(16));
    heap.push(new int(18));
    heap.push(new int(17));

    Heap<int*> copy;
    copy = heap;

    //! expect
    string expect =
        "size=18;empty=0;[18,17,14,16,7,12,13,10,15,3,4,1,9,8,11,2,6,5]";

    //! output
    stringstream ss;
    ss << "size=" << copy.size() << ";empty=" << copy.empty() << ";"
       << copy.toString(&strInt);
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap19() {
    cout << "\nHeap Test 19\n";
    //! data
    Heap<int*> heap(maxHeapComparator, Heap<int*>::free);
    heap.push(new int(4));
    heap.push(new int(2));
    heap.push(new int(1));
    heap.push(new int(8));
    heap.push(new int(6));
    heap.push(new int(9));
    heap.push(new int(12));
    heap.push(new int(7));
    heap.push(new int(5));
    heap.push(new int(3));
    heap.push(new int(10));
    heap.push(new int(14));
    heap.push(new int(15));
    heap.push(new int(11));
    heap.push(new int(13));
    heap.push(new int(16));
    heap.push(new int(18));
    heap.push(new int(17));

    int* a = heap.pop();
    stringstream ss;
    ss << *a << endl;
    delete a;

    //! expect
    string expect =
        "18\n"
        "size=17;empty=0;[17,16,14,15,7,12,13,10,5,3,4,1,9,8,11,2,6]";

    //! output
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
       << heap.toString(&strInt);
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap20() {
    cout << "\nHeap Test 20\n";
    //! data
    Heap<int*> heap(maxHeapComparator, Heap<int*>::free);
    heap.push(new int(4));
    heap.push(new int(2));
    heap.push(new int(1));
    heap.push(new int(8));
    heap.push(new int(6));
    heap.push(new int(9));
    heap.push(new int(12));
    heap.push(new int(7));
    heap.push(new int(5));
    heap.push(new int(3));
    heap.push(new int(10));
    heap.push(new int(14));
    heap.push(new int(15));
    heap.push(new int(11));
    heap.push(new int(13));
    heap.push(new int(16));
    heap.push(new int(18));
    heap.push(new int(17));

    int* a = heap.pop();
    stringstream ss;
    ss << *a << endl;
    delete a;
    a = heap.pop();
    ss << *a << endl;
    delete a;
    heap.clear();

    //! expect
    string expect = "18\n17\nsize=0;empty=1;[]";

    //! output
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";"
       << heap.toString(&strInt);
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap21() {
    cout << "\nHeap Test 21\n";
    //! data
    Heap<int*> heap(minHeapComparator, Heap<int*>::free);
    heap.push(new int(4));
    heap.push(new int(2));
    heap.push(new int(1));
    heap.push(new int(8));
    heap.push(new int(6));
    heap.push(new int(9));
    heap.push(new int(12));
    heap.push(new int(7));
    heap.push(new int(5));
    heap.push(new int(3));
    heap.push(new int(10));
    heap.push(new int(14));
    heap.push(new int(15));
    heap.push(new int(11));
    heap.push(new int(13));
    heap.push(new int(16));
    heap.push(new int(18));
    heap.push(new int(17));

    Heap<int*> copy;
    copy = heap;

    //! expect
    string expect = "size=18;empty=0;[1,3,2,5,4,9,11,8,7,6,10,14,15,12,13,16,18,17]";

    //! output
    stringstream ss;
    ss << "size=" << copy.size() << ";empty=" << copy.empty() << ";" << copy.toString(&strInt);
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

 void test_Heap22() {
    cout << "\nHeap Test 22\n";
    //! data
    Heap<int*> heap(minHeapComparator, Heap<int*>::free);
    heap.push(new int(4));
    heap.push(new int(2));
    heap.push(new int(1));
    heap.push(new int(8));
    heap.push(new int(6));
    heap.push(new int(9));
    heap.push(new int(12));
    heap.push(new int(7));
    heap.push(new int(5));
    heap.push(new int(3));
    heap.push(new int(10));
    heap.push(new int(14));
    int* value = new int(15);
    heap.push(value);
    heap.push(new int(11));
    heap.push(new int(13));
    heap.push(new int(16));
    heap.push(new int(18));
    heap.push(new int(17));

    heap.remove(value, deleteInt);

    //! expect
    string expect = "size=17;empty=0;[1,3,2,5,4,9,11,8,7,6,10,14,17,12,13,16,18]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString(&strInt);
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}
void test_Heap23() {
    cout << "\nHeap Test 23\n";
    //! data
    Heap<int*> heap(minHeapComparator, Heap<int*>::free);
    heap.push(new int(4));
    heap.push(new int(2));
    heap.push(new int(1));
    heap.push(new int(8));
    heap.push(new int(6));
    heap.push(new int(9));
    heap.push(new int(12));
    heap.push(new int(7));
    heap.push(new int(5));
    heap.push(new int(3));
    heap.push(new int(10));
    heap.push(new int(14));
    heap.push(new int(15));
    heap.push(new int(11));
    heap.push(new int(13));
    heap.push(new int(16));
    heap.push(new int(18));
    heap.push(new int(17));

    //! expect
    string expect = "1 3 2 5 4 9 11 8 7 6 10 14 15 12 13 16 18 17 ";

    //! output
    stringstream ss;
    for (auto i : heap) {
        ss << *i << " ";
    }
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap24() {
    cout << "\nHeap Test 24\n";
    //! data
    Heap<int*> heap(minHeapComparator, Heap<int*>::free);
    heap.push(new int(4));
    heap.push(new int(2));
    heap.push(new int(1));
    heap.push(new int(8));
    heap.push(new int(6));
    heap.push(new int(9));
    heap.push(new int(12));
    heap.push(new int(7));
    heap.push(new int(5));
    heap.push(new int(3));
    heap.push(new int(10));
    heap.push(new int(14));
    heap.push(new int(15));
    heap.push(new int(11));
    heap.push(new int(13));
    heap.push(new int(16));
    heap.push(new int(18));
    heap.push(new int(17));

    //! expect
    string expect = "1 4 2 7 6 14 11 13 18 12 10 15 ";

    //! output
    stringstream ss;
    int index = 0;
    for (auto i = heap.begin(); i != heap.end(); ++i) {
        if (index % 2) i.remove(deleteInt);
        ss << **i << " ";
        index++;
    }
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}
void test_Heap25() {
    cout << "\nHeap Test 25\n";
    //! data
    int array[] = {1, 4, 2};
    Heap<int> heap;
    heap.heapify(array, 3);

    //! expect
    string expect = "size=3;empty=0;[1,4,2]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}
void test_Heap26() {
    cout << "\nHeap Test 26\n";
    //! data
    int array[] = {15, 3, 8, 1, 20, 9, 4, 5, 12, 6,
                   11, 10, 7, 14, 2, 13, 17, 18, 19, 16};
    Heap<int> heap;
    heap.heapify(array, 20);

    //! expect
    string expect = "size=20;empty=0;[1,3,2,5,6,7,4,13,12,16,11,10,9,14,8,15,17,18,19,20]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}
void test_Heap27() {
    cout << "\nHeap Test 27\n";
    //! data
    int array[] = {};
    Heap<int> heap;
    heap.heapify(array, 0);

    //! expect
    string expect = "size=0;empty=1;[]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString();
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}
void test_Heap28() {
    cout << "\nHeap Test 28\n";
    //! data
    int* array[] = {new int(15), new int(3), new int(8), new int(1),
                    new int(20), new int(9), new int(4), new int(5),
                    new int(12), new int(6), new int(11), new int(10),
                    new int(7), new int(14), new int(2), new int(13),
                    new int(17), new int(18), new int(19), new int(16)};
    Heap<int*> heap(maxHeapComparator, Heap<int*>::free);
    heap.heapify(array, 20);

    //! expect
    string expect = "size=20;empty=0;[20,19,14,18,16,9,10,13,17,11,6,8,7,4,2,1,12,5,15,3]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString(&strInt);
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}
void test_Heap29() {
    cout << "\nHeap Test 29\n";
    //! data
    int* array[] = {};
    Heap<int*> heap(maxHeapComparator, Heap<int*>::free);
    heap.heapify(array, 0);

    //! expect
    string expect = "size=0;empty=1;[]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString(&strInt);
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}
void test_Heap30() {
    cout << "\nHeap Test 30\n";
    //! data
    int* array[] = {new int(15), new int(3), new int(8), new int(1),
                    new int(20), new int(9), new int(4), new int(5),
                    new int(12), new int(6), new int(11), new int(10),
                    new int(7), new int(14), new int(2), new int(13),
                    new int(17), new int(18), new int(19), new int(16)};
    Heap<int*> heap(minHeapComparator, Heap<int*>::free);
    heap.heapify(array, 20);

    //! expect
    string expect = "size=20;empty=0;[1,3,2,5,6,7,4,13,12,16,11,10,9,14,8,15,17,18,19,20]";

    //! output
    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString(&strInt);
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}
void test_Heap31() {
    cout << "\nHeap Test 31\n";
    //! data
    Heap<int> heap;
    int array[] = {50, 20, 15, 10, 8, 6, 7, 23};
    for (int idx = 0; idx < 8; idx++) heap.push(array[idx]);

    //! operations and output
    stringstream ss;
    ss << heap.toString();
    heap.pop();
    ss << heap.toString();
    heap.push(5);
    ss << heap.toString();

    Heap<int> maxHeap(&myIntComparator);
    for (int idx = 0; idx < 8; idx++) maxHeap.push(array[idx]);
    ss << maxHeap.toString();
    maxHeap.pop();
    ss << maxHeap.toString();
    maxHeap.push(70);
    ss << maxHeap.toString();

    //! expect
    string expect = "[6,10,7,23,15,20,8,50][7,10,8,23,15,20,50][5,7,8,10,15,20,50,23][50,23,15,20,8,6,7,10][23,20,15,10,8,6,7][70,23,15,20,8,6,7,10]";

    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap32() {
    cout << "\nHeap Test 32\n";
    int array[] = {50, 20, 15, 10, 8, 6, 7, 23};
    Heap<int> minHeap;
    stringstream ss;

    ss << "Input array: ";
    for (int i = 0; i < 8; i++) ss << array[i] << "  ";
    ss << endl;

    for (int i = 0; i < 8; i++) {
        minHeap.clear();
        minHeap.heapify(array, i + 1);
        ss << "Min heap: " << minHeap.toString() << endl;
    }
    const int& a = minHeap.peek();
    ss << "a = " << a << endl;

    string expect =
        "Input array: 50  20  15  10  8  6  7  23  \n"
        "Min heap: [50]\n"
        "Min heap: [20,50]\n"
        "Min heap: [15,50,20]\n"
        "Min heap: [10,15,20,50]\n"
        "Min heap: [8,10,20,50,15]\n"
        "Min heap: [6,10,8,50,15,20]\n"
        "Min heap: [6,10,7,50,15,20,8]\n"
        "Min heap: [6,10,7,23,15,20,8,50]\n"
        "a = 6\n";

    cout << "Expected:\n" << expect;
    cout << "Actual:\n" << ss.str();
    if (ss.str() == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}
void test_Heap33() {
    cout << "\nHeap Test 33\n";
    int array[] = {50, 20, 15, 10, 8, 6, 7, 23};
    stringstream ss;

    Heap<int> minHeap1;
    ss << "Min Heap: ";
    minHeap1.heapify(array, 8);
    ss << minHeap1.toString() << endl;

    Heap<int> minHeap2(minHeapComparator);
    ss << "Min Heap: ";
    minHeap2.heapify(array, 8);
    ss << minHeap2.toString() << endl;

    Heap<int> maxHeap(maxHeapComparator);
    ss << "Max Heap: ";
    maxHeap.heapify(array, 8);
    ss << maxHeap.toString() << endl;

    string expect =
        "Min Heap: [6,10,7,23,15,20,8,50]\n"
        "Min Heap: [6,10,7,23,15,20,8,50]\n"
        "Max Heap: [50,23,15,20,8,6,7,10]\n";

    cout << "Expected:\n" << expect;
    cout << "Actual:\n" << ss.str();
    if (ss.str() == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}
void test_Heap34() {
    cout << "\nHeap Test 34\n";
    Point array[] = {
        Point(13.1, 12.4), Point(5.5, 4.5), Point(15.5, 14.5),
        Point(23.1, 12.4), Point(35.5, 14.5), Point(5.5, 34.5)
    };
    stringstream ss;

    Heap<Point> minHeap1(minHeapComparator);
    ss << "Min Heap: ";
    minHeap1.heapify(array, 6);
    ss << minHeap1.toString(&point2str) << endl;

    Heap<Point> maxHeap(maxHeapComparator);
    ss << "Max Heap: ";
    maxHeap.heapify(array, 6);
    ss << maxHeap.toString(&point2str) << endl;

    string expect =
        "Min Heap: [(5.5, 4.5),(13.1, 12.4),(15.5, 14.5),(23.1, 12.4),(35.5, 14.5),(5.5, 34.5)]\n"
        "Max Heap: [(35.5, 14.5),(23.1, 12.4),(5.5, 34.5),(5.5, 4.5),(15.5, 14.5),(13.1, 12.4)]\n";

    cout << "Expected:\n" << expect;
    cout << "Actual:\n" << ss.str();
    if (ss.str() == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}
void test_Heap35() {
    cout << "\nHeap Test 35\n";
    Point* array[] = {
        new Point(13.1, 12.4), new Point(5.5, 4.5), new Point(15.5, 14.5),
        new Point(23.1, 12.4), new Point(35.5, 14.5), new Point(5.5, 34.5)
    };
    stringstream ss;

    Heap<Point*> heap(&myPointComparatorMAX, &Heap<Point*>::free);
    for (int i = 0; i < 6; i++) heap.push(array[i]);
    ss << heap.toString(&myPoint2Str);

    for (Heap<Point*>::Iterator it = heap.begin(); it != heap.end(); it++) {
        Point* point = *it;
        ss << point->radius() << ", ";
    }
    ss << endl;

    string expect = "[[    36,     14],[    23,     12],[   5.5,     34],[   5.5,    4.5],[    16,     14],[    13,     12]]38.3471, 26.2177, 34.9357, 7.10634, 21.225, 18.038, \n";

    cout << "Expected:\n" << expect;
    cout << "Actual:\n" << ss.str();
    if (ss.str() == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}
void test_Heap36() {
    cout << "\nHeap Test 36\n";
    Heap<int> heap;
    heap.push(4);
    heap.push(2);
    heap.push(1);

    XArrayList<int> arrayList;
    heap.heapsort(arrayList);

    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString();

    string expect = "size=0;empty=1;[]";

    string output = ss.str();
    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap37() {
    cout << "\nHeap Test 37\n";
    Heap<int> heap;
    heap.push(4);
    heap.push(2);
    heap.push(1);

    XArrayList<int> arrayList;
    arrayList.add(11);
    arrayList.add(22);
    arrayList.add(33);
    arrayList.add(0);
    arrayList.add(1);
    arrayList.add(1000);
    arrayList.add(2000);
    arrayList.add(4000);
    arrayList.add(9000);
    arrayList.add(9000);
    arrayList.add(9000);
    arrayList.add(5);

    heap.heapsort(arrayList);

    stringstream ss;
    ss << arrayList.toString() << endl;

    string expect = " [11]\n\
[11,22]\n\
[11,22,33]\n\
[0,11,33,22]\n\
[0,1,33,22,11]\n\
[0,1,33,22,11,1000]\n\
[0,1,33,22,11,1000,2000]\n\
[0,1,33,22,11,1000,2000,4000]\n\
[0,1,33,22,11,1000,2000,4000,9000]\n\
[0,1,33,22,11,1000,2000,4000,9000,9000]\n\
[0,1,33,22,11,1000,2000,4000,9000,9000,9000]\n\
[0,1,5,22,11,33,2000,4000,9000,9000,9000,1000]\n";

    string output = ss.str();
    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap38() {
    cout << "\nHeap Test 38\n";
    Heap<int> heap(maxHeapComparator);
    heap.push(4);
    heap.push(2);
    heap.push(1);

    XArrayList<int> arrayList;
    arrayList.add(11);
    arrayList.add(22);
    arrayList.add(33);
    arrayList.add(0);
    arrayList.add(1);
    arrayList.add(1000);
    arrayList.add(2000);
    arrayList.add(4000);
    arrayList.add(9000);
    arrayList.add(9000);
    arrayList.add(9000);
    arrayList.add(5);

    heap.heapsort(arrayList);

    stringstream ss;
    ss << arrayList.toString() << endl;

    string expect = " [11]\n\
[22,11]\n\
[33,11,22]\n\
[33,11,22,0]\n\
[33,11,22,0,1]\n\
[1000,11,33,0,1,22]\n\
[2000,11,1000,0,1,22,33]\n\
[4000,2000,1000,11,1,22,33,0]\n\
[9000,4000,1000,2000,1,22,33,0,11]\n\
[9000,9000,1000,2000,4000,22,33,0,11,1]\n\
[9000,9000,1000,2000,9000,22,33,0,11,1,4000]\n\
[9000,9000,1000,2000,9000,22,33,0,11,1,4000,5]\n";

    string output = ss.str();
    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Heap39() {
    cout << "\nHeap Test 39\n";
    Heap<int> heap;
    heap.push(4);
    heap.push(2);
    heap.push(1);

    XArrayList<int> *arrayList = new XArrayList<int>();
    heap.heapsort(*arrayList);

    stringstream ss;
    ss << "size=" << heap.size() << ";empty=" << heap.empty() << ";" << heap.toString();

    string expect = "size=0;empty=1;[]";

    string output = ss.str();
    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;

    delete arrayList;
}

void test_Heap40() {
    cout << "\nHeap Test 40\n";
    Heap<int> heap(maxHeapComparator);
    heap.push(4);
    heap.push(2);
    heap.push(1);

    XArrayList<int> arrayList;
    arrayList.add(11);
    arrayList.add(22);
    arrayList.add(33);
    arrayList.add(0);
    arrayList.add(1);
    arrayList.add(9000);
    arrayList.add(9000);
    arrayList.add(5);

    cout << "output : \n";
    heap.heapsort(arrayList);
    cout << "expect : \n[11]\n\
[22,11]\n\
[33,11,22]\n\
[33,11,22,0]\n\
[33,11,22,0,1]\n\
[9000,11,33,0,1,22]\n\
[9000,11,9000,0,1,22,33]\n\
[9000,11,9000,5,1,22,33,0]\n";

    stringstream ss;
    ss << arrayList.toString() << endl;

    string expect = "[9000, 9000, 33, 22, 11, 5, 1, 0]\n";

    string output = ss.str();
    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}










