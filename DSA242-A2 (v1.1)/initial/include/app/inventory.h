#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "list/XArrayList.h"
#include "list/DLinkedList.h"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// -------------------- List1D --------------------
template <typename T>
class List1D
{
private:
    IList<T> *pList;

public:
    List1D();
    List1D(int num_elements);
    List1D(const T *array, int num_elements);
    List1D(const List1D<T> &other);
    virtual ~List1D();

    int size() const;
    T get(int index) const;
    void set(int index, T value);
    void add(const T &value);
    string toString() const;
    IList<T> *getInternalList() const;
    template <typename U>
    friend ostream &operator<<(ostream &os, const List1D<T> &list);

    List1D<T> &operator=(const List1D<T> &other);
    //List1D<T> &removeAt(int index) { pList->removeAt(index); return *this; }
};

// -------------------- List2D --------------------
template <typename T>
class List2D
{
private:
    IList<IList<T> *> *pMatrix;

public:
    List2D();
    List2D(List1D<T> *array, int num_rows);
    List2D(const List2D<T> &other);
    virtual ~List2D();

    int rows() const;
    void setRow(int rowIndex, const List1D<T> &row);
    T get(int rowIndex, int colIndex) const;
    List1D<T> getRow(int rowIndex) const;
    string toString() const;
    IList<IList<T> *> *getInternalList() const { return pMatrix; }  
    void addRow(const List1D<T> &row);
    template <typename U>
    friend ostream &operator<<(ostream &os, const List2D<T> &matrix);
    List2D<T> &operator=(const List2D<T> &other);
    // List2D<T> &removeAt(int index) {
    //     pMatrix->get(index)->clear();
    //     delete pMatrix->get(index);
    //     pMatrix->removeAt(index);
    //     return *this;
    // }
};

struct InventoryAttribute
{
    string name;
    double value;
    InventoryAttribute() : name(""), value(0) {}
    InventoryAttribute(const string &name, double value) : name(name), value(value) {}
    string toString() const { return name + ": " + to_string(value); }

    bool operator==(const InventoryAttribute &other) const {
        return name == other.name && value == other.value; 
    }
    friend ostream &operator<<(ostream &os, const InventoryAttribute &attr){
        os << attr.toString();
        return os;
    }
};

// -------------------- InventoryManager --------------------
class InventoryManager
{
private:
    List2D<InventoryAttribute> attributesMatrix;
    List1D<string> productNames;
    List1D<int> quantities;

public:
    InventoryManager();
    InventoryManager(const List2D<InventoryAttribute> &matrix,
                     const List1D<string> &names,
                     const List1D<int> &quantities);
    InventoryManager(const InventoryManager &other);

    int size() const;
    List1D<InventoryAttribute> getProductAttributes(int index) const;
    string getProductName(int index) const;
    int getProductQuantity(int index) const;
    void updateQuantity(int index, int newQuantity);
    void addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity);
    void removeProduct(int index);

    List1D<string> query(string attributeName, const double &minValue,
                         const double &maxValue, int minQuantity, bool ascending) const;

    void removeDuplicates();

    static InventoryManager merge(const InventoryManager &inv1,
                                  const InventoryManager &inv2);

    void split(InventoryManager &section1,
               InventoryManager &section2,
               double ratio) const;

    List2D<InventoryAttribute> getAttributesMatrix() const;
    List1D<string> getProductNames() const;
    List1D<int> getQuantities() const;
    string toString() const;
    InventoryManager &operator=(const InventoryManager &other);
};

// -------------------- List1D Method Definitions --------------------
template <typename T>
List1D<T>::List1D()
{
    pList = new XArrayList<T>();
}

template <typename T>
List1D<T>::List1D(int num_elements)
{
    pList = new XArrayList<T>();
    for(int i = 0; i < num_elements; i++){
        pList->add(T());
    }
}

template <typename T>
List1D<T>::List1D(const T *array, int num_elements)
{   
    pList = new XArrayList<T>(0, 0, num_elements);
    for(int i = 0; i < num_elements; i++) {
        pList->add(array[i]);
    }
}

template <typename T>
List1D<T>::List1D(const List1D<T> &other)
{
    XArrayList<T>* xList = dynamic_cast<XArrayList<T>*>(other.getInternalList());

    if(xList != nullptr)
        pList = new XArrayList<T>(*xList); 
    else 
        pList = new DLinkedList<T>(*dynamic_cast<DLinkedList<T>*>(other.getInternalList()));
}

template <typename T>
List1D<T>::~List1D()
{
    delete pList;
}

template <typename T>
int List1D<T>::size() const
{
    return pList->size();
}

