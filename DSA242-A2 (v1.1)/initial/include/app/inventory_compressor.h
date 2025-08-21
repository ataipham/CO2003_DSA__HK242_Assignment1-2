#ifndef INVENTORY_COMPRESSOR_H
#define INVENTORY_COMPRESSOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <utility>
#include "inventory.h"
#include "hash/xMap.h"
#include "heap/Heap.h"
#include "list/XArrayList.h"

template<int treeOrder>
class HuffmanTree {
public:
    struct HuffmanNode {
        char symbol;
        int freq;
        XArrayList<HuffmanNode*> children;

        HuffmanNode(char s, int f){
            symbol = s;
            freq = f;
            children = XArrayList<HuffmanNode*>();
        } //Leaf node

        HuffmanNode(int f, const  XArrayList<HuffmanNode*>& childs){
            symbol = '\0'; //Internal node has no symbol
            freq = f;
            children = childs;
        } //Internal node
    };


    void deleteTree(HuffmanNode*& node) {
        if (node == nullptr) return;
        for (int i = 0; i < node->children.size(); ++i) {
            deleteTree(node->children.get(i));
        }
        delete node;
    }

    static int compareNodes(HuffmanNode *lhs, HuffmanNode *rhs);

    HuffmanTree();
    ~HuffmanTree();

    //XArrayList<HuffmanNode *> allNodes;

    void build(XArrayList<pair<char, int>>& symbolsFreqs);
    void generateCodes(xMap<char, std::string>& table);
    std::string decode(const std::string& huffmanCode);

    static string nodeToString(HuffmanNode*& node) {
        std::stringstream ss;
        if (node->symbol == '\0')
            ss << "[dummy:" << node->freq << "]";
        else
            ss << "[" << node->symbol << ":" << node->freq << "]";
        return ss.str();
    }

private:
    HuffmanNode* root;

    void deleteSubTree(HuffmanNode* node) {
        if(!node) return;

        for(HuffmanNode* child : node->children) {
            deleteSubTree(child);
        }
        //node->children.clear();
        delete node;
    }

    void generateCodesDFS(HuffmanNode* node, std::string prefix, xMap<char, std::string>& table) {
        if (!node) return;
        if (node->children.empty()) { // Leaf node
            if(node->symbol != '\0')
                table.put(node->symbol, prefix.empty() ? "0" : prefix); 

            else {
                std::string nullChar;
                nullChar.push_back('\0');
                table.put(nullChar[0], prefix.empty() ? nullChar : prefix); // Handle null character case
            }
            // Handle single symbol case
            return;
        }

        for (int i = 0; i < node->children.size(); ++i) {
            std::stringstream ss;
            if(treeOrder > 10)
                ss << hex << i;
            else
                ss << i;
            std::string next = prefix + ss.str(); // Use stringstream for index

            if(i < node->children.size() && node->children.get(i) != nullptr) {
                generateCodesDFS(node->children.get(i), next, table);
            }
        }
    }

};

template<int treeOrder>
class InventoryCompressor {
public:
    InventoryCompressor(InventoryManager* manager);
    ~InventoryCompressor();

    void buildHuffman();
    void printHuffmanTable();
    std::string productToString(const List1D<InventoryAttribute>& attributes, const std::string& name);
    std::string encodeHuffman(const List1D<InventoryAttribute>& attributes, const std::string& name);
    std::string decodeHuffman(const std::string& huffmanCode, List1D<InventoryAttribute>& attributesOutput, std::string& nameOutput);

private:
    xMap<char, std::string>* huffmanTable;
    InventoryManager* invManager;
    HuffmanTree<treeOrder>* tree;
};

#endif // INVENTORY_COMPRESSOR_H

template <int treeOrder>
int HuffmanTree<treeOrder>::compareNodes(HuffmanNode *lhs, HuffmanNode *rhs)
{
    if (lhs->freq < rhs->freq) return -1;
    if (lhs->freq > rhs->freq) return 1;
    if (lhs->symbol != '\0' && rhs->symbol != '\0') {
        return lhs->symbol < rhs->symbol ? -1 : (lhs->symbol > rhs->symbol ? 1 : 0);
    }
    if (lhs->symbol != '\0') return -1;
    if (rhs->symbol != '\0') return 1;

    return 0;
}

