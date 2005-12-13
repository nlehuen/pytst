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
                collector() : _entries(new entries()), _first(true) {
                }
            
                void perform(S* string, int string_length, int remaining_distance, p_entries data) {
                    p_entries::element_type::iterator s,e;
                    for(s=data->begin(),e=data->end();s != e;s++) {
                        (*_entries)[s->first] += s->second;
                    }
                }
                
                p_entries result() {
                    return _entries;
                }
                
            private:
                bool _first;
                p_entries _entries;
        };

        textindex() {
        }

        int put(std::basic_string< S > word,T value) {
            p_entries entries = _tst.get_or_build(word,this);
            return ++((*entries)[value]);
        }
        
        p_entries find(std::basic_string< S > word) {
            collector<S> c;
            _tst.walk(NULL,&c,const_cast<S*>(word.data()),word.size());
            return c.result();
        }
        
        p_entries perform(S* string, int string_length, int remaining_distance, p_entries data) {
            return p_entries(new entries());
        }

    private:
        memory_tst < S, p_entries > _tst;
};