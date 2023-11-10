//Fernando Morán Fougerat A01284623
//este código ordena un log, y muestra una sección de este.
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
#include "Log.h"
#include "Heap.h"
#include "MinHeap.h"
#include "BST.h"
#include "HeapIp.h"
#include "Count.h"

//cambia el mes de nombre a numero,siempre siendo string
template<class T>
void monthSwitch(T& month) {
    if (month == "Jan") {
        month = "01";
    } else if (month == "Feb") {
        month = "02";
    } else if (month == "Mar") {
        month = "03";
    } else if (month == "Apr") {
        month = "04";
    } else if (month == "May") {
        month = "05";
    } else if (month == "Jun") {
        month = "06";
    } else if (month == "Jul") {
        month = "07";
    } else if (month == "Aug") {
        month = "08";
    } else if (month == "Sep") {
        month = "09";
    } else if (month == "Oct") {
        month = "10";
    } else if (month == "Nov") {
        month = "11";
    } else if (month == "Dec") {
        month = "12";
    }
}

ostream&operator<<(ostream& os, const Log& logs){
    os<<logs.year<<" "<<logs.month<<" "<<logs.day<<" "<<logs.ip<<" "<<logs.message;
    return os;
}

ostream&operator<<(ostream& os, const Count& count){
    os<<count.ip<<" "<<count.counter;
    return os;
}

string addLeadingZeros(const string& str) {
    if (str.length() < 3) {
        return string(3 - str.length(), '0') + str;
    }
    return str;
}

string key2Generator(string year, string month,string day, string time, string ip) {
    string ipcopy=ip;
    size_t start = 0;
    
    vector<string> sections;
    string formattedIp;
    size_t end = ipcopy.find('.');
    while (end != string::npos) {
        sections.push_back(ipcopy.substr(start, end - start));
        start = end + 1;
            end = ipcopy.find('.', start);
        }
        sections.push_back(ipcopy.substr(start));
        for (const string& section : sections) {

            formattedIp += addLeadingZeros(section) + ".";
            formattedIp.pop_back();
            }
    ipcopy=formattedIp;
    ipcopy.erase(std::remove(ipcopy.begin(), ipcopy.end(), '.'), ipcopy.end());
    string timecopy=time;
    timecopy.erase(std::remove(timecopy.begin(), timecopy.end(), ':'), timecopy.end());
    string key2= ipcopy.erase(0,9) + year.erase(0,2) + month + day + timecopy;
    return key2;
}

string key1Generator(string year, string month,string day, string time) {
    string timecopy=time;
    timecopy.erase(std::remove(timecopy.begin(), timecopy.end(), ':'), timecopy.end());
    string keyStr = year + month + day + timecopy;
    return keyStr;
    
}

void top10(vector<Log> list) {
    // buscar el ip en el vector
    string ip = list[0].ip;
    
    Count cip(ip);
    HeapIp<Count> countHeap;
    for (int i=0; i<list.size(); i++) {
        if (list[i].ip == ip) {
            cip.counter++;
        } else {
            countHeap.push(cip);
            cip.ip = list[i].ip;
            cip.counter = 1;
            ip=cip.ip;
        }
    }
    countHeap.print();
    
}

void createSortedList(vector<Log> &sortedList, Heap<Log> heap) {
    while (!heap.empty()) {
        sortedList.push_back(heap.top());
        heap.pop();
    }
    
    top10(sortedList);

}

int main() {
    cout<<"bienvenido a evidencia 3!"<<endl;
    // ifstream fileIn("log602-3.txt");
    ifstream fileIn("log602-3.txt");
    string line;
    string word;
    string year;
    string month;
    string day;
    string time;
    string ip;
    string message;
    vector <Log> logs;
    BST<Log> bst;
    vector <Count> counts;
    
    //lleno mi vector de logs con cada línea
    while (getline(fileIn, line)) { 
        message = "";
        stringstream ss(line);
        ss >> month >> day >> year >> time >> ip;
        monthSwitch(month); //cambio meses
        while (ss >> word) {
            message = message + " " + word;
        }
       
       string key1=key1Generator(year,month,day,time);
       string key2=key2Generator(year,month,day,time,ip);
       Log loog(year,month,day,time,ip,message,key1,key2);
       logs.push_back(loog);
       bst.insert(loog);
    //    Count count(ip);
    //    counts.push_back(count);
        // addIP(counts, ip)
    //    cout<<count.ip<<" "<<count.counter<<endl; //si funciona 
    }

    cout << "contador de registros: " << logs.size() << endl;
    int menu,decision;
    Heap heapIPS(logs);
    while(menu!=5){
        cout<<"menu: \n1.Ordena datos de mayor a menor  \n2.Ordena datos de menor a mayor  \n3.10 ip's con mayor número de registros\n4.Búsqueda de una ip\n5.Salir"<<endl;
        cin>>menu;
        if (menu==1){
            cout<<"Ordena datos de mayor a menor "<<endl;
            Heap heapDes(logs);
            
            heapDes.fileOut("output602-1.out");            
        }else if (menu==2){
            cout<<"Ordena datos de menor a mayor "<<endl;
            MinHeap heapAsc(logs);
            heapAsc.fileOut("output602-2.out");      
        }else if (menu==3){
            cout<<"Top 10 IP que mas aparecen (heap sort)"<<endl;
            vector<Log> sortedList;            
            createSortedList(sortedList, heapIPS);
            // vector<pair<string, int>> ipCounts;
            // for (const Log& log : logs) {
            // bool found = false;
            // for (pair<string, int>& ipCount : ipCounts) {
            //     if (ipCount.first == log.ip) {
            //         ipCount.second++;
            //         found = true;
            //         break;
            //     }
            //     }
            // if (!found) {
            //     ipCounts.push_back({log.ip, 1});
            // }
            // }
            // sort(ipCounts.begin(), ipCounts.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            // return a.second > b.second;
            // });

            // cout << "\nTop 10 IP que mas aparecen (vector) :" << endl;
            // for (int i = 0; i < min(10, static_cast<int>(ipCounts.size())); i++) {
            // cout << "IP: " << ipCounts[i].first << " Records: " << ipCounts[i].second << endl;
            // } 
            
        }else if (menu==4){
            cout<<"Búsqueda de una ip \nDa ip a buscar ";
            string ipBusq;
            cin>>ipBusq;
            int counter = bst.countLogs(ipBusq);
            cout << "El valor aparece " << counter << " veces en el árbol binario."<<endl;
        }else if (menu==5){
            cout<<"adios :) ";
        }else{
            cout<<"Valor no valido, da numero entre 1 y 5."<<endl;
        }
        

    }
    
    return 0;
}