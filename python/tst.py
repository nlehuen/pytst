# This file was created automatically by SWIG 1.3.28.
# Don't modify this file, modify the SWIG interface instead.

import _tst
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


class TSTException(object):
    """Proxy of C++ TSTException class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __repr__(self):
        try: strthis = "at 0x%x" %( self.this, ) 
        except: strthis = "" 
        return "<%s.%s; proxy of C++ TSTException instance %s>" % (self.__class__.__module__, self.__class__.__name__, strthis,)
    def __init__(self, *args):
        """__init__(self, _message) -> TSTException"""
        this = _tst.new_TSTException(*args)
        try: self.this.append(this)
        except: self.this = this
    def what(*args):
        """what(self) -> char"""
        return _tst.TSTException_what(*args)

    __swig_destroy__ = _tst.delete_TSTException
_tst.TSTException_swigregister(TSTException)
cvar = _tst.cvar
TST_VERSION = cvar.TST_VERSION
UNDEFINED_INDEX = cvar.UNDEFINED_INDEX

class _TST(object):
    """Proxy of C++ _TST class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __repr__(self):
        try: strthis = "at 0x%x" %( self.this, ) 
        except: strthis = "" 
        return "<%s.%s; proxy of C++ tst<char,PythonReference,MemoryStorage,ObjectSerializer > instance %s>" % (self.__class__.__module__, self.__class__.__name__, strthis,)
    def __init__(self, *args):
        """__init__(self) -> _TST"""
        this = _tst.new__TST(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _tst.delete__TST
    def pack(*args):
        """pack(self)"""
        return _tst._TST_pack(*args)

    def walk(*args):
        """
        walk(self, filter, to_perform) -> PythonReference
        walk(self, filter, to_perform, string) -> PythonReference
        """
        return _tst._TST_walk(*args)

    def close_match(*args):
        """close_match(self, string, maximum_distance, filter, to_perform) -> PythonReference"""
        return _tst._TST_close_match(*args)

    def prefix_match(*args):
        """prefix_match(self, string, filter, to_perform) -> PythonReference"""
        return _tst._TST_prefix_match(*args)

    def get(*args):
        """get(self, string) -> PythonReference"""
        return _tst._TST_get(*args)

    def get_or_build(*args):
        """get_or_build(self, string, factory) -> PythonReference"""
        return _tst._TST_get_or_build(*args)

    def put(*args):
        """put(self, string, data) -> PythonReference"""
        return _tst._TST_put(*args)

    def remove(*args):
        """remove(self, string)"""
        return _tst._TST_remove(*args)

    def contains(*args):
        """contains(self, string) -> bool"""
        return _tst._TST_contains(*args)

    def get_maximum_key_length(*args):
        """get_maximum_key_length(self) -> int"""
        return _tst._TST_get_maximum_key_length(*args)

    def write(*args):
        """write(self, file)"""
        return _tst._TST_write(*args)

    def read(*args):
        """read(self, file)"""
        return _tst._TST_read(*args)

    def iterator(*args):
        """
        iterator(self) -> lexical_iterator<(char,PythonReference,MemoryStorage,ObjectSerializer)>
        iterator(self, string) -> lexical_iterator<(char,PythonReference,MemoryStorage,ObjectSerializer)>
        """
        return _tst._TST_iterator(*args)

    def close_match_iterator(*args):
        """close_match_iterator(self, string, distance) -> match_iterator<(char,PythonReference,MemoryStorage,ObjectSerializer)>"""
        return _tst._TST_close_match_iterator(*args)

    def get_number_of_nodes(*args):
        """get_number_of_nodes(self) -> int"""
        return _tst._TST_get_number_of_nodes(*args)

    def scan(*args):
        """scan(self, string, to_perform) -> PythonReference"""
        return _tst._TST_scan(*args)

    def scan_with_stop_chars(*args):
        """scan_with_stop_chars(self, string, stop_chars, to_perform) -> PythonReference"""
        return _tst._TST_scan_with_stop_chars(*args)

_tst._TST_swigregister(_TST)

class _Action(object):
    """Proxy of C++ _Action class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    def __repr__(self):
        try: strthis = "at 0x%x" %( self.this, ) 
        except: strthis = "" 
        return "<%s.%s; proxy of C++ action<char,PythonReference > instance %s>" % (self.__class__.__module__, self.__class__.__name__, strthis,)
    __swig_destroy__ = _tst.delete__Action
    def perform(*args):
        """perform(self, string, remaining_distance, data)"""
        return _tst._Action_perform(*args)

    def result(*args):
        """result(self) -> PythonReference"""
        return _tst._Action_result(*args)

_tst._Action_swigregister(_Action)

class _Filter(object):
    """Proxy of C++ _Filter class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    def __repr__(self):
        try: strthis = "at 0x%x" %( self.this, ) 
        except: strthis = "" 
        return "<%s.%s; proxy of C++ filter<char,PythonReference > instance %s>" % (self.__class__.__module__, self.__class__.__name__, strthis,)
    __swig_destroy__ = _tst.delete__Filter
    def perform(*args):
        """perform(self, string, remaining_distance, data) -> PythonReference"""
        return _tst._Filter_perform(*args)

_tst._Filter_swigregister(_Filter)

class CallableAction(_Action):
    """Proxy of C++ CallableAction class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __repr__(self):
        try: strthis = "at 0x%x" %( self.this, ) 
        except: strthis = "" 
        return "<%s.%s; proxy of C++ CallableAction instance %s>" % (self.__class__.__module__, self.__class__.__name__, strthis,)
    def __init__(self, *args):
        """__init__(self, perform, result) -> CallableAction"""
        this = _tst.new_CallableAction(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _tst.delete_CallableAction
_tst.CallableAction_swigregister(CallableAction)

class CallableFilter(_Filter):
    """Proxy of C++ CallableFilter class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __repr__(self):
        try: strthis = "at 0x%x" %( self.this, ) 
        except: strthis = "" 
        return "<%s.%s; proxy of C++ CallableFilter instance %s>" % (self.__class__.__module__, self.__class__.__name__, strthis,)
    def __init__(self, *args):
        """__init__(self, _callable) -> CallableFilter"""
        this = _tst.new_CallableFilter(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _tst.delete_CallableFilter
_tst.CallableFilter_swigregister(CallableFilter)

class DictAction(_Action):
    """Proxy of C++ DictAction class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __repr__(self):
        try: strthis = "at 0x%x" %( self.this, ) 
        except: strthis = "" 
        return "<%s.%s; proxy of C++ DictAction instance %s>" % (self.__class__.__module__, self.__class__.__name__, strthis,)
    def __init__(self, *args):
        """__init__(self) -> DictAction"""
        this = _tst.new_DictAction(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _tst.delete_DictAction
_tst.DictAction_swigregister(DictAction)

class ListAction(_Action):
    """Proxy of C++ ListAction class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __repr__(self):
        try: strthis = "at 0x%x" %( self.this, ) 
        except: strthis = "" 
        return "<%s.%s; proxy of C++ ListAction instance %s>" % (self.__class__.__module__, self.__class__.__name__, strthis,)
    def __init__(self, *args):
        """__init__(self) -> ListAction"""
        this = _tst.new_ListAction(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _tst.delete_ListAction
_tst.ListAction_swigregister(ListAction)

class TupleListAction(_Action):
    """Proxy of C++ TupleListAction class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __repr__(self):
        try: strthis = "at 0x%x" %( self.this, ) 
        except: strthis = "" 
        return "<%s.%s; proxy of C++ TupleListAction instance %s>" % (self.__class__.__module__, self.__class__.__name__, strthis,)
    def __init__(self, *args):
        """__init__(self) -> TupleListAction"""
        this = _tst.new_TupleListAction(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _tst.delete_TupleListAction
_tst.TupleListAction_swigregister(TupleListAction)

class ObjectSerializer(object):
    """Proxy of C++ ObjectSerializer class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __repr__(self):
        try: strthis = "at 0x%x" %( self.this, ) 
        except: strthis = "" 
        return "<%s.%s; proxy of C++ ObjectSerializer instance %s>" % (self.__class__.__module__, self.__class__.__name__, strthis,)
    def __init__(self, *args):
        """__init__(self) -> ObjectSerializer"""
        this = _tst.new_ObjectSerializer(*args)
        try: self.this.append(this)
        except: self.this = this
    def write(*args):
        """write(self, file, data)"""
        return _tst.ObjectSerializer_write(*args)

    def read(*args):
        """read(self, file) -> PythonReference"""
        return _tst.ObjectSerializer_read(*args)

    def write_to_file(*args):
        """write_to_file(self, file, data)"""
        return _tst.ObjectSerializer_write_to_file(*args)

    def read_from_file(*args):
        """read_from_file(self, file) -> PythonReference"""
        return _tst.ObjectSerializer_read_from_file(*args)

    __swig_destroy__ = _tst.delete_ObjectSerializer
_tst.ObjectSerializer_swigregister(ObjectSerializer)

class TST(_TST):
    """Proxy of C++ TST class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __repr__(self):
        try: strthis = "at 0x%x" %( self.this, ) 
        except: strthis = "" 
        return "<%s.%s; proxy of C++ TST instance %s>" % (self.__class__.__module__, self.__class__.__name__, strthis,)
    def __init__(self, *args):
        """__init__(self) -> TST"""
        this = _tst.new_TST(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _tst.delete_TST
    def write_to_file(*args):
        """write_to_file(self, file) -> PythonReference"""
        return _tst.TST_write_to_file(*args)

    def read_from_file(*args):
        """read_from_file(self, file) -> PythonReference"""
        return _tst.TST_read_from_file(*args)

    def __getitem__(*args):
        """__getitem__(self, string) -> PythonReference"""
        return _tst.TST___getitem__(*args)

    def __setitem__(*args):
        """__setitem__(self, string, data) -> PythonReference"""
        return _tst.TST___setitem__(*args)

    def __delitem__(*args):
        """__delitem__(self, string)"""
        return _tst.TST___delitem__(*args)

    def __contains__(*args):
        """__contains__(self, string) -> PythonReference"""
        return _tst.TST___contains__(*args)

    def iterator(*args):
        """
        iterator(self) -> TSTLexicalIterator
        iterator(self, string) -> TSTLexicalIterator
        """
        return _tst.TST_iterator(*args)

    def close_match_iterator(*args):
        """close_match_iterator(self, string, distance) -> TSTCloseMatchIterator"""
        return _tst.TST_close_match_iterator(*args)

    def __iter__(*args):
        """__iter__(self) -> TSTLexicalIterator"""
        return _tst.TST___iter__(*args)

_tst.TST_swigregister(TST)

class TSTLexicalIterator(object):
    """Proxy of C++ TSTLexicalIterator class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    def __repr__(self):
        try: strthis = "at 0x%x" %( self.this, ) 
        except: strthis = "" 
        return "<%s.%s; proxy of C++ TSTIterator<lexical_iterator_type > instance %s>" % (self.__class__.__module__, self.__class__.__name__, strthis,)
    def __iter__(*args):
        """__iter__(self) -> TSTLexicalIterator"""
        return _tst.TSTLexicalIterator___iter__(*args)

    def next(*args):
        """next(self) -> PyObject"""
        return _tst.TSTLexicalIterator_next(*args)

    __swig_destroy__ = _tst.delete_TSTLexicalIterator
_tst.TSTLexicalIterator_swigregister(TSTLexicalIterator)

class TSTCloseMatchIterator(object):
    """Proxy of C++ TSTCloseMatchIterator class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    def __repr__(self):
        try: strthis = "at 0x%x" %( self.this, ) 
        except: strthis = "" 
        return "<%s.%s; proxy of C++ TSTIterator<close_match_iterator_type > instance %s>" % (self.__class__.__module__, self.__class__.__name__, strthis,)
    def __iter__(*args):
        """__iter__(self) -> TSTCloseMatchIterator"""
        return _tst.TSTCloseMatchIterator___iter__(*args)

    def next(*args):
        """next(self) -> PyObject"""
        return _tst.TSTCloseMatchIterator_next(*args)

    __swig_destroy__ = _tst.delete_TSTCloseMatchIterator
_tst.TSTCloseMatchIterator_swigregister(TSTCloseMatchIterator)



