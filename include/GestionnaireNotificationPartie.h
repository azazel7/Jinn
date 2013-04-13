#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <condition_variable>
#include <mutex>

using namespace std;
class GestionnaireNotificationPartie
{
        public:
                GestionnaireNotificationPartie();
                void wait(int etat);
                void notify(int etat);
        private:
                std::condition_variable cond_var;
                std::mutex monMutex;
                int etat;
};
