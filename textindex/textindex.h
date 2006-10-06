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
#ifndef __TEXTINDEX__H_INCLUDED__
#define __TEXTINDEX__H_INCLUDED__

#include "tst.h"

#include <hash_map>
#include <boost/shared_ptr.hpp>
#include <boost/regex.hpp>
#include <iostream>

template <class pair>
inline bool sort_by_document(const pair& lhs, const pair& rhs)
{
    return lhs.first < rhs.first;
}

template <class pair>
inline bool sort_by_score(const pair& lhs, const pair& rhs)
{
    return lhs.second > rhs.second;
}

template <class item>
inline bool sort_by_first_item_length_desc(const item& lhs, const item& rhs) {
    return lhs.begin()->length() > rhs.begin()->length();
}

template <typename document_id_type, typename score_type>
class documents_scores {
    public:
        typedef std::pair<document_id_type,score_type> pair_type;
        typedef std::map<document_id_type,score_type> storage_type;
        typedef typename storage_type::const_iterator const_iterator;
        typedef boost::shared_ptr< typename documents_scores > shared_ptr; 

        documents_scores(typename storage_type::size_type size = 0) : documents() {
        }
        
        int add_document(const document_id_type &document, const score_type score) {
            return (documents[document] += score);
        }

        typename storage_type::size_type remove_document(const document_id_type &document) {
            return documents.erase(document);
        }

        void merge_with(const documents_scores &other,const documents_scores* intersect=0) {
            storage_type::iterator lhs(documents.begin());
            storage_type::const_iterator rhs(other.documents.begin());

            while(lhs!=documents.end() && rhs!=other.documents.end()) {
                if(lhs->first < rhs->first) {
                    ++lhs;
                }
                else if(lhs->first == rhs->first) {
                    lhs->second += rhs->second;
                    ++lhs;
                    ++rhs;
                }
                else {
                    if(intersect==0 || intersect->documents.find(rhs->first)!=intersect->documents.end()) {
                        documents.insert(*rhs);
                    }
                    ++rhs;
                }
            }

            while(rhs!=other.documents.end()) {
                if(intersect==0 || intersect->documents.find(rhs->first)!=intersect->documents.end()) {
                    documents.insert(*rhs);
                }
                ++rhs;
            }
        }

        void intersect_with(const documents_scores &other) {
            storage_type::iterator lhs(documents.begin());
            storage_type::const_iterator rhs(other.documents.begin());
            
            while(lhs!=documents.end() && rhs!=other.documents.end()) {
                if(lhs->first < rhs->first) {
                    lhs = documents.erase(lhs);
                }
                else if(lhs->first == rhs->first) {
                    lhs->second += rhs->second;
                    ++lhs;
                    ++rhs;
                }
                else {
                    ++rhs;
                }
            }
            documents.erase(lhs,documents.end());
        }

        const typename storage_type::size_type size() const {
            return documents.size();
        }

        const const_iterator begin() const {
            return documents.begin();
        }

        const const_iterator end() const {
            return documents.end();
        }

    class serializer {
       public:
            void write(std::ostream& file, shared_ptr value) {
                documents_scores* ds = value.get();
                if(ds!=0) {
                    size_t size = ds->size();
                    file.write((char*)(&size),sizeof(size_t));
                    for(storage_type::iterator iterator(ds->documents.begin()),end(ds->documents.end());iterator!=end;++iterator) {
                        file.write((char*)(&(iterator->first)),sizeof(document_id_type));
                        file.write((char*)(&(iterator->second)),sizeof(score_type));
                    }
                }
                else {
                    size_t size=0;
                    file.write((char*)(&size),sizeof(size_t));
                }
            }
            
            shared_ptr read(std::istream& file) {
                size_t size;
                file.read((char*)(&size),sizeof(size_t));

                if(size>0) {
                    documents_scores* result = new documents_scores(size);
                    for(size_t i=0;i<size;++i) {
                        document_id_type document_id;
                        file.read((char*)(&document_id),sizeof(document_id_type));
                        score_type score;
                        file.read((char*)(&score),sizeof(score_type));
                        result->documents[document_id]=score;
                    }

                    return shared_ptr(result);
                }
                else {
                    return shared_ptr();
                }
            }
    };

    private:
        storage_type documents;
};


template < typename character_type, typename document_type, typename reader_writer, typename document_id_type = unsigned int, typename score_type = unsigned int>
class textindex {
    public:
        // Chaînes de caractères
        typedef std::basic_string<typename character_type> string_type;

        // Mapping document <=> id
        typedef std::map< typename document_type, document_id_type > documents_ids_type;
        typedef std::map< document_id_type, typename document_type > reversed_documents_ids_type;

