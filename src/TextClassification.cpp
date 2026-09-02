#include "TextClassification.h"
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>

void TextClassification::nactiTextSoubor()
{
	fstream myfile;
    string line, soubor;
    vector<char> znaky = { '.','!','?',':','/','%','-',',','"' };                                               //znaky, ktere chceme odstranit z vet
    cin >> soubor;
    myfile.open(soubor, ios::in);
    while (!(myfile.is_open()))                                                                                 //kontrola zda soubor existuje
    {
        cout << "Soubor se nepovedlo otevrit. Zadejte spravny nazev souboru vcetne pripony: ";
        cin >> soubor;
        myfile.open(soubor, ios::in);
    }
	if (myfile.is_open())
	{
		cout << "Soubor " << soubor << " byl uspesne otevren." << endl;
        while (!myfile.eof()) {
            getline(myfile, line);                                                                              //nacteme jeden cely radek souboru
            transform(line.begin(), line.end(), line.begin(), ::tolower);                                       //nez ulozime do pole, tak rovnou prevdeme na mala pismena                                                                                       
            for (char znak : znaky)                                                                              //oddelani interpunkce a dalsich znaku
            {
                line.erase(remove(line.begin(), line.end(), znak), line.end());
            }
            this->text.insert(text.end(), line);
            if (myfile.fail() && !myfile.eof())
            {
                cout << "Chyba pri nacitani souboru!" << endl;
                break;
            }
        }
	}
    myfile.close();
}

void TextClassification::nactiTridySoubor()
{
	fstream myfile;
    string line, soubor, temp_string;
    vector<string> tridy_;
    cin >> soubor;
    myfile.open(soubor, ios::in);
    while (!(myfile.is_open()))                                                                                 //kontrola zda soubor existuje
    {
        cout << "Soubor se nepovedlo otevrit. Zadejte spravny nazev souboru vcetne pripony: ";
        cin >> soubor;
        myfile.open(soubor, ios::in);
    }
    if (myfile.is_open())
    {
        cout << "Soubor " << soubor << " byl uspesne otevren." << endl;
        while (!myfile.eof()) {
            getline(myfile, line);                                                                              //tridy mohou byt napsany bud po radcich nebo v jednom radku oddelene carkou a mezerou
            line.erase(remove(line.begin(), line.end(), ','), line.end());
            tridy_.insert(tridy_.end(), line);
            if (myfile.fail() && !myfile.eof())
            {
                cout << "Chyba pri nacitani souboru!" << endl;
                break;
            }
        }
        for (string radky : tridy_)                                                                              
        {
            stringstream ss(radky);
            while (getline(ss, temp_string, ' '))
            {
                this->tridy.push_back(temp_string);
            }
        }
    }
    myfile.close();
}

void TextClassification::vypisText()
{
    for (int i = 0; i < this->text.size(); i++)                                                                   //vypis pro kontrolu
    {
        cout << this->text[i] << endl;
    }
}

void TextClassification::vypisKeywords()
{
    for (int i = 0; i < this->tridy.size(); i++)                                                                   //vypis pro kontrolu
    {
        cout << this->tridy[i] << endl;
    }
}

void TextClassification::setUroven()
{
    string s = "";
    int hodnota;
    cout << "Zadejte uroven klasifikace: ";
    while (!(cin >> hodnota) || hodnota <= 0) {
        while (cin.get() != '\n')
            cin.clear();
        cout << "Nezadal jste platnou hodnotu. Opakujte: ";
        continue;
    }
    this->urovenklasifikace = hodnota;
}

void TextClassification::bagOfWords()
{
    string temp_string;
    for (string radky : this->text)                                                                                   //rodeleni nactenych radku na jednotliva "slova"
    {
        stringstream ss(radky);
        while (getline(ss, temp_string, ' '))
        {
            this->slova.push_back(temp_string);
        }
    }
    for (string slovo : this->slova)                                                                                  //pocitani slov
    {
        map <string, int> ::iterator it = this->slovapocet.find(slovo);
        if (it == this->slovapocet.end())                                                                              //nenajde slovo -> prida 
        {
            this->slovapocet.insert(pair<string, int>(slovo,1));
        }
        else {                                                                                              //slovo se vyskytuje -> zvedneme jeho hodnotu o +1
            this->slovapocet[slovo] = it->second + 1;
        }
    }
    for (string slovo : this->stopwords)                                                                         //vymaze spojky, predlozky atd.., pro vygenerovani klasifikacnich trid
    {
        map <string, int> ::iterator it = this->slovapocet.find(slovo);
        if (it != this->slovapocet.end())
        {
            this->slovapocet.erase(slovo);
        }
    }
}

void TextClassification::nactiStopWords()                                                                   
{
    fstream myfile;
    myfile.open("engstopwords.txt", ios::in);
    string line;
    if (myfile.is_open())
    {
        while (!myfile.eof()) {
            getline(myfile, line, ',');                                                                              
            this->stopwords.insert(stopwords.end(), line);
            if (myfile.fail() && !myfile.eof())
            {
                cout << "Chyba pri nacitani souboru!" << endl;
                break;
            }
        }
    }
    myfile.close();
}

