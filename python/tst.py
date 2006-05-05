# This file was created automatically by SWIG 1.3.29.
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


class TSTException(object):
    """Proxy of C++ TSTException class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """__init__(self, char _message) -> TSTException"""
        _tst.TSTException_swiginit(self,_tst.new_TSTException(*args))
    def what(*args):
        """what(self) -> char"""
        return _tst.TSTException_what(*args)

    __swig_destroy__ = _tst.delete_TSTException
TSTException.what = new_instancemethod(_tst.TSTException_what,None,TSTException)
TSTException_swigregister = _tst.TSTException_swigregister
TSTException_swigregister(TSTException)
cvar = _tst.cvar
TST_VERSION = cvar.TST_VERSION
UNDEFINED_INDEX = cvar.UNDEFINED_INDEX

class _TST(object):
    """Proxy of C++ _TST class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """__init__(self) -> _TST"""
        _tst._TST_swiginit(self,_tst.new__TST(*args))
    __swig_destroy__ = _tst.delete__TST
    def pack(*args):
        """pack(self)"""
        return _tst._TST_pack(*args)

    def walk(*args):
        """
        walk(self, _Filter filter, _Action to_perform) -> PythonReference
        walk(self, _Filter filter, _Action to_perform, std::basic_string<(char)> string) -> PythonReference
        """
        return _tst._TST_walk(*args)

    def close_match(*args):
        """
        close_match(self, std::basic_string<(char)> string, int maximum_distance, 
            _Filter filter, _Action to_perform) -> PythonReference
        """
        return _tst._TST_close_match(*args)

    def prefix_match(*args):
        """prefix_match(self, std::basic_string<(char)> string, _Filter filter, _Action to_perform) -> PythonReference"""
        return _tst._TST_prefix_match(*args)

    def match(*args):
        """match(self, std::basic_string<(char)> string, _Filter filter, _Action to_perform) -> PythonReference"""
        return _tst._TST_match(*args)

    def get(*args):
        """get(self, std::basic_string<(char)> string) -> PythonReference"""
        return _tst._TST_get(*args)

    def get_or_build(*args):
        """get_or_build(self, std::basic_string<(char)> string, _Filter factory) -> PythonReference"""
        return _tst._TST_get_or_build(*args)

    def put(*args):
        """put(self, std::basic_string<(char)> string, PythonReference data) -> PythonReference"""
        return _tst._TST_put(*args)

    def remove(*args):
        """remove(self, std::basic_string<(char)> string)"""
        return _tst._TST_remove(*args)

    def contains(*args):
        """contains(self, std::basic_string<(char)> string) -> bool"""
        return _tst._TST_contains(*args)

    def write(*args):
        """write(self, std::ostream file)"""
        return _tst._TST_write(*args)

    def read(*args):
        """read(self, std::istream file)"""
        return _tst._TST_read(*args)

    def iterator(*args):
        """
        iterator(self) -> lexical_iterator<(char,PythonReference,MemoryStorage,ObjectSerializer)>
        iterator(self, std::basic_string<(char)> string) -> lexical_iterator<(char,PythonReference,MemoryStorage,ObjectSerializer)>
        """
        return _tst._TST_iterator(*args)

    def close_match_iterator(*args):
        """close_match_iterator(self, std::basic_string<(char)> string, int distance) -> match_iterator<(char,PythonReference,MemoryStorage,ObjectSerializer)>"""
        return _tst._TST_close_match_iterator(*args)

    def get_number_of_nodes(*args):
        """get_number_of_nodes(self) -> int"""
        return _tst._TST_get_number_of_nodes(*args)

    def get_default_value(*args):
        """get_default_value(self) -> PythonReference"""
        return _tst._TST_get_default_value(*args)

    def scan(*args):
        """scan(self, std::basic_string<(char)> string, _Action to_perform) -> PythonReference"""
        return _tst._TST_scan(*args)

    def scan_with_stop_chars(*args):
        """
        scan_with_stop_chars(self, std::basic_string<(char)> string, std::basic_string<(char)> stop_chars, 
            _Action to_perform) -> PythonReference
        """
        return _tst._TST_scan_with_stop_chars(*args)

