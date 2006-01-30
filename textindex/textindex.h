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

#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/regex.hpp>

template < class character_type, class document_type > class textindex : private filter< character_type, boost::shared_ptr< std::map< document_type, int > > > {
    public:
        typedef std::map< document_type, int > documents_score;
        typedef boost::shared_ptr< documents_score > documents_score_pointer; 
        typedef string_tst < character_type, documents_score_pointer > tree_type;
        typedef boost::basic_regex < character_type > regex_type;
        typedef boost::regex_iterator<typename std::basic_string<character_type>::const_iterator> regex_type_iterator;
    
        template < class character_type > class collector : public action< character_type, documents_score_pointer > {
            public:
                collector() : _entries(new documents_score()), _first(true) {
                }
            
                virtual void perform(const character_type* string, size_t string_length, int remaining_distance, documents_score_pointer data) {
                    for(documents_score_pointer::element_type::iterator s(data->begin()),e(data->end());s != e;s++) {
                        (*_entries)[s->first] += s->second;
                    }
                }
                
                virtual documents_score_pointer result() {
                    return _entries;
                }
                
            private:
                bool _first;
                documents_score_pointer _entries;
        };

        textindex() : _tst(new tree_type::storage_type(16),tree_type::value_type()), _words(L"\\b\\w+\\b") {
        }

        int put_word(const std::basic_string< character_type > word,const document_type value) {
            documents_score_pointer documents_score = _tst.get_or_build(word,this);
            return ++((*documents_score)[value]);
        }

        int put_text(const std::basic_string< character_type > text,const document_type value) {
            typename regex_type_iterator word(text.begin(),text.end(),_words);
            typename regex_type_iterator end;
            int count = 0;
            while(word != end) {
                count += put_word((*word)[0],value);
                word++;
            }
            return count;
        }
        
        documents_score_pointer find_word(const std::basic_string< character_type > word) {
            collector<character_type> c;
            _tst.walk(NULL,&c,word.data(),word.size());
            return c.result();
        }
        
        documents_score_pointer find_text(const std::basic_string< character_type > text,bool intersection) {
            typename regex_type_iterator word(text.begin(),text.end(),_words);
            typename regex_type_iterator end;
            if(word!=end) {
                if(intersection) {
                    documents_score_pointer documents_score = find_word((*word)[0]);
                    word++;
                    while(word != end) {
                        documents_score_pointer additional = find_word((*word)[0]);

                        for(documents_score_pointer::element_type::iterator s(additional->begin()),e(additional->end());s != e;s++) {
                            documents_score_pointer::element_type::iterator found(documents_score->find(s->first));
                            if(found!=documents_score->end()) {
                                found->second += s->second;
                            }
                        }

                        for(documents_score_pointer::element_type::iterator s(documents_score->begin()),e(documents_score->end());s != e;) {
                            documents_score_pointer::element_type::iterator found(additional->find(s->first));
                            if(found==additional->end()) {
                                documents_score->erase((s++)->first);
                            }
                            else {
                                s++;
                            }
                        }

                        word++;
                    }
                    return documents_score;
                }
                else {
                    collector<character_type> c;
                    while(word != end) {
                        std::basic_string<character_type> w = (*word)[0];
                        _tst.walk(NULL,&c,const_cast<character_type*>(w.data()),w.size());
                        word++;
                    }
                    return c.result();
                }
            }
            else {
                return documents_score_pointer(new documents_score());
            }
        }

        virtual documents_score_pointer perform(const character_type* string, size_t string_length, int remaining_distance, documents_score_pointer data) {
            return documents_score_pointer(new documents_score());
        }
        
        void pack() {
            _tst.pack();
        }

    private:
        tree_type _tst;
        regex_type _words;
};

#endif