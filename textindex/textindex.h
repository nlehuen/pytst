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

template <class pair> bool invert_2nd_member(const pair& lhs, const pair& rhs)
{
    return lhs.second > rhs.second || lhs.first < rhs.first;
}

template < typename character_type, typename document_type, typename reader_writer > class textindex {
    public:
        typedef std::map< document_type, int > documents_score_map;
        typedef boost::shared_ptr< documents_score_map > documents_score_map_pointer; 
        typedef std::vector< std::pair<document_type, int> > documents_score_list;
        typedef boost::shared_ptr< documents_score_list > documents_score_list_pointer; 
        
    private:
        class serializer {
            public:
                void write(FILE* file, documents_score_map_pointer value) {
                    documents_score_map* map = value.get();
                    if(map!=NULL) {
                        size_t size = map->size();
                        fwrite(&size,sizeof(size_t),1,file);
                        for(documents_score_map::iterator iterator(map->begin()),end(map->end());iterator!=end;++iterator) {
                            rw.write(file,iterator->first);                        
                            fwrite(&(iterator->second),sizeof(int),1,file);
                        }
                    }
                    else {
                        size_t size=0;
                        fwrite(&size,sizeof(size_t),1,file);
                    }
                }
                
                documents_score_map_pointer read(FILE* file) {
                    documents_score_map* result = new documents_score_map();

                    size_t size;
                    fread(&size,sizeof(size_t),1,file);
                    for(size_t i=0;i<size;++i) {
                        document_type doc(rw.read(file));
                        int score;
                        fread(&score,sizeof(int),1,file);
                        (*result)[doc] = score;
                    }

                    return documents_score_map_pointer(result);
                }

            private:
                typename reader_writer rw;
        };

    public:
        typedef string_tst < character_type, documents_score_map_pointer, memory_storage<character_type,documents_score_map_pointer>, serializer> tree_type;
        
        typedef boost::basic_regex < character_type > regex_type;
        typedef boost::regex_iterator<typename std::basic_string<character_type>::const_iterator> regex_type_iterator;
    
        class collector : public action< character_type, documents_score_map_pointer > {
            public:
                collector() : entries(new documents_score_map()), first(true) {
                }
            
                virtual void perform(const character_type* string, size_t string_length, int remaining_distance, documents_score_map_pointer data) {
                    for(documents_score_map_pointer::element_type::iterator s(data->begin()),e(data->end());s != e;s++) {
                        (*entries)[s->first] += s->second;
                    }
                }
                
                virtual documents_score_map_pointer result() {
                    return entries;
                }
                
            private:
                bool first;
                documents_score_map_pointer entries;
        };
        
        class documents_score_map_factory : public filter< character_type, boost::shared_ptr< std::map< document_type, int > > > {
            public:
                virtual documents_score_map_pointer perform(const character_type* string, size_t string_length, int remaining_distance, documents_score_map_pointer data) {
                    return documents_score_map_pointer(new documents_score_map());
                }
        };

        textindex() : tree(new tree_type::storage_type(16),tree_type::value_type()), tokenizer(L"\\b\\w+\\b"), factory() {
        }

        int put_word(const std::basic_string< character_type > word,const document_type value) {
            documents_score_map_pointer documents_score_map = tree.get_or_build(word,&factory);
            return ++((*documents_score_map)[value]);
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
        
        documents_score_map_pointer find_word(const std::basic_string< character_type > word) {
            collector c;
            tree.walk(NULL,&c,word.data(),word.size());
            return c.result();
        }
        
        documents_score_map_pointer find_text(const std::basic_string< character_type > text,bool intersection) {
            typename regex_type_iterator token(text.begin(),text.end(),tokenizer);
            typename regex_type_iterator end;
            if(token!=end) {
                if(intersection) {
                    documents_score_map_pointer documents_score_map = find_word((*token)[0]);
                    token++;
                    while(token != end) {
                        documents_score_map_pointer additional = find_word((*token)[0]);

                        for(documents_score_map_pointer::element_type::iterator s(additional->begin()),e(additional->end());s != e;s++) {
                            documents_score_map_pointer::element_type::iterator found(documents_score_map->find(s->first));
                            if(found!=documents_score_map->end()) {
                                found->second += s->second;
                            }
                        }

                        for(documents_score_map_pointer::element_type::iterator s(documents_score_map->begin()),e(documents_score_map->end());s != e;) {
                            documents_score_map_pointer::element_type::iterator found(additional->find(s->first));
                            if(found==additional->end()) {
                                documents_score_map->erase((s++)->first);
                            }
                            else {
                                s++;
                            }
                        }

                        token++;
                    }
                    return documents_score_map;
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
                return documents_score_map_pointer(new documents_score_map());
            }
        }

        documents_score_list_pointer to_list(documents_score_map_pointer entries, bool sort) {
            documents_score_list_pointer result(new documents_score_list(entries->begin(),entries->end()));
            if(sort) {
                std::sort(result->begin(),result->end(),invert_2nd_member<documents_score_list_pointer::element_type::iterator::value_type>);
            }
            return result;
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
        documents_score_map_factory factory;
};

#endif