        // Types nécessaire à la construction du TST
        typedef documents_scores< typename document_id_type, typename score_type > documents_scores_type;
        typedef typename documents_scores_type::shared_ptr documents_scores_pointer; 
        typedef typename documents_scores_type::serializer documents_scores_serializer; 
        typedef tst < character_type, typename documents_scores_pointer, memory_storage<character_type, typename documents_scores_pointer>, documents_scores_serializer, typename string_type > tree_type;

        // Résultat des requêtes
        typedef std::pair< document_type, score_type > pair_type;
        typedef std::vector< pair_type > result_type;
        typedef boost::shared_ptr< result_type > result_pointer;

        // Regexes
        typedef boost::basic_regex < character_type > regex_type;
        typedef boost::regex_iterator<typename string_type::const_iterator> regex_type_iterator;

        class collector : public tst_action< typename character_type, typename documents_scores_pointer, typename string_type> {
            public:
                collector(collector* _intersect=0) : intersect(_intersect), entries(new documents_scores_type(0)) {
                }
            
                virtual void perform(const typename string_type& string, int remaining_distance, typename documents_scores_pointer data) {
                    entries->merge_with(*data,intersect ? intersect->entries.get() : 0);
                }
                
                virtual typename documents_scores_pointer result() {
                    return entries;
                }
                
                void set_intersect(bool _intersect) {
                    intersect = _intersect;
                }

                void merge_with(collector& c) {
                    entries->merge_with(*(c.entries),intersect ? intersect->entries.get() : 0);
                }

                void intersect_with(collector& c) {
                    entries->intersect_with(*(c.entries));
                }

        private:
                collector* intersect;
                documents_scores_pointer entries;
        };
        
        class eraser : public tst_action< typename character_type, typename documents_scores_pointer, typename string_type > {
            public:
                eraser(document_id_type _document_id) : document_id(_document_id) {
                }
            
                virtual void perform(const typename string_type& string, int remaining_distance, typename documents_scores_pointer data) {
                    data->remove_document(document_id);
                }
                
                virtual typename documents_scores_pointer result() {
                    return documents_scores_pointer();
                }
                    
            private:
                document_id_type document_id;
        };

        class cleaner : public tst_action< typename character_type, typename documents_scores_pointer, typename string_type > {
            public:
                typedef boost::shared_ptr< std::vector< typename string_type > > result_type;

                cleaner(typename tree_type* _tree) : tree(_tree), empty_words(new std::vector< typename string_type >() ) {
                }
            
                virtual void perform(const typename string_type& string, int remaining_distance, typename documents_scores_pointer data) {
                    if(data->size()==0) {
                        empty_words->push_back(string);
                    }
                }
                
                virtual typename documents_scores_pointer result() {
                    for(cleaner::result_type::element_type::const_iterator item(empty_words->begin()),end(empty_words->end());item!=end;++item) {
                        tree->remove(*item);
                    }
                    return documents_scores_pointer();
                }

            private:
                typename tree_type* tree;
                typename result_type empty_words;
        };

        class documents_scores_type_factory : public tst_filter< character_type, documents_scores_pointer, typename string_type > {
            public:
                virtual documents_scores_pointer perform(const typename string_type& string, int remaining_distance, typename documents_scores_pointer data) {
                    return typename documents_scores_pointer(new documents_scores_type(0));
                }
        };

        textindex() :
            tree(), tokenizer(L"[\\w\\?\\*\\-]+"),
            factory(),
            next_document_id(0) {
        }

        int put_word(const typename string_type& word,const document_type& document) {
            if(word.size()>2) {
                documents_scores_pointer scores(tree.get_or_build(word,&factory));
                return scores->add_document(get_document_id(document),1);
            }
            else {
                return 0;
            }
        }

        int put_text(const typename string_type& text,const document_type& document) {
            typename regex_type_iterator token(text.begin(),text.end(),tokenizer);
            typename regex_type_iterator end;
            int count = 0;
            document_id_type document_id(get_document_id(document));
            while(token != end) {
                documents_scores_pointer scores(tree.get_or_build(token->begin()->str(),&factory));
                count += scores->add_document(document_id,1);
                ++token;
            }
            return count;
        }
        
        void remove_document(const document_type& document) {
            documents_ids_type::iterator document_position(ids.find(document));
            if(document_position != ids.end()) {
                document_id_type document_id(document_position->second);
                ids.erase(document_position);
                reversed_ids.erase(document_id);

                eraser e(document_id);
                tree.walk(0,&e);
            }
        }

        result_pointer find_word(const typename string_type& word) {
            collector c;
            tree.match(word,0,&c);
            return convert_to_result(c);
        }
        