_TST.pack = new_instancemethod(_tst._TST_pack,None,_TST)
_TST.walk = new_instancemethod(_tst._TST_walk,None,_TST)
_TST.close_match = new_instancemethod(_tst._TST_close_match,None,_TST)
_TST.prefix_match = new_instancemethod(_tst._TST_prefix_match,None,_TST)
_TST.match = new_instancemethod(_tst._TST_match,None,_TST)
_TST.get = new_instancemethod(_tst._TST_get,None,_TST)
_TST.get_or_build = new_instancemethod(_tst._TST_get_or_build,None,_TST)
_TST.put = new_instancemethod(_tst._TST_put,None,_TST)
_TST.remove = new_instancemethod(_tst._TST_remove,None,_TST)
_TST.contains = new_instancemethod(_tst._TST_contains,None,_TST)
_TST.write = new_instancemethod(_tst._TST_write,None,_TST)
_TST.read = new_instancemethod(_tst._TST_read,None,_TST)
_TST.iterator = new_instancemethod(_tst._TST_iterator,None,_TST)
_TST.close_match_iterator = new_instancemethod(_tst._TST_close_match_iterator,None,_TST)
_TST.get_number_of_nodes = new_instancemethod(_tst._TST_get_number_of_nodes,None,_TST)
_TST.get_default_value = new_instancemethod(_tst._TST_get_default_value,None,_TST)
_TST.scan = new_instancemethod(_tst._TST_scan,None,_TST)
_TST.scan_with_stop_chars = new_instancemethod(_tst._TST_scan_with_stop_chars,None,_TST)
_TST_swigregister = _tst._TST_swigregister
_TST_swigregister(_TST)

class _Action(object):
    """Proxy of C++ _Action class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _tst.delete__Action
    def perform(*args):
        """
        perform(self, std::basic_string<(char)> string, int remaining_distance, 
            PythonReference data)
        """
        return _tst._Action_perform(*args)

    def result(*args):
        """result(self) -> PythonReference"""
        return _tst._Action_result(*args)

_Action.perform = new_instancemethod(_tst._Action_perform,None,_Action)
_Action.result = new_instancemethod(_tst._Action_result,None,_Action)
_Action_swigregister = _tst._Action_swigregister
_Action_swigregister(_Action)

class _Filter(object):
    """Proxy of C++ _Filter class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _tst.delete__Filter
    def perform(*args):
        """
        perform(self, std::basic_string<(char)> string, int remaining_distance, 
            PythonReference data) -> PythonReference
        """
        return _tst._Filter_perform(*args)

_Filter.perform = new_instancemethod(_tst._Filter_perform,None,_Filter)
_Filter_swigregister = _tst._Filter_swigregister
_Filter_swigregister(_Filter)

class CallableAction(_Action):
    """Proxy of C++ CallableAction class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """__init__(self, PythonReference perform, PythonReference result) -> CallableAction"""
        _tst.CallableAction_swiginit(self,_tst.new_CallableAction(*args))
    __swig_destroy__ = _tst.delete_CallableAction
CallableAction_swigregister = _tst.CallableAction_swigregister
CallableAction_swigregister(CallableAction)

class CallableFilter(_Filter):
    """Proxy of C++ CallableFilter class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """__init__(self, PythonReference _callable) -> CallableFilter"""
        _tst.CallableFilter_swiginit(self,_tst.new_CallableFilter(*args))
    __swig_destroy__ = _tst.delete_CallableFilter
CallableFilter_swigregister = _tst.CallableFilter_swigregister
CallableFilter_swigregister(CallableFilter)

class DictAction(_Action):
    """Proxy of C++ DictAction class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """__init__(self) -> DictAction"""
        _tst.DictAction_swiginit(self,_tst.new_DictAction(*args))
    __swig_destroy__ = _tst.delete_DictAction
DictAction_swigregister = _tst.DictAction_swigregister
DictAction_swigregister(DictAction)

class ListAction(_Action):
    """Proxy of C++ ListAction class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """__init__(self) -> ListAction"""
        _tst.ListAction_swiginit(self,_tst.new_ListAction(*args))
    __swig_destroy__ = _tst.delete_ListAction
ListAction_swigregister = _tst.ListAction_swigregister
ListAction_swigregister(ListAction)

class TupleListAction(_Action):
    """Proxy of C++ TupleListAction class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """__init__(self) -> TupleListAction"""
        _tst.TupleListAction_swiginit(self,_tst.new_TupleListAction(*args))
    __swig_destroy__ = _tst.delete_TupleListAction
TupleListAction_swigregister = _tst.TupleListAction_swigregister
TupleListAction_swigregister(TupleListAction)

class ObjectSerializer(object):
    """Proxy of C++ ObjectSerializer class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """__init__(self) -> ObjectSerializer"""
        _tst.ObjectSerializer_swiginit(self,_tst.new_ObjectSerializer(*args))
    def write(*args):
        """write(self, std::ostream file, PythonReference data)"""
        return _tst.ObjectSerializer_write(*args)

    def read(*args):
        """read(self, std::istream file) -> PythonReference"""
        return _tst.ObjectSerializer_read(*args)

    __swig_destroy__ = _tst.delete_ObjectSerializer
