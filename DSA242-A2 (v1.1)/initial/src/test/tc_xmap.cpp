#include "test/tc_xmap.h"

#include "hash/xMap.h"
#include "util/Point.h"
#include "util/ArrayLib.h"
#include "util/sampleFunc.h"
#include "util/FuncLib.h"

void newINT_delete(int* value) { delete value; }
bool newINT_EQ(int*& a, int*& b) { return *a == *b; }
int newINT_keyHash(int*& key, int capacity) { return *key % capacity; }
string newINT_toString(int*& key) { return "n_" + to_string(*key); }

int hashFunc(int& key, int tablesize) {
    return key % tablesize;
}

void simpleMap() {
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};

    xMap<int, int> map(&hashFunc);
    for (int idx = 0; idx < 6; idx++) {
        map.put(keys[idx], values[idx]);
    }
    map.println();
    DLinkedList<int> list = map.clashes();
    list.println();

}

void hashDemo1() {
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};
    xMap<int, int> hash(&xMap<int, int>::simpleHash);
    for (int idx = 0; idx < 8; idx++) {
        hash.put(keys[idx], values[idx]);
    }
    hash.println();
}



int hashFunc(int*& item, int size) {
    return *item % size;
}

bool keyEQ(int*& lhs, int*& rhs) {
    return *lhs == *rhs;
}

void deleteKey(int *key) {
    delete key;
}

string key2str(int*& item) {
    stringstream os;
    os << *item;
    return os.str();
}

bool valueEQ(int*& lhs, int*& rhs) {
    return *lhs == *rhs;
}

string value2str(int*& item) {
    stringstream os;
    os << *item;
    return os.str();
}

void hashDemo2() {
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};

    xMap<int, int*> hashMap(
            &xMap<int, int*>::simpleHash,
            0.75,
            &valueEQ,
            &xMap<int, int*>::freeValue,
            0, //keyEQ
            0 //deleteKeys
            );
    for (int idx = 0; idx < 8; idx++) {
        hashMap.put(keys[idx], new int(values[idx]));
    }
    hashMap.println(0, &value2str);
}

void hashDemo3() {
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};

    xMap<int*, int*> hashMap(
            &hashFunc,
            0.75,
            &valueEQ,
            &xMap<int*, int*>::freeValue,
            &keyEQ,
            &xMap<int*, int*>::freeKey
            );
    for (int idx = 0; idx < 8; idx++) {
        hashMap.put(new int(keys[idx]), new int(values[idx]));
    }
    hashMap.println(&key2str, &value2str);
    int* pkey = new int(42);
    hashMap.remove(pkey, &deleteKey);
    delete pkey;
    hashMap.println(&key2str, &value2str);
}

void hashDemo4() {
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    Point * values[] = {
        new Point(2.3, 4.5), new Point(4.2, 6.7),
        new Point(5.2, 7.2), new Point(9.1, 1.8),
        new Point(8.9, 9.1), new Point(8.1, 3.1),
        new Point(3.3, 5.4), new Point(7.3, 4.2)
    };

    xMap<int*, Point*> hashMap(
            &hashFunc,
            0.75,
            &Point::pointEQ,
            &xMap<int*, Point*>::freeValue,
            &keyEQ,
            &xMap<int*, Point*>::freeKey
            );
    for (int idx = 0; idx < 8; idx++) {
        hashMap.put(new int(keys[idx]), values[idx]);
    }
    hashMap.println(&key2str, &point2str);
}

void hashDemo5() {
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};
    xMap<int, int> hash(&xMap<int, int>::simpleHash);
    for (int idx = 0; idx < 8; idx++) {
        hash.put(keys[idx], values[idx]);
    }

    DLinkedList<int> keyset = hash.keys();
    cout << "Keys: " << keyset.toString() << endl;
    DLinkedList<int> valueset = hash.values();
    cout << "Values: " << valueset.toString() << endl;
}

void hashDemo6() {
    int count = 100000;
    //int count = 100;
    int *keys = genIntArray(count, 0, 1999999999);
    xMap<int, int*> hash(&xMap<int, int*>::simpleHash);
    for (int idx = 0; idx < count; idx++) {
        //cout << idx << endl;
        hash.put(keys[idx], 0);
    }
    //hash.println();
    

    DLinkedList<int> clashes = hash.clashes();
    int max = -1;
    for (DLinkedList<int>::Iterator it = clashes.begin(); it != clashes.end(); it++) {
        int item = *it;
        if (item > max) max = item;
    }

    cout << "table size: " << hash.getCapacity() << endl;
    cout << "current count: " << hash.size() << endl;
    cout << "real load factor: " << (float) hash.size() / hash.getCapacity() << endl;
    cout << "max #collisions: " << max << endl;
    delete []keys;
}

int stringHash(string& str, int size) {
    long long int sum = 0;
    for (int idx = 0; idx < str.length(); idx++) sum += str[idx];
    return sum % size;
}

//https://raw.githubusercontent.com/icyrockcom/country-capitals/master/data/country-list.csv