template <typename T>
T List1D<T>::get(int index) const
{
    return pList->get(index);
}

template <typename T>
void List1D<T>::set(int index, T value)
{
    pList->get(index) = value;
}

template <typename T>
void List1D<T>::add(const T &value)
{
    pList->add(value);
}

template <typename T>
string List1D<T>::toString() const
{
    return pList->toString();
}

template <typename T>
ostream &operator<<(ostream &os, const List1D<T> &list)
{
    os << list.toString();
    return os;
}

template <typename T>
IList<T> *List1D<T>::getInternalList() const
{
    return pList;
}

template <typename T>
List1D<T> &List1D<T>::operator=(const List1D<T> &other)
{
    if(this != &other){
        IList<T>* tmpList = nullptr;
        IList<T>* internal = other.getInternalList();
        XArrayList<T>* xList = dynamic_cast<XArrayList<T>*>(internal);

        if(xList != nullptr) tmpList = new XArrayList<T>(*xList); 
        else tmpList = new DLinkedList<T>(*dynamic_cast<DLinkedList<T>*>(internal));

        delete pList;
        pList = tmpList;

    }
    return *this;
}

// -------------------- List2D Method Definitions --------------------
template <typename T>
List2D<T>::List2D()
{
    pMatrix = new XArrayList<IList<T> *>();
}

template <typename T>
List2D<T>::List2D(List1D<T> *array, int num_rows)
{
    pMatrix = new XArrayList<IList<T> *>();
    for (int i = 0; i < num_rows; i++) 
        addRow(array[i]);
}

template <typename T>
List2D<T>::List2D(const List2D<T> &other)
{   
    if(dynamic_cast<XArrayList<IList<T>*>*>(other.getInternalList())) 
        pMatrix = new XArrayList<IList<T> *>();
    else 
        pMatrix = new DLinkedList<IList<T> *>();

    for(int i = 0; i < other.rows(); i++){
        addRow(other.getRow(i));    
    }
}

template <typename T>
List2D<T>::~List2D()
{
    for(int i = 0; i < pMatrix->size(); i++){
        delete pMatrix->get(i);
    }
    delete pMatrix;
}

template <typename T>
int List2D<T>::rows() const
{
    return pMatrix->size();
}

template <typename T>
void List2D<T>::setRow(int rowIndex, const List1D<T> &row)
{
    if(rowIndex < 0 || rowIndex > pMatrix->size()) throw std::out_of_range("Index is out of range!");
    if(rowIndex == pMatrix->size()) addRow(row);
    else {
    IList<T>* newRow = nullptr;
    XArrayList<T>* xList = dynamic_cast<XArrayList<T>*>(row.getInternalList());
    if(xList != nullptr)
        newRow = new XArrayList<T>(*xList);
    else
        newRow = new DLinkedList<T>(*dynamic_cast<DLinkedList<T>*>(row.getInternalList()));
    
    delete pMatrix->get(rowIndex);
    pMatrix->get(rowIndex) = newRow;
    }
}

template <typename T>
T List2D<T>::get(int rowIndex, int colIndex) const
{
    if(rowIndex < 0 || rowIndex >= pMatrix->size()) throw std::out_of_range("Index is out of range!");
    IList<T>* row = pMatrix->get(rowIndex);
    if(colIndex < 0 || colIndex >= row->size()) throw std::out_of_range("Index is out of range!");
    return row->get(colIndex);
}

template <typename T>
List1D<T> List2D<T>::getRow(int rowIndex) const
{
    if(rowIndex < 0 || rowIndex >= pMatrix->size()) throw std::out_of_range("Index is out of range!");
    List1D<T> result;
    IList<T>* row = pMatrix->get(rowIndex);
    for(int i = 0; i < row->size(); i++){
        result.add(row->get(i));
    }
    return result;
}

template <typename T>
string List2D<T>::toString() const
{
    stringstream ss;
    if(pMatrix == nullptr || pMatrix->size() == 0) {
        ss << "[]";
        return ss.str();
    }
    ss <<"[";
    for(int i = 0; i < pMatrix->size(); i++){
        IList<T>* row = pMatrix->get(i);
        if(i > 0) ss << ", ";
        ss << row->toString();
    }
    ss << "]";
    return ss.str();
}

template <typename T>
ostream &operator<<(ostream &os, const List2D<T> &matrix)
{
    os << matrix.toString();
    return os;
}

