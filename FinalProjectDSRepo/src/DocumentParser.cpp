#include "DocumentParser.h"

using namespace tinyxml2;

DocumentParser::DocumentParser() {
        ifs.open("StopWords.txt");
        while(ifs.good())
        {
                getline(ifs, input);
                input.erase(remove_if (input.begin(), input.end(), static_cast<int(*)(int)>(&ispunct)), input.end());
                stopWords.push_back(input);
        }
        ifs.close();
        //constructor populates the list of stop words prior to adding any words
}

DocumentParser::~DocumentParser() {

}

void DocumentParser::add(std::string filename) {
        words.clear();
        documents.clear();
        loadIndexes();
        XMLDocument doc;
        doc.LoadFile(filename.c_str());
        if(doc.ErrorID() != 0)
        {
                std::cout<< "Error reading XML file!" << std::endl;
                return;
        }
        XMLElement* documentStart = doc.FirstChildElement("mediawiki");
        XMLElement* currentPage = documentStart->FirstChildElement("page");
        XMLElement* lastPage = documentStart->LastChildElement("page");
        bool stillData = true;
        const char* constDate;
        const char* constContributor;
        const char* constTitle;
        const char* constID;
        const char* constText;
        string title, text, date, contributor;
        int ID;
        Document* tempDoc;
        while(stillData)
        {
                constDate = NULL;
                constContributor = NULL;
                constTitle = currentPage->FirstChildElement("title")->GetText();
                constID = currentPage->FirstChildElement("revision")->FirstChildElement("id")->GetText();
                if(currentPage->FirstChildElement("revision")->FirstChildElement("timestamp"))
                        constDate = currentPage->FirstChildElement("revision")->FirstChildElement("timestamp")->GetText();
                constText = currentPage->FirstChildElement("revision")->FirstChildElement("text")->GetText();
                if(currentPage->FirstChildElement("revision")->FirstChildElement("contributor")->FirstChildElement("username"))
                        constContributor = currentPage->FirstChildElement("revision")->FirstChildElement("contributor")->FirstChildElement("username")->GetText();
                if(constTitle != NULL && constText != NULL && constID != NULL)
                {
                        ID = atoi(constID);
                        title = constTitle;
                        text = constText;
                        date = " ";
                        contributor = " ";
                        title = constTitle;
                        text = constText;
                        if(constDate != NULL)
                                date = constDate;
                        if(constContributor != NULL)
                                contributor = constContributor;
                        docWords.clear();
                        parseWords(text, docWords);
                        tempDoc = new Document(ID, title, text, docWords, date, contributor);
                        documents.push_back(tempDoc);
                }
                if(currentPage == lastPage)
                        stillData = false;
                else
                        currentPage = currentPage->NextSiblingElement("page");
        }
        addNewWordsToIndexes();
        documents.clear();
        words.clear();
        return;
}

void DocumentParser::clearIndex() {
        system("exec rm -r documentIndex");
        system("exec mkdir documentIndex");
        ofs.open("InvertedFileIndex.txt", ios::trunc);
        ofs.close();
}

struct InvalidChar
{
    bool operator()(char c) const {
        return !isprint((unsigned)c);
    }
};

void DocumentParser::parseWords(std::string& rawwords, std::vector<std::string>& theWords) {
        istringstream ss(rawwords);
        std::string parse;
        while (ss)
        {
                if(!getline(ss, parse, ' '))
                        break;
                parse.erase(std::remove_if(parse.begin(), parse.end(), InvalidChar()), parse.end()); //removes nonenglish
                parse.erase(std::remove_if(parse.begin(), parse.end(), [] (std::string::value_type ch){ return !isalpha(ch); }), parse.end()); //removes nonalphanumeric
                std::transform(parse.begin(), parse.end(), parse.begin(), ::tolower);
                for(unsigned int j=0; j<stopWords.size()-1; j++)
                        if(parse == stopWords[j])
                                parse = " ";
                if(parse.length() > 1)
                {
                        char* temp = new char[parse.length()+1];
                        theWords.push_back(parse);
                        std::strcpy(temp, parse.c_str());
                        temp[stem(temp,0,parse.size()-1)+1] = 0;
                        string copy = temp;
                        theWords.push_back(copy);
                }
        }
}

void DocumentParser::loadIndexes() {
        ifs.open("InvertedFileIndex.txt");
        while(ifs.good())
        {
                if(!getline(ifs, input))
                        break;
                istringstream ss(input);
                std::vector<std::string> line;
                while (ss)
                {
                        std::string s;
                        if(!getline(ss, s, ','))
                                break;
                        line.push_back(s);
                }
                Word* tempWord = new Word;
                tempWord->setWord(line[0]);
                for(unsigned int i=1; i<line.size(); i++)
                {
                        int temp = atoi(line[i].c_str());
                        tempWord->addID(temp);
                        i++;
                        temp = atoi(line[i].c_str());
                        tempWord->addFrequency(temp);
                }
                words.push_back(tempWord);
                ss.clear();
                line.clear();
        }
        ifs.close();
}

void DocumentParser::addNewWordsToIndexes() {
	string filepath = "/home/tgjackson/workspace/FinalProjectDSRepo/documentIndex/";
        for(unsigned int i=0; i<documents.size(); i++)
        {
        		string filepathTemp = filepath;
        		string sID = static_cast<ostringstream*>( &(ostringstream() << documents[i]->getID()) )->str();
        		filepathTemp += sID;
                //makeDI
                ofs.open(filepathTemp);
                ofs << documents[i]->getTitle() << ". Author: " << documents[i]->getContributor() << ". Date: " << documents[i]->getDate() << endl;
                ofs << documents[i]->getText() << endl;
                ofs.close();

                //makeIFI
                std::vector<std::string> temp = documents[i]->getWords();
                std::vector<int> temp2 = documents[i]->getFrequency();
                for(unsigned int j=0; j<temp.size(); j++)
                {
                        bool isRepeat = false;
                        for(unsigned int k=0; k<words.size(); k++)
                        {
                                if(temp[j] == words[k]->getWord())
                                {
                                        isRepeat = true;
                                        words[k]->addID(documents[i]->getID());
                                        words[k]->addFrequency(temp2[j]);
                                        break;
                                }
                        }
                        if(isRepeat == false)
                        {
                                Word* tempWord = new Word;
                                tempWord->setWord(temp[j]);
                                tempWord->addID(documents[i]->getID());
                                tempWord->addFrequency(temp2[j]);
                                words.push_back(tempWord);
                        }
                }
        }
        ofs.close();
        ofs.open("InvertedFileIndex.txt");
        for(unsigned int i=0; i<words.size()-1; i++)
        {
                ofs << words[i]->getWord() << ",";
                std::vector<int> temp = words[i]->getIDs();
                std::vector<int> temp2 = words[i]->getFrequencies();
                for(unsigned int k=0; k<temp.size(); k++)
                        ofs << temp[k] << "," << temp2[k] << ",";
                if(i < words.size()-2)
                	ofs << endl;
        }
        ofs.close();
}
