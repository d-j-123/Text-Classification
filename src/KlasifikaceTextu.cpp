#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>                                                                
#include <map>
#include <sstream>
#include "TextClassification.h"
using namespace std;

int zadejHodnotu(int a) {                                   //metoda pro zadavani voleb menu
    string s = "";
    //cin.ignore();
    int hodnota;
    cout << "Co chcete provest: ";
    //cin.ignore();
    while (!(cin >> hodnota) || hodnota <= 0 || hodnota > a) {
        while (cin.get() != '\n')
            cin.clear();
        cout << "Nezadal jste platnou hodnotu. Opakujte: ";
        continue;
    }
    return hodnota;
}



int main(int argc, char* argv[])
{
    int volba1, volba2;
    cout << "Toto je program na klasifikaci textu." << endl;
    do
    {
        if (argc <= 2) {
            //printf("Nebyly vlozeny zadne argumenty.\n");
            
            fstream myfile;
            
            TextClassification* object1 = new TextClassification;
            cout << "......................" << endl;
            cout << "1. Nacteni textu ze souboru" << endl;                                      //volba nacitani textu
            cout << "2. Nacteni textu z klavesnice" << endl;
            cout << "3. Konec" << endl;
            cout << "......................" << endl;
            volba1 = zadejHodnotu(3);
            if (volba1 == 1)
            {
                cout << "Zadejte nazev souboru textu vcetne pripony: ";
                object1->nactiTextSoubor();                                                     //Text1.txt
                cout << "......................" << endl;
                cout << "1. Nacteni klasifikacnich skupin ze souboru" << endl;                  //volba nacitani skupin nebo vygenerovani skupin
                cout << "2. Nacteni klasifikacnich skupin z klavesnice" << endl;
                cout << "3. Vygenerovani klasifikacnich skupin" << endl;
                cout << "......................" << endl;
                volba2 = zadejHodnotu(3);
                if (volba2 == 1)
                {
                    //cin.ignore();
                    cout << "Zadejte nazev souboru klasifikacnich trid vcetne pripony: ";
                    object1->nactiTridySoubor();                                            //Class1.txt
                    /*cout << "Text: " << endl;
                    object1->vypisText();
                    cout << "Tridy: " << endl;
                    object1->vypisKeywords();*/
                    object1->bagOfWords();
                    object1->setUroven();
                    object1->klasifikuj();

                }
                else if (volba2 == 2)
                {
                    cout << "Zadejte klasifikacni tridy: ";
                    object1->nactiTridy();
                    object1->bagOfWords();
                    object1->setUroven();
                    object1->klasifikuj();
                }
                else if (volba2 == 3)
                {
                    object1->bagOfWords();
                    object1->vypisSlovaPocet();
                }

            }
            else if (volba1 == 2)
            {
                cout << "Zadejte text ke klasifikaci: ";
                object1->nactiText();
                //object1->vypisText();
                cout << "......................" << endl;
                cout << "1. Nacteni klasifikacnich skupin ze souboru" << endl;
                cout << "2. Nacteni klasifikacnich skupin z klavesnice" << endl;
                cout << "3. Vygenerovani klasifikacnich skupin" << endl;
                cout << "......................" << endl;
                //getchar();
                //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                volba2 = zadejHodnotu(3);
                if (volba2 == 1)
                {
                    cout << "Zadejte nazev souboru klasifikacnich trid vcetne pripony: ";
                    object1->nactiTridySoubor();
                    object1->bagOfWords();
                    object1->setUroven();
                    object1->klasifikuj();
                }
                else if (volba2 == 2)
                {
                    cout << "Zadejte klasifikacni tridy: ";
                    object1->nactiTridy();
                    object1->bagOfWords();
                    object1->setUroven();
                    object1->klasifikuj();
                }
                else if (volba2 == 3)
                {
                    object1->bagOfWords();
                    object1->vypisSlovaPocet();
                }
            }
            delete object1;
        }
        else {
            volba1 = 1;
            TextClassification* object1 = new TextClassification;
            cout << "......................" << endl;
            object1->argumenty(argv[1], argv[2]);
            object1->bagOfWords();
            cout << "......................" << endl;
            object1->setUroven();
            object1->klasifikuj();
            //argv[1].clear();
            argc = 0;
            //remove(argv[1]);  //maze soubor
            //delete argv[1]; //hazi chybu
            //argv[1].empty();
            delete object1;
        }
        //delete argv[1];
    } while (volba1 != 3);
    
    
    
    
    //object1->nactiText("Text1.txt");
    //object1->nactiKeywords("Class1.txt");
    ////object1->nactiStopWords();
    ////cout << "Vypis textu: " << endl;
    ////object1->vypisText();
    //cout << "Vypis klicovych slov: " << endl;
    //object1->vypisKeywords();
    //object1->bagOfWords();
    ////cout << "Vypis slov po tokenizaci: " << endl;
    ////object1->vypisSlova();
    ////cout << "Vypis slov po spocitani: " << endl;
    ////object1->vypisSlovaPocet();
    //object1->klasifikuj();

    //string str1 = "stroj";
    //string str2 = "strojni";
    //string str3 = "auto";
    //string str4 = "automobil";
    //bool je1, je2, je3;
    //je1 = str2.find(str1);                                  //kdyz 0 tak ok
    //je2 = str3.find(str1);
    //je3 = str4.find(str3);
    //cout << je1 << endl;
    //cout << je2 << endl;
    //cout << je3 << endl;

    //cout << endl;

    //vector<string> keywords = { "automobil", "stroj", "hospoda", "pub", "beer"};
    ////vector<string> slova = { "automobilni","strojovna", "strojni", "hospodsky"};
    //map<string, int> slovapocet;
    //slovapocet["automobilni"] = 2;
    //slovapocet["strojovna"] = 3;
    //slovapocet["strojni"] = 2;
    //slovapocet["strojarsky"] = 1;
    //map<string, int>::iterator it = slovapocet.begin();
    ////map<string, int>::iterator it;
    //int uroven = 2;
    //bool je;

    ///*while (it != slovapocet.end())
    //{
    //    cout << it->first << " " << it->second << endl;
    //    ++it;
    //}
    //it = slovapocet.begin();*/
    //vector<string> klasifikace;
    //for (string trida : keywords)
    //{
    //    while (it != slovapocet.end())
    //    {
    //        if (it->first.find(trida) == 0)
    //        {
    //            if (it->second >= uroven)
    //            {
    //                cout << "Text spada do klasifikace " << trida << endl;
    //                klasifikace.insert(klasifikace.end(), trida);
    //            }
    //        }
    //        ++it;
    //    }
    //    it = slovapocet.begin();
    //}

    //cout << "Tridy klasifikace: " << endl;
    //for (int i = 0; i < klasifikace.size(); i++)
    //{
    //    cout << klasifikace[i] << endl;
    //}
    
    //fstream myfile;
    //myfile.open("Class2.txt", ios::in);
    //string line;
    //string temp_string;
    //vector<string> keywords;
    //vector<string> keywords_;
    //vector<char> znaky = { ',' };
    //if (myfile.is_open())
    //{
    //    //cout << "Soubor " << nazev << " byl uspesne otevren." << endl;
    //    while (!myfile.eof()) {
    //        getline(myfile, line);
    //        for (char znak : znaky)                                                                              //oddelani interpunkce a dalsich znaku
    //        {
    //            line.erase(remove(line.begin(), line.end(), znak), line.end());
    //        }
    //        keywords.insert(keywords.end(), line);
    //        if (myfile.fail() && !myfile.eof())
    //        {
    //            cout << "Chyba pri nacitani souboru!" << endl;
    //            break;
    //        }
    //    }
    //    for (string radky : keywords)                                                                                   //rodeleni nactenych radku na jednotliva "slova"
    //    {
    //        stringstream ss(radky);
    //        while (getline(ss, temp_string, ' '))
    //        {
    //            keywords_.push_back(temp_string);
    //        }
    //    }
    //}
    //fstream myfile2;
    //myfile2.open("Class1.txt", ios::in);
    //vector<string> keywords2;
    //vector<string> keywords2_;
    //if (myfile2.is_open())
    //{
    //    //cout << "Soubor " << nazev << " byl uspesne otevren." << endl;
    //    while (!myfile2.eof()) {
    //        getline(myfile2, line);                                                                              //nacteme jeden cely radek souboru
    //        keywords2.insert(keywords2.end(), line);
    //        for (char znak : znaky)                                                                              //oddelani interpunkce a dalsich znaku
    //        {
    //            line.erase(remove(line.begin(), line.end(), znak), line.end());
    //        }
    //        if (myfile2.fail() && !myfile2.eof())
    //        {
    //            cout << "Chyba pri nacitani souboru!" << endl;
    //            break;
    //        }
    //    }
    //    for (string radky : keywords2)                                                                                   //rodeleni nactenych radku na jednotliva "slova"
    //    {
    //        stringstream ss(radky);
    //        while (getline(ss, temp_string, ' '))
    //        {
    //            keywords2_.push_back(temp_string);
    //        }
    //    }
    //}
    //cout << "Poprve" << endl;
    //cout << keywords.size() << endl;
    //cout << keywords2.size() << endl;
    //cout << "Podruhe" << endl;
    //cout << keywords_.size() << endl;
    //cout << keywords2_.size() << endl;
    //cout << keywords[0];

    getchar();
    getchar();
}


//beer              0
//pub               37
//alcohol           2
//friendship        0
//family            0
//happiness         0
//celebration       0/3
//community         1
//fun               1
//laughter          0
//music             5
//dancing           0
//food              1
//drinks            0/7      




else
{
    volba1 = 1;
    KlasifikaceTextu* object1 = new KlasifikaceTextu;
    cout << "......................" << endl;
    object1->argumenty(argv[1], argv[2]);
    object1->bagOfWords();
    object1->setUroven();
    object1->klasifikuj();
    cout << "......................" << endl;
    cout << "Prejete si ulozit vysledek? " << endl;
    cout << "1. Ano" << endl;
    cout << "2. Ne" << endl;
    volba3 = zadejHodnotu(2);
    cout << "......................" << endl;
    if (volba3 == 1)
    {
        object1->ulozDoSouboru(1);
    }
    argc = 0;
    delete object1;
}