/* File:: mapshpp.h
 * --------------------------------------------------
 * This interface exports simple version of map
 * based on AVL binary search tree
 */
#ifndef MAPSHPP
#define MAPSHPP

#include <iostream>


/* Class: MapSHPP
 * -------------------------------------------------
 * This class implements map of a specified ValueType
 * elements
 */
template<typename KeyType, typename ValueType>
class MapSHPP{

    /* Public methods prototypes*/
public:


    /* Constructor: MapSHPP
     * Usage: MapSHPP<KeyType, ValueType> map;
     * -----------------------------------------------------
     * Initializes a new empty map
     */
    MapSHPP();

    /* Destructor: ~MapSHPP
    * ----------------------------------------------
    * Frees all allocated memory for the map elements
    */
    virtual ~MapSHPP();

    /* Method: put
     * Usage: map.put(key, value);
     * -----------------------------------------------
     * Put the value in accordance with the key.
     * If this key already exists then its value is replaced by a new
     */
    void put(KeyType, ValueType);

    /* Method: get
     * Usage: value = map.get(key);
     * -----------------------------------------------
     * Returns the value of the corresponding key
     */
    ValueType get(KeyType key);

    /* Method: isEmpty
     * Usage: if (map.isEmpty());
     * -----------------------------------------------
     * Returns true if map is empty
     */
    bool isEmpty();

    /* Method: clear
     * Usage: map.clear();
     * ---------------------------------------------
     * Removes all elements of the map
     */
    void clear();

    /* Method: size
     * Usage: int size = map.size();
     * --------------------------------------------
     * Return current number of the elements of the
     * map
     */
    int size();

    /* Method: remove
     * Usage: map.remuve(key);
     * -----------------------------------------------------
     * Removes value of the map corresponding to the key
     */
    void remove(KeyType);

    /* Method: containsKey
     * Usage: if (map.containsKey(key))
     * -----------------------------------------------------
     * Return true if map contains input key
     */
    bool containsKey(KeyType key);

    /* Operator: []
     * Usage: map[key] = value;
     * ---------------------------------------------------
     * Returns link to value by the specfied key.
     */
    ValueType& operator[](KeyType);

    /* Private methods prototypes and instase variables*/
private:

    /* Structure for storing key-value pairs and build BST*/
    struct BSTNode {
        KeyType Key;
        ValueType Value;
        int length;
        BSTNode* left;
        BSTNode* right;
    };

    /*
     * Method: balanceTree
     * ---------------------------------------------------
     * Balancing of a binary tree
     */
    BSTNode* balanceTree(BSTNode* node);

    /* Method: getNodeHeight
     * --------------------------------------------------
     * Counts the height of a binary tree
     */
    int getNodeHeight(BSTNode* node);

    /* Method: getBalanceFactor
     * -------------------------------------------------
     * Counts the difference in height between the
     * left and right subtree
     */
    int getBalanceFactor(BSTNode* node);

    /* Method: fixHeight
     * ------------------------------------------------
     * Recalculates the height of a given node
     */
    void fixHeight(BSTNode* node);

    /* Method: rotateRight
     * -----------------------------------------------
     * Rotates tree right around a given node
     */
    BSTNode* rotateRight(BSTNode* node);

    /* Method: rotateRight
     * -----------------------------------------------
     * Rotates tree left around a given node
     */
    BSTNode* rotateLeft(BSTNode* node);

    /* Method: insertNode
     * -----------------------------------------------
     * Inserts new node with received key and value to
     * the tree and balance it after this
     */
    BSTNode* insertNode(BSTNode* node, KeyType key, ValueType value);

    /* Method: removeNode
     * -----------------------------------------------
     * Removed node with received key and balance tree
     * after this
     */
    BSTNode* removeNode(BSTNode* node, KeyType key);

    /* Method: findMinNode
     * -----------------------------------------------
     * Returns pointer to the node with minimal key in
     * the received sub-tree
     */
    BSTNode* findMinNode(BSTNode* node);

    /* Method: removeMinNode
     * -----------------------------------------------
     * Removes minimal element of the received sub-tree
     * and balance it after this
     */
    BSTNode* removeMinNode(BSTNode* node);

    /* Method: findNode
     * -----------------------------------------------
     * Returns pointer to the node that contains received
     * key or 0 if such node not found
     */
    BSTNode* findNode(BSTNode* node, KeyType key);

    /* Method: clearBST
     * -----------------------------------------------
     * Frees all memoty allocated for the nodes of
     * the binaty tree
     */
    void clearTree(BSTNode* node);

    /* Current number of the elements in map*/
    int count;

    /* Contains link the top node*/
    BSTNode* mainNode;
};


template<typename KeyType, typename ValueType>
MapSHPP<KeyType, ValueType>::MapSHPP(){
    mainNode = 0;
    count = 0;
}

template<typename KeyType, typename ValueType>
MapSHPP<KeyType, ValueType>::~MapSHPP(){
    clearTree(mainNode);
}

template<typename KeyType, typename ValueType>
int MapSHPP<KeyType, ValueType>::getNodeHeight(BSTNode *node){
    if (node != 0){
        return node->length;
    }
    return 0;
}

template<typename KeyType, typename ValueType>
int MapSHPP<KeyType, ValueType>::getBalanceFactor(BSTNode *node){
    return getNodeHeight(node->right) - getNodeHeight(node->left);
}

