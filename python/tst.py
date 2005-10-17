# This file was created automatically by SWIG 1.3.27.
# Don't modify this file, modify the SWIG interface instead.

import _tst

# This file is compatible with both classic and new-style classes.
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


class TSTException(_object):
    """Proxy of C++ TSTException class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TSTException, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TSTException, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ TSTException instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self, _message) -> TSTException"""
        _swig_setattr(self, TSTException, 'this', _tst.new_TSTException(*args))
        _swig_setattr(self, TSTException, 'thisown', 1)
    __swig_setmethods__["message"] = _tst.TSTException_message_set
    __swig_getmethods__["message"] = _tst.TSTException_message_get
    if _newclass:message = property(_tst.TSTException_message_get, _tst.TSTException_message_set)
    def __del__(self, destroy=_tst.delete_TSTException):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass


class TSTExceptionPtr(TSTException):
    def __init__(self, this):
        _swig_setattr(self, TSTException, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, TSTException, 'thisown', 0)
        self.__class__ = TSTException
_tst.TSTException_swigregister(TSTExceptionPtr)
cvar = _tst.cvar
TST_VERSION = cvar.TST_VERSION
UNDEFINED_INDEX = cvar.UNDEFINED_INDEX

class _TST(_object):
    """Proxy of C++ _TST class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, _TST, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, _TST, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ tst<char,PythonReference,MemoryStorage,ObjectSerializer > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self, storage, default_value) -> _TST"""
        _swig_setattr(self, _TST, 'this', _tst.new__TST(*args))
        _swig_setattr(self, _TST, 'thisown', 1)
    def __del__(self, destroy=_tst.delete__TST):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass

    def pack(*args):
        """pack(self)"""
        return _tst._TST_pack(*args)

    def walk(*args):
        """walk(self, filter, to_perform) -> PythonReference"""
        return _tst._TST_walk(*args)

    def almost(*args):
        """almost(self, string, maximum_distance, filter, to_perform) -> PythonReference"""
        return _tst._TST_almost(*args)

    def common_prefix(*args):
        """common_prefix(self, string, filter, to_perform) -> PythonReference"""
        return _tst._TST_common_prefix(*args)

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

    def get_maximum_key_length(*args):
        """get_maximum_key_length(self) -> int"""
        return _tst._TST_get_maximum_key_length(*args)

    def write(*args):
        """write(self, file)"""
        return _tst._TST_write(*args)

    def read(*args):
        """read(self, file)"""
        return _tst._TST_read(*args)

    def scan(*args):
        """scan(self, string, to_perform) -> PythonReference"""
        return _tst._TST_scan(*args)

    def scan_with_stop_chars(*args):
        """scan_with_stop_chars(self, string, stop_chars, to_perform) -> PythonReference"""
        return _tst._TST_scan_with_stop_chars(*args)


class _TSTPtr(_TST):
    def __init__(self, this):
        _swig_setattr(self, _TST, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, _TST, 'thisown', 0)
        self.__class__ = _TST
_tst._TST_swigregister(_TSTPtr)

class _Action(_object):
    """Proxy of C++ _Action class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, _Action, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, _Action, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ action<char,PythonReference > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __del__(self, destroy=_tst.delete__Action):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args):
        """perform(self, string, remaining_distance, data)"""
        return _tst._Action_perform(*args)

    def result(*args):
        """result(self) -> PythonReference"""
        return _tst._Action_result(*args)


class _ActionPtr(_Action):
    def __init__(self, this):
        _swig_setattr(self, _Action, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, _Action, 'thisown', 0)
        self.__class__ = _Action
_tst._Action_swigregister(_ActionPtr)

class _Filter(_object):
    """Proxy of C++ _Filter class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, _Filter, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, _Filter, name)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ filter<char,PythonReference > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __del__(self, destroy=_tst.delete__Filter):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args):
        """perform(self, string, remaining_distance, data) -> PythonReference"""
        return _tst._Filter_perform(*args)


class _FilterPtr(_Filter):
    def __init__(self, this):
        _swig_setattr(self, _Filter, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, _Filter, 'thisown', 0)
        self.__class__ = _Filter
_tst._Filter_swigregister(_FilterPtr)

class CallableAction(_Action):
    """Proxy of C++ CallableAction class"""
    __swig_setmethods__ = {}
    for _s in [_Action]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, CallableAction, name, value)
    __swig_getmethods__ = {}
    for _s in [_Action]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, CallableAction, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ CallableAction instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self, perform, result) -> CallableAction"""
        _swig_setattr(self, CallableAction, 'this', _tst.new_CallableAction(*args))
        _swig_setattr(self, CallableAction, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_CallableAction):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args):
        """perform(self, string, remaining_distance, data)"""
        return _tst.CallableAction_perform(*args)

    def result(*args):
        """result(self) -> PythonReference"""
        return _tst.CallableAction_result(*args)


class CallableActionPtr(CallableAction):
    def __init__(self, this):
        _swig_setattr(self, CallableAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, CallableAction, 'thisown', 0)
        self.__class__ = CallableAction
_tst.CallableAction_swigregister(CallableActionPtr)

class CallableFilter(_Filter):
    """Proxy of C++ CallableFilter class"""
    __swig_setmethods__ = {}
    for _s in [_Filter]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, CallableFilter, name, value)
    __swig_getmethods__ = {}
    for _s in [_Filter]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, CallableFilter, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ CallableFilter instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self, _callable) -> CallableFilter"""
        _swig_setattr(self, CallableFilter, 'this', _tst.new_CallableFilter(*args))
        _swig_setattr(self, CallableFilter, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_CallableFilter):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args):
        """perform(self, string, remaining_distance, data) -> PythonReference"""
        return _tst.CallableFilter_perform(*args)


