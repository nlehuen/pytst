# This file was created automatically by SWIG 1.3.29.
# Don't modify this file, modify the SWIG interface instead.

import _xapian
import new
new_instancemethod = new.instancemethod
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'PySwigObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0
del types


def _swig_setattr_nondynamic_method(set):
    def set_attr(self,name,value):
        if (name == "thisown"): return self.this.own(value)
        if hasattr(self,name) or (name == "this"):
            set(self,name,value)
        else:
            raise AttributeError("You cannot add attributes to %s" % self)
    return set_attr


try:
    import weakref
    weakref_proxy = weakref.proxy
except:
    weakref_proxy = lambda x: x


class PySwigIterator(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _xapian.delete_PySwigIterator
    def __iter__(self): return self
PySwigIterator.value = new_instancemethod(_xapian.PySwigIterator_value,None,PySwigIterator)
PySwigIterator.incr = new_instancemethod(_xapian.PySwigIterator_incr,None,PySwigIterator)
PySwigIterator.decr = new_instancemethod(_xapian.PySwigIterator_decr,None,PySwigIterator)
PySwigIterator.distance = new_instancemethod(_xapian.PySwigIterator_distance,None,PySwigIterator)
PySwigIterator.equal = new_instancemethod(_xapian.PySwigIterator_equal,None,PySwigIterator)
PySwigIterator.copy = new_instancemethod(_xapian.PySwigIterator_copy,None,PySwigIterator)
PySwigIterator.next = new_instancemethod(_xapian.PySwigIterator_next,None,PySwigIterator)
PySwigIterator.previous = new_instancemethod(_xapian.PySwigIterator_previous,None,PySwigIterator)
PySwigIterator.advance = new_instancemethod(_xapian.PySwigIterator_advance,None,PySwigIterator)
PySwigIterator.__eq__ = new_instancemethod(_xapian.PySwigIterator___eq__,None,PySwigIterator)
PySwigIterator.__ne__ = new_instancemethod(_xapian.PySwigIterator___ne__,None,PySwigIterator)
PySwigIterator.__iadd__ = new_instancemethod(_xapian.PySwigIterator___iadd__,None,PySwigIterator)
PySwigIterator.__isub__ = new_instancemethod(_xapian.PySwigIterator___isub__,None,PySwigIterator)
PySwigIterator.__add__ = new_instancemethod(_xapian.PySwigIterator___add__,None,PySwigIterator)
PySwigIterator.__sub__ = new_instancemethod(_xapian.PySwigIterator___sub__,None,PySwigIterator)
PySwigIterator_swigregister = _xapian.PySwigIterator_swigregister
PySwigIterator_swigregister(PySwigIterator)

MSET_DID = _xapian.MSET_DID
MSET_WT = _xapian.MSET_WT
MSET_RANK = _xapian.MSET_RANK
MSET_PERCENT = _xapian.MSET_PERCENT
MSET_DOCUMENT = _xapian.MSET_DOCUMENT
ESET_TNAME = _xapian.ESET_TNAME
ESET_WT = _xapian.ESET_WT
class MatchDecider(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    __swig_destroy__ = _xapian.delete_MatchDecider
    def __init__(self, *args): 
        if self.__class__ == MatchDecider:
            args = (None,) + args
        else:
            args = (self,) + args
        _xapian.MatchDecider_swiginit(self,_xapian.new_MatchDecider(*args))
    def __disown__(self):
        self.this.disown()
        _xapian.disown_MatchDecider(self)
        return weakref_proxy(self)
MatchDecider.__call__ = new_instancemethod(_xapian.MatchDecider___call__,None,MatchDecider)
MatchDecider_swigregister = _xapian.MatchDecider_swigregister
MatchDecider_swigregister(MatchDecider)

version_string = _xapian.version_string
major_version = _xapian.major_version
minor_version = _xapian.minor_version
revision = _xapian.revision
xapian_version_string = _xapian.xapian_version_string
xapian_major_version = _xapian.xapian_major_version
xapian_minor_version = _xapian.xapian_minor_version
xapian_revision = _xapian.xapian_revision
class PositionIterator(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.PositionIterator_swiginit(self,_xapian.new_PositionIterator(*args))
    __swig_destroy__ = _xapian.delete_PositionIterator
PositionIterator.get_termpos = new_instancemethod(_xapian.PositionIterator_get_termpos,None,PositionIterator)
PositionIterator.next = new_instancemethod(_xapian.PositionIterator_next,None,PositionIterator)
PositionIterator.equals = new_instancemethod(_xapian.PositionIterator_equals,None,PositionIterator)
PositionIterator.skip_to = new_instancemethod(_xapian.PositionIterator_skip_to,None,PositionIterator)
PositionIterator.get_description = new_instancemethod(_xapian.PositionIterator_get_description,None,PositionIterator)
PositionIterator.__eq__ = new_instancemethod(_xapian.PositionIterator___eq__,None,PositionIterator)
PositionIterator.__ne__ = new_instancemethod(_xapian.PositionIterator___ne__,None,PositionIterator)
PositionIterator_swigregister = _xapian.PositionIterator_swigregister
PositionIterator_swigregister(PositionIterator)

class PostingIterator(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.PostingIterator_swiginit(self,_xapian.new_PostingIterator(*args))
    __swig_destroy__ = _xapian.delete_PostingIterator
PostingIterator.get_docid = new_instancemethod(_xapian.PostingIterator_get_docid,None,PostingIterator)
PostingIterator.next = new_instancemethod(_xapian.PostingIterator_next,None,PostingIterator)
PostingIterator.equals = new_instancemethod(_xapian.PostingIterator_equals,None,PostingIterator)
PostingIterator.skip_to = new_instancemethod(_xapian.PostingIterator_skip_to,None,PostingIterator)
PostingIterator.get_doclength = new_instancemethod(_xapian.PostingIterator_get_doclength,None,PostingIterator)
PostingIterator.get_wdf = new_instancemethod(_xapian.PostingIterator_get_wdf,None,PostingIterator)
PostingIterator.positionlist_begin = new_instancemethod(_xapian.PostingIterator_positionlist_begin,None,PostingIterator)
PostingIterator.positionlist_end = new_instancemethod(_xapian.PostingIterator_positionlist_end,None,PostingIterator)
PostingIterator.get_description = new_instancemethod(_xapian.PostingIterator_get_description,None,PostingIterator)
PostingIterator.__eq__ = new_instancemethod(_xapian.PostingIterator___eq__,None,PostingIterator)
PostingIterator.__ne__ = new_instancemethod(_xapian.PostingIterator___ne__,None,PostingIterator)
PostingIterator_swigregister = _xapian.PostingIterator_swigregister
PostingIterator_swigregister(PostingIterator)

class TermIterator(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.TermIterator_swiginit(self,_xapian.new_TermIterator(*args))
    __swig_destroy__ = _xapian.delete_TermIterator
TermIterator.get_term = new_instancemethod(_xapian.TermIterator_get_term,None,TermIterator)
TermIterator.next = new_instancemethod(_xapian.TermIterator_next,None,TermIterator)
TermIterator.equals = new_instancemethod(_xapian.TermIterator_equals,None,TermIterator)
TermIterator.skip_to = new_instancemethod(_xapian.TermIterator_skip_to,None,TermIterator)
TermIterator.get_wdf = new_instancemethod(_xapian.TermIterator_get_wdf,None,TermIterator)
TermIterator.get_termfreq = new_instancemethod(_xapian.TermIterator_get_termfreq,None,TermIterator)
TermIterator.positionlist_begin = new_instancemethod(_xapian.TermIterator_positionlist_begin,None,TermIterator)
TermIterator.positionlist_end = new_instancemethod(_xapian.TermIterator_positionlist_end,None,TermIterator)
TermIterator.get_description = new_instancemethod(_xapian.TermIterator_get_description,None,TermIterator)
TermIterator.__eq__ = new_instancemethod(_xapian.TermIterator___eq__,None,TermIterator)
TermIterator.__ne__ = new_instancemethod(_xapian.TermIterator___ne__,None,TermIterator)
TermIterator_swigregister = _xapian.TermIterator_swigregister
TermIterator_swigregister(TermIterator)

class ValueIterator(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.ValueIterator_swiginit(self,_xapian.new_ValueIterator(*args))
    __swig_destroy__ = _xapian.delete_ValueIterator
ValueIterator.get_value = new_instancemethod(_xapian.ValueIterator_get_value,None,ValueIterator)
ValueIterator.next = new_instancemethod(_xapian.ValueIterator_next,None,ValueIterator)
ValueIterator.equals = new_instancemethod(_xapian.ValueIterator_equals,None,ValueIterator)
ValueIterator.get_valueno = new_instancemethod(_xapian.ValueIterator_get_valueno,None,ValueIterator)
ValueIterator.get_description = new_instancemethod(_xapian.ValueIterator_get_description,None,ValueIterator)
ValueIterator.__eq__ = new_instancemethod(_xapian.ValueIterator___eq__,None,ValueIterator)
ValueIterator.__ne__ = new_instancemethod(_xapian.ValueIterator___ne__,None,ValueIterator)
ValueIterator_swigregister = _xapian.ValueIterator_swigregister
ValueIterator_swigregister(ValueIterator)

class Document(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.Document_swiginit(self,_xapian.new_Document(*args))
    __swig_destroy__ = _xapian.delete_Document
Document.get_value = new_instancemethod(_xapian.Document_get_value,None,Document)
Document.add_value = new_instancemethod(_xapian.Document_add_value,None,Document)
Document.remove_value = new_instancemethod(_xapian.Document_remove_value,None,Document)
Document.clear_values = new_instancemethod(_xapian.Document_clear_values,None,Document)
Document.get_data = new_instancemethod(_xapian.Document_get_data,None,Document)
Document.set_data = new_instancemethod(_xapian.Document_set_data,None,Document)
Document.add_posting = new_instancemethod(_xapian.Document_add_posting,None,Document)
Document.add_term = new_instancemethod(_xapian.Document_add_term,None,Document)
Document.add_term_nopos = new_instancemethod(_xapian.Document_add_term_nopos,None,Document)
Document.remove_posting = new_instancemethod(_xapian.Document_remove_posting,None,Document)
Document.remove_term = new_instancemethod(_xapian.Document_remove_term,None,Document)
Document.clear_terms = new_instancemethod(_xapian.Document_clear_terms,None,Document)
Document.termlist_count = new_instancemethod(_xapian.Document_termlist_count,None,Document)
Document.termlist_begin = new_instancemethod(_xapian.Document_termlist_begin,None,Document)
Document.termlist_end = new_instancemethod(_xapian.Document_termlist_end,None,Document)
Document.values_count = new_instancemethod(_xapian.Document_values_count,None,Document)
Document.values_begin = new_instancemethod(_xapian.Document_values_begin,None,Document)
Document.values_end = new_instancemethod(_xapian.Document_values_end,None,Document)
Document.get_description = new_instancemethod(_xapian.Document_get_description,None,Document)
Document_swigregister = _xapian.Document_swigregister
Document_swigregister(Document)

class MSet(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.MSet_swiginit(self,_xapian.new_MSet(*args))
    __swig_destroy__ = _xapian.delete_MSet
    items = property(_xapian.MSet_items_get)
MSet.fetch = new_instancemethod(_xapian.MSet_fetch,None,MSet)
MSet.convert_to_percent = new_instancemethod(_xapian.MSet_convert_to_percent,None,MSet)
MSet.get_termfreq = new_instancemethod(_xapian.MSet_get_termfreq,None,MSet)
MSet.get_termweight = new_instancemethod(_xapian.MSet_get_termweight,None,MSet)
MSet.get_firstitem = new_instancemethod(_xapian.MSet_get_firstitem,None,MSet)
MSet.get_matches_lower_bound = new_instancemethod(_xapian.MSet_get_matches_lower_bound,None,MSet)
MSet.get_matches_estimated = new_instancemethod(_xapian.MSet_get_matches_estimated,None,MSet)
MSet.get_matches_upper_bound = new_instancemethod(_xapian.MSet_get_matches_upper_bound,None,MSet)
MSet.get_max_possible = new_instancemethod(_xapian.MSet_get_max_possible,None,MSet)
MSet.get_max_attained = new_instancemethod(_xapian.MSet_get_max_attained,None,MSet)
MSet.size = new_instancemethod(_xapian.MSet_size,None,MSet)
MSet.empty = new_instancemethod(_xapian.MSet_empty,None,MSet)
MSet.is_empty = new_instancemethod(_xapian.MSet_is_empty,None,MSet)
MSet.begin = new_instancemethod(_xapian.MSet_begin,None,MSet)
MSet.end = new_instancemethod(_xapian.MSet_end,None,MSet)
MSet.back = new_instancemethod(_xapian.MSet_back,None,MSet)
MSet.get_hit = new_instancemethod(_xapian.MSet_get_hit,None,MSet)
MSet.get_document_percentage = new_instancemethod(_xapian.MSet_get_document_percentage,None,MSet)
MSet.get_document = new_instancemethod(_xapian.MSet_get_document,None,MSet)
MSet.get_docid = new_instancemethod(_xapian.MSet_get_docid,None,MSet)
MSet.get_document_id = new_instancemethod(_xapian.MSet_get_document_id,None,MSet)
MSet.get_description = new_instancemethod(_xapian.MSet_get_description,None,MSet)
MSet.__cmp__ = new_instancemethod(_xapian.MSet___cmp__,None,MSet)
MSet_swigregister = _xapian.MSet_swigregister
MSet_swigregister(MSet)

class MSetIterator(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.MSetIterator_swiginit(self,_xapian.new_MSetIterator(*args))
    __swig_destroy__ = _xapian.delete_MSetIterator
MSetIterator.get_docid = new_instancemethod(_xapian.MSetIterator_get_docid,None,MSetIterator)
MSetIterator.next = new_instancemethod(_xapian.MSetIterator_next,None,MSetIterator)
MSetIterator.prev = new_instancemethod(_xapian.MSetIterator_prev,None,MSetIterator)
MSetIterator.equals = new_instancemethod(_xapian.MSetIterator_equals,None,MSetIterator)
MSetIterator.get_document = new_instancemethod(_xapian.MSetIterator_get_document,None,MSetIterator)
MSetIterator.get_rank = new_instancemethod(_xapian.MSetIterator_get_rank,None,MSetIterator)
MSetIterator.get_weight = new_instancemethod(_xapian.MSetIterator_get_weight,None,MSetIterator)
MSetIterator.get_collapse_count = new_instancemethod(_xapian.MSetIterator_get_collapse_count,None,MSetIterator)
MSetIterator.get_percent = new_instancemethod(_xapian.MSetIterator_get_percent,None,MSetIterator)
MSetIterator.get_description = new_instancemethod(_xapian.MSetIterator_get_description,None,MSetIterator)
MSetIterator.__eq__ = new_instancemethod(_xapian.MSetIterator___eq__,None,MSetIterator)
MSetIterator.__ne__ = new_instancemethod(_xapian.MSetIterator___ne__,None,MSetIterator)
MSetIterator_swigregister = _xapian.MSetIterator_swigregister
MSetIterator_swigregister(MSetIterator)

class ESet(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.ESet_swiginit(self,_xapian.new_ESet(*args))
    __swig_destroy__ = _xapian.delete_ESet
    items = property(_xapian.ESet_items_get)
ESet.get_ebound = new_instancemethod(_xapian.ESet_get_ebound,None,ESet)
ESet.size = new_instancemethod(_xapian.ESet_size,None,ESet)
ESet.empty = new_instancemethod(_xapian.ESet_empty,None,ESet)
ESet.is_empty = new_instancemethod(_xapian.ESet_is_empty,None,ESet)
ESet.begin = new_instancemethod(_xapian.ESet_begin,None,ESet)
ESet.end = new_instancemethod(_xapian.ESet_end,None,ESet)
ESet.back = new_instancemethod(_xapian.ESet_back,None,ESet)
ESet.get_description = new_instancemethod(_xapian.ESet_get_description,None,ESet)
ESet_swigregister = _xapian.ESet_swigregister
ESet_swigregister(ESet)

class ESetIterator(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.ESetIterator_swiginit(self,_xapian.new_ESetIterator(*args))
    __swig_destroy__ = _xapian.delete_ESetIterator
ESetIterator.get_termname = new_instancemethod(_xapian.ESetIterator_get_termname,None,ESetIterator)
ESetIterator.next = new_instancemethod(_xapian.ESetIterator_next,None,ESetIterator)
ESetIterator.prev = new_instancemethod(_xapian.ESetIterator_prev,None,ESetIterator)
ESetIterator.equals = new_instancemethod(_xapian.ESetIterator_equals,None,ESetIterator)
ESetIterator.get_weight = new_instancemethod(_xapian.ESetIterator_get_weight,None,ESetIterator)
ESetIterator.get_description = new_instancemethod(_xapian.ESetIterator_get_description,None,ESetIterator)
ESetIterator.__eq__ = new_instancemethod(_xapian.ESetIterator___eq__,None,ESetIterator)
ESetIterator.__ne__ = new_instancemethod(_xapian.ESetIterator___ne__,None,ESetIterator)
ESetIterator_swigregister = _xapian.ESetIterator_swigregister
ESetIterator_swigregister(ESetIterator)

class RSet(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.RSet_swiginit(self,_xapian.new_RSet(*args))
    __swig_destroy__ = _xapian.delete_RSet
RSet.size = new_instancemethod(_xapian.RSet_size,None,RSet)
RSet.empty = new_instancemethod(_xapian.RSet_empty,None,RSet)
RSet.is_empty = new_instancemethod(_xapian.RSet_is_empty,None,RSet)
RSet.add_document = new_instancemethod(_xapian.RSet_add_document,None,RSet)
RSet.remove_document = new_instancemethod(_xapian.RSet_remove_document,None,RSet)
RSet.contains = new_instancemethod(_xapian.RSet_contains,None,RSet)
RSet.get_description = new_instancemethod(_xapian.RSet_get_description,None,RSet)
RSet_swigregister = _xapian.RSet_swigregister
RSet_swigregister(RSet)

class Enquire(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.Enquire_swiginit(self,_xapian.new_Enquire(*args))
    __swig_destroy__ = _xapian.delete_Enquire
    ASCENDING = _xapian.Enquire_ASCENDING
    DESCENDING = _xapian.Enquire_DESCENDING
    DONT_CARE = _xapian.Enquire_DONT_CARE
Enquire.set_query = new_instancemethod(_xapian.Enquire_set_query,None,Enquire)
Enquire.get_query = new_instancemethod(_xapian.Enquire_get_query,None,Enquire)
Enquire.set_weighting_scheme = new_instancemethod(_xapian.Enquire_set_weighting_scheme,None,Enquire)
Enquire.set_collapse_key = new_instancemethod(_xapian.Enquire_set_collapse_key,None,Enquire)
Enquire.set_docid_order = new_instancemethod(_xapian.Enquire_set_docid_order,None,Enquire)
Enquire.set_sort_forward = new_instancemethod(_xapian.Enquire_set_sort_forward,None,Enquire)
Enquire.set_cutoff = new_instancemethod(_xapian.Enquire_set_cutoff,None,Enquire)
Enquire.set_sorting = new_instancemethod(_xapian.Enquire_set_sorting,None,Enquire)
Enquire.set_sort_by_relevance = new_instancemethod(_xapian.Enquire_set_sort_by_relevance,None,Enquire)
Enquire.set_sort_by_value = new_instancemethod(_xapian.Enquire_set_sort_by_value,None,Enquire)
Enquire.set_sort_by_value_then_relevance = new_instancemethod(_xapian.Enquire_set_sort_by_value_then_relevance,None,Enquire)
Enquire.set_sort_by_relevance_then_value = new_instancemethod(_xapian.Enquire_set_sort_by_relevance_then_value,None,Enquire)
Enquire.set_bias = new_instancemethod(_xapian.Enquire_set_bias,None,Enquire)
Enquire.get_mset = new_instancemethod(_xapian.Enquire_get_mset,None,Enquire)
Enquire.get_eset = new_instancemethod(_xapian.Enquire_get_eset,None,Enquire)
Enquire.get_matching_terms_begin = new_instancemethod(_xapian.Enquire_get_matching_terms_begin,None,Enquire)
Enquire.get_matching_terms_end = new_instancemethod(_xapian.Enquire_get_matching_terms_end,None,Enquire)
Enquire.register_match_decider = new_instancemethod(_xapian.Enquire_register_match_decider,None,Enquire)
Enquire.get_matching_terms = new_instancemethod(_xapian.Enquire_get_matching_terms,None,Enquire)
Enquire.get_description = new_instancemethod(_xapian.Enquire_get_description,None,Enquire)
Enquire_swigregister = _xapian.Enquire_swigregister
Enquire_swigregister(Enquire)

class Weight(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _xapian.delete_Weight
Weight.name = new_instancemethod(_xapian.Weight_name,None,Weight)
Weight.serialise = new_instancemethod(_xapian.Weight_serialise,None,Weight)
Weight.unserialise = new_instancemethod(_xapian.Weight_unserialise,None,Weight)
Weight.get_sumpart = new_instancemethod(_xapian.Weight_get_sumpart,None,Weight)
Weight.get_maxpart = new_instancemethod(_xapian.Weight_get_maxpart,None,Weight)
Weight.get_sumextra = new_instancemethod(_xapian.Weight_get_sumextra,None,Weight)
Weight.get_maxextra = new_instancemethod(_xapian.Weight_get_maxextra,None,Weight)
Weight.get_sumpart_needs_doclength = new_instancemethod(_xapian.Weight_get_sumpart_needs_doclength,None,Weight)
Weight_swigregister = _xapian.Weight_swigregister
Weight_swigregister(Weight)

class BoolWeight(Weight):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.BoolWeight_swiginit(self,_xapian.new_BoolWeight(*args))
    __swig_destroy__ = _xapian.delete_BoolWeight
BoolWeight.clone = new_instancemethod(_xapian.BoolWeight_clone,None,BoolWeight)
BoolWeight.unserialise = new_instancemethod(_xapian.BoolWeight_unserialise,None,BoolWeight)
BoolWeight_swigregister = _xapian.BoolWeight_swigregister
BoolWeight_swigregister(BoolWeight)

class BM25Weight(Weight):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.BM25Weight_swiginit(self,_xapian.new_BM25Weight(*args))
    __swig_destroy__ = _xapian.delete_BM25Weight
BM25Weight.clone = new_instancemethod(_xapian.BM25Weight_clone,None,BM25Weight)
BM25Weight.unserialise = new_instancemethod(_xapian.BM25Weight_unserialise,None,BM25Weight)
BM25Weight_swigregister = _xapian.BM25Weight_swigregister
BM25Weight_swigregister(BM25Weight)

class TradWeight(Weight):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.TradWeight_swiginit(self,_xapian.new_TradWeight(*args))
    __swig_destroy__ = _xapian.delete_TradWeight
TradWeight.clone = new_instancemethod(_xapian.TradWeight_clone,None,TradWeight)
TradWeight.unserialise = new_instancemethod(_xapian.TradWeight_unserialise,None,TradWeight)
TradWeight_swigregister = _xapian.TradWeight_swigregister
TradWeight_swigregister(TradWeight)

class Database(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    __swig_destroy__ = _xapian.delete_Database
    def __init__(self, *args): 
        _xapian.Database_swiginit(self,_xapian.new_Database(*args))
Database.add_database = new_instancemethod(_xapian.Database_add_database,None,Database)
Database.reopen = new_instancemethod(_xapian.Database_reopen,None,Database)
Database.get_description = new_instancemethod(_xapian.Database_get_description,None,Database)
Database.postlist_begin = new_instancemethod(_xapian.Database_postlist_begin,None,Database)
Database.postlist_end = new_instancemethod(_xapian.Database_postlist_end,None,Database)
Database.termlist_begin = new_instancemethod(_xapian.Database_termlist_begin,None,Database)
Database.termlist_end = new_instancemethod(_xapian.Database_termlist_end,None,Database)
Database.positionlist_begin = new_instancemethod(_xapian.Database_positionlist_begin,None,Database)
Database.positionlist_end = new_instancemethod(_xapian.Database_positionlist_end,None,Database)
Database.allterms_begin = new_instancemethod(_xapian.Database_allterms_begin,None,Database)
Database.allterms_end = new_instancemethod(_xapian.Database_allterms_end,None,Database)
Database.get_doccount = new_instancemethod(_xapian.Database_get_doccount,None,Database)
Database.get_lastdocid = new_instancemethod(_xapian.Database_get_lastdocid,None,Database)
Database.get_avlength = new_instancemethod(_xapian.Database_get_avlength,None,Database)
Database.get_termfreq = new_instancemethod(_xapian.Database_get_termfreq,None,Database)
Database.term_exists = new_instancemethod(_xapian.Database_term_exists,None,Database)
Database.get_collection_freq = new_instancemethod(_xapian.Database_get_collection_freq,None,Database)
Database.get_doclength = new_instancemethod(_xapian.Database_get_doclength,None,Database)
Database.keep_alive = new_instancemethod(_xapian.Database_keep_alive,None,Database)
Database.get_document = new_instancemethod(_xapian.Database_get_document,None,Database)
Database_swigregister = _xapian.Database_swigregister
Database_swigregister(Database)

class WritableDatabase(Database):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    __swig_destroy__ = _xapian.delete_WritableDatabase
    def __init__(self, *args): 
        _xapian.WritableDatabase_swiginit(self,_xapian.new_WritableDatabase(*args))
WritableDatabase.flush = new_instancemethod(_xapian.WritableDatabase_flush,None,WritableDatabase)
WritableDatabase.begin_transaction = new_instancemethod(_xapian.WritableDatabase_begin_transaction,None,WritableDatabase)
WritableDatabase.commit_transaction = new_instancemethod(_xapian.WritableDatabase_commit_transaction,None,WritableDatabase)
WritableDatabase.cancel_transaction = new_instancemethod(_xapian.WritableDatabase_cancel_transaction,None,WritableDatabase)
WritableDatabase.add_document = new_instancemethod(_xapian.WritableDatabase_add_document,None,WritableDatabase)
WritableDatabase.delete_document = new_instancemethod(_xapian.WritableDatabase_delete_document,None,WritableDatabase)
WritableDatabase.replace_document = new_instancemethod(_xapian.WritableDatabase_replace_document,None,WritableDatabase)
WritableDatabase.get_description = new_instancemethod(_xapian.WritableDatabase_get_description,None,WritableDatabase)
WritableDatabase_swigregister = _xapian.WritableDatabase_swigregister
WritableDatabase_swigregister(WritableDatabase)

DB_CREATE_OR_OPEN = _xapian.DB_CREATE_OR_OPEN
DB_CREATE = _xapian.DB_CREATE
DB_CREATE_OR_OVERWRITE = _xapian.DB_CREATE_OR_OVERWRITE
DB_OPEN = _xapian.DB_OPEN
open_stub = _xapian.open_stub
inmemory_open = _xapian.inmemory_open
class Query(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    OP_AND = _xapian.Query_OP_AND
    OP_OR = _xapian.Query_OP_OR
    OP_AND_NOT = _xapian.Query_OP_AND_NOT
    OP_XOR = _xapian.Query_OP_XOR
    OP_AND_MAYBE = _xapian.Query_OP_AND_MAYBE
    OP_FILTER = _xapian.Query_OP_FILTER
    OP_NEAR = _xapian.Query_OP_NEAR
    OP_PHRASE = _xapian.Query_OP_PHRASE
    OP_ELITE_SET = _xapian.Query_OP_ELITE_SET
    def __init__(self, *args): 
        _xapian.Query_swiginit(self,_xapian.new_Query(*args))
    __swig_destroy__ = _xapian.delete_Query
Query.get_length = new_instancemethod(_xapian.Query_get_length,None,Query)
Query.get_terms_begin = new_instancemethod(_xapian.Query_get_terms_begin,None,Query)
Query.get_terms_end = new_instancemethod(_xapian.Query_get_terms_end,None,Query)
Query.empty = new_instancemethod(_xapian.Query_empty,None,Query)
Query.is_empty = new_instancemethod(_xapian.Query_is_empty,None,Query)
Query.get_description = new_instancemethod(_xapian.Query_get_description,None,Query)
Query_swigregister = _xapian.Query_swigregister
Query_swigregister(Query)
open = _xapian.open
quartz_open = _xapian.quartz_open
open_da = _xapian.open_da
open_db = _xapian.open_db
remote_open = _xapian.remote_open

class Stopper(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    __swig_destroy__ = _xapian.delete_Stopper
    def __init__(self, *args): 
        if self.__class__ == Stopper:
            args = (None,) + args
        else:
            args = (self,) + args
        _xapian.Stopper_swiginit(self,_xapian.new_Stopper(*args))
    def __disown__(self):
        self.this.disown()
        _xapian.disown_Stopper(self)
        return weakref_proxy(self)
Stopper.__call__ = new_instancemethod(_xapian.Stopper___call__,None,Stopper)
Stopper.get_description = new_instancemethod(_xapian.Stopper_get_description,None,Stopper)
Stopper_swigregister = _xapian.Stopper_swigregister
Stopper_swigregister(Stopper)

class SimpleStopper(Stopper):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.SimpleStopper_swiginit(self,_xapian.new_SimpleStopper(*args))
    __swig_destroy__ = _xapian.delete_SimpleStopper
SimpleStopper.add = new_instancemethod(_xapian.SimpleStopper_add,None,SimpleStopper)
SimpleStopper_swigregister = _xapian.SimpleStopper_swigregister
SimpleStopper_swigregister(SimpleStopper)

class QueryParser(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    FLAG_BOOLEAN = _xapian.QueryParser_FLAG_BOOLEAN
    FLAG_PHRASE = _xapian.QueryParser_FLAG_PHRASE
    FLAG_LOVEHATE = _xapian.QueryParser_FLAG_LOVEHATE
    FLAG_BOOLEAN_ANY_CASE = _xapian.QueryParser_FLAG_BOOLEAN_ANY_CASE
    FLAG_WILDCARD = _xapian.QueryParser_FLAG_WILDCARD
    STEM_NONE = _xapian.QueryParser_STEM_NONE
    STEM_SOME = _xapian.QueryParser_STEM_SOME
    STEM_ALL = _xapian.QueryParser_STEM_ALL
    def __init__(self, *args): 
        _xapian.QueryParser_swiginit(self,_xapian.new_QueryParser(*args))
    __swig_destroy__ = _xapian.delete_QueryParser
QueryParser.set_stemmer = new_instancemethod(_xapian.QueryParser_set_stemmer,None,QueryParser)
QueryParser.set_stemming_strategy = new_instancemethod(_xapian.QueryParser_set_stemming_strategy,None,QueryParser)
QueryParser.set_stopper = new_instancemethod(_xapian.QueryParser_set_stopper,None,QueryParser)
QueryParser.set_default_op = new_instancemethod(_xapian.QueryParser_set_default_op,None,QueryParser)
QueryParser.get_default_op = new_instancemethod(_xapian.QueryParser_get_default_op,None,QueryParser)
QueryParser.set_database = new_instancemethod(_xapian.QueryParser_set_database,None,QueryParser)
QueryParser.parse_query = new_instancemethod(_xapian.QueryParser_parse_query,None,QueryParser)
QueryParser.add_prefix = new_instancemethod(_xapian.QueryParser_add_prefix,None,QueryParser)
QueryParser.add_boolean_prefix = new_instancemethod(_xapian.QueryParser_add_boolean_prefix,None,QueryParser)
QueryParser.stoplist_begin = new_instancemethod(_xapian.QueryParser_stoplist_begin,None,QueryParser)
QueryParser.stoplist_end = new_instancemethod(_xapian.QueryParser_stoplist_end,None,QueryParser)
QueryParser.unstem_begin = new_instancemethod(_xapian.QueryParser_unstem_begin,None,QueryParser)
QueryParser.unstem_end = new_instancemethod(_xapian.QueryParser_unstem_end,None,QueryParser)
QueryParser.get_description = new_instancemethod(_xapian.QueryParser_get_description,None,QueryParser)
QueryParser_swigregister = _xapian.QueryParser_swigregister
QueryParser_swigregister(QueryParser)

class Stem(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        _xapian.Stem_swiginit(self,_xapian.new_Stem(*args))
    __swig_destroy__ = _xapian.delete_Stem
    get_available_languages = staticmethod(_xapian.Stem_get_available_languages)
Stem.__call__ = new_instancemethod(_xapian.Stem___call__,None,Stem)
Stem.stem_word = new_instancemethod(_xapian.Stem_stem_word,None,Stem)
Stem.get_description = new_instancemethod(_xapian.Stem_get_description,None,Stem)
Stem_swigregister = _xapian.Stem_swigregister
Stem_swigregister(Stem)
Stem_get_available_languages = _xapian.Stem_get_available_languages

# Python-style iterators to mirror the C++ ones
class MSetIter:
    def __init__(self, start, end):
        self.iter = start
        self.end = end

    def __iter__(self):
        return self

    def next(self):
        if self.iter==self.end:
            raise StopIteration
        else:
            r = [self.iter.get_docid(), self.iter.get_weight(), self.iter.get_rank(), self.iter.get_percent(), self.iter.get_document()]
            self.iter.next()
            return r

class ESetIter:
    def __init__(self, start, end):
        self.iter = start
        self.end = end

    def __iter__(self):
        return self

    def next(self):
        if self.iter==self.end:
            raise StopIteration
        else:
            r = [self.iter.get_termname(), self.iter.get_weight()]
            self.iter.next()
            return r

class TermIter:
    HAS_NOTHING = 0
    HAS_TERMFREQS = 1
    HAS_POSITIONS = 2

    def __init__(self, start, end, has = HAS_NOTHING):
        self.iter = start
        self.end = end
        self.has = has

    def __iter__(self):
        return self

    def next(self):
        if self.iter==self.end:
            raise StopIteration
        else:
            termfreq = 0
            if self.has & TermIter.HAS_TERMFREQS:
                termfreq = self.iter.get_termfreq()
            if self.has & TermIter.HAS_POSITIONS:
                positer = PositionIter(self.iter.positionlist_begin(), self.iter.positionlist_end())
            else:
                positer = PositionIter()
            r = [self.iter.get_term(), self.iter.get_wdf(), termfreq, positer]
            self.iter.next()
            return r

class PostingIter:
    def __init__(self, start, end):
        self.iter = start
        self.end = end

    def __iter__(self):
        return self

    def next(self):
        if self.iter==self.end:
            raise StopIteration
        else:
            r = [self.iter.get_docid(), self.iter.get_doclength(), self.iter.get_wdf(), PositionIter(self.iter.positionlist_begin(), self.iter.positionlist_end())]
            self.iter.next()
            return r

class PositionIter:
    def __init__(self, start = 0, end = 0):
        self.iter = start
        self.end = end

    def __iter__(self):
        return self

    def next(self):
        if self.iter==self.end:
            raise StopIteration
        else:
            r = self.iter.get_termpos()
            self.iter.next()
            return r

class ValueIter:
    def __init__(self, start, end):
        self.iter = start
        self.end = end

    def __iter__(self):
        return self

    def next(self):
        if self.iter==self.end:
            raise StopIteration
        else:
            r = [self.iter.get_valueno(), self.iter.get_value()]
            self.iter.next()
            return r

# Bind the Python iterators into the shadow classes
def mset_gen_iter(self):
    return MSetIter(self.begin(), self.end())

MSet.__iter__ = mset_gen_iter

def eset_gen_iter(self):
    return ESetIter(self.begin(), self.end())

ESet.__iter__ = eset_gen_iter

def enquire_gen_iter(self, which):
    return TermIter(self.get_matching_terms_begin(which), self.get_matching_terms_end(which))

Enquire.matching_terms = enquire_gen_iter

def query_gen_iter(self):
    return TermIter(self.get_terms_begin(), self.get_terms_end())

Query.__iter__ = query_gen_iter

def database_gen_allterms_iter(self):
    return TermIter(self.allterms_begin(), self.allterms_end(), TermIter.HAS_TERMFREQS)

Database.__iter__ = database_gen_allterms_iter

def database_gen_postlist_iter(self, tname):
    return PostingIter(self.postlist_begin(tname), self.postlist_end(tname))
def database_gen_termlist_iter(self, docid):
    return TermIter(self.termlist_begin(docid), self.termlist_end(docid), TermIter.HAS_TERMFREQS|TermIter.HAS_POSITIONS)
def database_gen_positionlist_iter(self, docid, tname):
    return PositionIter(self.positionlist_begin(docid, tname), self.positionlist_end(docid, tname))

Database.allterms = database_gen_allterms_iter
Database.postlist = database_gen_postlist_iter
Database.termlist = database_gen_termlist_iter
Database.positionlist = database_gen_positionlist_iter

def document_gen_termlist_iter(self):
    return TermIter(self.termlist_begin(), self.termlist_end(), TermIter.HAS_POSITIONS)
def document_gen_values_iter(self):
    return ValueIter(self.values_begin(), self.values_end())

Document.__iter__ = document_gen_termlist_iter
Document.termlist = document_gen_termlist_iter
Document.values = document_gen_values_iter

def queryparser_gen_stoplist_iter(self):
    return TermIter(self.stoplist_begin(), self.stoplist_end())
def queryparser_gen_unstemlist_iter(self, tname):
    return TermIter(self.unstem_begin(tname), self.unstem_end(tname))

QueryParser.stoplist = queryparser_gen_stoplist_iter
QueryParser.unstemlist = queryparser_gen_unstemlist_iter




