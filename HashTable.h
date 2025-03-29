//
// Created by Tomer on 1/19/2025.
//

#ifndef HW2_HASHTABLE_H
#define HW2_HASHTABLE_H

#include <iostream>
#include "LinkedList.h"
#include <memory> // Include for std::shared_ptr

template <typename T>
class HashTable{
private:
    const int default_size = 8; // Default size of the hash table

    int size;          // Current size of the hash table
    int element_count; // Number of elements in the hash table
    LinkedList<T>* table; // Array of linked lists, each bucket in the hash table

    /**
     * @brief Calculates the hash index for a given key.
     *
     * @param key The key to hash.
     * @return The hash index.
     */
    int hash(int key) const {
        if (key < 0){
            key = -key; // Ensure positive key for modulo operation
        }
        return key % size; // Modulo operation to get index within table size
    }

    /**
     * @brief Resizes the hash table, doubling its size.
     *
     * @param isRecord Boolean to determine if the key used for rehashing is the record of the data.
     */
    void resize(bool isRecord = false) {
        int new_size = size * 2; // Double the size
        LinkedList<T>* new_table = new LinkedList<T>[new_size]; // Create new table

        for (int i = 0; i < size; ++i) {
            typename LinkedList<T>::Node* current = table[i].getHead();
            while (current) {
                int new_index;
                if (isRecord == false){
                    new_index = current->key % new_size; // Rehash using the key itself
                }
                else{
                    // Rehash using the record of the data
                    new_index = current->data->getRecord() > 0 ?
                                current->data->getRecord() % new_size : (-current->data->getRecord()) % new_size;
                }
                new_table[new_index].insert(current->key, current->data); // Insert into the new table
                current = current->next;
            }
        }

        delete[] table; // Delete old table
        table = new_table; // Assign new table
        size = new_size; // Update size
    }

public:

    /**
     * @brief Constructor for HashTable. Initializes the table with default size.
     */
    HashTable() :
            size(default_size),
            element_count(0),
            table(new LinkedList<T>[default_size]){}

    /**
     * @brief Destructor for HashTable. Deallocates the table.
     */
    ~HashTable() {
        delete[] table;
    }

    /**
     * @brief Inserts a key-value pair into the hash table.
     *
     * @param keyHash The hash key to use for insertion.
     * @param value The value to insert (shared pointer).
     * @param keyNode The node key, if using a different key than the hash key.
     * @return True if insertion was successful, false otherwise.
     */
    bool insert(int keyHash, std::shared_ptr<T> value, int keyNode = 0) {
        int index = hash(keyHash);

        if (keyNode == 0){
            if (table[index].insert(keyHash, value)) {
                ++element_count;

                if (element_count > size) {
                    resize(); // Resize if load factor exceeds 1
                }
                return true;
            }

            return false;
        }
        if (table[index].insert(keyNode, value)) {
            ++element_count;

            if (element_count > size) {
                resize(true); // Resize using the record of the data
            }
            return true;
        }

        return false;
    }

    /**
     * @brief Removes a key-value pair from the hash table.
     *
     * @param keyHash The hash key to use for removal.
     * @param keyDelete The key to delete, if using a different key than the hash key.
     * @return True if removal was successful, false otherwise.
     */
    bool remove(int keyHash, int keyDelete = 0) {
        int index = hash(keyHash);
        if(keyDelete == 0){
            if (table[index].Delete(keyHash)) {
                --element_count;
                return true;
            }
            return false;
        }
        if (table[index].Delete(keyDelete)) {
            --element_count;
            return true;
        }
        return false;
    }

    /**
     * @brief Finds a value in the hash table based on the key.
     *
     * @param keyHash The hash key to use for finding.
     * @param keyFind The key to find, if using a different key than the hash key.
     * @return A shared pointer to the found value, or nullptr if not found.
     */
    std::shared_ptr<T> find(int keyHash, int keyFind = 0) const {
        int index = hash(keyHash);
        if (keyFind == 0){
            return table[index].find(keyHash);
        }
        return table[index].find(keyFind);
    }

    /**
     * @brief Checks if a record can be united (i.e., if both positive and negative records exist).
     *
     * @param record The record to check.
     * @return True if the record can be united, false otherwise.
     */
    bool canUnitedByRecord(int record){
        int index = hash(record);
        typename LinkedList<T>::Node* current = table[index].getHead();
        int counter = 0;
        int negativeCounter = 0;
        while (current) {
            if (current->data->getRecord() == record){
                counter++;
            }
            if (current->data->getRecord() == -record){
                negativeCounter++;
            }
            current = current->next;
        }
        return (counter == 1 && negativeCounter == 1);
    }

    /**
     * @brief Gets the team associated with a given record.
     *
     * @param record The record to find the team for.
     * @return The team key, or 0 if not found.
     */
    int getTeamByRecord(int record){
        int index = hash(record);
        typename LinkedList<T>::Node* current = table[index].getHead();
        while (current) {
            if (current->data->getRecord() == record){
                return current->key;
            }
            current = current->next;
        }
        return 0;
    }

    /**
     * @brief Prints the contents of the hash table for debugging purposes.
     */
    void PrintHashTable(){
        for (int i = 0; i < size; i++){
            typename LinkedList<T>::Node* current = table[i].getHead();
            while (current) {
                std::cout << current->key << ", ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
};

#endif //HW2_HASHTABLE_H
