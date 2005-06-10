# This file was created automatically by SWIG.
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.

import _tst

def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "this"):
        if isinstance(value, class_type):
            self.__dict__[name] = value.this
            if hasattr(value,"thisown"): self.__dict__["thisown"] = value.thisown
            del value.thisown
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name) or (name == "thisown"):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
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


TST_VERSION = _tst.TST_VERSION
UNDEFINED_INDEX = _tst.UNDEFINED_INDEX
class TSTException(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TSTException, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TSTException, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ TSTException instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, TSTException, 'this', _tst.new_TSTException(*args))
        _swig_setattr(self, TSTException, 'thisown', 1)
    __swig_setmethods__["message"] = _tst.TSTException_message_set
    __swig_getmethods__["message"] = _tst.TSTException_message_get
    if _newclass:message = property(_tst.TSTException_message_get, _tst.TSTException_message_set)
    def __del__(self, destroy=_tst.delete_TSTException):
        try:
            if self.thisown: destroy(self)
        except: pass


class TSTExceptionPtr(TSTException):
    def __init__(self, this):
        _swig_setattr(self, TSTException, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, TSTException, 'thisown', 0)
        _swig_setattr(self, TSTException,self.__class__,TSTException)
_tst.TSTException_swigregister(TSTExceptionPtr)

class _MemoryStorage(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, _MemoryStorage, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, _MemoryStorage, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ memory_storage<char,PyObject * > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, _MemoryStorage, 'this', _tst.new__MemoryStorage(*args))
        _swig_setattr(self, _MemoryStorage, 'thisown', 1)
    def __del__(self, destroy=_tst.delete__MemoryStorage):
        try:
            if self.thisown: destroy(self)
        except: pass

    def get(*args): return _tst._MemoryStorage_get(*args)
    def store_data(*args): return _tst._MemoryStorage_store_data(*args)
    def set(*args): return _tst._MemoryStorage_set(*args)
    def new_node(*args): return _tst._MemoryStorage_new_node(*args)
    def delete_node(*args): return _tst._MemoryStorage_delete_node(*args)
    def pack(*args): return _tst._MemoryStorage_pack(*args)
    def read(*args): return _tst._MemoryStorage_read(*args)
    def write(*args): return _tst._MemoryStorage_write(*args)

class _MemoryStoragePtr(_MemoryStorage):
    def __init__(self, this):
        _swig_setattr(self, _MemoryStorage, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, _MemoryStorage, 'thisown', 0)
        _swig_setattr(self, _MemoryStorage,self.__class__,_MemoryStorage)
_tst._MemoryStorage_swigregister(_MemoryStoragePtr)

class _TST(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, _TST, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, _TST, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ tst<char,PyObject *,MemoryStorage > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, _TST, 'this', _tst.new__TST(*args))
        _swig_setattr(self, _TST, 'thisown', 1)
    def __del__(self, destroy=_tst.delete__TST):
        try:
            if self.thisown: destroy(self)
        except: pass

    def pack(*args): return _tst._TST_pack(*args)
    def walk(*args): return _tst._TST_walk(*args)
    def almost(*args): return _tst._TST_almost(*args)
    def common_prefix(*args): return _tst._TST_common_prefix(*args)
    def get(*args): return _tst._TST_get(*args)
    def get_or_build(*args): return _tst._TST_get_or_build(*args)
    def put(*args): return _tst._TST_put(*args)
    def remove(*args): return _tst._TST_remove(*args)
    def get_maximum_key_length(*args): return _tst._TST_get_maximum_key_length(*args)
    def write(*args): return _tst._TST_write(*args)
    def scan(*args): return _tst._TST_scan(*args)
    def scan_with_stop_chars(*args): return _tst._TST_scan_with_stop_chars(*args)

class _TSTPtr(_TST):
    def __init__(self, this):
        _swig_setattr(self, _TST, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, _TST, 'thisown', 0)
        _swig_setattr(self, _TST,self.__class__,_TST)
_tst._TST_swigregister(_TSTPtr)

