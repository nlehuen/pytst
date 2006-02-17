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

template <class pair> inline bool sort_by_document(const pair& lhs, const pair& rhs)
{
    return lhs.first < rhs.first;
}

template <class pair> inline bool sort_by_score(const pair& lhs, const pair& rhs)
{
    return lhs.second > rhs.second;
}

template <class item> inline bool sort_by_first_item_length_desc(const item& lhs, const item& rhs) {
    return lhs.begin()->length() > rhs.begin()->length();
}

template <typename document_type> class documents_scores {
    public:
        typedef std::pair<typename document_type,int> pair_type;
        typedef std::map<typename document_type,int> storage_type;
        typedef std::vector<pair_type> list_type;
        typedef typename storage_type::iterator iterator;
        typedef boost::shared_ptr< typename documents_scores > shared_ptr; 

        documents_scores(typename storage_type::size_type size = 0) : documents(), documents_list(0) {
        }
        
        ~documents_scores() {
            if(documents_list) {
                delete documents_list;
            }
        }


        int add_document(const document_type &doc, const int score) {
            if(documents_list) {
                delete documents_list;
                documents_list = 0;
            }

            return (documents[doc] += score);
        }

        void merge_with(const documents_scores &other,const documents_scores* intersect=0) {
            if(documents_list) {
                delete documents_list;
                documents_list = 0;
            }

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
            if(documents_list) {
                delete documents_list;
                documents_list = 0;
            }

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

        const list_type& get_sorted_list() const {
            if(documents_list==0) {
                documents_list = new typename list_type(documents.begin(),documents.end());
                std::stable_sort(documents_list->begin(),documents_list->end(),sort_by_score<pair_type>);
            }
            return *documents_list;
        }

        const document_type get_document(const int index) const {
            return get_sorted_list()[index].first;
        }

        const int get_score(const int index) const {
            return get_sorted_list()[index].second;
        }

    template <typename reader_writer> class serializer {
        public:
            void write(FILE* file, shared_ptr value) {
                documents_scores* ds = value.get();
                if(ds!=0) {
                    size_t size = ds->size();
                    fwrite(&size,sizeof(size_t),1,file);
                    for(storage_type::iterator iterator(ds->documents.begin()),end(ds->documents.end());iterator!=end;++iterator) {
                        rw.write(file,iterator->first);                        
                        fwrite(&(iterator->second),sizeof(int),1,file);
                    }
                }
                else {
                    size_t size=0;
                    fwrite(&size,sizeof(size_t),1,file);
                }
            }
            
            shared_ptr read(FILE* file) {
                size_t size;
                fread(&size,sizeof(size_t),1,file);
                documents_scores* result = new documents_scores(size);
                for(size_t i=0;i<size;++i) {
                    document_type doc(rw.read(file));
                    int score;
                    fread(&score,sizeof(int),1,file);
                    result->documents.insert(pair_type(doc,score));
                }

                return shared_ptr(result);
            }

        private:
            typename reader_writer rw;
    };

    private:
        storage_type documents;
        mutable list_type* documents_list;
};


template < typename character_type, typename document_type, typename reader_writer > class textindex {
    public:
        typedef documents_scores< typename document_type > documents_scores_type;
        typedef boost::shared_ptr< typename documents_scores_type > documents_scores_pointer; 
        typedef typename documents_scores_type::serializer<typename reader_writer> serializer;
        typedef string_tst < character_type, documents_scores_pointer, memory_storage<character_type,documents_scores_pointer>, serializer > tree_type;

        typedef boost::basic_regex < character_type > regex_type;
        typedef boost::regex_iterator<typename std::basic_string<character_type>::const_iterator> regex_type_iterator;
    
        class collector : public action< character_type, documents_scores_pointer > {
            public:
                collector(collector* _intersect=0) : intersect(_intersect), entries(new documents_scores_type(0)) {
                }
            
                virtual void perform(const character_type* string, size_t string_length, int remaining_distance, documents_scores_pointer data) {
                    entries->merge_with(*data,intersect ? intersect->entries.get() : 0);
                }
                
                virtual documents_scores_pointer result() {
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
        
        class documents_scores_type_factory : public filter< character_type, documents_scores_pointer > {
            public:
                virtual documents_scores_pointer perform(const character_type* string, size_t string_length, int remaining_distance, documents_scores_pointer data) {
                    return documents_scores_pointer(new documents_scores_type(0));
                }
        };

        textindex() : tree(new tree_type::storage_type(16),tree_type::value_type()), tokenizer(L"\\b\\w+\\b"), factory() {
        }

        int put_word(const std::basic_string< character_type >& word,const document_type& value) {
            if(word.size()>2) {
                documents_scores_pointer documents_scores_type = tree.get_or_build(word,&factory);
                return documents_scores_type->add_document(value,1);
            }
            else {
                return 0;
            }
        }

        int put_text(const std::basic_string< character_type >& text,const document_type& value) {
            typename regex_type_iterator token(text.begin(),text.end(),tokenizer);
            typename regex_type_iterator end;
            int count = 0;
            while(token != end) {
                count += put_word(token->begin()->str(),value);
                ++token;
            }
            return count;
        }
        
        documents_scores_pointer find_word(const std::basic_string< character_type >& word) {
            collector c;
            tree.walk2(0,&c,word);
            return c.result();
        }
        
        documents_scores_pointer find_text(const std::basic_string< character_type >& text,bool intersection) {
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
                        tree.walk2(0,&c,tokens_iterator->begin()->str());
                        ++tokens_iterator;
                        while(tokens_iterator != tokens.end()) {
                            // on se fiche de la longueur des autres mots
                            collector c2(&c);
                            tree.walk2(0,&c2,tokens_iterator->begin()->str());
                            c.intersect_with(c2);
                            ++tokens_iterator;
                        }
                    }

                    return c.result();
                }
                else {
                    collector c;
                    while(token != end) {
                        std::basic_string<character_type> word = token->begin()->str();
                        tree.walk2(0,&c,word);
                        ++token;
                    }
                    return c.result();
                }
            }
            else {
                return documents_scores_pointer(new documents_scores_type(0));
            }
        }

        void pack() {
            tree.pack();
        }

        void write(FILE* file) {
            tree.write(file);
        }

        void read(FILE* file) {
            tree.read(file);
        }

    private:
        tree_type tree;
        regex_type tokenizer;
        documents_scores_type_factory factory;
};

#endif
