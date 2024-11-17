#ifndef AVLTREE_H
#define AVLTREE_H

#include <cstdint>

template<typename K, typename V>
class AvlMap {
    class Node {
    public:
        K key;
        V value;
        uint8_t height = 1;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(K key, V value) : key(key), value(value) {}

        int bFactor() const {
            int leftHeight = left ? left->height : 0;
            int rightHeight = right ? right->height : 0;
            return rightHeight - leftHeight;
        }

        void fixHeight() {
            int leftHeight = left ? left->height : 0;
            int rightHeight = right ? right->height : 0;
            height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
        }
    };

    Node* _root = nullptr;

    Node* __rotateLeft(Node* node);
    Node* __rotateRight(Node* node);
    Node* __balance(Node* node);

    Node* __findMin(Node* node) const;
    Node* __removeMin(Node* node);

    Node* __insert(Node* node, K key, V value);
    Node* __delete(Node* node, K key);

    void __delTrav(Node* node);

    Node* __findElem(Node* elem, K key) const;

public:
    ~AvlMap();

    void Insert(K key, V value);

    V Delete(K key);

    V Find(K key) const;

    V operator[](K key) const;
};

#endif
