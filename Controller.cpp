#include "Controller.h"
#include <ctime>

void Controller::analyze(const string& s) {
    time_t now = time(0);
    string date_time = ctime(&now);
    if (s.substr(0,13) == "ADD NEW-GROUP"){ //ADD NEW-GROUP [group name] FIELDS ([field dataType], ...);
        string groupName = s.substr(14,s.find(' ', 14)-14);
        List<Field*> *fields = getFields(s.substr(14+groupName.size()));
        auto fieldsTbl = new HashTable<string, Tree<string>*>();
        for (int i = 0; i < fields->getSize(); ++i) {
            fieldsTbl->insert(fields->get(i)->getIdentifier(), new Tree<string>(fields->get(i)->getType()) );
        }
        groups->insert(groupName, fieldsTbl);
        log->add(">>"+date_time+"\tCREATED GROUP ["+groupName+"] with ["+ to_string(fields->getSize())+"] fields");
        cout<<"\nCreado exitosamente";
    } else if (s.substr(0,14) == "ADD CONTACT IN"){ //ADD CONTACT IN [group name] FIELDS ([data], ...);
        string groupName = s.substr(15,s.find(' ', 15)-15);
        List<string>*data = getData(s.substr(16+groupName.size()));
        HashTable<string, Tree<string>*> *fieldsTbl = groups->get(groupName);
        List<string> *keys = fieldsTbl->getKeys();
        int j=0;
        for (int i = data->getSize()-1; i >= 0; --i) {
            Tree<string>* tree = fieldsTbl->get(keys->get(j));
            tree->insert(data->get(i), data);
            j++;
        }
        log->add(">>"+date_time+"\tCREATED new contact in group: ["+groupName+"] ");
        cout<<"\nCreado exitosamente";
    } else if (s.substr(0,15) == "FIND CONTACT IN"){ //FIND CONTACT IN [group name] CONTACT-FIELD [field]=[DataToCompare];
        string groupName = s.substr(16,s.find(' ', 16)-16);
        int n = s.find('=', 31+groupName.size())-31-groupName.size();
        string fieldName = s.substr(31+groupName.size(),n);
        string value = s.substr(32+groupName.size()+n, s.size()-1);
        HashTable<string, Tree<string>*> *fieldsTbl = groups->get(groupName);
        Tree<string>* tree = fieldsTbl->get(fieldName);
        List<List<string>*> * found = tree->get(value);
        List<string> *keys = fieldsTbl->getKeys();
        cout<<"\n   | ";
        for (int i = 0; i < keys->getSize(); ++i) {
            cout<< keys->get(i)<<" | ";
        }
        for (int i = 0; i < found->getSize(); ++i) {
            cout<<"\n "<<i+1<<" | ";
            List<string> * f = found->get(i);
            for (int j = f->getSize()-1; j>=0 ; --j) {
                cout<<f->get(j)<<" | ";
            }
        }
        cout<<endl<<"---"<<endl;
        log->add(">>"+date_time+"\tSEARCHED contact in group: ["+groupName+"] with condition: ["
                        +fieldName+"="+value+"] found:["+to_string(found->getSize())+"]");
    } else if (s.substr(0,6) == "EXPORT"){
        string groupName = s.substr(7, s.length()-8);
        HashTable<string, Tree<string>*> *fieldsTbl = groups->get(groupName);
        List<string> *keys = fieldsTbl->getKeys();
        List<List<string> *> *fieldsL = fieldsTbl->get(keys->get(0))->get();
        files->createFolder("groups/"+groupName);
        for (int i = 0; i < fieldsL->getSize(); ++i) {
            List<string> *fields = fieldsL->get(i);
            string content = "\n";
            for (int j = 0; j < keys->getSize(); ++j) {
                content.append(keys->get(j)+": "+fields->get(fields->getSize()-1-j)+"\n");
            }
            files->writeFile("groups/"+groupName, to_string(i), content);
        }
        log->add(">>"+date_time+"\tEXPORTED group: ["+groupName+"] with ["+ to_string(fieldsL->getSize())+"] contacts");
    } else if (s.substr(0,3) == "LOG"){
        files->createFolder("logs/");
        string content;
        for (int i = log->getSize()-1; i>=0 ; --i) {
            content.append(log->get(i)+"\n");
        }
        files->writeFile("logs/", "log", content);
    } else if (s.substr(0,7) == "REPORTS"){
        List<string> *groupNames = groups->getKeys();
        int totalElements = 0;
        for (int j = 0; j < groupNames->getSize(); ++j) {
            HashTable<string, Tree<string>*> *fieldsTbl = groups->get(groupNames->get(j));
            totalElements += (fieldsTbl->get(fieldsTbl->getKeys()->get(0))->get()->getSize())*(fieldsTbl->getKeys()->getSize());
        }
        cout<<"\nNumero de datos en el sistema: "<<totalElements;
        cout<<"\nNumero de datos por grupo:";
        for (int j = 0; j < groupNames->getSize(); ++j) {
            HashTable<string, Tree<string>*> *fieldsTbl = groups->get(groupNames->get(j));
            int elements = fieldsTbl->get(fieldsTbl->getKeys()->get(0))->get()->getSize();
            cout<<"\n  "<<groupNames->get(j)<<" [ contactos:"<<elements<<", datos:"<<elements*(fieldsTbl->getKeys()->getSize())<<" ]";
        }
        cout<<"\nNumero de datos por tipo de dato: ";
        int ints, strings, dates, chars;
        for (int j = 0; j < groupNames->getSize(); ++j) {
            HashTable<string, Tree<string>*> *fieldsTbl = groups->get(groupNames->get(j));
            List<string> *fieldsNames = fieldsTbl->getKeys();
            for (int i = 0; i < fieldsNames->getSize(); ++i) {
                Tree<string>* tree =  fieldsTbl->get(fieldsNames->get(i));
                int listSize = tree->get()->getSize();
                if (tree->getType() == INTEGER) ints += listSize;
                if (tree->getType() == CHAR) chars += listSize;
                if (tree->getType() == DATE) dates += listSize;
                if (tree->getType() == STRING) strings += listSize;
            }
        }
        cout<<"\n  INTEGER: "<<ints<<"\n  DATE: "<<dates;
        cout<<"\n  CHAR: "<<chars<<"\n  STRING: "<<strings;
        log->add(">>"+date_time+"\tCONSULTED REPORTS");
    } else if (s.substr(0,5) == "GRAPH"){ // GRAPH; | GRAPH [groupName]; | GRAPH [groupName] COMPLETE;
        if (s.length()==6) {
            drawCompleteGraph();
            log->add(">>"+date_time+"\tGENERATED GRAPH");
        }
        else if (s.substr(s.length()-9,8) == "COMPLETE") {
            string groupName = s.substr(6, s.length()-16);
            drawCompleteGraph(groupName);
            log->add(">>"+date_time+"\tGENERATED COMPLETE GRAPH of ["+groupName+"]");
        } else {
            string groupName = s.substr(6, s.length()-7);
            drawGraph(groupName);
            log->add(">>"+date_time+"\tGENERATED GRAPH of ["+groupName+"]");
        }
    }
}