template <typename T>
void List2D<T>::addRow(const List1D<T> &row)
{   

    IList<T>* newRow = nullptr;
    IList<T>* internal = row.getInternalList();
    XArrayList<T>* xList = dynamic_cast<XArrayList<T>*>(internal);

    if(xList != nullptr){
        newRow = new XArrayList<T>(*xList);
    }
    else
        newRow = new DLinkedList<T>(*dynamic_cast<DLinkedList<T>*>(internal));

    pMatrix->add(newRow);
}

template <typename T>
List2D<T> &List2D<T>::operator=(const List2D<T> &other)
{   
    if(this != &other){
        if(pMatrix != nullptr){
            for(int i = 0; i < rows(); i++){
                delete pMatrix->get(i);
            }
            delete pMatrix;
            pMatrix = nullptr;
        }
        if(this != &other){
            if(dynamic_cast<XArrayList<IList<T>*>*>(other.getInternalList())) 
                pMatrix= new XArrayList<IList<T> *>();
            else 
                pMatrix = new DLinkedList<IList<T> *>();

            for(int i = 0; i < other.rows(); i++){
                addRow(other.getRow(i));
            }
        }
    }
    return *this;
}


// -------------------- InventoryManager Method Definitions --------------------
inline InventoryManager::InventoryManager() //: attributesMatrix(), productNames(), quantities()
{
    this->attributesMatrix = List2D<InventoryAttribute>();
    this->productNames = List1D<string>();
    this->quantities = List1D<int>();
}

inline InventoryManager::InventoryManager(const List2D<InventoryAttribute> &matrix,
                                   const List1D<string> &names,
                                   const List1D<int> &quantities)
{
    this->attributesMatrix = matrix;
    this->productNames = names;
    this->quantities = quantities;
}

inline InventoryManager::InventoryManager(const InventoryManager &other)
{
    this->attributesMatrix = other.attributesMatrix;
    this->productNames = other.productNames;
    this->quantities = other.quantities;
}

inline int InventoryManager::size() const
{
    return productNames.size();
}

inline List1D<InventoryAttribute> InventoryManager::getProductAttributes(int index) const
{
    if(index < 0 || index >= size()) throw std::out_of_range("Index is invalid!");
    return attributesMatrix.getRow(index);
}

inline string InventoryManager::getProductName(int index) const
{
    if(index < 0 || index >= size()) throw std::out_of_range("Index is invalid!");
    return productNames.get(index);
}

inline int InventoryManager::getProductQuantity(int index) const
{
    if(index < 0 || index >= size()) throw std::out_of_range("Index is invalid!");
    return quantities.get(index);
}

inline void InventoryManager::updateQuantity(int index, int newQuantity)
{
    if(index < 0 || index >= size()) throw std::out_of_range("Index is invalid!");
    quantities.set(index, newQuantity);
}

inline void InventoryManager::addProduct(const List1D<InventoryAttribute> &attributes
    , const string &name, int quantity)
{   
    this->attributesMatrix.addRow(attributes);
    this->productNames.add(name);
    this->quantities.add(quantity);
}

inline void InventoryManager::removeProduct(int index)
{
    if(index < 0 || index >= size()) throw std::out_of_range("Index is invalid!");
    List2D<InventoryAttribute> newAtts;
    for(int i = 0 ; i < size(); i++){
        if(i != index) newAtts.addRow(attributesMatrix.getRow(i));
    }
    this->attributesMatrix = newAtts;
    this->productNames.getInternalList()->removeAt(index);
    this->quantities.getInternalList()->removeAt(index);
}

inline void merge(List1D<double>& values, List1D<int>& indices, int l, int m, int r, bool ascend){
	int N = m - l + 1; int M = r - m;
	double* L_val = new double[N];
	double* R_val = new double[M];
	int* l_ind = new int[N];
	int* r_ind = new int[M];
	
	for(int i = 0; i < N; i++){
		L_val[i] = values.get(l + i);
		l_ind[i] = indices.get(l + i);
	}
	for(int i = 0; i < M; i++){
		R_val[i] = values.get(m + 1 + i);
		r_ind[i] = indices.get(m + 1 + i);
	}
	int i = 0, j = 0;

		while(i < N && j < M){
			if(ascend){
				if(L_val[i] <= R_val[j]) {
					values.set(l, L_val[i]);
					indices.set(l , l_ind[i]);
					i++;
				}
				else{
					values.set(l , R_val[j]);
					indices.set(l , r_ind[j]);
					j++;
				}
				l++;
			}
			else{
				if(L_val[i] <= R_val[j]) {
					values.set(l , R_val[j]);
					indices.set(l , r_ind[j]);
					j++;
				}
				else{
					values.set(l, L_val[i]);
					indices.set(l , l_ind[i]);
					i++;
				}
				l++;
			}
		}
		
		while(i < N){
			values.set(l, L_val[i]);
			indices.set(l , l_ind[i]);
			i++;
			l++;
		}
		while(j < M){
			values.set(l , R_val[j]);
			indices.set(l , r_ind[j]);
			j++;
			l++;	
		}
	delete[] L_val;
	delete[] R_val;
	delete[] l_ind;
	delete[] r_ind;
}

