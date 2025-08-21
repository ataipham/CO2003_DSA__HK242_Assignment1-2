#include <iostream>
#include <string>
#include <sstream>
#include "app/inventory_compressor.h"
#include "app/inventory.h"

using namespace std;

typedef HuffmanTree<3> HTree;
typedef HTree::HuffmanNode HNode;
typedef InventoryCompressor<4> InvCompressor;
typedef InventoryCompressor<12> InvCompressorTwelve;
typedef HuffmanTree<4> HTreeFour;
typedef HuffmanTree<16> HTreeSixteen;

int charHashFunc(char& key, int tablesize) {
    return (int)key % tablesize;
}

void tc_huffman1001() {
    XArrayList<pair<char, int>> symbolFreqs;
    symbolFreqs.add(make_pair('A', 5));
    symbolFreqs.add(make_pair('B', 3));
    //symbolFreqs.add(make_pair('C', 6));
    //symbolFreqs.add(make_pair('D', 4));
    //symbolFreqs.add(make_pair('E', 2));
    HTree tree;
    tree.build(symbolFreqs);
    
    xMap<char, string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);
    
    string codeA = codeTable.get('A');
    cout << "Code for A: " << codeA << endl;
    string codeB = codeTable.get('B');
    cout << "Code for B: " << codeB << endl;
    
    string decoded = tree.decode(codeA);
    cout << "Decoded string: " << decoded << endl;
    cout << "Decoded string from B: " << tree.decode(codeB) << endl;

    //new:
    // string mssg = "BCCDACCBDABC\n\
    // CDEAA\n\
    // EDA";
    // stringstream ss;
    // for (char ch : mssg) {
    //     string code = codeTable.get(ch);
    //     ss << code;
    // }
    // string encoded = ss.str();
    // cout << "Encoded message: " << encoded << endl;
    // string decoded = tree.decode(encoded);
    // cout << "Decoded message: " << decoded << endl;
}


void tc_huffman1002() {
    XArrayList<pair<char, int>> symbolFreqs;
    symbolFreqs.add(make_pair('A', 5));
    symbolFreqs.add(make_pair('B', 3));
    symbolFreqs.add(make_pair('C', 7));
    symbolFreqs.add(make_pair('D', 2));
    
    HTree tree;
    tree.build(symbolFreqs);
    
    xMap<char, string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);
    
    cout << "Generated codes:" << endl;
    for (char ch = 'A'; ch <= 'D'; ++ch) {
        string code = codeTable.get(ch);
        cout << "Code for " << ch << ": " << code << endl;
    }

    string mssg = "BCCDACCBDABCCACAA";
    stringstream ss;
    for (char ch : mssg) {
        string code = codeTable.get(ch);
        ss << code;
    }
    string encoded = ss.str();
    cout << "Encoded message: " << encoded << endl;
    string decoded = tree.decode(encoded);
    cout << "Decoded message: " << decoded << endl;
}

void tc_huffman1003() {    
    XArrayList<pair<char, int>> symbolFreqs;
    symbolFreqs.add(make_pair('X', 4));
    symbolFreqs.add(make_pair('Y', 6));
    symbolFreqs.add(make_pair('Z', 2));
    
    HTree tree;
    tree.build(symbolFreqs);
    
    xMap<char, string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);
    
    string codeZ = codeTable.get('Z');
    cout << "Code for Z: " << codeZ << endl;
    
    string decoded = tree.decode(codeZ);
    cout << "Decoded string: " << decoded << endl;
}

void tc_huffman1004() {
    XArrayList<pair<char, int>> symbolFreqs;
    symbolFreqs.add(make_pair('M', 3));
    symbolFreqs.add(make_pair('N', 5));
    
    HTree tree;
    tree.build(symbolFreqs);
    
    xMap<char, string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);
    
    for(char ch = 'M'; ch <= 'N'; ++ch) {
        string code = codeTable.get(ch);
        cout << "Code for " << ch << ": " << code << endl;
    }

    string decoded = tree.decode("0");
    cout << decoded << endl;
    cout << "Decoded string from invalid code: " << decoded << endl;
}