string countries[] = {
    "country", "capital", "type",
    "Abkhazia", "Sukhumi", "countryCapital",
    "Afghanistan", "Kabul", "countryCapital",
    "Akrotiri and Dhekelia", "Episkopi Cantonment", "countryCapital",
    "Albania", "Tirana", "countryCapital",
    "Algeria", "Algiers", "countryCapital",
    "American Samoa", "Pago Pago", "countryCapital",
    "Andorra", "Andorra la Vella", "countryCapital",
    "Angola", "Luanda", "countryCapital",
    "Anguilla", "The Valley", "countryCapital",
    "Antigua and Barbuda", "St. John's", "countryCapital",
    "Argentina", "Buenos Aires", "countryCapital",
    "Armenia", "Yerevan", "countryCapital",
    "Aruba", "Oranjestad", "countryCapital",
    "Ascension Island", "Georgetown", "countryCapital",
    "Australia", "Canberra", "countryCapital",
    "Austria", "Vienna", "countryCapital",
    "Azerbaijan", "Baku", "countryCapital",
    "Bahamas", "Nassau", "countryCapital",
    "Bahrain", "Manama", "countryCapital",
    "Bangladesh", "Dhaka", "countryCapital",
    "Barbados", "Bridgetown", "countryCapital",
    "Belarus", "Minsk", "countryCapital",
    "Belgium", "Brussels", "countryCapital",
    "Belize", "Belmopan", "countryCapital",
    "Benin", "Porto-Novo", "countryCapital",
    "Bermuda", "Hamilton", "countryCapital",
    "Bhutan", "Thimphu", "countryCapital",
    "Bolivia", "Sucre", "countryCapital",
    "Bolivia", "La Paz", "countryCapital",
    "Bosnia and Herzegovina", "Sarajevo", "countryCapital",
    "Botswana", "Gaborone", "countryCapital",
    "Brazil", "Brasília", "countryCapital",
    "British Virgin Islands", "Road Town", "countryCapital",
    "Brunei", "Bandar Seri Begawan", "countryCapital",
    "Bulgaria", "Sofia", "countryCapital",
    "Burkina Faso", "Ouagadougou", "countryCapital",
    "Burundi", "Bujumbura", "countryCapital",
    "Cambodia", "Phnom Penh", "countryCapital",
    "Cameroon", "Yaoundé", "countryCapital",
    "Canada", "Ottawa", "countryCapital",
    "Cape Verde", "Praia", "countryCapital",
    "Cayman Islands", "George Town", "countryCapital",
    "Central African Republic", "Bangui", "countryCapital",
    "Chad", "N'Djamena", "countryCapital",
    "Chile", "Santiago", "countryCapital",
    "China", "Beijing", "countryCapital",
    "Christmas Island", "Flying Fish Cove", "countryCapital",
    "Cocos (Keeling) Islands", "West Island", "countryCapital",
    "Colombia", "Bogotá", "countryCapital",
    "Comoros", "Moroni", "countryCapital",
    "Cook Islands", "Avarua", "countryCapital",
    "Costa Rica", "San José", "countryCapital",
    "Croatia", "Zagreb", "countryCapital",
    "Cuba", "Havana", "countryCapital",
    "Curaçao", "Willemstad", "countryCapital",
    "Cyprus", "Nicosia", "countryCapital",
    "Czech Republic", "Prague", "countryCapital",
    "Côte d'Ivoire", "Yamoussoukro", "countryCapital",
    "Democratic Republic of the Congo", "Kinshasa", "countryCapital",
    "Denmark", "Copenhagen", "countryCapital",
    "Djibouti", "Djibouti", "countryCapital",
    "Dominica", "Roseau", "countryCapital",
    "Dominican Republic", "Santo Domingo", "countryCapital",
    "East Timor (Timor-Leste)", "Dili", "countryCapital",
    "Easter Island", "Hanga Roa", "countryCapital",
    "Ecuador", "Quito", "countryCapital",
    "Egypt", "Cairo", "countryCapital",
    "El Salvador", "San Salvador", "countryCapital",
    "Equatorial Guinea", "Malabo", "countryCapital",
    "Eritrea", "Asmara", "countryCapital",
    "Estonia", "Tallinn", "countryCapital",
    "Ethiopia", "Addis Ababa", "countryCapital",
    "Falkland Islands", "Stanley", "countryCapital",
    "Faroe Islands", "Tórshavn", "countryCapital",
    "Federated States of Micronesia", "Palikir", "countryCapital",
    "Fiji", "Suva", "countryCapital",
    "Finland", "Helsinki", "countryCapital",
    "France", "Paris", "countryCapital",
    "French Guiana", "Cayenne", "countryCapital",
    "French Polynesia", "Papeete", "countryCapital",
    "Gabon", "Libreville", "countryCapital",
    "Gambia", "Banjul", "countryCapital",
    "Georgia", "Tbilisi", "countryCapital",
    "Germany", "Berlin", "countryCapital",
    "Ghana", "Accra", "countryCapital",
    "Gibraltar", "Gibraltar", "countryCapital",
    "Greece", "Athens", "countryCapital",
    "Greenland", "Nuuk", "countryCapital",
    "Grenada", "St. George's", "countryCapital",
    "Guam", "Hagåtña", "countryCapital",
    "Guatemala", "Guatemala City", "countryCapital",
    "Guernsey", "St. Peter Port", "countryCapital",
    "Guinea", "Conakry", "countryCapital",
    "Guinea-Bissau", "Bissau", "countryCapital",
    "Guyana", "Georgetown", "countryCapital",
    "Haiti", "Port-au-Prince", "countryCapital",
    "Honduras", "Tegucigalpa", "countryCapital",
    "Hungary", "Budapest", "countryCapital",
    "Iceland", "Reykjavík", "countryCapital",
    "India", "New Delhi", "countryCapital",
    "Indonesia", "Jakarta", "countryCapital",
    "Iran", "Tehran", "countryCapital",
    "Iraq", "Baghdad", "countryCapital",
    "Ireland", "Dublin", "countryCapital",
    "Isle of Man", "Douglas", "countryCapital",
    "Israel", "Jerusalem", "countryCapital",
    "Italy", "Rome", "countryCapital",
    "Jamaica", "Kingston", "countryCapital",
    "Japan", "Tokyo", "countryCapital",
    "Jersey", "St. Helier", "countryCapital",
    "Jordan", "Amman", "countryCapital",
    "Kazakhstan", "Astana", "countryCapital",
    "Kenya", "Nairobi", "countryCapital",
    "Kiribati", "Tarawa", "countryCapital",
    "Kosovo", "Pristina", "countryCapital",
    "Kuwait", "Kuwait City", "countryCapital",
    "Kyrgyzstan", "Bishkek", "countryCapital",
    "Laos", "Vientiane", "countryCapital",
    "Latvia", "Riga", "countryCapital",
    "Lebanon", "Beirut", "countryCapital",
    "Lesotho", "Maseru", "countryCapital",
    "Liberia", "Monrovia", "countryCapital",
    "Libya", "Tripoli", "countryCapital",
    "Liechtenstein", "Vaduz", "countryCapital",
    "Lithuania", "Vilnius", "countryCapital",
    "Luxembourg", "Luxembourg", "countryCapital",
    "Macedonia", "Skopje", "countryCapital",
    "Madagascar", "Antananarivo", "countryCapital",
    "Malawi", "Lilongwe", "countryCapital",
    "Malaysia", "Kuala Lumpur", "countryCapital",
    "Maldives", "Malé", "countryCapital",
    "Mali", "Bamako", "countryCapital",
    "Malta", "Valletta", "countryCapital",
    "Marshall Islands", "Majuro", "countryCapital",
    "Mauritania", "Nouakchott", "countryCapital",
    "Mauritius", "Port Louis", "countryCapital",
    "Mexico", "Mexico City", "countryCapital",
    "Moldova", "Chisinau", "countryCapital",
    "Monaco", "Monaco", "countryCapital",
    "Mongolia", "Ulaanbaatar", "countryCapital",
    "Montenegro", "Podgorica", "countryCapital",
    "Montserrat", "Plymouth", "countryCapital",
    "Morocco", "Rabat", "countryCapital",
    "Mozambique", "Maputo", "countryCapital",
    "Myanmar", "Naypyidaw", "countryCapital",
    "Nagorno-Karabakh Republic", "Stepanakert", "countryCapital",
    "Namibia", "Windhoek", "countryCapital",
    "Nauru", "Yaren", "countryCapital",
    "Nepal", "Kathmandu", "countryCapital",
    "Netherlands", "Amsterdam", "countryCapital",
    "New Caledonia", "Nouméa", "countryCapital",
    "New Zealand", "Wellington", "countryCapital",
    "Nicaragua", "Managua", "countryCapital",
    "Niger", "Niamey", "countryCapital",
    "Nigeria", "Abuja", "countryCapital",
    "Niue", "Alofi", "countryCapital",
    "Norfolk Island", "Kingston", "countryCapital",
    "North Korea", "Pyongyang", "countryCapital",
    "Northern Cyprus", "Nicosia", "countryCapital",
    "United Kingdom Northern Ireland", "Belfast", "countryCapital",
    "Northern Mariana Islands", "Saipan", "countryCapital",
    "Norway", "Oslo", "countryCapital",
    "Oman", "Muscat", "countryCapital",
    "Pakistan", "Islamabad", "countryCapital",
    "Palau", "Ngerulmud", "countryCapital",
    "Palestine", "Jerusalem", "countryCapital",
    "Panama", "Panama City", "countryCapital",
    "Papua New Guinea", "Port Moresby", "countryCapital",
    "Paraguay", "Asunción", "countryCapital",
    "Peru", "Lima", "countryCapital",
    "Philippines", "Manila", "countryCapital",
    "Pitcairn Islands", "Adamstown", "countryCapital",
    "Poland", "Warsaw", "countryCapital",
    "Portugal", "Lisbon", "countryCapital",
    "Puerto Rico", "San Juan", "countryCapital",
    "Qatar", "Doha", "countryCapital",
    "Republic of China (Taiwan)", "Taipei", "countryCapital",
    "Republic of the Congo", "Brazzaville", "countryCapital",
    "Romania", "Bucharest", "countryCapital",
    "Russia", "Moscow", "countryCapital",
    "Rwanda", "Kigali", "countryCapital",
    "Saint Barthélemy", "Gustavia", "countryCapital",
    "Saint Helena", "Jamestown", "countryCapital",
    "Saint Kitts and Nevis", "Basseterre", "countryCapital",
    "Saint Lucia", "Castries", "countryCapital",
    "Saint Martin", "Marigot", "countryCapital",
    "Saint Pierre and Miquelon", "St. Pierre", "countryCapital",
    "Saint Vincent and the Grenadines", "Kingstown", "countryCapital",
    "Samoa", "Apia", "countryCapital",
    "San Marino", "San Marino", "countryCapital",
    "Saudi Arabia", "Riyadh", "countryCapital",
    "Scotland", "Edinburgh", "countryCapital",
    "Senegal", "Dakar", "countryCapital",
    "Serbia", "Belgrade", "countryCapital",
    "Seychelles", "Victoria", "countryCapital",
    "Sierra Leone", "Freetown", "countryCapital",
    "Singapore", "Singapore", "countryCapital",
    "Sint Maarten", "Philipsburg", "countryCapital",
    "Slovakia", "Bratislava", "countryCapital",
    "Slovenia", "Ljubljana", "countryCapital",
    "Solomon Islands", "Honiara", "countryCapital",
    "Somalia", "Mogadishu", "countryCapital",
    "Somaliland", "Hargeisa", "countryCapital",
    "South Africa", "Pretoria", "countryCapital",
    "South Georgia and the South Sandwich Islands", "Grytviken", "countryCapital",
    "South Korea", "Seoul", "countryCapital",
    "South Ossetia", "Tskhinvali", "countryCapital",
    "South Sudan South Sudan", "Juba", "countryCapital",
    "Spain", "Madrid", "countryCapital",
    "Sri Lanka", "Sri Jayawardenapura Kotte", "countryCapital",
    "Sudan", "Khartoum", "countryCapital",
    "Suriname", "Paramaribo", "countryCapital",
    "Swaziland", "Mbabane", "countryCapital",
    "Sweden", "Stockholm", "countryCapital",
    "Switzerland", "Bern", "countryCapital",
    "Syria", "Damascus", "countryCapital",
    "São Tomé and Príncipe", "São Tomé", "countryCapital",
    "Tajikistan", "Dushanbe", "countryCapital",
    "Tanzania", "Dodoma", "countryCapital",
    "Thailand", "Bangkok", "countryCapital",
    "Togo", "Lomé", "countryCapital",
    "Tonga", "Nukuʻalofa", "countryCapital",
    "Transnistria", "Tiraspol", "countryCapital",
    "Trinidad and Tobago", "Port of Spain", "countryCapital",
    "Tristan da Cunha", "Edinburgh of the Seven Seas", "countryCapital",
    "Tunisia", "Tunis", "countryCapital",
    "Turkey", "Ankara", "countryCapital",
    "Turkmenistan", "Ashgabat", "countryCapital",
    "Turks and Caicos Islands", "Cockburn Town", "countryCapital",
    "Tuvalu", "Funafuti", "countryCapital",
    "Uganda", "Kampala", "countryCapital",
    "Ukraine", "Kiev", "countryCapital",
    "United Arab Emirates", "Abu Dhabi", "countryCapital",
    "United Kingdom; England", "London", "countryCapital",
    "United States", "Washington, D.C.", "countryCapital",
    "United States Virgin Islands", "Charlotte Amalie", "countryCapital",
    "Uruguay", "Montevideo", "countryCapital",
    "Uzbekistan", "Tashkent", "countryCapital",
    "Vanuatu", "Port Vila", "countryCapital",
    "Vatican City", "Vatican City", "countryCapital",
    "Venezuela", "Caracas", "countryCapital",
    "Vietnam", "Hanoi", "countryCapital",
    "Wales", "Cardiff", "countryCapital",
    "Wallis and Futuna", "Mata-Utu", "countryCapital",
    "Western Sahara", "El Aaiún", "countryCapital",
    "Yemen", "Sanaá", "countryCapital",
    "Zambia", "Lusaka", "countryCapital",
    "Zimbabwe", "Harare", "countryCapital"
};
int ncountry = 248;


