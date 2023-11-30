#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder {
private:
    priority_queue<int> maxHeap; // Heap for the smaller half
    priority_queue<int, vector<int>, greater<int>> minHeap; // Heap for the larger half

public:
    // Function to add a number to the data structure
    void addNumber(int num) {
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }

        // Balance the heaps to make sure the size difference is at most 1
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    // Function to find the median of the data structure
    double findMedian() {
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        } else {
            return maxHeap.top();
        }
    }
};

int main() {
    MedianFinder medianFinder;

    // Taking numbers as input from the user
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the elements:\n";
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        medianFinder.addNumber(num);
    }

    // Finding and displaying the median
    cout << "Median: " << medianFinder.findMedian() << endl;

    return 0;
}
