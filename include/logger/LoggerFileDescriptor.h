#ifndef LoggerFileDescriptor_h
#define LoggerFileDescriptor_h

#include "logger/GestionnaireLogger.h"
#include "logger/Logger.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <string.h>

class LoggerFileDescriptor : public Logger
{
public:
    /**
     * @brief LoggerFileDescriptor Constructeur
     * @param fd Le descripteur de fichier dans lequel écrire
     */
    LoggerFileDescriptor(int fd);

    /**
     * @brief LoggerFileDescriptor Constructeur
     * @param fd Le descripteur de fichier dans lequel écrire
     * @param aFermer indique s'il faut fermer le descripteur de fichier à la destruction
     */
    LoggerFileDescriptor(int fd, bool aFermer);
    void ecrirMessage(TypeMessage typeMsg, string message);
    ~LoggerFileDescriptor();
private:
    int fd;
    bool aFermer;
};


#endif
