#include "Controller.h"

void Controller::analyze(const string& s) {
    if (s.substr(0,13) == "ADD NEW-GROUP"){ //ADD NEW-GROUP [group name] FIELDS ([field dataType], ...);
        string groupName = s.substr(14,s.find(' ', 14)-14);
        List<Field*> *fields = getFields(s.substr(14+groupName.size()));
        auto fieldsTbl = new HashTable<string, Tree<string>*>();
        for (int i = 0; i < fields->getSize(); ++i) {
            fieldsTbl->insert(fields->get(i)->getIdentifier(), new Tree<string>());
        }
        groups->insert(groupName, fieldsTbl);
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
    } else if (s.substr(0,15) == "FIND CONTACT IN"){ //FIND CONTACT IN [group name] CONTACT-FIELD [field]=[DataToCompare];
        //FIND CONTACT IN amigos CONTACT-FIELD nombre=Pedro;
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
        cout<<endl;
    } else if (s.substr(0,6) == "EXPORT"){

    } else if (s.substr(0,7) == "REPORTS"){

    } else if (s.substr(0,5) == "GRAPH"){
        drawCompleteGraph();
    }
}

Type Controller::getType(const string& s) {
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
                 "    lblG [label=\"GROUPS HashTable\" shape = \"record\"];\n";
    dot.append(groups->dotGraph("_g"));
    dot.append("\n  }");
    List<Pair<int, HashTable<string, Tree<string>*>*>*> *fields = groups->getValues();
    for (int i = 0; i < fields->getSize(); ++i) {
        dot.append( "\n  subgraph cluster_fs"+to_string(i)+"  {\n"
                        "    lblF"+to_string(i)+" [label=\"FIELDS HashTable\" shape = \"record\"];\n");
        dot.append(fields->get(i)->getValue()->dotGraph("_f"+ to_string(i)));
        dot.append("\n  }");
        dot.append("\n  pair_g:c"+to_string(fields->get(i)->getKey())+" ->lblF"+to_string(i));

        List<Pair<int, Tree<string>*>*> *trees = fields->get(i)->getValue()->getValues();
        for (int j = 0; j < trees->getSize(); ++j) {
            Tree<string> *tree = trees->get(j)->getValue();
            string id = "F"+to_string(i)+"T"+to_string(j);
            dot.append( "\n  subgraph cluster_f"+to_string(i)+"_t"+to_string(j)+"  {\n"
                            "    lblF"+to_string(i)+"T"+to_string(j)+" [label=\"DATA AVL-Tree\" shape = \"record\"];\n");
            dot.append(tree->dotGraphOfNode(tree->getRoot(), id));
            dot.append("\n  }");
            dot.append("\n  pair_f"+ to_string(i)+":c"+to_string(trees->get(j)->getKey())+" ->lblF"+to_string(i)+"T"+to_string(j));
        }

    }
    dot.append("\n}");
    cout<<dot;
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
        int k = 0;
        list->add(data);
    } while (end != -1);
    return list;
}

Controller::Controller() {
    groups = new HashTable<string, HashTable<string,Tree<string>*>* >();
}
