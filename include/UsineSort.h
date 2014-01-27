#ifndef UsineSort_h
#define UsineSort_h

#include "sort/Sort.h"
#include <dirent.h>
#include <map>

class Sort;
class RecetteSort;
/**
 * @brief Classe UsineSort
 */
class UsineSort
{

public:
    /**
     * @brief fabriqueSort
     *  Permet de créer un sort via son nom
     * @param nom nom du sort à créer
     * @return Un pointeur vers le sort créé
     */
    static Sort* fabriqueSort(string nom);
    /**
     * @brief fabriqueSort
     *  Permet de dupliquer un sort à partir d'un autre
     * @param sortModele Le sort initial
     * @return Un pointeur vers un sort qui est la copie de celui passé en argument
     */
    static Sort* fabriqueSort(Sort* sortModele);
    /**
     * @brief liste
     *  Liste les sorts que la classe peut générer
     * @return Un vector de string contenant les noms des sorts disponible
     */
    static vector<string> liste();

    static void chargerConfiguration(string nomDossier);
private:
    static map<string, RecetteSort> listeSort;
    static map<string, string> listeActionChronique();
    static map<string, string> listeAppliquerSurCase();
};
#endif // UsineSort

//class ai_factory{
//public:
//        typedef boost::shared_ptr< ai_factory > factory_ptr;
//        typedef std::map<std::string, factory_ptr> factory_map;
//        typedef std::pair<const std::string, factory_ptr> factory_map_pair;

//        static factory_map& get_list() {
//                static factory_map *ai_factories;
//                if (ai_factories==NULL) {
//                        ai_factories = new factory_map;
//                }
//                return *ai_factories;
//        }

//        virtual ai_ptr get_new_instance( ai_context &context, const config &cfg) = 0;

//        ai_factory( const std::string &name )
//        {
//                std::cerr << "Add " << name << " to the list of AI" << std::endl;
//                factory_ptr ptr_to_this(this);
//                get_list().insert(make_pair(name,ptr_to_this));
//        }

//        virtual ~ai_factory() {}
//};


//template<class AI>
//class register_ai_factory : public ai_factory {
//public:
//        register_ai_factory( const std::string &name )
//                : ai_factory( name )
//        {
//        }

//        virtual ai_ptr get_new_instance( ai_context &context, const config &cfg){
//                ai_ptr a(new AI(context,cfg));
//                a->on_create();
//                return a;
//        }
//};
