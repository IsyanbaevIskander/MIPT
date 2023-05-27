#include <iostream>
#include <vector>

struct Node {
  int key;
  int priority;
  int number;

  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;

  Node(int key, int priority, int number) : key(key), priority(priority), number(number) {
  }
};

Node* BuildTree(std::vector<Node*>& values) {
  Node* root = nullptr;
  Node* last_inserted = nullptr;

  for (auto value : values) {
    Node* newnode = value;
    Node* curr = last_inserted;

    while (curr != nullptr && value->priority < curr->priority) {
      curr = curr->parent;
    }

    if (curr == nullptr) {
      newnode->left = root;

      if (root != nullptr) {
        root->parent = newnode;
      }

      root = newnode;
    } else {
      newnode->left = curr->right;

      if (curr->right != nullptr) {
        curr->right->parent = newnode;
      }

      curr->right = newnode;
      newnode->parent = curr;
    }
    last_inserted = newnode;
  }

  return root;
}

void TreeTraversal(Node* curr) {
  if (curr != nullptr) {
    if (curr->left != nullptr) {
      TreeTraversal(curr->left);
    }

    std::cout << (curr->parent != nullptr ? curr->parent->number : 0) << " ";
    std::cout << (curr->left != nullptr ? curr->left->number : 0) << " ";
    std::cout << (curr->right != nullptr ? curr->right->number : 0) << "\n";

    if (curr->right != nullptr) {
      TreeTraversal(curr->right);
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<Node*> values;

  for (int i = 0; i < n; ++i) {
    int a, b;
    std::cin >> a >> b;
    Node* new_elem = new Node(a, b, i + 1);
    values.push_back(new_elem);
  }

  Node* root = BuildTree(values);
  std::cout << "YES\n";
  TreeTraversal(root);

  for (int i = 0; i < n; ++i) {
    delete values[i];
  }
  return 0;
}
