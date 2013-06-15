#include "logger/LoggerFileDescriptor.h"

LoggerFileDescriptor::LoggerFileDescriptor(int fd)
{
    this->fd = fd;
    this->aFermer = true;
}
LoggerFileDescriptor::LoggerFileDescriptor(int fd, bool aFermer)
{
    this->fd = fd;
    this->aFermer = aFermer;
}
void LoggerFileDescriptor::ecrirMessage(TypeMessage typeMsg, string message)
{
    string type = "";
    switch(typeMsg)
    {
            case FATAL:
                    type = "[x_x]";
            break;
            case ERREUR:
                    type = "[-]";
            break;
            case WARN:
                    type = "[~]";
            break;
            case INFO:
                    type = "[i]";
            break;
    }
    type = type + " ";
    type = type + message + "\n";
    write(this->fd, type.c_str(), type.size());

}
LoggerFileDescriptor::~LoggerFileDescriptor()
{
    fsync(this->fd);
    if(this->aFermer == true)
    {
        close(this->fd);
    }
}