inline void mergeSort(List1D<double>& values, List1D<int>& indices, int l, int r, bool ascend){
	if(l >= r) return;
	int m = (l + r)/2;
	mergeSort(values, indices, l, m, ascend);
    mergeSort(values, indices, m + 1, r, ascend);
	merge(values, indices, l , m, r, ascend);
}


inline List1D<string> InventoryManager::query(string attributeName, const double &minValue,
                    const double &maxValue, int minQuantity, bool ascending) const {
    List1D<string> result;
    List1D<int> indices;
    List1D<double> values;
    for(int i = 0; i < size(); i++){
        if (getProductQuantity(i) < minQuantity)
            continue;
        List1D<InventoryAttribute> atts = getProductAttributes(i);
        for (int j = 0; j < atts.size(); j++)
        {
            if(atts.get(j).name == attributeName 
            && atts.get(j).value >= minValue && atts.get(j).value <= maxValue){
                    indices.add(i);
                    values.add(atts.get(j).value);
                break;
            }
        }
    }
    int n = indices.size();
    mergeSort(values, indices, 0, n - 1, ascending);

    for(int i = 0; i < n; i++){
        result.add(getProductName(indices.get(i)));
    }
    return result;
}

inline void InventoryManager::removeDuplicates() {
    int n = size();

    for (int i = 0; i < n; i++) {
        
        for (int j = i + 1; j < n; ) {
            List1D<InventoryAttribute> attrs_i = getProductAttributes(i);
            List1D<InventoryAttribute> attrs_j = getProductAttributes(j);
            bool duplicate = false;
            
            if (getProductName(i) == getProductName(j) && attrs_i.size() == attrs_j.size()) {
                duplicate = true;

                for (int k = 0; k < attrs_i.size(); k++) {
                    InventoryAttribute a = attrs_i.get(k);
                    InventoryAttribute b = attrs_j.get(k);
                    if (a.name != b.name || a.value != b.value) {
                        duplicate = false;
                        break;
                    }
                }

            }
            
            if (duplicate) {
                int newQuantity = getProductQuantity(i) + getProductQuantity(j);
                updateQuantity(i, newQuantity);
                removeProduct(j);
                n = size();
            } 
            else j++;
            
        }
    }

}


inline InventoryManager InventoryManager::merge(const InventoryManager &inv1,
                                         const InventoryManager &inv2)
{
    InventoryManager result(inv1);
    for (int i = 0; i < inv2.size(); i++){
        result.addProduct(inv2.getProductAttributes(i), 
                        inv2.getProductName(i), 
                        inv2.getProductQuantity(i));
    }
    return result;
}

inline void InventoryManager::split(InventoryManager &section1,
    InventoryManager &section2,
    double ratio) const
{   
    if(ratio < 0.00) ratio = 0.00;
    if(ratio > 1.00) ratio = 1.00;
    int n = size();
    section1 = InventoryManager();
    section2 = InventoryManager();
    int n1 = int(n * ratio + 0.99);
    for(int i = 0; i < n1; i++){
        section1.addProduct(getProductAttributes(i), 
        getProductName(i), getProductQuantity(i));
    }
    for(int i = n1; i < n; i++){
        section2.addProduct(getProductAttributes(i), 
        getProductName(i), getProductQuantity(i));
    }
}

inline List2D<InventoryAttribute> InventoryManager::getAttributesMatrix() const
{
    return this->attributesMatrix;
}

inline List1D<string> InventoryManager::getProductNames() const
{
    return this->productNames;
}

inline List1D<int> InventoryManager::getQuantities() const
{
    return this->quantities;    
}

inline string InventoryManager::toString() const
{
    stringstream ss;
    ss << "InventoryManager[\n";
    ss << "  AttributesMatrix: " << attributesMatrix.toString() << ",\n";
    ss << "  ProductNames: " << productNames.toString() << ",\n";
    ss << "  Quantities: " << quantities.toString() << "\n";
    ss << "]";
    return ss.str();
}

inline InventoryManager& InventoryManager::operator=(const InventoryManager &other)
{
    if(this != &other){
        this->attributesMatrix = other.attributesMatrix;
        this->productNames = other.productNames;
        this->quantities = other.quantities;
    }
    return *this;
}

#endif /* INVENTORY_MANAGER_H */
