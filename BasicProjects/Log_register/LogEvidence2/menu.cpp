#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

#include "Log.h"
#include "doubleLink.h"

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

string key1Generator(string year, string month,string day, string time) {
    string timecopy=time;
    timecopy.erase(std::remove(timecopy.begin(), timecopy.end(), ':'), timecopy.end());
    string keyStr = year + month + day + timecopy;
    return keyStr;
    
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
    string key2= ipcopy.erase(0,6) + year + month + day + timecopy;
    return key2;
}



ostream&operator<<(ostream& os, const Log& logs){
    os<<logs.year<<" "<<logs.month<<" "<<logs.day<<" "<<logs.ip<<" "<<logs.message;
    return os;
}

void contadorIPs(const string& filename) {
    ifstream fileInn(filename);
    string line;
    map<string, int> ipCount; // uso mapa para contar las IPs

    while (getline(fileInn, line)) {
        string year, month, ip;
        stringstream ss(line);
        ss >> month >> ws >> ws >> year >> ws >> ws >> ws >> ws >> ip;

        string yearAndMonth = year + "-" + month;
        ipCount[yearAndMonth]++;
    }
    // muestro todos las sumas
    for (const auto& entry : ipCount) {
        cout << "Mes y year: " << entry.first << ". sumatoria de IPs: " << entry.second << endl;
    }
}


    


int main() {
    ifstream fileIn("log602-2.txt");
    string line;
    string word;
    string year;
    string month;
    string day;
    string time;
    string ip;
    string message;
    LinkedList<Log> logs;
    // Node<Log>* head = nullptr;
    
   
    

    //lleno mi Double linked list de logs con cada línea
    while (getline(fileIn, line)) { 
         message = "";
         stringstream ss(line);
         ss >> month >> day >> year >> time >> ip;
         monthSwitch(month);
         while (ss >> word) {
             message = message + " " + word;
             
         }
         string key1=key1Generator(year,month,day,time);
         string key2=key2Generator(year,month,day,time,ip);
         Log loog(year,month,day,time,ip,message,key1,key2);
         
         logs.push(loog);
    }



    cout << "contador de registros: " << logs.getSize() << endl;
    //creo una lista auxiliar, la lleno de los logs que ya encontre. usare esto para no ordenar ya ordenada.
    LinkedList<Log> listAux;
    
    
    cout<<"Hola, bienvenido a evidencia 2"<<endl;
    
    int menu;
    int exit=0;
    while (exit==0){
        cout<<"Elige que hacer: \n1.Ordena los datos por fecha y hora \n2.Ordena los datos por ip, fecha y hora.\n3.Búsqueda por rango de ip's\n4.Sumatoria de datos.\n5.Salir."<<endl;
        cin>>menu;
        if(menu==1){
            ofstream fileOut("output602-1.out");
            cout<<"Ordena los datos por fecha y hora."<<endl;
            listAux=logs;
            listAux.quickSort(listAux.getHead());
            Node<Log>* current = listAux.getHead();
            while (current != nullptr) {
                const Log& log = current->data;
                cout << log.year << " " << log.month << " " << log.day << " " << log.time << " "<< log.ip << " " << log.message << " " <<  "\n";
                fileOut<< log.year << " " << log.month << " " << log.day << " " << log.time << " " << log.ip << " " << log.message << endl;
                current = current->next;   
                }
            fileOut.close();

            }else if (menu==2){
                ofstream fileOut("output602-2.out");
                cout<<"Ordena los datos por ip, fecha y hora."<<endl;
                listAux=logs;
                listAux.quickSort2(listAux.getHead());
                Node<Log>* current = logs.getHead();
                while (current != nullptr) {
                    const Log& log = current->data;
                    cout << log.year << " " << log.month << " " << log.day << " " << log.time << " "<< log.ip << " " << log.message << " " <<  "\n";
                    fileOut<< log.year << " " << log.month << " " << log.day << " " << log.time << " " << log.ip << " " << log.message << endl;
                    current = current->next;    
                    }
                fileOut.close();


            }else if (menu == 3) {
            cout<<"Busqueda por rango de ip's"<<endl;
            listAux=logs;
            listAux.quickSort2(listAux.getHead()); //aqui ya tengo ip ordenados.
            cout<<"Da ip inicial para busqueda secuencial "<<endl;
            //(10.14.000.000), (10.14.00.000) o (10.14.000.00), cualquiera funciona
            string a;
            cin>>a;
            Log ipInicial("","","","",a,"","","");
            int inicio=logs.findData(ipInicial);
            cout<<"Da ip final para busqueda secuencial "<<endl;
            string b;
            cin>>b;
            Log ipFinal("","","","",b,"","","");
            int fin=logs.findData(ipFinal);
            LinkedList<Log> Rango;
            Node<Log>* actual = listAux.getHead();
            for(int i=0;i<listAux.getSize();i++){
                if (i>=inicio and i<=fin){
                    const Log& log = actual->data;
                    Rango.push(log);
                }
              actual = actual->next;  
            }

            Node<Log>* current = Rango.getHead();
            cout<<"numeros en rango: "<<Rango.getSize()<<endl;
            ofstream fileOutD("output602-d.out");
            cout<<"Rango descendiente: "<<endl;
            while (current != nullptr) {
                    const Log& log = current->data;
                    cout << log.year << " " << log.month << " " << log.day << " " << log.time << " "<< log.ip << " " << log.message << " " <<  "\n";
                    fileOutD<< log.year << " " << log.month << " " << log.day << " " << log.time << " " << log.ip << " " << log.message << endl;
                    current = current->next;    
                    }
            fileOutD.close();

            Node<Log>* ultimo = Rango.getTail();
            
            ofstream fileOutA("output602-a.out");
            cout<<"Rango ascendente: "<<endl;
            
            while (ultimo != nullptr) {
                    const Log& log = ultimo->data;
                    cout << log.year << " " << log.month << " " << log.day << " " << log.time << " "<< log.ip << " " << log.message << " " <<  "\n";
                    fileOutA<< log.year << " " << log.month << " " << log.day << " " << log.time << " " << log.ip << " " << log.message << endl;
                    ultimo = ultimo->prev;    
                    }

            fileOutA.close();

            }else if (menu == 4) {
            cout<<"Sumatoria de datos"<<endl;

            string filename = "output602-2.txt";
            contadorIPs(filename);

        }else if (menu == 5) {
            cout << "Adios   :)" << endl;
            exit=1;
            break;
        } else {
            cout << "Eleccion no valida. Debes ingresar un número del 1 al 4; o 5 para salir." << endl;
        }
    }
    return 0;
}