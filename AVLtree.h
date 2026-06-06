#include "wet1util.h"

class Rooms_Tree;

template<class T>
class AVLtree {
    friend class ::Rooms_Tree;

protected:
    struct node {
        int key;
        int height;
        T value;
        node* leftSon;
        node* rightSon;
        node* parent;
    };

    int num_node; //total nodes
    node* root;

public:
    AVLtree(); //DOR

    ~AVLtree(); //DOR

    AVLtree(const AVLtree &) = delete; // חוסם בנאי העתקה

    AVLtree &operator=(const AVLtree &t) {
        if (this == &t) {
            return *this;
        }
        AVLtree<T> temp(t);
        node* temp_root = this->root;
        this->root = temp.root;
        temp.root = temp_root;
        int temp_num = this->num_node;
        this->num_node = temp.num_node;
        temp.num_node = temp_num;
        return *this;
    }

    //insert new key and value,if key exists does nothing, keeps balance
    void insert(int key, T value) {
        if (find(key) != nullptr) {
            return;
        }
        node* newNode = new node();
        newNode->key = key;
        newNode->value = value;
        newNode->height = 0;
        newNode->leftSon = nullptr;
        newNode->rightSon = nullptr;
        newNode->parent = nullptr;
        if (root == nullptr) {
            root = newNode;
            num_node++;
            return;
        }
        node* current = root;
        bool inserted = false;
        while (!inserted) {
            if (current->key < key) {
                if (current->rightSon == nullptr) {
                    current->rightSon = newNode;
                    newNode->parent = current;
                    inserted = true;
                    continue;
                }
                current = current->rightSon;
                continue;
            }
            if (current->key > key) {
                if (current->leftSon == nullptr) {
                    current->leftSon = newNode;
                    newNode->parent = current;
                    inserted = true;
                    continue;
                }
                current = current->leftSon;
            }
        }
        num_node++;
        node* temp = newNode->parent;
        while (temp != nullptr) {
            temp->height = 1 + getHeight(temp);
            int bf = getBF(temp);
            if (bf > 1 || bf < -1) {
                if (bf > 1) {
                    if (getBF(temp->leftSon) >= 0) {
                        temp = rotateLL(temp);
                    } else {
                        temp = rotateLR(temp);
                    }
                } else {
                    if (getBF(temp->rightSon) <= 0) {
                        temp = rotateRR(temp);
                    } else {
                        temp = rotateRL(temp);
                    }
                }
            }
            temp = temp->parent;
        }
    } //DOR, update total

    //remove key and val, keeps balance
    void remove(int key/*, T value*/); //DOR

    //find key and return value, if not return nullptr!
    T* find(int key) const {
        if (root == nullptr) {
            return nullptr;
        }
        node* current = root;
        while (current) {
            if (current->key == key) {
                return &current->value;
            }
            if (current->key > key) {
                current = current->leftSon;
            } else {
                current = current->rightSon;
            }
        }
        return nullptr;
    }

    //search if key exists (will use find)
    bool contains(int key) const {
        return find(key) != nullptr;
    }

    //return pointer to the value with min key
    T* getMin(); //DOR

    int getNumNodes(); //Yaara

    //make an empty tree
    void clearTree(); //DOR

    static AVLtree<T>* mergeTrees(AVLtree<T>* tree1, AVLtree<T>* tree2) {
        int size1 = tree1->num_node;
        int size2 = tree2->num_node;
        node** tree1_arr = nullptr;
        node** tree2_arr = nullptr;
        node** newTree_arr = nullptr;
        AVLtree<T>* newTree = nullptr;
        try {
            newTree = new AVLtree<T>();
            if (size2 == 0)
                return newTree;
            if (size1 == 0)
                return newTree;
            tree1_arr = new node*[size1];
            tree1->inOrderToArray(tree1_arr);
            tree2_arr = new node*[size2];
            tree2->inOrderToArray(tree2_arr);
            newTree_arr = new node*[size1 + size2];
            merge_sort(tree1_arr, size1, tree2_arr, size2, newTree_arr);
            newTree->root = fill_from_arr(newTree_arr, 0, size1 + size2 - 1, newTree->root);
            newTree->num_node = size1 + size2;
            tree1->root = nullptr;
            tree1->num_node = 0;
            tree2->root = nullptr;
            tree2->num_node = 0;
        } catch (const std::exception &e) {
            delete[] tree1_arr;
            delete[] tree2_arr;
            delete[] newTree_arr;
            delete newTree;
            throw;
        }
        return newTree;
    }

private:
    node* rotateRL(node* v); //DOR