DataType Controller::getType(const string& s) {
    if (s == "INTEGER") return INTEGER;
    else if (s == "DATE") return DATE;
    else if (s == "CHAR") return CHAR;
    else return STRING;
}

List<Field*>* Controller::getFields(string s) {
    auto *fields = new List<Field*>();
    int j = 0, start, end = -1;
    while (s[j] != '('){ j++; }
    s = s.substr(j+1, s.size()-3-j);
    do {
        start = end + 1;
        end = (int) s.find(',', start);
        string sField = s.substr(start, end - start);
        sField.erase(sField.find_last_not_of(' ')+1); //trim suffix
        sField.erase(0, sField.find_first_not_of(' ')); //trim prefix
        int k = 0;
        while (sField[k] != ' '){ k++; }
        string sId = sField.substr(0, k);
        string sType = sField.substr(k+1, s.size()-k);
        fields->add(new Field(sId, getType(sType)));
    } while (end != -1);
    return fields;
}

void Controller::drawCompleteGraph() {
    string dot = "digraph G {\n"
                 "  fontname=\"Helvetica,Arial,sans-serif\"\n"
                 "  node [fontname=\"Helvetica,Arial,sans-serif\"]\n"
                 "  edge [fontname=\"Helvetica,Arial,sans-serif\"]\n"
                 "  graph [rankdir = \"LR\"];\n"
                 "  subgraph cluster_gs {\n"
                 "    lblG [label=\"GROUPS HashTable\" shape = \"record\"];";
    dot.append(groups->dotGraph("_g"));
    dot.append("\n  }");
    List<Pair<int, HashTable<string, Tree<string>*>*>*> *fields = groups->getValues();
    for (int i = 0; i < fields->getSize(); ++i) {
        dot.append( "\n  subgraph cluster_fs"+to_string(i)+"  {\n"
                        "    lblF"+to_string(i)+R"( [label="FIELDS HashTable" shape = "record"];)");
        dot.append(fields->get(i)->getValue()->dotGraph("_f"+ to_string(i)));
        dot.append("\n  }");
        dot.append("\n  pair_g:c"+to_string(fields->get(i)->getKey())+" ->lblF"+to_string(i));

        List<Pair<int, Tree<string>*>*> *trees = fields->get(i)->getValue()->getValues();
        for (int j = 0; j < trees->getSize(); ++j) {
            Tree<string> *tree = trees->get(j)->getValue();
            string id = "F"+to_string(i)+"T"+to_string(j);
            dot.append( "\n  subgraph cluster_f"+to_string(i)+"_t"+to_string(j)+"  {\n"
                            "    lblF"+to_string(i)+"T"+to_string(j)+R"( [label="DATA AVL-Tree" shape = "record"];)");
            dot.append(tree->dotGraphOfNode(tree->getRoot(), id));
            dot.append("\n  }");
            dot.append("\n  pair_f"+ to_string(i)+":c"+to_string(trees->get(j)->getKey())+" ->lblF"+to_string(i)+"T"+to_string(j));
        }
    }
    dot.append("\n}");
    files->generateGraph(dot);
}

