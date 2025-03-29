//
// Created by Tomer on 1/19/2025.
//

#ifndef HW2_LINKEDLIST_H
#define HW2_LINKEDLIST_H

#include "HashTable.h" // Include HashTable if needed for potential interactions
#include <memory>    // Include for std::shared_ptr

template <typename T>
class LinkedList{
public:
    /**
     * @brief Node class representing an element in the linked list.
     */
    class Node{
    public:
        int key;              // Key associated with the data
        std::shared_ptr<T> data; // Shared pointer to the data
        Node* next;           // Pointer to the next node

        /**
         * @brief Constructor for Node.
         *
         * @param key The key of the node.
         * @param data Shared pointer to the data.
         */
        Node(int key, std::shared_ptr<T> data) : key(key), data(data), next(nullptr){}

        /**
         * @brief Default destructor for Node.
         */
        ~Node() = default;

        friend class LinkedList; // Allow LinkedList to access private members
    };

    Node* head; // Pointer to the head of the linked list

    /**
     * @brief Constructor for LinkedList. Initializes an empty list.
     */
    LinkedList() : head(nullptr){}

    /**
     * @brief Destructor for LinkedList. Deallocates all nodes.
     */
    ~LinkedList(){
        Node* current = head;
        while(current){
            Node* temp = current->next;
            delete current;
            current = temp;
        }
    }

    /**
     * @brief Finds a node with the given key and returns its data.
     *
     * @param key The key to search for.
     * @return Shared pointer to the data if found, nullptr otherwise.
     */
    std::shared_ptr<T> find(int key) const {
        Node* current = head;
        while (current) {
            if (current->key == key) {
                return current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

    /**
     * @brief Inserts a new node at the beginning of the list.
     *
     * @param key The key of the new node.
     * @param data Shared pointer to the data of the new node.
     * @return True if insertion was successful, false if a node with the same key already exists.
     */
    bool insert(int key, std::shared_ptr<T> data) {
        if (find(key)){ // Check if key already exists
            return false;
        }
        Node* newNode = new Node(key, data);
        newNode->next = head;
        head = newNode;
        return true;
    }

    /**
     * @brief Deletes a node with the given key from the list.
     *
     * @param key The key of the node to delete.
     * @return True if deletion was successful, false if the node was not found.
     */
    bool Delete(int key) {
        if (!head) { // Empty list
            return false;
        }

        if (head->key == key) { // Head node matches key
            Node* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        Node* current = head;
        while (current->next && current->next->key != key) {
            current = current->next;
        }

        if (!current->next) { // Key not found
            return false;
        }

        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        return true;
    }

    /**
     * @brief Returns the head of the linked list.
     *
     * @return Pointer to the head node.
     */
    Node* getHead() const{
        return head;
    }
};

#endif //HW2_LINKEDLIST_H