ObjectSerializer.write = new_instancemethod(_tst.ObjectSerializer_write,None,ObjectSerializer)
ObjectSerializer.read = new_instancemethod(_tst.ObjectSerializer_read,None,ObjectSerializer)
ObjectSerializer_swigregister = _tst.ObjectSerializer_swigregister
ObjectSerializer_swigregister(ObjectSerializer)

class TST(_TST):
    """Proxy of C++ TST class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args): 
        """__init__(self) -> TST"""
        _tst.TST_swiginit(self,_tst.new_TST(*args))
    __swig_destroy__ = _tst.delete_TST
    def write_to_file(*args):
        """write_to_file(self, PythonReference file) -> PythonReference"""
        return _tst.TST_write_to_file(*args)

    def read_from_file(*args):
        """read_from_file(self, PythonReference file) -> PythonReference"""
        return _tst.TST_read_from_file(*args)

    def __getitem__(*args):
        """__getitem__(self, std::basic_string<(char)> string) -> PythonReference"""
        return _tst.TST___getitem__(*args)

    def __setitem__(*args):
        """__setitem__(self, std::basic_string<(char)> string, PythonReference data) -> PythonReference"""
        return _tst.TST___setitem__(*args)

    def __delitem__(*args):
        """__delitem__(self, std::basic_string<(char)> string)"""
        return _tst.TST___delitem__(*args)

    def __contains__(*args):
        """__contains__(self, std::basic_string<(char)> string) -> PythonReference"""
        return _tst.TST___contains__(*args)

    def iterator(*args):
        """
        iterator(self) -> TSTLexicalIterator
        iterator(self, std::basic_string<(char)> string) -> TSTLexicalIterator
        """
        return _tst.TST_iterator(*args)

    def close_match_iterator(*args):
        """close_match_iterator(self, std::basic_string<(char)> string, int distance) -> TSTCloseMatchIterator"""
        return _tst.TST_close_match_iterator(*args)

    def __iter__(*args):
        """__iter__(self) -> TSTLexicalIterator"""
        return _tst.TST___iter__(*args)

TST.write_to_file = new_instancemethod(_tst.TST_write_to_file,None,TST)
TST.read_from_file = new_instancemethod(_tst.TST_read_from_file,None,TST)
TST.__getitem__ = new_instancemethod(_tst.TST___getitem__,None,TST)
TST.__setitem__ = new_instancemethod(_tst.TST___setitem__,None,TST)
TST.__delitem__ = new_instancemethod(_tst.TST___delitem__,None,TST)
TST.__contains__ = new_instancemethod(_tst.TST___contains__,None,TST)
TST.iterator = new_instancemethod(_tst.TST_iterator,None,TST)
TST.close_match_iterator = new_instancemethod(_tst.TST_close_match_iterator,None,TST)
TST.__iter__ = new_instancemethod(_tst.TST___iter__,None,TST)
TST_swigregister = _tst.TST_swigregister
TST_swigregister(TST)

class TSTLexicalIterator(object):
    """Proxy of C++ TSTLexicalIterator class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def __iter__(*args):
        """__iter__(self) -> TSTLexicalIterator"""
        return _tst.TSTLexicalIterator___iter__(*args)

    def next(*args):
        """next(self) -> PyObject"""
        return _tst.TSTLexicalIterator_next(*args)

    __swig_destroy__ = _tst.delete_TSTLexicalIterator
TSTLexicalIterator.__iter__ = new_instancemethod(_tst.TSTLexicalIterator___iter__,None,TSTLexicalIterator)
TSTLexicalIterator.next = new_instancemethod(_tst.TSTLexicalIterator_next,None,TSTLexicalIterator)
TSTLexicalIterator_swigregister = _tst.TSTLexicalIterator_swigregister
TSTLexicalIterator_swigregister(TSTLexicalIterator)

class TSTCloseMatchIterator(object):
    """Proxy of C++ TSTCloseMatchIterator class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def __iter__(*args):
        """__iter__(self) -> TSTCloseMatchIterator"""
        return _tst.TSTCloseMatchIterator___iter__(*args)

    def next(*args):
        """next(self) -> PyObject"""
        return _tst.TSTCloseMatchIterator_next(*args)

    __swig_destroy__ = _tst.delete_TSTCloseMatchIterator
TSTCloseMatchIterator.__iter__ = new_instancemethod(_tst.TSTCloseMatchIterator___iter__,None,TSTCloseMatchIterator)
TSTCloseMatchIterator.next = new_instancemethod(_tst.TSTCloseMatchIterator_next,None,TSTCloseMatchIterator)
TSTCloseMatchIterator_swigregister = _tst.TSTCloseMatchIterator_swigregister
TSTCloseMatchIterator_swigregister(TSTCloseMatchIterator)