void tc_huffman1005() {
    XArrayList<pair<char, int>> symbolFreqs;
    const string symbols = "ABCDEFGHIJ";
    int n = symbols.size();
    for (int i = 0; i < n; ++i) {
        symbolFreqs.add(make_pair(symbols[i], (i + 1) * 2));
    }
    
    HTree tree;
    tree.build(symbolFreqs);
    
    xMap<char, string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);
    
    for (char ch : symbols) {
        string code = codeTable.get(ch);
        string decoded = tree.decode(code);
        cout << ch << " with code " << code << " decodes as: " << decoded << endl;
    }
}

	
void tc_compressor1001() {
    InventoryManager manager;
    List1D<InventoryAttribute> attrs;
    attrs.add(InventoryAttribute("weight", 2.5));
    attrs.add(InventoryAttribute("voltage", 12.0));
    manager.addProduct(attrs, "Gadget", 50);

    InvCompressor compressor(&manager);
    compressor.buildHuffman();

    string productStr = compressor.productToString(attrs, "Gadget");
    cout << "Product string: " << productStr << endl;

    compressor.printHuffmanTable();

    string encoded = compressor.encodeHuffman(attrs, "Gadget");
    cout << "Encoded product: " << encoded << endl;
}

void tc_compressor1002() {    
    InventoryManager manager;
    
    List1D<InventoryAttribute> carAttrs;
    carAttrs.add(InventoryAttribute("speed", 88.0));
    manager.addProduct(carAttrs, "Car", 1);
    
    List1D<InventoryAttribute> batteryAttrs;
    batteryAttrs.add(InventoryAttribute("capacity", 250.0));
    batteryAttrs.add(InventoryAttribute("voltage", 12.0));
    manager.addProduct(batteryAttrs, "Battery", 5);
    
    InvCompressor compressor(&manager);
    compressor.buildHuffman();
    compressor.printHuffmanTable(); 
    
    string encodedCar = compressor.encodeHuffman(carAttrs, "Car");
    string encodedBattery = compressor.encodeHuffman(batteryAttrs, "Battery");
    
    cout << "Encoded Car: " << encodedCar << endl;
    cout << "Encoded Battery: " << encodedBattery << endl;

    std::string emptyStringCar;
    cout << "Decoded Car: " << compressor.decodeHuffman(encodedCar, carAttrs, emptyStringCar) << endl;
    string emptyStringBattery;
    cout << "Decoded Battery: " << compressor.decodeHuffman(encodedBattery, batteryAttrs, emptyStringBattery) << endl;
}

void test(){
    XArrayList<pair<char, int>> symbolFreqs;
    symbolFreqs.add(make_pair('A', 1));
    symbolFreqs.add(make_pair('B', 1));
    symbolFreqs.add(make_pair('C', 1));
    symbolFreqs.add(make_pair('D', 1));
    symbolFreqs.add(make_pair('E', 1));
    symbolFreqs.add(make_pair('F', 1));
    symbolFreqs.add(make_pair('G', 1));
    symbolFreqs.add(make_pair('H', 1));
    symbolFreqs.add(make_pair('I', 1));
    symbolFreqs.add(make_pair('J', 1));
    HTree tree;
    tree.build(symbolFreqs);
    
    xMap<char, string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);
    
    for(char ch = 'A'; ch <= 'J'; ++ch) {
        string code = codeTable.get(ch);
        cout << "Code for " << ch << ": " << code << endl;
    }

}