class _Action(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, _Action, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, _Action, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ action<char,PyObject * > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __del__(self, destroy=_tst.delete__Action):
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args): return _tst._Action_perform(*args)
    def result(*args): return _tst._Action_result(*args)

class _ActionPtr(_Action):
    def __init__(self, this):
        _swig_setattr(self, _Action, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, _Action, 'thisown', 0)
        _swig_setattr(self, _Action,self.__class__,_Action)
_tst._Action_swigregister(_ActionPtr)

class _Filter(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, _Filter, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, _Filter, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ filter<char,PyObject * > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __del__(self, destroy=_tst.delete__Filter):
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args): return _tst._Filter_perform(*args)

class _FilterPtr(_Filter):
    def __init__(self, this):
        _swig_setattr(self, _Filter, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, _Filter, 'thisown', 0)
        _swig_setattr(self, _Filter,self.__class__,_Filter)
_tst._Filter_swigregister(_FilterPtr)

class PythonReference(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, PythonReference, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, PythonReference, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ PythonReference instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, PythonReference, 'this', _tst.new_PythonReference(*args))
        _swig_setattr(self, PythonReference, 'thisown', 1)
    def get(*args): return _tst.PythonReference_get(*args)
    def lend(*args): return _tst.PythonReference_lend(*args)
    def __del__(self, destroy=_tst.delete_PythonReference):
        try:
            if self.thisown: destroy(self)
        except: pass

    def write(*args): return _tst.PythonReference_write(*args)

class PythonReferencePtr(PythonReference):
    def __init__(self, this):
        _swig_setattr(self, PythonReference, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, PythonReference, 'thisown', 0)
        _swig_setattr(self, PythonReference,self.__class__,PythonReference)
_tst.PythonReference_swigregister(PythonReferencePtr)

class CallableAction(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CallableAction, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CallableAction, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ CallableAction instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, CallableAction, 'this', _tst.new_CallableAction(*args))
        _swig_setattr(self, CallableAction, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_CallableAction):
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args): return _tst.CallableAction_perform(*args)
    def result(*args): return _tst.CallableAction_result(*args)

class CallableActionPtr(CallableAction):
    def __init__(self, this):
        _swig_setattr(self, CallableAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, CallableAction, 'thisown', 0)
        _swig_setattr(self, CallableAction,self.__class__,CallableAction)
_tst.CallableAction_swigregister(CallableActionPtr)

class CallableFilter(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CallableFilter, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CallableFilter, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ CallableFilter instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, CallableFilter, 'this', _tst.new_CallableFilter(*args))
        _swig_setattr(self, CallableFilter, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_CallableFilter):
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args): return _tst.CallableFilter_perform(*args)

class CallableFilterPtr(CallableFilter):
    def __init__(self, this):
        _swig_setattr(self, CallableFilter, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, CallableFilter, 'thisown', 0)
        _swig_setattr(self, CallableFilter,self.__class__,CallableFilter)
_tst.CallableFilter_swigregister(CallableFilterPtr)

class NullFilter(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, NullFilter, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, NullFilter, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ NullFilter instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, NullFilter, 'this', _tst.new_NullFilter(*args))
        _swig_setattr(self, NullFilter, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_NullFilter):
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args): return _tst.NullFilter_perform(*args)

class NullFilterPtr(NullFilter):
    def __init__(self, this):
        _swig_setattr(self, NullFilter, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, NullFilter, 'thisown', 0)
        _swig_setattr(self, NullFilter,self.__class__,NullFilter)
_tst.NullFilter_swigregister(NullFilterPtr)

class DictAction(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DictAction, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DictAction, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ DictAction instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DictAction, 'this', _tst.new_DictAction(*args))
        _swig_setattr(self, DictAction, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_DictAction):
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args): return _tst.DictAction_perform(*args)
    def result(*args): return _tst.DictAction_result(*args)

class DictActionPtr(DictAction):
    def __init__(self, this):
        _swig_setattr(self, DictAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DictAction, 'thisown', 0)
        _swig_setattr(self, DictAction,self.__class__,DictAction)
_tst.DictAction_swigregister(DictActionPtr)