        result_pointer find_text(const typename string_type& text,bool intersection) {
            typename regex_type_iterator token(text.begin(),text.end(),tokenizer);
            typename regex_type_iterator end;
            if(token!=end) {
                if(intersection) {
                    // On va trier les tokens par ordre décroissant de longueur afin
                    // de mettre le plus limitant en premier
                    std::vector< regex_type_iterator::value_type > tokens(token,end);
                    std::sort(tokens.begin(),tokens.end(),sort_by_first_item_length_desc<regex_type_iterator::value_type>);
                    std::vector< regex_type_iterator::value_type >::const_iterator tokens_iterator(tokens.begin());

                    collector c;
                    // Le mot le plus long doit faire au moins 3 caractères.
                    if(tokens_iterator->begin()->length()>2) {
                        tree.match(tokens_iterator->begin()->str(),0,&c);
                        ++tokens_iterator;
                        while(tokens_iterator != tokens.end()) {
                            // on se fiche de la longueur des autres mots
                            collector c2(&c);
                            tree.match(tokens_iterator->begin()->str(),0,&c2);
                            c.intersect_with(c2);
                            ++tokens_iterator;
                        }
                    }

                    return convert_to_result(c);
                }
                else {
                    collector c;
                    while(token != end) {
                        if(token->begin()->length()>2) {
                            typename string_type word = token->begin()->str();
                            tree.match(word,0,&c);
                        }
                        ++token;
                    }
                    return convert_to_result(c);
                }
            }
            else {
                return result_pointer(new result_type());
            }
        }

        void pack() {
            cleaner c(&tree);
            tree.walk(NULL,&c);
            tree.pack();
        }

        void write(std::ostream& file) const {
            // On écrit l'arbre
            tree.write(file);
            
            // On écrit le prochain id de document
            file.write((char*)(&next_document_id),sizeof(document_id_type));

            // On écrit la taille du lexique
            documents_ids_type::size_type size = ids.size();
            file.write((char*)(&size),sizeof(documents_ids_type::size_type));
            
            // On écrit le lexique
            reader_writer rw;
            for(documents_ids_type::const_iterator item(ids.begin()),end(ids.end());item!=end;item++) {
                rw.write(file,item->first);
                file.write((char*)(&(item->second)),sizeof(document_id_type));
            }
        }

        void read(std::istream& file) {
            // On lit l'arbre
            tree.read(file);

            // On lit le prochain id de document
            file.read((char*)(&next_document_id),sizeof(document_id_type));
            
            // On lit la taille du lexique
            documents_ids_type::size_type size;
            file.read((char*)(&size),sizeof(documents_ids_type::size_type));
            
            // On lit le lexique dans de nouveaux objets
            reader_writer rw;
            documents_ids_type new_ids;
            reversed_documents_ids_type new_reversed_ids;
            for(;size>0;--size) {
                document_type document(rw.read(file));
                document_id_type document_id;
                file.read((char*)(&document_id),sizeof(document_id_type));

                new_ids[document] = document_id;
                new_reversed_ids[document_id] = document;
            }

            // On met les nouveaux objets en place
            ids.swap(new_ids);
            reversed_ids.swap(new_reversed_ids);
        }

    private:
        const document_id_type get_document_id(const document_type& document) {
            documents_ids_type::const_iterator document_id(ids.find(document));
            if(document_id == ids.end()) {
                document_id_type new_id = next_document_id++;
                ids[document] = new_id;
                reversed_ids[new_id] = document;
                return new_id;
            }
            else {
                return document_id->second;
            }
        }

        const document_type get_document(const document_id_type& document_id) const {
            reversed_documents_ids_type::const_iterator document(reversed_ids.find(document_id));
            if(document == reversed_ids.end()) {
                return document_type();
            }
            else {
                return document->second;
            }
        }

        const result_pointer convert_to_result(collector& to_convert) const {
            documents_scores_type* scores(to_convert.result().get());
            result_type* p_result = new result_type();
            result_pointer result(p_result);
            p_result->reserve(scores->size());
            for(documents_scores_type::const_iterator item(scores->begin()),end(scores->end());item!=end;++item) {
                document_type document = get_document(item->first);
                p_result->push_back(pair_type(document,item->second));
            }
            std::sort(p_result->begin(),p_result->end(),sort_by_score<pair_type>);
            return result;
        }

        // Données à sauver
        document_id_type next_document_id;
        documents_ids_type ids;
        tree_type tree;
        
        // Données transitoires
        reversed_documents_ids_type reversed_ids;
        
        // Utilitaires
        const regex_type tokenizer;
        documents_scores_type_factory factory;
};

#endif
