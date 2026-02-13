#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Node {
  Node* next;
  Node* prev;
  int value;
  int key;
  Node(Node* p, Node* n, int k, int val)
      : prev(p), next(n), key(k), value(val){};
  Node(int k, int val) : prev(NULL), next(NULL), key(k), value(val){};
};

class Cache {
 protected:
  map<int, Node*> mp;              // map the key to the node in the linked list
  int cp;                          // capacity
  Node* tail;                      // double linked list tail pointer
  Node* head;                      // double linked list head pointer
  virtual void set(int, int) = 0;  // set function
  virtual int get(int) = 0;        // get function
};

class LRUCache : public Cache {
 public:
  LRUCache(int capacity) {
    cp = capacity;
    tail = nullptr;
    head = nullptr;
  }
  LRUCache(const LRUCache&) = delete;
  LRUCache& operator=(const LRUCache&) = delete;
  ~LRUCache() {
    if (nullptr != head) {
      while (nullptr != head->next) {
        Node* next = head->next;
        mp.erase(head->key);
        delete head;
        head = next;
      }
      mp.erase(head->key);
      if (head != tail) {
        delete tail;
      }
      delete head;
    }
  }

  void set(int key, int value) override {
    auto it = mp.find(key);
    Node* node;
    if (mp.end() == it) {
      node = new Node(key, value);
      if (mp.size() + 1 > static_cast<size_t>(cp)) {
        auto oldtail = tail;
        removeNode(oldtail);
        mp.erase(oldtail->key);
        delete oldtail;
      }
      insertNode(node);
      mp[key] = node;
    } else {
      Node* node = it->second;
      node->value = value;
      removeNode(node);
      insertNode(node);
    }
  }

  int get(int key) override {
    // if map has key cache hit
    auto it = mp.find(key);
    if (it != mp.end()) {
      Node* keyNode = it->second;
      if (head != keyNode) {
        removeNode(keyNode);
        insertNode(keyNode);
      }
      return keyNode->value;
    } else {
      return -1;
    }
  }

 private:
  void removeNode(Node* node) {
    auto previousNode = node->prev;
    auto nextNode = node->next;
    if (nullptr != previousNode) {
      previousNode->next = nextNode;
    } else {
      if (nextNode != nullptr) {
        nextNode->prev = nullptr;
        head = nextNode;
      } else {
        head = nullptr;
      }
    }
    if (nullptr != nextNode) {
      nextNode->prev = previousNode;
    } else {
      if (previousNode != nullptr) {
        previousNode->next = nextNode;
        tail = previousNode;
      } else {
        tail = nullptr;
      }
    }
    node->prev = nullptr;
    node->next = nullptr;
  }

  void insertNode(Node* node) {
    if (head != nullptr) {
      head->prev = node;
      node->next = head;
    } else {
      tail = node;
      node->next = nullptr;
    }
    node->prev = nullptr;
    head = node;
  }
};

int main() {
  int n, capacity, i;
  cin >> n >> capacity;
  LRUCache l(capacity);
  for (i = 0; i < n; i++) {
    string command;
    cin >> command;
    if (command == "get") {
      int key;
      cin >> key;
      cout << l.get(key) << endl;
    } else if (command == "set") {
      int key, value;
      cin >> key >> value;
      l.set(key, value);
    }
  }
  return 0;
}
