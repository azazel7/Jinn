#include "logger/LoggerFileDescriptor.h"

LoggerFileDescriptor::LoggerFileDescriptor(int fd)
{
    this->fd = fd;
    this->aFermer = true;
    this->aDelete = true;
}
LoggerFileDescriptor::LoggerFileDescriptor(int fd, bool aFermer)
{
    this->fd = fd;
    this->aFermer = aFermer;
    this->aDelete = true;
}
void LoggerFileDescriptor::ecrirMessage(TypeMessage typeMsg, string message)
{
    string type = "";
    string complement = "";
    switch(typeMsg)
    {
            case FATAL:
                    type = "[x_x]";
                    complement = " : ";
                    complement += strerror(errno);
            break;
            case ERROR:
                    type = "[-]";
                    complement = " : ";
                    complement += strerror(errno);
            break;
            case WARN:
                    type = "[~]";
            break;
            case INFO:
                    type = "[i]";
            break;
            case SUCCESS:
                    type = "[+]";
            break;
    }
    type = type + " ";
    type = type + message + complement + "\n";
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