template <int treeOrder>
HuffmanTree<treeOrder>::HuffmanTree()
{
    this->root = nullptr;
}

template <int treeOrder>
HuffmanTree<treeOrder>::~HuffmanTree()
{
    deleteSubTree(root);
    root = nullptr;
}


template <int treeOrder>
void HuffmanTree<treeOrder>::build(XArrayList<pair<char, int>> &symbolsFreqs)
{
    // --- Step 0: Reset State ---

    // Handle empty input or invalid treeOrder
    int size = symbolsFreqs.size();
    if (size == 0 || treeOrder <= 1) return;

    // --- Step 1: Sort symbols by ASCII code (ascending) ---
    for(int i = 0; i < size - 1; ++i) {
        bool swapped = false;
        for(int j = 0; j < size - i - 1; ++j) {
            auto &a = symbolsFreqs.get(j);
            auto &b = symbolsFreqs.get(j + 1);
            // if freq(a) > freq(b), or freq equal and symbol(a) > symbol(b), swap:
            if (a.second > b.second || (a.second == b.second && a.first > b.first)) {
                auto tmp = a;
                symbolsFreqs.get(j) = b;
                symbolsFreqs.get(j + 1) = tmp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    // --- Step 2: Determine how many dummy nodes to add ---
    size = symbolsFreqs.size();
    int dummyCount = 0;
    if (size == 1) {
        // Single symbol → need (treeOrder - 1) dummy leaves
        dummyCount = treeOrder - 1;
    } else {
        int remainder = (size - 1) % (treeOrder - 1); 
        if (remainder != 0) {
            dummyCount = (treeOrder - 1) - remainder;
        }
    }

    // --- Step 3: Create an initial node list ---

    // Add dummy nodes
    for (int i = 0; i < dummyCount; i++) {
        HuffmanNode* dummy = new HuffmanNode('\0', 0);
        heapNodes.add(dummy);
    }
    // Add real nodes
    XArrayList<HuffmanNode *> heapNodes;
    for (auto &sf : symbolsFreqs) {
        HuffmanNode* node = new HuffmanNode(sf.first, sf.second);
        heapNodes.add(node);
    }

    // --- Step 4: Build the tree iteratively ---
    while (heapNodes.size() > 1) {
        // Extract up to treeOrder lowest-priority nodes
        XArrayList<HuffmanNode *> selected;
        int totalFreq = 0;
        int countToExtract = std::min(treeOrder, heapNodes.size());
        for (int i = 0; i < countToExtract; i++){
            HuffmanNode* node = heapNodes.get(0);
            selected.add(node);
            totalFreq += node->freq;
            heapNodes.removeAt(0);
        }

        // Create a new internal node
        HuffmanNode* internalNode = new HuffmanNode(totalFreq, selected);
        allNodes.add(internalNode);

        // Add the new node at the end, then bubble it up
        heapNodes.add(internalNode);
        int curr = heapNodes.size() - 1;
        // Bubble up while compareNodes says the predecessor is "larger"
        while(curr > 0 && compareNodes(heapNodes.get(curr - 1), heapNodes.get(curr)) > 0) {
            HuffmanNode* tmp = heapNodes.get(curr - 1);
            heapNodes.get(curr - 1) = heapNodes.get(curr);
            heapNodes.get(curr) = tmp;
            curr--;
        }
    }

    // --- Step 5: The root is the sole node left
    if (!heapNodes.empty()) {
        root = heapNodes.get(0);
    }
    else {
        root = nullptr;
    }
}


template <int treeOrder>
void HuffmanTree<treeOrder>::generateCodes(xMap<char, std::string> &table)
{
    if(!root) return;
    generateCodesDFS(root, "", table);
}

template <int treeOrder>
std::string HuffmanTree<treeOrder>::decode(const std::string &huffmanCode)
{
    std::string nullChar;
    nullChar.push_back('\0');

    if(!root || huffmanCode.empty()) return nullChar;
    std::string result = "";

    HuffmanNode* curr = root;

    if(root->children.empty()){ // Only one symbol in the tree
        for (size_t i = 0; i < huffmanCode.length(); i++){
            result += root->symbol; // Append the symbol for each bit in the code
        }
        return result;
    }

    for(char bit : huffmanCode){
        int index;
        if(bit >= '0' && bit <= '9'){
            index = bit - '0';
        } else if(bit >= 'a' && bit <= 'z'){
            index = bit - 'a' + 10; // Convert A-Z to 10-15
        } else {
            return nullChar; // Invalid character in huffmanCode
        }

        if(index < 0 || index >= curr->children.size()){
            return nullChar;
        }

        curr = curr->children.get(index);
        if(curr->children.empty()){ // Leaf node
            if(curr->symbol != '\0'){  // Valid code
                result += curr->symbol;
            }

            curr = root; // Reset to root for next symbol
        }
    }

    if(curr != root || (result.empty() && !huffmanCode.empty())) { // If we are not at the root, it means the code is invalid
        return nullChar;
    }

    return result;
}

template <int treeOrder>
InventoryCompressor<treeOrder>::InventoryCompressor(InventoryManager *manager)
{
    this->invManager = manager;
    this->huffmanTable = new xMap<char, std::string>(&xMap<char, std::string>::simpleHash);
    this->tree = new HuffmanTree<treeOrder>();
}

template <int treeOrder>
InventoryCompressor<treeOrder>::~InventoryCompressor()
{
    delete huffmanTable;
    huffmanTable = nullptr;
    delete tree;
    tree = nullptr;
}

template <int treeOrder>
void InventoryCompressor<treeOrder>::buildHuffman()
{
    xMap<char, int> freqMap(&xMap<char, int>::simpleHash);
    int invManagerSize = invManager->size();
    for (int i = 0; i < invManagerSize; i++){
         std::string productStr = productToString(invManager->getProductAttributes(i), 
                                                  invManager->getProductName(i));    
                                                 
        for(char c : productStr){
            if(freqMap.containsKey(c)){
                freqMap.put(c, freqMap.get(c) + 1);
            } else{
                freqMap.put(c, 1);
            }
        }
    }

    XArrayList<pair<char, int>> symbolsFreqs;
    DLinkedList<char> keys = freqMap.keys();

    for(char ch : keys){
        symbolsFreqs.add(make_pair(ch, freqMap.get(ch)));
    }
    tree->build(symbolsFreqs);
    huffmanTable->clear(); // Clear the previous table before generating new codes
    tree->generateCodes(*huffmanTable);

}

template <int treeOrder>
void InventoryCompressor<treeOrder>::printHuffmanTable() {
    DLinkedList<char> keys = huffmanTable->keys();

    for (char ch : keys) {
        std::cout << "'" << ch << "' : " << huffmanTable->get(ch) << std::endl;
    }
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::productToString(const List1D<InventoryAttribute> &attributes, 
    const std::string &name)
{
    std::string result = "";
    result += name + ":";
    for (int i = 0; i < attributes.size(); i++){
        if(i != 0) result += ", ";
        result += "(" + attributes.get(i).name + ": " 
                + std::to_string(attributes.get(i).value) + ")";
    }
    return result;
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::encodeHuffman(const List1D<InventoryAttribute> &attributes, const std::string &name)
{
    std::string productStr = productToString(attributes, name);
    std::string huffmanCode = "";
    for(char c : productStr){
        huffmanCode += huffmanTable->get(c);
    }
    return huffmanCode;
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::decodeHuffman(const std::string &huffmanCode, 
                                        List1D<InventoryAttribute> &attributesOutput, 
                                        std::string &nameOutput)
{
    std::string decodedStr = tree->decode(huffmanCode);
    std::string decoding = decodedStr;
    List1D<InventoryAttribute> attributesOut;
    size_t colonPos = decoding.find(':');
    nameOutput = decoding.substr(0, colonPos);
    decoding = decoding.substr(colonPos + 1);
    while( decoding != "" ){
        size_t openBracket = decoding.find('(');
        if(openBracket == std::string::npos) break; // No more attributes

        size_t colon = decoding.find(':');
        if(colon == std::string::npos) break; // No more attributes

        size_t closeBracket = decoding.find(')');
        if(closeBracket == std::string::npos) break; // No more attributes

        string nameAtt = decoding.substr(openBracket + 1, colon - openBracket - 1);
        string valueAtt = decoding.substr(colon + 1, closeBracket - colon - 1);
        double value = std::stod(valueAtt);
        attributesOutput.add(InventoryAttribute(nameAtt, value));
        decoding = decoding.substr(closeBracket + 1);
    }
    return decodedStr;
}