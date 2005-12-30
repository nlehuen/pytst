/* 
 # $Id$
 # Copyright (C) 2004-2005 Nicolas Lehuen <nicolas@lehuen.com>
 #
 # This library is free software; you can redistribute it and/or
 # modify it under the terms of the GNU Lesser General Public
 # License as published by the Free Software Foundation; either
 # version 2.1 of the License, or (at your option) any later version.
 #
 # This library is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 # Lesser General Public License for more details.
 #
 # You should have received a copy of the GNU Lesser General Public
 # License along with this library; if not, write to the Free Software
 # Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef __MEMORY_STORAGE__H_INCLUDED__
#define __MEMORY_STORAGE__H_INCLUDED__

#include <vector>

template<typename S,typename T> class memory_storage {
public:
    typedef typename std::vector< tst_node<S,T> > array_type;
    typedef typename array_type::iterator iterator_type;

    memory_storage(int initial_size) : array(initial_size), empty(UNDEFINED_INDEX) {
    }

    ~memory_storage() {
    }

    inline tst_node<S,T>* get(int index) {
        return &(array[index]);
    }

    inline void delete_node(int index) {
        get(index)->next = empty;
        empty = index;
    }

    void new_node(node_info<S,T>* info);
    void pack();
    
protected:
    array_type array;
    int empty;
};

template<typename S,typename T> void memory_storage<S,T>::new_node(node_info<S,T>* info) {
    if(empty!=UNDEFINED_INDEX) {
        // si on a un noeud vide on l'utilise.
        info->index=empty;
        info->node=get(empty);
        info->height=0;
        
        // on passe au noeud vide suivant.
        empty = get(empty)->next;
    }
    else {
        // on construit un noeud supplémentaire dans le tableau.
        info->index = array.size();
        array.push_back(tst_node<S,T>());
        // array.resize(next); // moins rapide !
        info->node=get(info->index);
    }
}

template<typename S,typename T> void memory_storage<S,T>::pack() {
    size_t last_index = array.size() - 1;

    // On va essayer de déplacer les noeuds en fin de vecteur vers
    // les noeuds vides, s'il y en a.
    while(empty!=UNDEFINED_INDEX) {
        int next_empty = get(empty)->next; 
    
        if(empty==last_index) {
            // Le noeud vide est en dernière position
            // On le sort de la chaîne des noeuds vides
            empty = next_empty;
            // Et on n'en a plus besoin
            last_index--;
        }
        else if(next_empty==last_index) {
            // Le noeud suivant est le dernier noeud
            // Il est donc inutile de procéder à l'échange :
            // On sort le suivant de la chaine des noeuds vide
            get(empty)->next = get(next_empty)->next; 
            // et on le supprime
            last_index--;
        }
        else {
            // On échange le noeud vide actuel
            // avec le dernier noeud
            array[empty] = array[last_index];
            
            // On réécrit tout le tableau
            // Une seule réécriture suffit puisqu'un noeud n'a qu'un seul
            // parent
            for(iterator_type i=array.begin(),e=array.end();i!=e;i++) {
                if(i->right == last_index) {
                    i->right = empty;
                    break;
                }
                else if(i->left == last_index) {
                    i->left = empty;
                    break;
                }
                else if(i->next == last_index) {
                    i->next = empty;
                    break;
                }
            }
            
            // On peut ensuite éliminer le dernier noeud
            last_index--;
            // Et passer au noeud vide suivant.
            empty = next_empty;
        }

    }
    
    
    if(last_index+1<array.size()) {
        // On réduit le nombre d'éléments du vecteur si nécessaire
        array.resize(last_index+1);
    }

    // On réduit la taille des réservations du vecteur.
    std::vector< tst_node<S,T> >(array).swap(array);
}

#endif
