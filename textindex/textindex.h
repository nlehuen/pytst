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
    return lhs.second > rhs.second || lhs.first < rhs.first;
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

        void merge_with(const documents_scores &other) {
            if(documents_list) {
                delete documents_list;
                documents_list = 0;
            }

            storage_type::iterator lhs(documents.begin()),lhe(documents.end());
            storage_type::const_iterator rhs(other.documents.begin()),rhe(other.documents.end());
            storage_type result;

            while(lhs!=lhe && rhs!=rhe) {
                if(lhs->first < rhs->first) {
                    ++lhs;
                }
                else if(lhs->first == rhs->first) {
                    result.insert(pair_type(lhs->first,lhs->second+rhs->second));
                    ++lhs;
                    ++rhs;
                }
                else {
                    result.insert(*rhs);
                    ++rhs;
                }
            }

            while(rhs!=rhe) {
                result.insert(*rhs);
                ++rhs;
            }

            documents.swap(result);
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

        const pair_type& get_entry(int index) const {
            if(documents_list==0) {
                documents_list = new typename list_type(documents.begin(),documents.end());
                std::sort(documents_list->begin(),documents_list->end(),sort_by_score<pair_type>);
            }
            return (*documents_list)[index];
        }

        const document_type get_document(int index) const {
            return get_entry(index).first;
        }

        const int get_score(int index) const {
            return get_entry(index).second;
        }

    template <typename reader_writer> class serializer {
        public:
            void write(FILE* file, shared_ptr value) {
                documents_scores* ds = value.get();
                if(ds!=NULL) {
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
                collector() : entries(new documents_scores_type(0)), first(true) {
                }
            
                virtual void perform(const character_type* string, size_t string_length, int remaining_distance, documents_scores_pointer data) {
                    entries->merge_with(*data);
                }
                
                virtual documents_scores_pointer result() {
                    return entries;
                }
                
            private:
                bool first;
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

        int put_word(const std::basic_string< character_type > word,const document_type value) {
            documents_scores_pointer documents_scores_type = tree.get_or_build(word,&factory);
            return documents_scores_type->add_document(value,1);
        }

        int put_text(const std::basic_string< character_type > text,const document_type value) {
            typename regex_type_iterator token(text.begin(),text.end(),tokenizer);
            typename regex_type_iterator end;
            int count = 0;
            while(token != end) {
                count += put_word((*token)[0],value);
                token++;
            }
            return count;
        }
        
        documents_scores_pointer find_word(const std::basic_string< character_type > word) {
            collector c;
            tree.walk(NULL,&c,word.data(),word.size());
            return c.result();
        }
        
        documents_scores_pointer find_text(const std::basic_string< character_type > text,bool intersection) {
            typename regex_type_iterator token(text.begin(),text.end(),tokenizer);
            typename regex_type_iterator end;
            if(token!=end) {
                if(intersection) {
                    documents_scores_pointer result = find_word((*token)[0]);
                    token++;
                    while(token != end) {
                        const documents_scores_pointer additional = find_word((*token)[0]);
                        result->intersect_with(*additional);
                        token++;
                    }
                    return result;
                }
                else {
                    collector c;
                    while(token != end) {
                        std::basic_string<character_type> w = (*token)[0];
                        tree.walk(NULL,&c,const_cast<character_type*>(w.data()),w.size());
                        token++;
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