void hashDemo7() {
    xMap<string, string> map(&stringHash);
    for (int c = 0; c < ncountry * 3; c += 3) {
        string ten = countries[c];
        string capital = countries[c + 1];
        map.put(ten, capital);
    }
    DLinkedList<int> clashes = map.clashes();
    int max = -1;
    for (DLinkedList<int>::Iterator it = clashes.begin(); it != clashes.end(); it++) {
        int item = *it;
        if (item > max) max = item;
    }
    cout << "table size: " << map.getCapacity() << endl;
    cout << "current count: " << map.size() << endl;
    cout << "real load factor: " << (float) map.size() / map.getCapacity() << endl;
    cout << "max #collisions: " << max << endl;

    string country = "Vietnam";
    cout << "Capital of " << country << " is " << map.get("Vietnam") << endl;
}

int countryHash(string& country, int size){
    int sum =0;
    for(int idx=0; idx < country.length(); idx++)
        sum += country[idx];
    return sum%size;
}

void countryDemo(){
    xMap<string, string> map(&countryHash);
    for(int idx=0; idx < ncountry*3; idx+=3){
        string name = countries[idx];
        string capital = countries[idx+1];
        map.put(name, capital);
    }
    map.println();
    
    DLinkedList<int> list = map.clashes();
    int max = -1;
    for(DLinkedList<int>::Iterator it= list.begin(); it != list.end(); it++){
        if (*it > max) max = *it;
    }
    cout << "Size: " << map.size() << endl;
    cout << "MAX COLLISION: " << max << endl;
    
    string countryname = "Thailand";
    cout << countryname << " : " << map.get(countryname) << endl;
}

void test_hash01() {
    cout << "hash01";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash);

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   10\n"
        "size:       0\n"
        "0   : \n"
        "1   : \n"
        "2   : \n"
        "3   : \n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n";

    //! output
    string output = "";
    output = "\n" + hash.toString();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;

    // Print whether the test passed
    if (output == expect) {
        cout << "TEST PASSED" << endl;
    } else {
        cout << "TEST FAILED" << endl;
    }
}

void test_hash02() {
    cout << "hash02";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash);
    xMap<int, string> copy(hash);

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   10\n"
        "size:       0\n"
        "0   : \n"
        "1   : \n"
        "2   : \n"
        "3   : \n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n";

    //! output
    string output = "\n" + copy.toString();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n"   << output << endl;

    if (output == expect) {
        cout << "TEST PASSED" << endl;
    } else {
        cout << "TEST FAILED" << endl;
    }
}

void test_hash03() {
    cout << "hash03";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash);
    xMap<int, string> copy(xMap<int, string>::intKeyHash);
    copy = hash;

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   10\n"
        "size:       0\n"
        "0   : \n"
        "1   : \n"
        "2   : \n"
        "3   : \n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n";

    //! output
    string output = "\n" + hash.toString();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n"   << output << endl;

    if (output == expect) {
        cout << "TEST PASSED" << endl;
    } else {
        cout << "TEST FAILED" << endl;
    }
}

void test_hash04() {
    cout << "hash04";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash);
    hash.put(1, "votien1");

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   10\n"
        "size:       1\n"
        "0   : \n"
        "1   :  (1,votien1)\n"
        "2   : \n"
        "3   : \n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n";

    //! output
    string output = "\n" + hash.toString();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n"   << output << endl;

    if (output == expect) {
        cout << "TEST PASSED" << endl;
    } else {
        cout << "TEST FAILED" << endl;
    }
}

void test_hash05() {
    cout << "hash05";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash);
    hash.put(1,  "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(2,  "votien2");
    hash.put(10, "votien10");

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   10\n"
        "size:       5\n"
        "0   :  (10,votien10)\n"
        "1   :  (1,votien1); (11,votien11); (21,votien21)\n"
        "2   :  (2,votien2)\n"
        "3   : \n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n";

    //! output
    string output = "\n" + hash.toString();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n"   << output << endl;

    if (output == expect) {
        cout << "TEST PASSED" << endl;
    } else {
        cout << "TEST FAILED" << endl;
    }
}

void test_hash06() {
    cout << "hash06";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1,  "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   15\n"
        "size:       7\n"
        "0   : \n"
        "1   :  (1,votien1); (31,votien31); (61,votien61)\n"
        "2   : \n"
        "3   : \n"
        "4   : \n"
        "5   : \n"
        "6   :  (21,votien21); (51,votien51)\n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "10  : \n"
        "11  :  (11,votien11); (41,votien41)\n"
        "12  : \n"
        "13  : \n"
        "14  : \n"
        "==================================================\n";

    //! output
    string output = "\n" + hash.toString();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n"   << output << endl;

    if (output == expect) {
        cout << "TEST PASSED" << endl;
    } else {
        cout << "TEST FAILED" << endl;
    }
}

void test_hash07() {
    cout << "hash07";
    //! data
    xMap<int*, string> hash(
        &newINT_keyHash,
        0.45,
        0,
        xMap<int*, string>::freeKey
    );
    hash.put(new int(1),  "votien1");
    hash.put(new int(11), "votien11");
    hash.put(new int(3),  "votien3");

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   10\n"
        "size:       3\n"
        "0   : \n"
        "1   :  (n_1,votien1); (n_11,votien11)\n"
        "2   : \n"
        "3   :  (n_3,votien3)\n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n";

    //! output
    string output = "\n" + hash.toString(&newINT_toString);

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n"   << output << endl;

    if (output == expect) {
        cout << "TEST PASSED" << endl;
    } else {
        cout << "TEST FAILED" << endl;
    }
}

void test_hash08() {
    cout << "hash08";
    //! data
    xMap<int*, string> hash(
        &newINT_keyHash,
        1,
        0,
        xMap<int*, string>::freeKey,
        &newINT_EQ
    );
    hash.put(new int(1),  "votien1");
    hash.put(new int(11), "votien11");
    hash.put(new int(3),  "votien3");

    // first replace
    int* key1 = new int(1);
    string old1 = hash.put(key1, "votien_1");
    delete key1;

    hash.put(new int(21), "votien21");
    hash.put(new int(31), "votien31");
    hash.put(new int(41), "votien41");
    hash.put(new int(51), "votien51");

    // second replace
    int* key2 = new int(11);
    string old2 = hash.put(key2, "votien_11");
    delete key2;

    xMap<int*, string> copy(&newINT_keyHash);
    copy = hash;

    //! expect
    string expect =
        "votien1votien11\n"
        "==================================================\n"
        "capacity:   10\n"
        "size:       7\n"
        "0   : \n"
        "1   :  (n_1,votien_1); (n_11,votien_11); (n_21,votien21); (n_31,votien31); (n_41,votien41); (n_51,votien51)\n"
        "2   : \n"
        "3   :  (n_3,votien3)\n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n";

    //! output
    string output = old1 + old2 + "\n" + copy.toString(&newINT_toString);

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n"   << output << endl;

    if (output == expect) {
        cout << "TEST PASSED" << endl;
    } else {
        cout << "TEST FAILED" << endl;
    }
}

