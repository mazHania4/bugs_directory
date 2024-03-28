#include "Controller.h"

void Controller::analyze(const string& s) {
    if (s.substr(0,13) == "ADD NEW-GROUP"){ //ADD NEW-GROUP [group name] FIELDS ([field dataType], ...);
        string groupName = s.substr(14,s.find(' ', 14)-14);
        List<Field*> *fields = getFields(s);
        auto fieldsTbl = new HashTable<string, Tree<string>*>();
        for (int i = 0; i < fields->getSize(); ++i) {
            fieldsTbl->insert(fields->get(i)->getIdentifier(), new Tree<string>());
        }
        groups->insert(groupName, fieldsTbl);
    } else if (s.substr(0,14) == "ADD CONTACT IN"){ //ADD CONTACT IN [group name] FIELDS ([data], ...);
        string groupName = s.substr(15,s.find(' ', 15)-15);

    } else if (s.substr(0,15) == "FIND CONTACT IN"){ //FIND CONTACT IN [group name] CONTACT-FIELD [field]=[DataToCompare];
        string groupName = s.substr(16,s.find(' ', 16)-16);

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
            dot.append( "\n  subgraph cluster_f"+to_string(i)+"_t"+to_string(j)+"  {\n"
                            "    lblF"+to_string(i)+"T"+to_string(j)+" [label=\"DATA AVL-Tree\" shape = \"record\"];\n");
            dot.append(tree->dotGraphOfNode(tree->getRoot()));
            dot.append("\n  }");
            dot.append("\n  pair_f"+ to_string(i)+":c"+to_string(trees->get(j)->getKey())+" ->lblF"+to_string(i)+"T"+to_string(j));
        }

    }
    /*
     */
    dot.append("\n}");
    cout<<dot;
}

Controller::Controller() {
    groups = new HashTable<string, HashTable<string,Tree<string>*>* >();
}
