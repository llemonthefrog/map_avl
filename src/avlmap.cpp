#include "avlmap.h"
#include <stdexcept>

template<typename K, typename V>
typename AvlMap<K, V>::Node* AvlMap<K, V>::__rotateLeft(Node* node) {
    Node* temp = node->right;
    node->right = temp->left;
    if (temp->left) {
        temp->left->parent = node;
    }
    temp->left = node;
    temp->parent = node->parent;
    node->parent = temp;

    node->fixHeight();
    temp->fixHeight();

    return temp;
}

template<typename K, typename V>
typename AvlMap<K, V>::Node* AvlMap<K, V>::__rotateRight(Node* node) {
    Node* temp = node->left;
    node->left = temp->right;
    if (temp->right) {
        temp->right->parent = node;
    }
    temp->right = node;
    temp->parent = node->parent;
    node->parent = temp;

    node->fixHeight();
    temp->fixHeight();

    return temp;
}

template<typename K, typename V>
typename AvlMap<K, V>::Node* AvlMap<K, V>::__balance(Node* node) {
    node->fixHeight();
    if (node->bFactor() == 2) {
        if (node->right && node->right->bFactor() < 0) {
            node->right = __rotateRight(node->right);
        }
        return __rotateLeft(node);
    }
    if (node->bFactor() == -2) {
        if (node->left && node->left->bFactor() > 0) {
            node->left = __rotateLeft(node->left);
        }
        return __rotateRight(node);
    }
    return node;
}

template<typename K, typename V>
typename AvlMap<K, V>::Node* AvlMap<K, V>::__findMin(Node* node) const {
    return node->left ? __findMin(node->left) : node;
}

template<typename K, typename V>
typename AvlMap<K, V>::Node* AvlMap<K, V>::__removeMin(Node* node) {
    if(node->left == nullptr) {
        return node->right;
    }
    node->left = __removeMin(node->left);
    return __balance(node);
}

template<typename K, typename V>
typename AvlMap<K, V>::Node* AvlMap<K, V>::__insert(Node* node, K key, V value) {
    if (node == nullptr) {
        return new Node(key, value);
    }
    if (key < node->key) {
        node->left = __insert(node->left, key, value);
        node->left->parent = node;
    } else {
        node->right = __insert(node->right, key, value);
        node->right->parent = node;
    }
    return __balance(node);
}

template<typename K, typename V>
typename AvlMap<K, V>::Node* AvlMap<K, V>::__delete(Node* node, K key) {
    if(node == nullptr) {
        return nullptr;
    }

    if(node->key > key) {
        node->left = __delete(node->left, key);
    } else if(node->key < key) {
        node->right = __delete(node->right, key);
    } else {
        Node* l = node->left;
        Node* r = node->right;

        delete node;

        if(r == nullptr) {
            return l;
        }

        Node* min = __findMin(r);
        min->right = __removeMin(r);
        min->left = l;

        if(min->left) {
            min->left->parent = min;
        }

        if(min->right) {
            min->right->parent = min;
        }

        return __balance(min);
    }
    return __balance(node);
}

template<typename K, typename V>
void AvlMap<K, V>::__delTrav(Node* node) {
    if(node != nullptr) {
        __delTrav(node->left);
        __delTrav(node->right);
        delete node;
    }
}

template<typename K, typename V>
typename AvlMap<K, V>::Node* AvlMap<K, V>::__findElem(Node* elem, K key) const {
    if (elem == nullptr) {
        return nullptr;
    }

    if(elem->key > key) {
        return __findElem(elem->left, key);
    } else if (elem->key < key) {
        return __findElem(elem->right, key);
    }

    return elem;
}

template<typename K, typename V>
AvlMap<K, V>::~AvlMap() {
    __delTrav(_root);
}

template<typename K, typename V>
void AvlMap<K, V>::Insert(K key, V value) {
    _root = __insert(_root, key, value);
}

template<typename K, typename V>
V AvlMap<K, V>::Delete(K key) {
    Node* node = __findElem(_root, key);
    if (node) {
        V value = node->value;
        _root = __delete(_root, key);
        return value;
    }
    throw std::out_of_range("Key not found");
}

template<typename K, typename V>
V AvlMap<K, V>::Find(K key) const {
    Node* elem = __findElem(_root, key);
    if(elem) {
        return elem->value;
    }
    throw std::out_of_range("Key not found");
}

template<typename K, typename V>
V AvlMap<K, V>::operator[](K key) const {
    return Find(key);
}