#ifndef T2_CSSAST_H
#define T2_CSSAST_H

#include <iostream>
#include <fstream>
#include <string>
#include <TattyUI/script/css/t2CSSBison.hpp>
#include <TattyUI/script/css/t2CSSLex.h>
#include <TattyUI/script/css/t2CSSNode.h>

class t2CSSAST
{
public:
    t2CSSAST() :root(NULL) {}

    yyscan_t scaninfo;

    t2CSSNode* root;

    void saveAsDot() { saveAsDot(root); }

    // --!�������Ǳ������� ͬʱҲ�и���RTTI������ �����
    void traversal() { traversal(root); }

protected:
    void saveAsDot(t2CSSNode* root)
    {
        traversal(root);

        std::ofstream file;
        // --!Ӳ�������
        file.open("../bin/graph/AST.txt");

        printf("\n--------------------Graphviz--------------------\n");

        file << "digraph G {\n";
        file << "node[shape=rect]\n";

        traversalAsDot(root, file);

        file << "}\n";

        printf("Sueccess: Graphviz�ļ�����ɹ�\n");
        printf("------------------------------------------------\n");

        file.close(); //�ر� 
    }

    void traversal(t2CSSNode* root)
    {
        if(!root) return;

        t2CSSNode *l = root->leftChild();
        t2CSSNode *r = root->rightChild();

        traversal(l);
        root->node();
        traversal(r);
    }

    void traversalAsDot(t2CSSNode* root, std::ofstream& file)
    {
        if(!root) return;

        t2CSSNode *l = root->leftChild();
        t2CSSNode *r = root->rightChild();

        file << "_" << root << "[label=" << root->nodeName.c_str() << "]\n";

        if(l != NULL) file << "_" << root << "-> _" << l << "\n";
        if(r != NULL) file << "_" << root << "-> _" << r << "\n";

        traversalAsDot(l, file);
        traversalAsDot(r, file);
    }
};

#endif