void Controller::drawCompleteGraph(string groupName) {
    string dot = "digraph G {\n"
                 "  fontname=\"Helvetica,Arial,sans-serif\"\n"
                 "  node [fontname=\"Helvetica,Arial,sans-serif\"]\n"
                 "  edge [fontname=\"Helvetica,Arial,sans-serif\"]\n"
                 "  graph [rankdir = \"LR\"];\n"
                 "  subgraph cluster_g {\n"
                 "    lblG [label=\""+groupName+R"( fields HashTable" shape = "record"];)";
    dot.append(groups->get(groupName)->dotGraph("_f"));
    dot.append("\n  }");
    List<Pair<int, Tree<string>*>*> *trees = groups->get(groupName)->getValues();
    for (int j = 0; j < trees->getSize(); ++j) {
        Tree<string> *tree = trees->get(j)->getValue();
        string id = "FT"+to_string(j);
        dot.append( "\n  subgraph cluster_ft"+to_string(j)+"  {\n    lblFT"+to_string(j)+R"( [label="DATA AVL-Tree" shape = "record"];)");
        dot.append(tree->dotGraphOfNode(tree->getRoot(), id));
        dot.append("\n  }");
        dot.append("\n  pair_f:c"+to_string(trees->get(j)->getKey())+" ->lblFT"+to_string(j));
    }
    dot.append("\n}");
    files->generateGraph(dot);
}

void Controller::drawGraph(string groupName) {
    string dot = "digraph G {\n"
                 "  fontname=\"Helvetica,Arial,sans-serif\"\n"
                 "  node [fontname=\"Helvetica,Arial,sans-serif\"]\n"
                 "  edge [fontname=\"Helvetica,Arial,sans-serif\"]\n"
                 "  graph [rankdir = \"LR\"];\n"
                 "  subgraph cluster_g {\n"
                 "    lblG [label=\""+groupName+R"( fields HashTable" shape = "record"];)";
    dot.append(groups->get(groupName)->dotGraph("_f"));
    dot.append("\n  }\n}");
    files->generateGraph(dot);
}


List<string> *Controller::getData(string s) {
    auto *list = new List<string>();
    int j = 0, start, end = -1;
    while (s[j] != '('){ j++; }
    s = s.substr(j+1, s.size()-3-j);
    do {
        start = end + 1;
        end = (int) s.find(',', start);
        string data = s.substr(start, end - start);
        data.erase(data.find_last_not_of(' ')+1); //trim suffix
        data.erase(0, data.find_first_not_of(' ')); //trim prefix
        list->add(data);
    } while (end != -1);
    return list;
}

Controller::Controller() {
    groups = new HashTable<string, HashTable<string,Tree<string>*>* >();
    files = new FileManager();
    log = new List<string>();
}

void Controller::printStatus() {
    List<string> *gKeys = groups->getKeys();
    cout<<"\n------------Grupos creados:--------------";
    for (int i = 0; i < gKeys->getSize(); i++) {
        cout<<endl<<gKeys->get(i)<<" [";
        List<string> *fKeys = groups->get(gKeys->get(i))->getKeys();
        for (int j = 0; j < fKeys->getSize(); ++j) {
            cout<<fKeys->get(j);
            if (j != fKeys->getSize()-1) cout<<", ";
        }
        cout<<"]";
    }
    cout<<"\n-----------------------------------------";
    cout<<endl;
}