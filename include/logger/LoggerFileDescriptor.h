#ifndef LoggerFileDescriptor_h
#define LoggerFileDescriptor_h

#include "logger/GestionnaireLogger.h"
#include "logger/Logger.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>

class LoggerFileDescriptor : public Logger
{
        public:
                LoggerFileDescriptor(int fd);
                LoggerFileDescriptor(int fd, bool aFermer);
                void ecrirMessage(TypeMessage typeMsg, string message);
                ~LoggerFileDescriptor();
        private:
                int fd;
                bool aFermer;
};


#endif