void test_hash09() {
    cout << "hash09";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1,  "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2,  "votien2");
    hash.put(3,  "votien3");
    hash.put(1,  "votien_1");

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   15\n"
        "size:       9\n"
        "0   : \n"
        "1   :  (1,votien_1); (31,votien31); (61,votien61)\n"
        "2   :  (2,votien2)\n"
        "3   :  (3,votien3)\n"
        "4   : \n"
        "5   : \n"
        "6   :  (21,votien21); (51,votien51)\n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "10  : \n"
        "11  :  (11,votien11); (41,votien41)\n"
        "12  : \n"
        "13  : \n"
        "14  : \n"
        "==================================================\n";

    //! output
    string output = "\n" + hash.toString();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n"   << output << endl;

    if (output == expect) {
        cout << "TEST PASSED" << endl;
    } else {
        cout << "TEST FAILED" << endl;
    }
}

void test_hash10() {
    cout << "hash10";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1,  "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2,  "votien2");
    hash.put(3,  "votien3");
    hash.put(1,  "votien_1");

    //! expect
    string expect = "votien_1";

    //! output
    string output;
    try {
        output = hash.get(1);
    } catch (const KeyNotFound& e) {
        output = string("Caught exception: ") + e.what();
    }

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n"   << output << endl;

    if (output == expect) {
        cout << "TEST PASSED" << endl;
    } else {
        cout << "TEST FAILED" << endl;
    }
}

void test_hash11() {
    cout << "hash11";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1,  "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2,  "votien2");
    hash.put(3,  "votien3");
    hash.put(1,  "votien_1");

    //! expect
    string expect = "Caught exception: key (0) is not found";

    //! output
    string output;
    try {
        output = hash.get(0);
    } catch (const KeyNotFound& e) {
        output = string("Caught exception: ") + e.what();
    }

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n"   << output << endl;

    if (output == expect) {
        cout << "TEST PASSED" << endl;
    } else {
        cout << "TEST FAILED" << endl;
    }
}

void test_hash12() {
    cout << "hash12";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1,  "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2,  "votien2");
    hash.put(3,  "votien3");
    hash.put(1,  "votien_1");

    //! expect
    string expect =
        "votien_1\n"
        "==================================================\n"
        "capacity:   15\n"
        "size:       8\n"
        "0   : \n"
        "1   :  (31,votien31); (61,votien61)\n"
        "2   :  (2,votien2)\n"
        "3   :  (3,votien3)\n"
        "4   : \n"
        "5   : \n"
        "6   :  (21,votien21); (51,votien51)\n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "10  : \n"
        "11  :  (11,votien11); (41,votien41)\n"
        "12  : \n"
        "13  : \n"
        "14  : \n"
        "==================================================\n";

    //! output
    string output;
    try {
        output = hash.remove(1) + "\n";
    } catch (const KeyNotFound& e) {
        output = string("Caught exception: ") + e.what() + "\n";
    }
    output += hash.toString();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n"   << output << endl;

    if (output == expect) {
        cout << "TEST PASSED" << endl;
    } else {
        cout << "TEST FAILED" << endl;
    }
}