    node* rotateRR(node* v); //DOR

    node* rotateLR(node* v) {
        //YAARA
        v->leftSon = rotateRR(v->leftSon);
        return rotateLL(v);
    }

    node* rotateLL(node* v) {
        //YAARA
        node* original_parent = v->parent;
        node* c = v->leftSon->rightSon;
        node* b = v->leftSon;
        b->rightSon = v;
        v->leftSon = c;
        if (c != nullptr)
            c->parent = v;
        v->parent = b;
        b->parent = original_parent;
        int v_left_height;
        if (c != nullptr) {
            v_left_height = c->height;
        } else {
            v_left_height = -1;
        }
        int v_right_height;
        if (v->rightSon != nullptr) {
            v_right_height = v->rightSon->height;
        } else {
            v_right_height = -1;
        }
        if (v_left_height > v_right_height) {
            v->height = 1 + v_left_height;
        } else {
            v->height = 1 + v_right_height;
        }

        int b_left_height;
        if (b->leftSon != nullptr) {
            b_left_height = b->leftSon->height;
        } else {
            b_left_height = -1;
        }

        if (b_left_height > v->height) {
            b->height = 1 + b_left_height;
        } else {
            b->height = 1 + v->height;
        }
        return b;
    }

    node* fill_from_arr(node** newTree_arr, int start, int end, node* parent) {
        if (start > end) {
            return nullptr;
        }
        int mid = start + (end - start) / 2;
        node* root = newTree_arr[mid];
        root->parent = parent;
        root->leftSon = fill_from_arr(newTree_arr, start, mid - 1, root);
        root->rightSon = fill_from_arr(newTree_arr, mid + 1, end, root);
        int left_height;
        if (root->leftSon != nullptr) {
            left_height = root->leftSon->height;
        } else {
            left_height = -1;
        }
        int right_height;
        if (root->rightSon != nullptr) {
            right_height = root->rightSon->height;
        } else {
            right_height = -1;
        }
        int max_height;
        if (left_height > right_height) {
            max_height = left_height;
        } else {
            max_height = right_height;
        }
        root->height = 1 + max_height;

        return root;
    }

    void merge_sort(node** arr1, int size1, node** arr2, int size2, node** dest) {
        int index1 = 0;
        int index2 = 0;
        int indexDest = 0;
        while (size1 != 0 && size2 != 0) {
            if (arr1[index1]->key < arr2[index2]->key) {
                dest[indexDest] = arr1[index1];
                size1--;
                index1++;
            } else {
                dest[indexDest] = arr2[index2];
                size2--;
                index2++;
            }
            indexDest++;
        }
        while (size1 != 0) {
            dest[indexDest] = arr1[index1];
            size1--;
            index1++;
            indexDest++;
        }
        while (size2 != 0) {
            dest[indexDest] = arr2[index2];
            size2--;
            index2++;
            indexDest++;
        }
    }

    void inOrderToArray(node** arr) {
        if (this->root == nullptr)
            return;
        node* current = this->root;
        node* last = nullptr;
        int arr_index = 0;
        while (current != nullptr) {
            if (last == nullptr || last == current->parent) {
                //on our way down
                if (current->leftSon != nullptr) {
                    //go left
                    last = current;
                    current = current->leftSon;
                } else {
                    // no more left
                    arr[arr_index] = current;
                    arr_index++;
                    if (current->rightSon != nullptr) {
                        //go right
                        last = current;
                        current = current->rightSon;
                    } else {
                        //finished, go up
                        last = current;
                        current = current->parent;
                    }
                }
            } else if (current->leftSon == last) {
                //on our way up from the left
                arr[arr_index] = current;
                arr_index++;
                if (current->rightSon != nullptr) {
                    //go right
                    last = current;
                    current = current->rightSon;
                } else {
                    //finished, go up
                    last = current;
                    current = current->parent;
                }
            } else if (current->rightSon == last) {
                //on our way up from the right
                last = current;
                current = current->parent;
            }
        }
    }

    int getHeight(node* node) const {
        if (node == nullptr) {
            return -1;
        }
        int leftHeight = -1,rightHeight = -1;
        if (node->leftSon != nullptr) {
            leftHeight = node->leftSon->height;
        }
        if (node->rightSon != nullptr) {
            rightHeight = node->rightSon->height;
        }
        if (leftHeight >= rightHeight) {
            return leftHeight;
        }
        return rightHeight;
    }

    int getBF(node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->leftSon) - getHeight(node->rightSon);
    }
};