void test_Huffman01() {
    cout << "HuffmanInv Test 01";
    //! data
    XArrayList<pair<char,int>> symbolFreqs;
    symbolFreqs.add(make_pair('A', 5));
    HTree tree;
    tree.build(symbolFreqs);

    xMap<char,string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);

    //! expect
    string expect =
        "Code for A: 2\n"
        "Decoded string: A\n";

    //! output
    stringstream ss;
    string codeA = codeTable.get('A');
    ss << "Code for A: " << codeA << endl;
    ss << "Decoded string: " << tree.decode(codeA) << endl;
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Huffman02() {
    cout << "HuffmanInv Test 02";
    //! data
    XArrayList<pair<char,int>> symbolFreqs;
    symbolFreqs.add(make_pair('A',5));
    symbolFreqs.add(make_pair('B',3));
    symbolFreqs.add(make_pair('C',7));
    symbolFreqs.add(make_pair('D',2));
    HTree tree;
    tree.build(symbolFreqs);

    xMap<char,string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);

    //! expect
    string expect = "Generated codes:\n\
Code for A: 0\n\
Code for B: 12\n\
Code for C: 2\n\
Code for D: 11\n";

    //! output
    stringstream ss;
    ss << "Generated codes:" << endl;
    for (char ch : {'A','B','C','D'}) {
        ss << "Code for " << ch << ": " << codeTable.get(ch) << endl;
    }
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Huffman03() {
    cout << "HuffmanInv Test 03";
    //! data
    XArrayList<pair<char,int>> symbolFreqs;
    symbolFreqs.add(make_pair('X',4));
    symbolFreqs.add(make_pair('Y',6));
    symbolFreqs.add(make_pair('Z',2));
    HTree tree;
    tree.build(symbolFreqs);

    xMap<char,string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);

    //! expect
    string expect =
        "Code for Z: 0\n"
        "Decoded string: Z\n";

    //! output
    stringstream ss;
    string codeZ = codeTable.get('Z');
    ss << "Code for Z: " << codeZ << endl;
    ss << "Decoded string: " << tree.decode(codeZ) << endl;
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Huffman04() {
    cout << "HuffmanInv Test 04";
    //! data
    XArrayList<pair<char,int>> symbolFreqs;
    symbolFreqs.add(make_pair('M',3));
    symbolFreqs.add(make_pair('N',5));
    HTree tree;
    tree.build(symbolFreqs);

    xMap<char,string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);

    //! expect
    string expect =
        "Decoded string from invalid code: \n";

    //! output
    stringstream ss;
    ss << "Decoded string from invalid code: " << tree.decode("0") << endl;
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Huffman05() {
    cout << "HuffmanInv Test 05";
    //! data
    XArrayList<pair<char,int>> symbolFreqs;
    const string symbols = "ABCDEFGHIJ";
    for (int i = 0; i < (int)symbols.size(); ++i)
        symbolFreqs.add(make_pair(symbols[i], (i+1)*2));
    HTree tree;
    tree.build(symbolFreqs);

    xMap<char,string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);

    //! expect
    string expect = "A with code 011 decodes as: A\n\
B with code 012 decodes as: B\n\
C with code 00 decodes as: C\n\
D with code 02 decodes as: D\n\
E with code 10 decodes as: E\n\
F with code 11 decodes as: F\n\
G with code 12 decodes as: G\n\
H with code 20 decodes as: H\n\
I with code 21 decodes as: I\n\
J with code 22 decodes as: J\n";

    //! output
    stringstream ss;
    for (char ch : symbols) {
        string code = codeTable.get(ch);
        ss << ch << " with code " << code
           << " decodes as: " << tree.decode(code) << endl;
    }
    string output = ss.str();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_Huffman06() {
    cout << "HuffmanInv Test 06";
    //! data
    InventoryManager manager;
    List1D<InventoryAttribute> attrs;
    attrs.add(InventoryAttribute("weight", 2.5));
    attrs.add(InventoryAttribute("voltage", 12.0));
    manager.addProduct(attrs, "Gadget", 50);

    InvCompressor compressor(&manager);
    compressor.buildHuffman();

    //! expect
    string expect =
        "Encoded product: 3112031022212330003312131322312233003023321111101321333003303223202320222130323030211111101\n"
        "decoded product: Gadget:(weight:2.500000), (voltage:12.000000)\n";

    //! output
    stringstream ss;
    string encoded = compressor.encodeHuffman(attrs, "Gadget");
    List1D<InventoryAttribute> attributesOutput;
    string nameOutput;
    ss << "Encoded product: " << encoded << endl;
    ss << "decoded product: " << compressor.decodeHuffman(encoded, attributesOutput, nameOutput) << endl;
    string output = ss.str();

    cout << "Expected:\n" << expect;
    cout << "Actual:\n" << output;
    if (output == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}

void test_Huffman07() {
    cout << "HuffmanInv Test 07";
    //! data
    InventoryManager manager;
    List1D<InventoryAttribute> carAttrs;
    carAttrs.add(InventoryAttribute("speed", 88.0));
    manager.addProduct(carAttrs, "Car", 1);
    List1D<InventoryAttribute> batteryAttrs;
    batteryAttrs.add(InventoryAttribute("capacity", 250.0));
    batteryAttrs.add(InventoryAttribute("voltage", 12.0));
    manager.addProduct(batteryAttrs, "Battery", 5);

    InvCompressor compressor(&manager);
    compressor.buildHuffman();

    //! expect
    string expect = "Car:(speed:88.000000)Battery:(capacity:250.000000), (voltage:12.000000)Encoded Car: 1323133230001313311010032303303300222222201\n\
Encoded Battery: 130311111103323333000322313313132212111333303230332022222220132132000133123122113112010300313230222222201\n\
decodeHuffman: Car:(speed:88.000000)\n\
1323133230001313311010032303303300222222201 [speed: 88.000000]  Car\n";
    //! output
    stringstream ss;
    ss << compressor.productToString(carAttrs, "Car");
    ss << compressor.productToString(batteryAttrs, "Battery");
    string encodedCar = compressor.encodeHuffman(carAttrs, "Car");
    string encodedBattery = compressor.encodeHuffman(batteryAttrs, "Battery");
    List1D<InventoryAttribute> attributesOutput;
    string nameOutput;
    ss << "Encoded Car: " << encodedCar << endl;
    ss << "Encoded Battery: " << encodedBattery << endl;
    ss << "decodeHuffman: " << compressor.decodeHuffman(encodedCar, attributesOutput, nameOutput) << endl;
    ss << encodedCar << " " << attributesOutput.toString() << "  " << nameOutput << endl;
    string output = ss.str();

    cout << "Expected:\n" << expect;
    cout << "Actual:\n" << output;
    if (output == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}

void test_Huffman08() {
    cout << "HuffmanInv Test 08";
    //! data
    XArrayList<pair<char,int>> symbolFreqs;
    const string symbols = "ABCDEFGHIJKLMNOP";
    for (char ch : symbols)
        symbolFreqs.add(make_pair(ch, (ch - 'A' + 1) * 3));

    HTreeFour tree;
    tree.build(symbolFreqs);
    xMap<char,string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);

    //! expect
    string expect =
        "A with code 220 decodes as: A\n"
        "B with code 221 decodes as: B\n"
        "C with code 222 decodes as: C\n"
        "D with code 223 decodes as: D\n"
        "E with code 10 decodes as: E\n"
        "F with code 11 decodes as: F\n"
        "G with code 12 decodes as: G\n"
        "H with code 13 decodes as: H\n"
        "I with code 20 decodes as: I\n"
        "J with code 21 decodes as: J\n"
        "K with code 23 decodes as: K\n"
        "L with code 30 decodes as: L\n"
        "M with code 31 decodes as: M\n"
        "N with code 32 decodes as: N\n"
        "O with code 33 decodes as: O\n"
        "P with code 0 decodes as: P\n";

    //! output
    stringstream ss;
    for (char ch : symbols) {
        string code = codeTable.get(ch);
        string decoded = tree.decode(code);
        ss << ch << " with code " << code << " decodes as: " << decoded << endl;
    }
    string output = ss.str();

    cout << "Expected:\n" << expect;
    cout << "Actual:\n" << output;
    if (output == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}

void test_Huffman09() {
    cout << "HuffmanInv Test 09\n";
    //! data
    XArrayList<pair<char,int>> symbolFreqs;
    const string symbols = "AB";
    for (char ch : symbols)
        symbolFreqs.add(make_pair(ch, (int)ch));

    HTreeSixteen tree;
    tree.build(symbolFreqs);
    xMap<char,string> codeTable(&charHashFunc);
    tree.generateCodes(codeTable);

    //! expect
    string expect =
        "A with code e decodes as: A\n"
        "B with code f decodes as: B\n";

    //! output
    stringstream ss;
    for (char ch : symbols) {
        string code = codeTable.get(ch);
        cout << "Code for " << ch << ": " << code << endl;
        string decoded = tree.decode(code);
        ss << ch << " with code " << code << " decodes as: " << decoded << endl;
    }
    string output = ss.str();

    cout << "Expected:\n" << expect;
    cout << "Actual:\n" << output;
    if (output == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}

void test_Huffman10() {
    cout << "HuffmanInv Test 10\n";
    //! data
    InventoryManager manager;
    List1D<InventoryAttribute> carAttrs, batteryAttrs, fanAttrs, laptopAttrs, airconAttrs, fridgeAttrs;

    carAttrs.add(InventoryAttribute("speed", 123.456));
    carAttrs.add(InventoryAttribute("fuel", 7.89));
    carAttrs.add(InventoryAttribute("engine_temp", 98.76));
    carAttrs.add(InventoryAttribute("tire_pressure", 32.5));
    manager.addProduct(carAttrs, "Car", 2);

    batteryAttrs.add(InventoryAttribute("capacity", 250.75));
    batteryAttrs.add(InventoryAttribute("voltage", 12.45));
    batteryAttrs.add(InventoryAttribute("life", 3.5));
    batteryAttrs.add(InventoryAttribute("weight", 5.8));
    manager.addProduct(batteryAttrs, "Battery", 3);

    fanAttrs.add(InventoryAttribute("rpm", 1230.5));
    fanAttrs.add(InventoryAttribute("power", 45.75));
    fanAttrs.add(InventoryAttribute("noise", 23.33));
    fanAttrs.add(InventoryAttribute("speed_levels", 5.0));
    manager.addProduct(fanAttrs, "Fan", 5);

    laptopAttrs.add(InventoryAttribute("ram", 16.0));
    laptopAttrs.add(InventoryAttribute("storage", 512.5));
    laptopAttrs.add(InventoryAttribute("weight", 1.25));
    laptopAttrs.add(InventoryAttribute("cpu", 2.7));
    laptopAttrs.add(InventoryAttribute("gpu", 6.5));
    manager.addProduct(laptopAttrs, "Laptop", 4);

    airconAttrs.add(InventoryAttribute("btu", 12000.0));
    airconAttrs.add(InventoryAttribute("power", 850.5));
    airconAttrs.add(InventoryAttribute("efficiency", 3.75));
    airconAttrs.add(InventoryAttribute("noise", 32.1));
    airconAttrs.add(InventoryAttribute("filter", 2.0));
    manager.addProduct(airconAttrs, "Aircon", 3);

    fridgeAttrs.add(InventoryAttribute("volume", 300.0));
    fridgeAttrs.add(InventoryAttribute("power", 150.0));
    fridgeAttrs.add(InventoryAttribute("noise", 28.0));
    fridgeAttrs.add(InventoryAttribute("temp_range", -18.0));
    manager.addProduct(fridgeAttrs, "Fridge", 2);

    InvCompressorTwelve compressor(&manager);
    compressor.buildHuffman();

    //! expect
    string expect =
        "Car:(speed:123.456000), (fuel:7.890000), (engine_temp:98.760000), (tire_pressure:32.500000)\n"
        "Battery:(capacity:250.750000), (voltage:12.450000), (life:3.500000), (weight:5.800000)\n"
        "Fan:(rpm:1230.500000), (power:45.750000), (noise:23.330000), (speed_levels:5.000000)\n"
        "Laptop:(ram:16.000000), (storage:512.500000), (weight:1.250000), (cpu:2.700000), (gpu:6.500000)\n"
        "Aircon:(btu:12000.000000), (power:850.500000), (efficiency:3.750000), (noise:32.100000), (filter:2.000000)\n"
        "Fridge:(volume:300.000000), (power:150.000000), (noise:28.000000), (temp_range:-18.000000)\n"
        "Encoded Car: 06a3ab84a2aa770a8a4a8a5691193bbb5324949879b89969a08bbbb53247a1a0a9a1792a7795aa8089a69993bbbb5324a7a9ab792aaab7a2a298ab78a5a861bbbbb5\n"
        "Encoded Battery: 05a3a7a77ab908497a3aaa397a9a7908a81b6991bbbb53240ba69ba7a3a078a4a86911bbbb53249ba99478a561bbbbb5324967a9a007a78169abbbbb5\n"
        "Encoded Fan: 09a3a184abaa958a4a8a5b61bbbbb5324aaa6967ab89116991bbbb5324a1a6a9a278a8a56a5a5bbbb5324a2aa770a929b70b79ba2816bbbbbb5\n"
        "Encoded Laptop: 01a3aaa7a6aa84aba3958a4936bbbbbb5324a2a7a6aba3a0781a4a861bbbbb5324967a9a007a78a46a81bbbb532497aa988a8699bbbbb5324a0aa9889361bbbbb5\n"
        "Encoded Aircon: 04a9ab97a6a18402a7988a4a8bbb6bbbbbb5324aaa6967ab89a1b61bbbbb532479494a997a97a197908a56991bbbb5324a1a6a9a278a5a86a4bbbbb532494a99ba77ab8a86bbbbbb5\n"
        "Encoded Fridge: 09aba90aa07840ba69b989578a5bb6bbbbbb5324aaa6967ab8a41b6bbbbbb5324a1a6a9a278a89a6bbbbbb5324a7795aa92aba3a1a07803a49a6bbbbbb5\n"
        "decodeHuffman: Fan:(rpm:1230.500000), (power:45.750000), (noise:23.330000), (speed_levels:5.000000)\n"
        "decodeHuffman: Battery:(capacity:250.750000), (voltage:12.450000), (life:3.500000), (weight:5.800000)\n"
        "decodeHuffman: Aircon:(btu:12000.000000), (power:850.500000), (efficiency:3.750000), (noise:32.100000), (filter:2.000000)\n"
        "decodeHuffman: Laptop:(ram:16.000000), (storage:512.500000), (weight:1.250000), (cpu:2.700000), (gpu:6.500000)\n"
        "[rpm: 1230.500000, power: 45.750000, noise: 23.330000, speed_levels: 5.000000, capacity: 250.750000, voltage: 12.450000, life: 3.500000, weight: 5.800000, btu: 12000.000000, power: 850.500000, efficiency: 3.750000, noise: 32.100000, filter: 2.000000, ram: 16.000000, storage: 512.500000, weight: 1.250000, cpu: 2.700000, gpu: 6.500000]\n";

    //! output
    stringstream ss;
    ss << compressor.productToString(carAttrs, "Car") << endl;
    ss << compressor.productToString(batteryAttrs, "Battery") << endl;
    ss << compressor.productToString(fanAttrs, "Fan") << endl;
    ss << compressor.productToString(laptopAttrs, "Laptop") << endl;
    ss << compressor.productToString(airconAttrs, "Aircon") << endl;
    ss << compressor.productToString(fridgeAttrs, "Fridge") << endl;

    string encodedCar    = compressor.encodeHuffman(carAttrs,    "Car");
    string encodedBattery= compressor.encodeHuffman(batteryAttrs,"Battery");
    string encodedFan    = compressor.encodeHuffman(fanAttrs,    "Fan");
    string encodedLaptop = compressor.encodeHuffman(laptopAttrs, "Laptop");
    string encodedAircon = compressor.encodeHuffman(airconAttrs, "Aircon");
    string encodedFridge = compressor.encodeHuffman(fridgeAttrs, "Fridge");

    ss << "Encoded Car: "    << encodedCar    << endl;
    ss << "Encoded Battery: "<< encodedBattery<< endl;
    ss << "Encoded Fan: "    << encodedFan    << endl;
    ss << "Encoded Laptop: " << encodedLaptop << endl;
    ss << "Encoded Aircon: " << encodedAircon << endl;
    ss << "Encoded Fridge: " << encodedFridge << endl;

    string nameOutput;
    List1D<InventoryAttribute> attributesOutput;
    ss << "decodeHuffman: " << compressor.decodeHuffman(encodedFan, attributesOutput, nameOutput) << endl;
    ss << "decodeHuffman: " << compressor.decodeHuffman(encodedBattery, attributesOutput, nameOutput) << endl;
    ss << "decodeHuffman: " << compressor.decodeHuffman(encodedAircon, attributesOutput, nameOutput) << endl;
    ss << "decodeHuffman: " << compressor.decodeHuffman(encodedLaptop, attributesOutput, nameOutput) << endl;
    ss << attributesOutput.toString() << endl;

    string output = ss.str();

    cout << "Expected:\n" << expect;
    cout << "Actual:\n" << output;
    if (output == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}