void test_hash13() {
    cout << "TEST HASH13";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1, "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2, "votien2");
    hash.put(3, "votien3");
    hash.put(1, "votien_1");

    //! expect
    string expect =
        "Caught exception: key (0) is not found\n"
        "==================================================\n"
        "capacity:   15\n"
        "size:       9\n"
        "0   : \n"
        "1   :  (1,votien_1); (31,votien31); (61,votien61)\n"
        "2   :  (2,votien2)\n"
        "3   :  (3,votien3)\n"
        "4   : \n"
        "5   : \n"
        "6   :  (21,votien21); (51,votien51)\n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "10  : \n"
        "11  :  (11,votien11); (41,votien41)\n"
        "12  : \n"
        "13  : \n"
        "14  : \n"
        "==================================================\n";

    //! output
    stringstream ss;
    try {
        ss << hash.remove(0) << endl;
    } catch (const KeyNotFound& e) {
        ss << "Caught exception: " << e.what() << endl;
    }
    ss << hash.toString();
    string output = ss.str();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash14() {
    cout << "TEST HASH14";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1, "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2, "votien2");
    hash.put(3, "votien3");
    hash.put(1, "votien_1");

    //! expect
    string expect = "True";

    //! output
    string output = (hash.containsKey(51) ? "True" : "False");

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash15() {
    cout << "TEST HASH15";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1, "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2, "votien2");
    hash.put(3, "votien3");
    hash.put(1, "votien_1");

    //! expect
    string expect = "False";

    //! output
    string output = (hash.containsKey(71) ? "True" : "False");

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash16() {
    cout << "TEST HASH16";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1, "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2, "votien2");
    hash.put(3, "votien3");
    hash.put(1, "votien_1");

    //! expect
    string expect = "False";

    //! output
    string output = (hash.containsKey(22) ? "True" : "False");

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash17() {
    cout << "TEST HASH17";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1, "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2, "votien2");
    hash.put(3, "votien3");
    hash.put(1, "votien_1");

    //! expect
    string expect = "True";

    //! output
    string output = (hash.containsValue("votien_1") ? "True" : "False");

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash18() {
    cout << "TEST HASH18";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1, "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2, "votien2");
    hash.put(3, "votien3");
    hash.put(1, "votien_1");

    //! expect
    string expect = "False";

    //! output
    string output = (hash.containsValue("votien_2") ? "True" : "False");

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash19() {
    cout << "TEST HASH19";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1, "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2, "votien2");
    hash.put(3, "votien3");
    hash.put(1, "votien_1");

    //! expect
    string expect = "False";

    //! output
    string output = (hash.containsValue("votien_71") ? "True" : "False");

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash20() {
    cout << "TEST HASH20";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1, "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2, "votien2");
    hash.put(3, "votien3");
    hash.put(1, "votien_1");

    //! expect
    string expect = "[1, 31, 61, 2, 3, 21, 51, 11, 41]";

    //! output
    string output = hash.keys().toString();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash21() {
    cout << "TEST HASH21";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1, "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2, "votien2");
    hash.put(3, "votien3");
    hash.put(1, "votien_1");

    //! expect
    string expect =
        "[votien_1, votien31, votien61, votien2, votien3, votien21, votien51, votien11, votien41]";

    //! output
    string output = hash.values().toString();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash22() {
    cout << "TEST HASH22";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.6);
    hash.put(1, "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2, "votien2");
    hash.put(3, "votien3");
    hash.put(1, "votien_1");

    //! expect
    string expect = "[0, 3, 1, 1, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0]";

    //! output
    string output = hash.clashes().toString();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash23() {
    cout << "TEST HASH23";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.5);
    hash.put(1, "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2, "votien2");
    hash.put(3, "votien3");
    hash.put(1, "votien_1");

    //! expect
    string expect =
        "0\n"
        "[1, 2, 3, 51, 31, 11, 61, 41, 21]\n"
        "[votien_1, votien2, votien3, votien51, votien31, votien11, votien61, votien41, votien21]\n"
        "[0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1]";

    //! output
    stringstream ss23;
    ss23 << hash.empty() << endl;
    ss23 << hash.keys().toString() << endl;
    ss23 << hash.values().toString() << endl;
    ss23 << hash.clashes().toString();
    string output = ss23.str();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash24() {
    cout << "TEST HASH24";
    //! data
    xMap<int, string> hash(xMap<int, string>::intKeyHash, 0.5);
    hash.put(1, "votien1");
    hash.put(11, "votien11");
    hash.put(21, "votien21");
    hash.put(31, "votien31");
    hash.put(41, "votien41");
    hash.put(51, "votien51");
    hash.put(61, "votien61");
    hash.put(2, "votien2");
    hash.put(3, "votien3");
    hash.put(1, "votien_1");
    hash.clear();

    //! expect
    string expect =
        "1\n"
        "[]\n"
        "[]\n"
        "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0]";

    //! output
    stringstream ss24;
    ss24 << hash.empty() << endl;
    ss24 << hash.keys().toString() << endl;
    ss24 << hash.values().toString() << endl;
    ss24 << hash.clashes().toString();
    string output = ss24.str();

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash25() {
    cout << "TEST HASH25";
    //! data
    xMap<int*, int*> hash(
        &newINT_keyHash, 1, &newINT_EQ,
        xMap<int*, int*>::freeKey,
        &newINT_EQ,
        xMap<int*, int*>::freeValue
    );
    int* key1   = new int(1);
    int* key11  = new int(11);
    int* key21  = new int(21);
    int* key31  = new int(31);
    int* key41  = new int(41);
    int* key51  = new int(51);
    int* key61  = new int(61);
    int* key2   = new int(2);
    int* key3   = new int(1);

    int* value1  = new int(100);
    int* value11 = new int(200);
    int* value21 = new int(300);
    int* value31 = new int(400);
    int* value41 = new int(500);
    int* value51 = new int(600);
    int* value61 = new int(700);
    int* value2  = new int(800);
    int* value3  = new int(900);

    hash.put(key1,  value1);
    hash.put(key11, value11);
    hash.put(key21, value21);
    hash.put(key31, value31);
    hash.put(key41, value41);
    hash.put(key51, value51);
    hash.put(key61, value61);
    hash.put(key2,  value2);
    hash.put(key3,  value3);

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   10\n"
        "size:       8\n"
        "0   : \n"
        "1   :  (n_1,n_900); (n_11,n_200); (n_21,n_300); (n_31,n_400); (n_41,n_500); (n_51,n_600); (n_61,n_700)\n"
        "2   :  (n_2,n_800)\n"
        "3   : \n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n";

    //! output
    string output = "\n" + hash.toString(&newINT_toString, &newINT_toString);

    // cleanup
    delete value1;
    delete key3;

    cout << "Expected: \n" << expect << endl;
    cout << "Actual: \n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash26() {
    cout << "TEST HASH 26";
    //! data
    xMap<int*, int*> hash(
        &newINT_keyHash, 1, &newINT_EQ,
        xMap<int*, int*>::freeKey,
        &newINT_EQ,
        xMap<int*, int*>::freeValue
    );
    int* key1   = new int(1);
    int* key11  = new int(11);
    int* key21  = new int(21);
    int* key31  = new int(31);
    int* key41  = new int(41);
    int* key51  = new int(51);
    int* key61  = new int(61);
    int* key2   = new int(2);
    int* key3   = new int(1);

    int* value1  = new int(100);
    int* value11 = new int(200);
    int* value21 = new int(300);
    int* value31 = new int(400);
    int* value41 = new int(500);
    int* value51 = new int(600);
    int* value61 = new int(700);
    int* value2  = new int(800);
    int* value3  = new int(900);

    hash.put(key1,  value1);
    hash.put(key11, value11);
    hash.put(key21, value21);
    hash.put(key31, value31);
    hash.put(key41, value41);
    hash.put(key51, value51);
    hash.put(key61, value61);
    hash.put(key2,  value2);
    hash.put(key3,  value3);

    hash.remove(key61, &newINT_delete);

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   10\n"
        "size:       7\n"
        "0   : \n"
        "1   :  (n_1,n_900); (n_11,n_200); (n_21,n_300); (n_31,n_400); (n_41,n_500); (n_51,n_600)\n"
        "2   :  (n_2,n_800)\n"
        "3   : \n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n";

    //! output
    string output = "\n" + hash.toString(&newINT_toString, &newINT_toString);

    // cleanup
    delete value1;
    delete key3;
    delete value61;

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash27() {
    cout << "TEST HASH 27";
    //! data
    xMap<int*, int*> hash(
        &newINT_keyHash, 1, &newINT_EQ,
        xMap<int*, int*>::freeKey,
        &newINT_EQ,
        xMap<int*, int*>::freeValue
    );
    int* key1   = new int(1);
    int* key11  = new int(11);
    int* key21  = new int(21);
    int* key31  = new int(31);
    int* key41  = new int(41);
    int* key51  = new int(51);
    int* key61  = new int(61);
    int* key2   = new int(2);
    int* key3   = new int(1);

    int* value1  = new int(100);
    int* value11 = new int(200);
    int* value21 = new int(300);
    int* value31 = new int(400);
    int* value41 = new int(500);
    int* value51 = new int(600);
    int* value61 = new int(700);
    int* value2  = new int(800);
    int* value3  = new int(900);

    hash.put(key1,  value1);
    hash.put(key11, value11);
    hash.put(key21, value21);
    hash.put(key31, value31);
    hash.put(key41, value41);
    hash.put(key51, value51);
    hash.put(key61, value61);
    hash.put(key2,  value2);
    hash.put(key3,  value3);

    hash.remove(key61, &newINT_delete);
    hash.remove(key31, value31, &newINT_delete, &newINT_delete);

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   10\n"
        "size:       6\n"
        "0   : \n"
        "1   :  (n_1,n_900); (n_11,n_200); (n_21,n_300); (n_41,n_500); (n_51,n_600)\n"
        "2   :  (n_2,n_800)\n"
        "3   : \n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n";

    //! output
    string output = "\n" + hash.toString(&newINT_toString, &newINT_toString);

    // cleanup
    delete value1;
    delete key3;
    delete value61;

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash28() {
    cout << "TEST HASH 28";
    //! data
    xMap<int*, int*> hash(
        &newINT_keyHash, 1, &newINT_EQ,
        xMap<int*, int*>::freeKey,
        &newINT_EQ,
        xMap<int*, int*>::freeValue
    );
    int* key1   = new int(1);
    int* key11  = new int(11);
    int* key21  = new int(21);
    int* key31  = new int(31);
    int* key41  = new int(41);
    int* key51  = new int(51);
    int* key61  = new int(61);
    int* key2   = new int(2);
    int* key3   = new int(1);

    int* value1  = new int(100);
    int* value11 = new int(200);
    int* value21 = new int(300);
    int* value31 = new int(400);
    int* value41 = new int(500);
    int* value51 = new int(600);
    int* value61 = new int(700);
    int* value2  = new int(800);
    int* value3  = new int(900);

    hash.put(key1,  value1);
    hash.put(key11, value11);
    hash.put(key21, value21);
    hash.put(key31, value31);
    hash.put(key41, value41);
    hash.put(key51, value51);
    hash.put(key61, value61);
    hash.put(key2,  value2);
    hash.put(key3,  value3);

    hash.remove(key61, &newINT_delete);
    hash.remove(key31, value31, &newINT_delete, &newINT_delete);

    xMap<int*,int*> copy(&newINT_keyHash);
    copy = hash;

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   10\n"
        "size:       6\n"
        "0   : \n"
        "1   :  (n_1,n_900); (n_11,n_200); (n_21,n_300); (n_41,n_500); (n_51,n_600)\n"
        "2   :  (n_2,n_800)\n"
        "3   : \n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n";

    //! output
    string output = "\n" + copy.toString(&newINT_toString, &newINT_toString);

    // cleanup
    delete value1;
    delete key3;
    delete value61;

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash29() {
    cout << "TEST HASH 29";
    //! data
    xMap<int*, int*> hash(
        &newINT_keyHash, 1, &newINT_EQ,
        xMap<int*, int*>::freeKey,
        &newINT_EQ,
        xMap<int*, int*>::freeValue
    );
    int* key1   = new int(1);
    int* key11  = new int(11);
    int* key21  = new int(21);
    int* key31  = new int(31);
    int* key41  = new int(41);
    int* key51  = new int(51);
    int* key61  = new int(61);
    int* key2   = new int(2);
    int* key3   = new int(1);

    int* value1  = new int(100);
    int* value11 = new int(200);
    int* value21 = new int(300);
    int* value31 = new int(400);
    int* value41 = new int(500);
    int* value51 = new int(600);
    int* value61 = new int(700);
    int* value2  = new int(800);
    int* value3  = new int(900);

    hash.put(key1,  value1);
    hash.put(key11, value11);
    hash.put(key21, value21);
    hash.put(key31, value31);
    hash.put(key41, value41);
    hash.put(key51, value51);
    hash.put(key61, value61);
    hash.put(key2,  value2);
    hash.put(key3,  value3);

    hash.remove(key61, &newINT_delete);
    hash.remove(key31, value31, &newINT_delete, &newINT_delete);

    xMap<int*,int*> copy = hash;

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   10\n"
        "size:       6\n"
        "0   : \n"
        "1   :  (n_1,n_900); (n_11,n_200); (n_21,n_300); (n_41,n_500); (n_51,n_600)\n"
        "2   :  (n_2,n_800)\n"
        "3   : \n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n";

    //! output
    string output = "\n" + copy.toString(&newINT_toString, &newINT_toString);

    // cleanup
    delete value1;
    delete key3;
    delete value61;

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash30() {
    cout << "TEST HASH 30";
    //! data
    xMap<int*, int*> hash(
        &newINT_keyHash, 1, &newINT_EQ,
        xMap<int*, int*>::freeKey,
        &newINT_EQ,
        xMap<int*, int*>::freeValue
    );
    int* key1   = new int(1);
    int* key11  = new int(11);
    int* key21  = new int(21);
    int* key31  = new int(31);
    int* key41  = new int(41);
    int* key51  = new int(51);
    int* key61  = new int(61);
    int* key2   = new int(2);
    int* key3   = new int(1);

    int* value1  = new int(100);
    int* value11 = new int(200);
    int* value21 = new int(300);
    int* value31 = new int(400);
    int* value41 = new int(500);
    int* value51 = new int(600);
    int* value61 = new int(700);
    int* value2  = new int(800);
    int* value3  = new int(900);

    hash.put(key1,  value1);
    hash.put(key11, value11);
    hash.put(key21, value21);
    hash.put(key31, value31);
    hash.put(key41, value41);
    hash.put(key51, value51);
    hash.put(key61, value61);
    hash.put(key2,  value2);
    hash.put(key3,  value3);

    hash.remove(key61, &newINT_delete);
    hash.remove(key31, value31, &newINT_delete, &newINT_delete);

    hash.clear();

    //! expect
    string expect =
        "\n"
        "==================================================\n"
        "capacity:   10\n"
        "size:       0\n"
        "0   : \n"
        "1   : \n"
        "2   : \n"
        "3   : \n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n";

    //! output
    string output = "\n" + hash.toString(&newINT_toString, &newINT_toString);

    // cleanup
    delete value1;
    delete key3;
    delete value61;

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash31() {
    cout << "TEST HASH 31";
    //! data
    int keys[]   = {2, 12, 42, 72, 3, 45};
    int values[] = {35, 67, 100, 23, 68, 68};

    xMap<int,int> map(&hashFunc);
    for (int i = 0; i < 6; ++i) {
        map.put(keys[i], values[i]);
    }

    //! expect
    string expect =
        "==================================================\n"
        "capacity:   10\n"
        "size:       6\n"
        "0   : \n"
        "1   : \n"
        "2   :  (2,35); (12,67); (42,100); (72,23)\n"
        "3   :  (3,68)\n"
        "4   : \n"
        "5   :  (45,68)\n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "==================================================\n"
        "[0, 0, 4, 1, 0, 1, 0, 0, 0, 0]";

    //! output
    string output = map.toString();
    DLinkedList<int> list = map.clashes();
    output += list.toString();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}

void test_hash32() {

    cout << "TEST HASH 32";
    //! data
    int keys[]   = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};

    xMap<int,int> hash(&xMap<int,int>::simpleHash);
    for (int i = 0; i < 8; ++i) {
        hash.put(keys[i], values[i]);
    }

    //! expect
    string expect =
        "==================================================\n"
        "capacity:   15\n"
        "size:       8\n"
        "0   :  (30,45); (45,68)\n"
        "1   :  (76,72)\n"
        "2   :  (2,35)\n"
        "3   :  (3,68)\n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "10  : \n"
        "11  : \n"
        "12  :  (12,67); (42,100); (72,23)\n"
        "13  : \n"
        "14  : \n"
        "==================================================\n";

    //! output
    string output = hash.toString();

    cout << "Expected:\n" << expect << endl;
    cout << "Actual:\n" << output << endl;
    if (output == expect) cout << "TEST PASSED" << endl;
    else cout << "TEST FAILED" << endl;
}


void test_hash33() {
    cout << "TEST HASH 33";
    //! data
    int keys[]   = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};
    xMap<int, int*> hashMap(
        &xMap<int, int*>::simpleHash,
        0.75,
        &valueEQ,
        &xMap<int, int*>::freeValue,
        0, // keyEQ
        0  // deleteKeys
    );
    for (int i = 0; i < 8; ++i) {
        hashMap.put(keys[i], new int(values[i]));
    }

    //! expect
    string expect =
        "==================================================\n"
        "capacity:   15\n"
        "size:       8\n"
        "0   :  (30,45); (45,68)\n"
        "1   :  (76,72)\n"
        "2   :  (2,35)\n"
        "3   :  (3,68)\n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "10  : \n"
        "11  : \n"
        "12  :  (12,67); (42,100); (72,23)\n"
        "13  : \n"
        "14  : \n"
        "==================================================\n";

    //! output
    string output = hashMap.toString(0, &value2str);

    cout << "Expected: \n" << expect;
    cout << "Actual: \n" << output;
    if (output == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}

void test_hash34() {
    cout << "TEST HASH 34";
    //! data
    int keys[]   = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};
    xMap<int*, int*> hashMap(
        &hashFunc,
        0.75,
        &valueEQ,
        &xMap<int*, int*>::freeValue,
        &keyEQ,
        &xMap<int*, int*>::freeKey
    );
    for (int i = 0; i < 8; ++i) {
        hashMap.put(new int(keys[i]), new int(values[i]));
    }

    //! output (before & after removal)
    string output;
    output += hashMap.toString(&key2str, &value2str);

    int* pkey = new int(42);
    delete hashMap.remove(pkey, &deleteKey);
    delete pkey;

    output += hashMap.toString(&key2str, &value2str);

    //! expect
    string expect =
        "==================================================\n"
        "capacity:   15\n"
        "size:       8\n"
        "0   :  (30,45); (45,68)\n"
        "1   :  (76,72)\n"
        "2   :  (2,35)\n"
        "3   :  (3,68)\n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "10  : \n"
        "11  : \n"
        "12  :  (12,67); (42,100); (72,23)\n"
        "13  : \n"
        "14  : \n"
        "==================================================\n"
        "==================================================\n"
        "capacity:   15\n"
        "size:       7\n"
        "0   :  (30,45); (45,68)\n"
        "1   :  (76,72)\n"
        "2   :  (2,35)\n"
        "3   :  (3,68)\n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "10  : \n"
        "11  : \n"
        "12  :  (12,67); (72,23)\n"
        "13  : \n"
        "14  : \n"
        "==================================================\n";

    cout << "Expected: \n" << expect;
    cout << "Actual: \n" << output;
    if (output == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}

void test_hash35() {
    cout << "TEST HASH 35";
    //! data
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    Point* values[] = {
        new Point(2.3,4.5), new Point(4.2,6.7),
        new Point(5.2,7.2), new Point(9.1,1.8),
        new Point(8.9,9.1), new Point(8.1,3.1),
        new Point(3.3,5.4), new Point(7.3,4.2)
    };
    xMap<int*, Point*> hashMap(
        &hashFunc,
        0.75,
        &Point::pointEQ,
        &xMap<int*, Point*>::freeValue,
        &keyEQ,
        &xMap<int*, Point*>::freeKey
    );
    for (int i = 0; i < 8; ++i) {
        hashMap.put(new int(keys[i]), values[i]);
    }

    //! expect
    string expect =
        "==================================================\n"
        "capacity:   15\n"
        "size:       8\n"
        "0   :  (30,(7.3, 4.2)); (45,(8.1, 3.1))\n"
        "1   :  (76,(3.3, 5.4))\n"
        "2   :  (2,(2.3, 4.5))\n"
        "3   :  (3,(8.9, 9.1))\n"
        "4   : \n"
        "5   : \n"
        "6   : \n"
        "7   : \n"
        "8   : \n"
        "9   : \n"
        "10  : \n"
        "11  : \n"
        "12  :  (12,(4.2, 6.7)); (42,(5.2, 7.2)); (72,(9.1, 1.8))\n"
        "13  : \n"
        "14  : \n"
        "==================================================\n";

    //! output
    string output = hashMap.toString(&key2str, &point2str);

    cout << "Expected: \n" << expect;
    cout << "Actual: \n" << output;
    if (output == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}

void test_hash36() {
    cout << "TEST HASH 36";
    //! data
    int keys[]   = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};
    xMap<int, int> hash(&xMap<int,int>::simpleHash);
    for (int i = 0; i < 8; ++i) {
        hash.put(keys[i], values[i]);
    }

    DLinkedList<int> keyset   = hash.keys();
    DLinkedList<int> valueset = hash.values();

    //! expect
    string expect =
        "Keys: [30, 45, 76, 2, 3, 12, 42, 72]\n"
        "Values: [45, 68, 72, 35, 68, 67, 100, 23]\n";

    //! output
    string output = "Keys: "   + keyset.toString()   + "\n"
                  + "Values: " + valueset.toString() + "\n";

    cout << "Expected: \n" << expect;
    cout << "Actual: \n" << output;
    if (output == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}

void test_hash37() {
    cout << "TEST HASH 37";
    //! data
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    xMap<int, int*> hash(&xMap<int,int*>::simpleHash);
    for (int i = 0; i < 8; ++i) {
        hash.put(keys[i], nullptr);
    }

    DLinkedList<int> clashes = hash.clashes();
    int maxColl = -1;
    for (auto it = clashes.begin(); it != clashes.end(); ++it) {
        maxColl = max(maxColl, *it);
    }
    float lf = (float)hash.size() / hash.getCapacity();

    //! expect
    string expect =
        "table size: 15\n"
        "current count: 8\n"
        "real load factor: 0.533333\n"
        "max #collisions: 3\n";

    //! output
    ostringstream oss;
    oss << "table size: "       << hash.getCapacity() << "\n"
        << "current count: "    << hash.size()        << "\n"
        << "real load factor: " << lf                 << "\n"
        << "max #collisions: "  << maxColl            << "\n";
    string output = oss.str();

    cout << "Expected: \n" << expect;
    cout << "Actual: \n" << output;
    if (output == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}

string countries1[] = {
    "country", "capital", "type",
    "Abkhazia", "Sukhumi", "countryCapital",
    "Afghanistan", "Kabul", "countryCapital",
    "Akrotiri and Dhekelia", "Episkopi Cantonment", "countryCapital",
    "Albania", "Tirana", "countryCapital",
    "Algeria", "Algiers", "countryCapital",
    "American Samoa", "Pago Pago", "countryCapital",
    "Andorra", "Andorra la Vella", "countryCapital",
    "Angola", "Luanda", "countryCapital",
    "Anguilla", "The Valley", "countryCapital",
    "Antigua and Barbuda", "St. John's", "countryCapital",
    "Argentina", "Buenos Aires", "countryCapital",
    "Armenia", "Yerevan", "countryCapital",
    "Aruba", "Oranjestad", "countryCapital",
    "Ascension Island", "Georgetown", "countryCapital",
    "Australia", "Canberra", "countryCapital",
    "Austria", "Vienna", "countryCapital",
    "Azerbaijan", "Baku", "countryCapital",
    "Bahamas", "Nassau", "countryCapital",
    "Bahrain", "Manama", "countryCapital",
    "Bangladesh", "Dhaka", "countryCapital",
    "Barbados", "Bridgetown", "countryCapital",
    "Belarus", "Minsk", "countryCapital",
    "Belgium", "Brussels", "countryCapital",
    "Belize", "Belmopan", "countryCapital",
    "Benin", "Porto-Novo", "countryCapital",
    "Bermuda", "Hamilton", "countryCapital",
    "Bhutan", "Thimphu", "countryCapital",
    "Bolivia", "Sucre", "countryCapital",
    "Bolivia", "La Paz", "countryCapital",
    "Bosnia and Herzegovina", "Sarajevo", "countryCapital",
    "Botswana", "Gaborone", "countryCapital",
    "Brazil", "Brasília", "countryCapital",
    "British Virgin Islands", "Road Town", "countryCapital",
    "Brunei", "Bandar Seri Begawan", "countryCapital",
    "Bulgaria", "Sofia", "countryCapital",
    "Burkina Faso", "Ouagadougou", "countryCapital",
    "Burundi", "Bujumbura", "countryCapital",
    "Cambodia", "Phnom Penh", "countryCapital",
    "Cameroon", "Yaoundé", "countryCapital",
    "Canada", "Ottawa", "countryCapital",
    "Cape Verde", "Praia", "countryCapital",
    "Cayman Islands", "George Town", "countryCapital",
    "Central African Republic", "Bangui", "countryCapital",
    "Chad", "N'Djamena", "countryCapital",
    "Chile", "Santiago", "countryCapital",
    "China", "Beijing", "countryCapital",
    "Christmas Island", "Flying Fish Cove", "countryCapital",
    "Cocos (Keeling) Islands", "West Island", "countryCapital",
    "Colombia", "Bogotá", "countryCapital",
    "Comoros", "Moroni", "countryCapital",
    "Cook Islands", "Avarua", "countryCapital",
    "Costa Rica", "San José", "countryCapital",
    "Croatia", "Zagreb", "countryCapital",
    "Cuba", "Havana", "countryCapital",
    "Curaçao", "Willemstad", "countryCapital",
    "Cyprus", "Nicosia", "countryCapital",
    "Czech Republic", "Prague", "countryCapital",
    "Côte d'Ivoire", "Yamoussoukro", "countryCapital",
    "Democratic Republic of the Congo", "Kinshasa", "countryCapital",
    "Denmark", "Copenhagen", "countryCapital",
    "Djibouti", "Djibouti", "countryCapital",
    "Dominica", "Roseau", "countryCapital",
    "Dominican Republic", "Santo Domingo", "countryCapital",
    "East Timor (Timor-Leste)", "Dili", "countryCapital",
    "Easter Island", "Hanga Roa", "countryCapital",
    "Ecuador", "Quito", "countryCapital",
    "Egypt", "Cairo", "countryCapital",
    "El Salvador", "San Salvador", "countryCapital",
    "Equatorial Guinea", "Malabo", "countryCapital",
    "Eritrea", "Asmara", "countryCapital",
    "Estonia", "Tallinn", "countryCapital",
    "Ethiopia", "Addis Ababa", "countryCapital",
    "Falkland Islands", "Stanley", "countryCapital",
    "Faroe Islands", "Tórshavn", "countryCapital",
    "Federated States of Micronesia", "Palikir", "countryCapital",
    "Fiji", "Suva", "countryCapital",
    "Finland", "Helsinki", "countryCapital",
    "France", "Paris", "countryCapital",
    "French Guiana", "Cayenne", "countryCapital",
    "French Polynesia", "Papeete", "countryCapital",
    "Gabon", "Libreville", "countryCapital",
    "Gambia", "Banjul", "countryCapital",
    "Georgia", "Tbilisi", "countryCapital",
    "Germany", "Berlin", "countryCapital",
    "Ghana", "Accra", "countryCapital",
    "Gibraltar", "Gibraltar", "countryCapital",
    "Greece", "Athens", "countryCapital",
    "Greenland", "Nuuk", "countryCapital",
    "Grenada", "St. George's", "countryCapital",
    "Guam", "Hagåtña", "countryCapital",
    "Guatemala", "Guatemala City", "countryCapital",
    "Guernsey", "St. Peter Port", "countryCapital",
    "Guinea", "Conakry", "countryCapital",
    "Guinea-Bissau", "Bissau", "countryCapital",
    "Guyana", "Georgetown", "countryCapital",
    "Haiti", "Port-au-Prince", "countryCapital",
    "Honduras", "Tegucigalpa", "countryCapital",
    "Hungary", "Budapest", "countryCapital",
    "Iceland", "Reykjavík", "countryCapital",
    "India", "New Delhi", "countryCapital",
    "Indonesia", "Jakarta", "countryCapital",
    "Iran", "Tehran", "countryCapital",
    "Iraq", "Baghdad", "countryCapital",
    "Ireland", "Dublin", "countryCapital",
    "Isle of Man", "Douglas", "countryCapital",
    "Israel", "Jerusalem", "countryCapital",
    "Italy", "Rome", "countryCapital",
    "Jamaica", "Kingston", "countryCapital",
    "Japan", "Tokyo", "countryCapital",
    "Jersey", "St. Helier", "countryCapital",
    "Jordan", "Amman", "countryCapital",
    "Kazakhstan", "Astana", "countryCapital",
    "Kenya", "Nairobi", "countryCapital",
    "Kiribati", "Tarawa", "countryCapital",
    "Kosovo", "Pristina", "countryCapital",
    "Kuwait", "Kuwait City", "countryCapital",
    "Kyrgyzstan", "Bishkek", "countryCapital",
    "Laos", "Vientiane", "countryCapital",
    "Latvia", "Riga", "countryCapital",
    "Lebanon", "Beirut", "countryCapital",
    "Lesotho", "Maseru", "countryCapital",
    "Liberia", "Monrovia", "countryCapital",
    "Libya", "Tripoli", "countryCapital",
    "Liechtenstein", "Vaduz", "countryCapital",
    "Lithuania", "Vilnius", "countryCapital",
    "Luxembourg", "Luxembourg", "countryCapital",
    "Macedonia", "Skopje", "countryCapital",
    "Madagascar", "Antananarivo", "countryCapital",
    "Malawi", "Lilongwe", "countryCapital",
    "Malaysia", "Kuala Lumpur", "countryCapital",
    "Maldives", "Malé", "countryCapital",
    "Mali", "Bamako", "countryCapital",
    "Malta", "Valletta", "countryCapital",
    "Marshall Islands", "Majuro", "countryCapital",
    "Mauritania", "Nouakchott", "countryCapital",
    "Mauritius", "Port Louis", "countryCapital",
    "Mexico", "Mexico City", "countryCapital",
    "Moldova", "Chisinau", "countryCapital",
    "Monaco", "Monaco", "countryCapital",
    "Mongolia", "Ulaanbaatar", "countryCapital",
    "Montenegro", "Podgorica", "countryCapital",
    "Montserrat", "Plymouth", "countryCapital",
    "Morocco", "Rabat", "countryCapital",
    "Mozambique", "Maputo", "countryCapital",
    "Myanmar", "Naypyidaw", "countryCapital",
    "Nagorno-Karabakh Republic", "Stepanakert", "countryCapital",
    "Namibia", "Windhoek", "countryCapital",
    "Nauru", "Yaren", "countryCapital",
    "Nepal", "Kathmandu", "countryCapital",
    "Netherlands", "Amsterdam", "countryCapital",
    "New Caledonia", "Nouméa", "countryCapital",
    "New Zealand", "Wellington", "countryCapital",
    "Nicaragua", "Managua", "countryCapital",
    "Niger", "Niamey", "countryCapital",
    "Nigeria", "Abuja", "countryCapital",
    "Niue", "Alofi", "countryCapital",
    "Norfolk Island", "Kingston", "countryCapital",
    "North Korea", "Pyongyang", "countryCapital",
    "Northern Cyprus", "Nicosia", "countryCapital",
    "United Kingdom Northern Ireland", "Belfast", "countryCapital",
    "Northern Mariana Islands", "Saipan", "countryCapital",
    "Norway", "Oslo", "countryCapital",
    "Oman", "Muscat", "countryCapital",
    "Pakistan", "Islamabad", "countryCapital",
    "Palau", "Ngerulmud", "countryCapital",
    "Palestine", "Jerusalem", "countryCapital",
    "Panama", "Panama City", "countryCapital",
    "Papua New Guinea", "Port Moresby", "countryCapital",
    "Paraguay", "Asunción", "countryCapital",
    "Peru", "Lima", "countryCapital",
    "Philippines", "Manila", "countryCapital",
    "Pitcairn Islands", "Adamstown", "countryCapital",
    "Poland", "Warsaw", "countryCapital",
    "Portugal", "Lisbon", "countryCapital",
    "Puerto Rico", "San Juan", "countryCapital",
    "Qatar", "Doha", "countryCapital",
    "Republic of China (Taiwan)", "Taipei", "countryCapital",
    "Republic of the Congo", "Brazzaville", "countryCapital",
    "Romania", "Bucharest", "countryCapital",
    "Russia", "Moscow", "countryCapital",
    "Rwanda", "Kigali", "countryCapital",
    "Saint Barthélemy", "Gustavia", "countryCapital",
    "Saint Helena", "Jamestown", "countryCapital",
    "Saint Kitts and Nevis", "Basseterre", "countryCapital",
    "Saint Lucia", "Castries", "countryCapital",
    "Saint Martin", "Marigot", "countryCapital",
    "Saint Pierre and Miquelon", "St. Pierre", "countryCapital",
    "Saint Vincent and the Grenadines", "Kingstown", "countryCapital",
    "Samoa", "Apia", "countryCapital",
    "San Marino", "San Marino", "countryCapital",
    "Saudi Arabia", "Riyadh", "countryCapital",
    "Scotland", "Edinburgh", "countryCapital",
    "Senegal", "Dakar", "countryCapital",
    "Serbia", "Belgrade", "countryCapital",
    "Seychelles", "Victoria", "countryCapital",
    "Sierra Leone", "Freetown", "countryCapital",
    "Singapore", "Singapore", "countryCapital",
    "Sint Maarten", "Philipsburg", "countryCapital",
    "Slovakia", "Bratislava", "countryCapital",
    "Slovenia", "Ljubljana", "countryCapital",
    "Solomon Islands", "Honiara", "countryCapital",
    "Somalia", "Mogadishu", "countryCapital",
    "Somaliland", "Hargeisa", "countryCapital",
    "South Africa", "Pretoria", "countryCapital",
    "South Georgia and the South Sandwich Islands", "Grytviken", "countryCapital",
    "South Korea", "Seoul", "countryCapital",
    "South Ossetia", "Tskhinvali", "countryCapital",
    "South Sudan South Sudan", "Juba", "countryCapital",
    "Spain", "Madrid", "countryCapital",
    "Sri Lanka", "Sri Jayawardenapura Kotte", "countryCapital",
    "Sudan", "Khartoum", "countryCapital",
    "Suriname", "Paramaribo", "countryCapital",
    "Swaziland", "Mbabane", "countryCapital",
    "Sweden", "Stockholm", "countryCapital",
    "Switzerland", "Bern", "countryCapital",
    "Syria", "Damascus", "countryCapital",
    "São Tomé and Príncipe", "São Tomé", "countryCapital",
    "Tajikistan", "Dushanbe", "countryCapital",
    "Tanzania", "Dodoma", "countryCapital",
    "Thailand", "Bangkok", "countryCapital",
    "Togo", "Lomé", "countryCapital",
    "Tonga", "Nukuʻalofa", "countryCapital",
    "Transnistria", "Tiraspol", "countryCapital",
    "Trinidad and Tobago", "Port of Spain", "countryCapital",
    "Tristan da Cunha", "Edinburgh of the Seven Seas", "countryCapital",
    "Tunisia", "Tunis", "countryCapital",
    "Turkey", "Ankara", "countryCapital",
    "Turkmenistan", "Ashgabat", "countryCapital",
    "Turks and Caicos Islands", "Cockburn Town", "countryCapital",
    "Tuvalu", "Funafuti", "countryCapital",
    "Uganda", "Kampala", "countryCapital",
    "Ukraine", "Kiev", "countryCapital",
    "United Arab Emirates", "Abu Dhabi", "countryCapital",
    "United Kingdom; England", "London", "countryCapital",
    "United States", "Washington, D.C.", "countryCapital",
    "United States Virgin Islands", "Charlotte Amalie", "countryCapital",
    "Uruguay", "Montevideo", "countryCapital",
    "Uzbekistan", "Tashkent", "countryCapital",
    "Vanuatu", "Port Vila", "countryCapital",
    "Vatican City", "Vatican City", "countryCapital",
    "Venezuela", "Caracas", "countryCapital",
    "Vietnam", "Hanoi", "countryCapital",
    "Wales", "Cardiff", "countryCapital",
    "Wallis and Futuna", "Mata-Utu", "countryCapital",
    "Western Sahara", "El Aaiún", "countryCapital",
    "Yemen", "Sanaá", "countryCapital",
    "Zambia", "Lusaka", "countryCapital",
    "Zimbabwe", "Harare", "countryCapital"
};
int ncountry1 = 248;

void test_hash38() {
    cout << "TEST HASH 38";
    //! data
    xMap<string, string> map(&stringHash);
    for (int i = 0; i < ncountry1*3; i += 3) {
        map.put(countries1[i], countries1[i+1]);
    }

    DLinkedList<int> clashes = map.clashes();
    int maxColl = -1;
    for (auto it = clashes.begin(); it != clashes.end(); ++it) {
        maxColl = max(maxColl, *it);
    }
    float lf = (float)map.size() / map.getCapacity();
    string capital = map.get("Vietnam");

    //! expect
    string expect =
        "table size: 366\n"
        "current count: 247\n"
        "real load factor: 0.674863\n"
        "max #collisions: 4\n"
        "Capital of Vietnam is Hanoi\n";

    //! output
    ostringstream oss;
    oss << "table size: "      << map.getCapacity() << "\n"
        << "current count: "   << map.size()        << "\n"
        << "real load factor: "<< lf                 << "\n"
        << "max #collisions: " << maxColl            << "\n"
        << "Capital of Vietnam is " << capital       << "\n";
    string output = oss.str();

    cout << "Expected: \n" << expect;
    cout << "Actual: \n" << output;
    if (output == expect) cout << "TEST PASSED\n";
    else cout << "TEST FAILED\n";
}