template<typename KeyType, typename ValueType>
void MapSHPP<KeyType, ValueType>::fixHeight(BSTNode *node){
    if (getNodeHeight(node->left) > getNodeHeight(node->right)){
        node->length = getNodeHeight(node->left) + 1;
    } else {
        node->length = getNodeHeight(node->right) + 1;
    }
}

template<typename KeyType, typename ValueType>
typename MapSHPP<KeyType, ValueType>::BSTNode* MapSHPP<KeyType, ValueType>::rotateLeft(BSTNode *node){
    BSTNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    fixHeight(newRoot);
    fixHeight(node);
    return newRoot;
}


template<typename KeyType, typename ValueType>
typename MapSHPP<KeyType, ValueType>::BSTNode* MapSHPP<KeyType, ValueType>::rotateRight(BSTNode *node){
    BSTNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    fixHeight(node);
    fixHeight(newRoot);
    return newRoot;
}

template<typename KeyType, typename ValueType>
typename MapSHPP<KeyType, ValueType>::BSTNode* MapSHPP<KeyType, ValueType>::balanceTree(BSTNode *node){
    fixHeight(node);
    if (getBalanceFactor(node) == 2){
        if (getBalanceFactor(node->right) < 0){
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    if (getBalanceFactor(node) == -2){
        if (getBalanceFactor(node->left) > 0){
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    return node;
}

template<typename KeyType, typename ValueType>
typename MapSHPP<KeyType, ValueType>::BSTNode* MapSHPP<KeyType, ValueType>::insertNode(BSTNode* node, KeyType key, ValueType value){
    if (node == 0){
        node = new BSTNode;
        node->Key = key;
        node->Value = value;
        node->length = 1;
        node->right = 0;
        node->left = 0;
        count++;
        return node;
    } else if (key > node->Key){
        node->right = insertNode(node->right, key, value);
    } else if (key < node->Key){
        node->left = insertNode(node->left, key, value);
    } else {
        node->Value = value;
    }
    return balanceTree(node);
}

template<typename KeyType, typename ValueType>
typename MapSHPP<KeyType, ValueType>::BSTNode* MapSHPP<KeyType, ValueType>::findNode(BSTNode* node, KeyType key){
    if (key > node->Key){
        if(node->right == 0){
            return 0;
        }
        return findNode(node->right, key);
    } else if (key < node->Key){
        if (node->left == 0){
            return 0;
        }
        return findNode(node->left, key);
    }
    return node;
}

template<typename KeyType, typename ValueType>
typename MapSHPP<KeyType, ValueType>::BSTNode* MapSHPP<KeyType, ValueType>::removeNode(BSTNode* node, KeyType key){
    if (key < node->Key){
        node->left = removeNode(node->left, key);
    } else if (key >node->Key){
        node->right = removeNode(node->right, key);
    } else if (key == node->Key){
        BSTNode* leftNode = node->left;
        BSTNode* rightNode = node->right;
        delete node;
        count--;
        if (rightNode == 0){
            return leftNode;
        }
        BSTNode* minNode = findMinNode(rightNode);
        minNode->right = removeMinNode(rightNode);
        minNode->left = leftNode;
        return balanceTree(minNode);
    }
    return balanceTree(node);
}

template<typename KeyType, typename ValueType>
typename MapSHPP<KeyType, ValueType>::BSTNode* MapSHPP<KeyType, ValueType>::findMinNode(BSTNode *node){
    if (node->left != 0){
        return findMinNode(node->left);
    }
    return node;
}

template<typename KeyType, typename ValueType>
typename MapSHPP<KeyType, ValueType>::BSTNode* MapSHPP<KeyType, ValueType>::removeMinNode(BSTNode *node){
    if(node->left == 0){
        return node->right;
    }
    node->left = removeMinNode(node->left);
    return balanceTree(node);
}

template<typename KeyType, typename ValueType>
void MapSHPP<KeyType, ValueType>::clearTree(BSTNode *node){
    if (node->left != 0){
        clearTree(node->left);
    }
    if (node->right != 0){
        clearTree(node->right);
    }

    delete node;
}

template<typename KeyType, typename ValueType>
void MapSHPP<KeyType, ValueType>::put(KeyType key, ValueType value){
    mainNode = insertNode(mainNode, key, value);
}

template<typename KeyType, typename ValueType>
ValueType MapSHPP<KeyType, ValueType>::get(KeyType key){
    BSTNode* tmp = findNode(mainNode, key);
    return tmp->Value;
}

template<typename KeyType, typename ValueType>
int MapSHPP<KeyType, ValueType>::size(){
    return count;
}

template<typename KeyType, typename ValueType>
void MapSHPP<KeyType, ValueType>::remove(KeyType key){
    if(count > 0){
        mainNode = removeNode(mainNode, key);
    } else {
        std::cout << "Error: Map is empty" << std::endl;
        exit(1);
    }
}

template<typename KeyType, typename ValueType>
bool MapSHPP<KeyType, ValueType>::isEmpty(){
    return count == 0;
}

template<typename KeyType, typename ValueType>
void MapSHPP<KeyType, ValueType>::clear(){
    clearTree(mainNode);
    count = 0;
    mainNode = 0;
}

template<typename KeyType, typename ValueType>
bool MapSHPP<KeyType, ValueType>::containsKey(KeyType key){
    return findNode(mainNode, key) != 0;
}

template<typename KeyType, typename ValueType>
ValueType& MapSHPP<KeyType, ValueType>::operator [](KeyType key){
    return findNode(mainNode, key)->Value;
}

#endif // MAPSHPP