class ListAction(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ListAction, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ListAction, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ ListAction instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, ListAction, 'this', _tst.new_ListAction(*args))
        _swig_setattr(self, ListAction, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_ListAction):
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args): return _tst.ListAction_perform(*args)
    def result(*args): return _tst.ListAction_result(*args)

class ListActionPtr(ListAction):
    def __init__(self, this):
        _swig_setattr(self, ListAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, ListAction, 'thisown', 0)
        _swig_setattr(self, ListAction,self.__class__,ListAction)
_tst.ListAction_swigregister(ListActionPtr)

class TupleListAction(_Action):
    __swig_setmethods__ = {}
    for _s in [_Action]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, TupleListAction, name, value)
    __swig_getmethods__ = {}
    for _s in [_Action]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, TupleListAction, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ TupleListAction instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, TupleListAction, 'this', _tst.new_TupleListAction(*args))
        _swig_setattr(self, TupleListAction, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_TupleListAction):
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args): return _tst.TupleListAction_perform(*args)
    def result(*args): return _tst.TupleListAction_result(*args)

class TupleListActionPtr(TupleListAction):
    def __init__(self, this):
        _swig_setattr(self, TupleListAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, TupleListAction, 'thisown', 0)
        _swig_setattr(self, TupleListAction,self.__class__,TupleListAction)
_tst.TupleListAction_swigregister(TupleListActionPtr)

class ObjectSerializer(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ObjectSerializer, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ObjectSerializer, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ ObjectSerializer instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, ObjectSerializer, 'this', _tst.new_ObjectSerializer(*args))
        _swig_setattr(self, ObjectSerializer, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_ObjectSerializer):
        try:
            if self.thisown: destroy(self)
        except: pass

    def write(*args): return _tst.ObjectSerializer_write(*args)
    def read(*args): return _tst.ObjectSerializer_read(*args)

class ObjectSerializerPtr(ObjectSerializer):
    def __init__(self, this):
        _swig_setattr(self, ObjectSerializer, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, ObjectSerializer, 'thisown', 0)
        _swig_setattr(self, ObjectSerializer,self.__class__,ObjectSerializer)
_tst.ObjectSerializer_swigregister(ObjectSerializerPtr)

class MemoryStorage(_MemoryStorage):
    __swig_setmethods__ = {}
    for _s in [_MemoryStorage]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, MemoryStorage, name, value)
    __swig_getmethods__ = {}
    for _s in [_MemoryStorage]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, MemoryStorage, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ MemoryStorage instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, MemoryStorage, 'this', _tst.new_MemoryStorage(*args))
        _swig_setattr(self, MemoryStorage, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_MemoryStorage):
        try:
            if self.thisown: destroy(self)
        except: pass

    def store_data(*args): return _tst.MemoryStorage_store_data(*args)

class MemoryStoragePtr(MemoryStorage):
    def __init__(self, this):
        _swig_setattr(self, MemoryStorage, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, MemoryStorage, 'thisown', 0)
        _swig_setattr(self, MemoryStorage,self.__class__,MemoryStorage)
_tst.MemoryStorage_swigregister(MemoryStoragePtr)

class TST(_TST):
    __swig_setmethods__ = {}
    for _s in [_TST]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, TST, name, value)
    __swig_getmethods__ = {}
    for _s in [_TST]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, TST, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ TST instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, TST, 'this', _tst.new_TST(*args))
        _swig_setattr(self, TST, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_TST):
        try:
            if self.thisown: destroy(self)
        except: pass

    def write(*args): return _tst.TST_write(*args)
    def get(*args): return _tst.TST_get(*args)
    def get_or_build(*args): return _tst.TST_get_or_build(*args)
    def put(*args): return _tst.TST_put(*args)
    def __getitem__(*args): return _tst.TST___getitem__(*args)
    def __setitem__(*args): return _tst.TST___setitem__(*args)
    def __delitem__(*args): return _tst.TST___delitem__(*args)

class TSTPtr(TST):
    def __init__(self, this):
        _swig_setattr(self, TST, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, TST, 'thisown', 0)
        _swig_setattr(self, TST,self.__class__,TST)
_tst.TST_swigregister(TSTPtr)