void TextClassification::nactiText()
{
    string radek;
    vector<char> znaky = { '.','!','?',':','/','%','-',',','"' };
    //while ((getline(cin, radek).eof()))                                                      //nacitani ukoncujeme pomoci ctrl+z
    //{
    //    //&& static_cast<char>EOF
    //    /*if (eof())
    //    {
    //        break;
    //    }*/
    //    //else
    //    {
    //        transform(radek.begin(), radek.end(), radek.begin(), ::tolower);
    //        for (char znak : znaky)                                                                              //oddelani interpunkce a dalsich znaku
    //        {
    //            radek.erase(remove(radek.begin(), radek.end(), znak), radek.end());
    //        }
    //        this->text.insert(text.end(), radek);
    //    }
    //    
    //    //getchar();
    //}
    //getchar();
    do
    {
        getline(cin>>ws, radek);
        transform(radek.begin(), radek.end(), radek.begin(), ::tolower);
                for (char znak : znaky)                                                                              //oddelani interpunkce a dalsich znaku
                {
                    radek.erase(remove(radek.begin(), radek.end(), znak), radek.end());
                }
                this->text.insert(text.end(), radek);

    } while ((getline(cin,radek).eof()));//!(cin.eof())
    //cin.ignore();
}

void TextClassification::vypisSlova()
{
    for (int i = 0; i < this->slova.size(); i++)
    {
        cout << this->slova[i] << endl;
    }
}

void TextClassification::nactiTridy()
{
    string temp_string, radek;
    vector<string> tridy_;
    while (getline(cin, radek) && static_cast<char>EOF)
    {
        radek.erase(remove(radek.begin(), radek.end(), ','), radek.end());
        tridy_.insert(tridy_.end(), radek);
    }
    /*do
    {
        radek.erase(remove(radek.begin(), radek.end(), ','), radek.end());
        tridy_.insert(tridy_.end(), radek);
    } while (getline(cin, radek).eof());*/
    for (string radky : tridy_)                                                                                   //rozdeleni nactenych radku na jednotliva "slova"
    {
        stringstream ss(radky);
        while (getline(ss, temp_string, ' '))
        {
            this->tridy.push_back(temp_string);
        }
    }
}

void TextClassification::vypisSlovaPocet()
{
    map<string, int>::iterator it = this->slovapocet.begin();                                                         //vypis na kontrolu
    while (it != this->slovapocet.end())
    {
        cout << it->first <<" "<< it->second << endl;
        ++it;
    }
}

void TextClassification::klasifikuj()
{
    map<string, int>::iterator it = this->slovapocet.begin();
    //int uroven = 5;
    for (string trida : this->tridy)
    {
        while (it != this->slovapocet.end())
        {
            if (it->first.find(trida) == 0)
            {
                if (it->second >= this->urovenklasifikace)
                {
                    //cout << "Text spada do klasifikace " << trida << endl;
                    this->klasifikace.insert(this->klasifikace.end(), trida);
                }
            }
            else
            {
                string str = trida;
                if (str.length() >= 8)
                {
                    for (int i = 1; i < 4; i++)
                    {
                        if (it->first.find(str.erase(str.length() - i)) == 0)
                        {
                            if (it->second >= this->urovenklasifikace)
                            {
                                //cout << "Text spada do klasifikace " << trida << endl;
                                this->klasifikace.insert(this->klasifikace.end(), trida);
                            }
                        }
                    }
                }
            }
            ++it;
        }
        it = this->slovapocet.begin();
    }

    cout << "Tridy klasifikace: " << endl;
    for (int i = 0; i < this->klasifikace.size(); i++)
    {
        cout << this->klasifikace[i] << endl;
    }
}

void TextClassification::argumenty(string arg1, string arg2)
{
    fstream myfile1, myfile2;
    string line1,line2,soubor1,soubor2,temp_string;                                                                                        //nacitani textu
    vector<char> znaky = { '.','!','?',':','/','%','-',',','"' };                                               //znaky, ktere chceme odstranit z vet
    myfile1.open(arg1, ios::in);
    while (!(myfile1.is_open()))                                                                                 //kontrola zda soubor existuje
    {
        cout << "Soubor se nepovedlo otevrit. Zadejte spravny nazev souboru vcetne pripony: ";
        cin >> soubor1;
        myfile1.open(soubor1, ios::in);
    }
    if (myfile1.is_open())
    {
        cout << "Soubor " << arg1 << " byl uspesne otevren." << endl;
        while (!myfile1.eof()) {
            getline(myfile1, line1);                                                                              //nacteme jeden cely radek souboru
            transform(line1.begin(), line1.end(), line1.begin(), ::tolower);                                       //nez ulozime do pole, tak rovnou prevdeme na mala pismena                                                                                       
            for (char znak : znaky)                                                                              //oddelani interpunkce a dalsich znaku
            {
                line1.erase(remove(line1.begin(), line1.end(), znak), line1.end());
            }
            this->text.insert(text.end(), line1);
            if (myfile1.fail() && !myfile1.eof())
            {
                cout << "Chyba pri nacitani souboru!" << endl;
                break;
            }
        }
    }
    myfile1.close();
                                                                         
    vector<string> tridy_;                                                                                      //nacitani trid
    myfile2.open(arg2, ios::in);
    while (!(myfile2.is_open()))                                                                                 //kontrola zda soubor existuje
    {
        cout << "Soubor se nepovedlo otevrit. Zadejte spravny nazev souboru vcetne pripony: ";
        cin >> soubor2;
        myfile2.open(soubor2, ios::in);
    }
    if (myfile2.is_open())
    {
        cout << "Soubor " << arg2 << " byl uspesne otevren." << endl;
        while (!myfile2.eof()) {
            getline(myfile2, line2);                                                                              //tridy mohou byt napsany bud po radcich nebo v jednom radku oddelene carkou a mezerou
            line2.erase(remove(line2.begin(), line2.end(), ','), line2.end());
            tridy_.insert(tridy_.end(), line2);
            if (myfile2.fail() && !myfile2.eof())
            {
                cout << "Chyba pri nacitani souboru!" << endl;
                break;
            }
        }
        for (string radky : tridy_)
        {
            stringstream ss(radky);
            while (getline(ss, temp_string, ' '))
            {
                this->tridy.push_back(temp_string);
            }
        }
    }
    myfile2.close();
}
