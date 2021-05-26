#ifndef LO21___PRINTEMPS_2021___PROJET_CELLULUT_OUTILS_H
#define LO21___PRINTEMPS_2021___PROJET_CELLULUT_OUTILS_H

// int char_to_int(char * c); // convertir un objet de type char en objet de type int

class AutomateException
{
public:
    AutomateException(const std::string& message):info(message) {}
    std::string getInfo() const { return info; }
private:
    std::string info;
};

#endif //LO21___PRINTEMPS_2021___PROJET_CELLULUT_OUTILS_H
