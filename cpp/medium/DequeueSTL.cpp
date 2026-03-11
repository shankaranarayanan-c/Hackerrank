#include <deque>
#include <iostream>
using namespace std;

void printKMax(int arr[], int n, int k) {
  int beginIdx = 0;
  int endIdx = 1;
  std::deque<int> queue;
  int max = arr[0];
  for (int i = 0; i < k; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
    queue.push_back(arr[i]);
  }
  std::cout << max << " ";
  for (int i = k; i < n; i++) {
    int front = queue.front();
    queue.pop_front();
    queue.push_back(arr[i]);
    if (front != max) {
      if (max < queue.back()) {
        max = queue.back();
      }
      std::cout << max << " ";
    } else {
      max = queue.front();
      for (int i = 0; i < k; i++) {
        if (max < queue[i]) {
          max = queue[i];
        }
      }
      std::cout << max << " ";
    }
  }
  std::cout << "\n";
}

int main() {

  int t;
  cin >> t;
  while (t > 0) {
    int n, k;
    cin >> n >> k;
    int i;
    int arr[n];
    for (i = 0; i < n; i++)
      cin >> arr[i];
    printKMax(arr, n, k);
    t--;
  }
  return 0;
}