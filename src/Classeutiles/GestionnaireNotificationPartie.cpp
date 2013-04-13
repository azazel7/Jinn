#include <GestionnaireNotificationPartie.h>

GestionnaireNotificationPartie::GestionnaireNotificationPartie()
{
    this->etat = 0;
}

void GestionnaireNotificationPartie::wait(int etat)
{
    this->etat = etat;
    std::unique_lock<std::mutex> lock(m);
    this->cond_var.wait(lock);

}

void GestionnaireNotificationPartie::notify(int etat)
{
    if(etat == this->etat)
    {
        this->cond_var.notify_one();
    }
}
