#ifndef T2_HTMLPARSER_H
#define T2_HTMLPARSER_H

#include <TattyUI/common/t2Settings.h>


namespace TattyUI
{
    class t2HTMLParser
    {
    public:
        t2HTMLParser();
        t2HTMLParser(string& htmlPath);

        bool openFile(string& htmlPath);

        void parse();

        void set(string& html);

        // һ��html�ļ��������Ӷ��css�ļ�
        vector<string> cssFilePaths;

    protected:
        class t2LabelParser;
        t2LabelParser *parser;

        string html;

        bool bLoaded;
    };
}

#endif