class CallableFilterPtr(CallableFilter):
    def __init__(self, this):
        _swig_setattr(self, CallableFilter, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, CallableFilter, 'thisown', 0)
        self.__class__ = CallableFilter
_tst.CallableFilter_swigregister(CallableFilterPtr)

class NullFilter(_Filter):
    """Proxy of C++ NullFilter class"""
    __swig_setmethods__ = {}
    for _s in [_Filter]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, NullFilter, name, value)
    __swig_getmethods__ = {}
    for _s in [_Filter]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, NullFilter, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ NullFilter instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> NullFilter"""
        _swig_setattr(self, NullFilter, 'this', _tst.new_NullFilter(*args))
        _swig_setattr(self, NullFilter, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_NullFilter):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args):
        """perform(self, string, remaining_distance, data) -> PythonReference"""
        return _tst.NullFilter_perform(*args)


class NullFilterPtr(NullFilter):
    def __init__(self, this):
        _swig_setattr(self, NullFilter, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, NullFilter, 'thisown', 0)
        self.__class__ = NullFilter
_tst.NullFilter_swigregister(NullFilterPtr)

class DictAction(_Action):
    """Proxy of C++ DictAction class"""
    __swig_setmethods__ = {}
    for _s in [_Action]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, DictAction, name, value)
    __swig_getmethods__ = {}
    for _s in [_Action]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, DictAction, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ DictAction instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> DictAction"""
        _swig_setattr(self, DictAction, 'this', _tst.new_DictAction(*args))
        _swig_setattr(self, DictAction, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_DictAction):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args):
        """perform(self, string, remaining_distance, data)"""
        return _tst.DictAction_perform(*args)

    def result(*args):
        """result(self) -> PythonReference"""
        return _tst.DictAction_result(*args)


class DictActionPtr(DictAction):
    def __init__(self, this):
        _swig_setattr(self, DictAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DictAction, 'thisown', 0)
        self.__class__ = DictAction
_tst.DictAction_swigregister(DictActionPtr)

class ListAction(_Action):
    """Proxy of C++ ListAction class"""
    __swig_setmethods__ = {}
    for _s in [_Action]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ListAction, name, value)
    __swig_getmethods__ = {}
    for _s in [_Action]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ListAction, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ ListAction instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> ListAction"""
        _swig_setattr(self, ListAction, 'this', _tst.new_ListAction(*args))
        _swig_setattr(self, ListAction, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_ListAction):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args):
        """perform(self, string, remaining_distance, data)"""
        return _tst.ListAction_perform(*args)

    def result(*args):
        """result(self) -> PythonReference"""
        return _tst.ListAction_result(*args)


class ListActionPtr(ListAction):
    def __init__(self, this):
        _swig_setattr(self, ListAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, ListAction, 'thisown', 0)
        self.__class__ = ListAction
_tst.ListAction_swigregister(ListActionPtr)

class TupleListAction(_Action):
    """Proxy of C++ TupleListAction class"""
    __swig_setmethods__ = {}
    for _s in [_Action]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, TupleListAction, name, value)
    __swig_getmethods__ = {}
    for _s in [_Action]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, TupleListAction, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ TupleListAction instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> TupleListAction"""
        _swig_setattr(self, TupleListAction, 'this', _tst.new_TupleListAction(*args))
        _swig_setattr(self, TupleListAction, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_TupleListAction):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass

    def perform(*args):
        """perform(self, string, remaining_distance, data)"""
        return _tst.TupleListAction_perform(*args)

    def result(*args):
        """result(self) -> PythonReference"""
        return _tst.TupleListAction_result(*args)


class TupleListActionPtr(TupleListAction):
    def __init__(self, this):
        _swig_setattr(self, TupleListAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, TupleListAction, 'thisown', 0)
        self.__class__ = TupleListAction
_tst.TupleListAction_swigregister(TupleListActionPtr)

class ObjectSerializer(_object):
    """Proxy of C++ ObjectSerializer class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ObjectSerializer, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ObjectSerializer, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ ObjectSerializer instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> ObjectSerializer"""
        _swig_setattr(self, ObjectSerializer, 'this', _tst.new_ObjectSerializer(*args))
        _swig_setattr(self, ObjectSerializer, 'thisown', 1)
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

    def __del__(self, destroy=_tst.delete_ObjectSerializer):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass


class ObjectSerializerPtr(ObjectSerializer):
    def __init__(self, this):
        _swig_setattr(self, ObjectSerializer, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, ObjectSerializer, 'thisown', 0)
        self.__class__ = ObjectSerializer
_tst.ObjectSerializer_swigregister(ObjectSerializerPtr)

class TST(_TST):
    """Proxy of C++ TST class"""
    __swig_setmethods__ = {}
    for _s in [_TST]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, TST, name, value)
    __swig_getmethods__ = {}
    for _s in [_TST]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, TST, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ TST instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> TST"""
        _swig_setattr(self, TST, 'this', _tst.new_TST(*args))
        _swig_setattr(self, TST, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_TST):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass

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


class TSTPtr(TST):
    def __init__(self, this):
        _swig_setattr(self, TST, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, TST, 'thisown', 0)
        self.__class__ = TST
_tst.TST_swigregister(TSTPtr)



