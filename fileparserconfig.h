#ifndef FILEPARSERCONFIG_H
#define FILEPARSERCONFIG_H
#include <QList>
#include <fileparser.h>

class FileParserConfig
{
public:
    static FileParserConfig *instance();
    QList<FileParser> fileParserList;
    void loadConfig();
    void writeConfig();

private:
    FileParserConfig();
    static FileParserConfig *s_instance;

};

#endif // FILEPARSERCONFIG_H
