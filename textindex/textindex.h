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

#include "tst.h"

#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/regex.hpp>

template < class S, class T > class textindex : private filter< S, boost::shared_ptr< std::map< T, int > > > {
    public:
        typedef std::map< T, int > entries;
        typedef boost::shared_ptr< entries > p_entries; 
    
        template < class S > class collector : public action< S, p_entries > {
            public:
                virtual collector() : _entries(new entries()), _first(true) {
                }
            
                virtual void perform(S* string, int string_length, int remaining_distance, p_entries data) {
                    for(p_entries::element_type::iterator s(data->begin()),e(data->end());s != e;s++) {
                        (*_entries)[s->first] += s->second;
                    }
                }
                
                virtual p_entries result() {
                    return _entries;
                }
                
            private:
                bool _first;
                p_entries _entries;
        };

        textindex() : _tst(), _words("\\b\\w+\\b") {
        }

        int put_word(std::basic_string< S > word,T value) {
            p_entries entries = _tst.get_or_build(word,this);
            return ++((*entries)[value]);
        }

        int put_text(std::basic_string< S > text,T value) {
            boost::sregex_iterator word(text.begin(),text.end(),_words);
            boost::sregex_iterator end;
            int count = 0;
            while(word != end) {
                count += put_word((*word)[0],value);
                word++;
            }
            return count;
        }
        
        p_entries find_word(std::basic_string< S > word) {
            collector<S> c;
            _tst.walk(NULL,&c,const_cast<S*>(word.data()),word.size());
            return c.result();
        }
        
        p_entries find_text(std::basic_string< S > text,bool intersection) {
            boost::sregex_iterator word(text.begin(),text.end(),_words);
            boost::sregex_iterator end;
            if(word!=end) {
                if(intersection) {
                    p_entries entries = find_word((*word)[0]);
                    word++;
                    while(word != end) {
                        p_entries additional = find_word((*word)[0]);

                        for(p_entries::element_type::iterator s(additional->begin()),e(additional->end());s != e;s++) {
                            p_entries::element_type::iterator found(entries->find(s->first));
                            if(found!=entries->end()) {
                                found->second += s->second;
                            }
                        }

                        for(p_entries::element_type::iterator s(entries->begin()),e(entries->end());s != e;s++) {
                            p_entries::element_type::iterator found(additional->find(s->first));
                            if(found==additional->end()) {
                                entries->erase(s->first);
                            }
                        }

                        word++;
                    }
                    return entries;
                }
                else {
                    collector<S> c;
                    while(word != end) {
                        std::basic_string<S> w = (*word)[0];
                        _tst.walk(NULL,&c,const_cast<S*>(w.data()),w.size());
                        word++;
                    }
                    return c.result();
                }
            }
            else {
                return p_entries(new entries());
            }
        }

        virtual p_entries perform(S* string, int string_length, int remaining_distance, p_entries data) {
            return p_entries(new entries());
        }
        
        void pack() {
            _tst.pack();
        }

    private:
        memory_tst < S, p_entries > _tst;
        boost::basic_regex < S > _words;
};