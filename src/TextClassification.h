#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
class TextClassification
{
private:
	vector<string> tridy;
	vector<string> text;
	vector<string> slova;
	vector<string> klasifikace;
	map<string, int> slovapocet;
	vector<string> stopwords;																				//zatim nepotrebujeme
	int urovenklasifikace;
public:
	void nactiTextSoubor();
	void nactiText();
	void nactiTridySoubor();
	void nactiTridy();
	void nactiStopWords();
	void vypisText();
	void vypisKeywords();
	void vypisSlova();
	void vypisSlovaPocet();
	void setUroven();
	void bagOfWords();
	void klasifikuj();
	void argumenty(string arg1, string arg2);
	
};

