# This file was created automatically by SWIG.
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.

import _tst

def _swig_setattr(self,class_type,name,value):
    if (name == "this"):
        if isinstance(value, class_type):
            self.__dict__[name] = value.this
            if hasattr(value,"thisown"): self.__dict__["thisown"] = value.thisown
            del value.thisown
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    self.__dict__[name] = value

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


try:
    from weakref import proxy as weakref_proxy
except:
    weakref_proxy = lambda x: x


class IntegerTST(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, IntegerTST, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, IntegerTST, name)
    def __repr__(self):
        return "<C tst<(int)> instance at %s>" % (self.this,)
    def __init__(self, *args):
        _swig_setattr(self, IntegerTST, 'this', _tst.new_IntegerTST(*args))
        _swig_setattr(self, IntegerTST, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_IntegerTST):
        try:
            if self.thisown: destroy(self)
        except: pass
    def adjust(*args): return _tst.IntegerTST_adjust(*args)
    def walk(*args): return _tst.IntegerTST_walk(*args)
    def almost(*args): return _tst.IntegerTST_almost(*args)
    def common_prefix(*args): return _tst.IntegerTST_common_prefix(*args)
    def get(*args): return _tst.IntegerTST_get(*args)
    def __getitem__(*args): return _tst.IntegerTST___getitem__(*args)
    def put(*args): return _tst.IntegerTST_put(*args)
    def __setitem__(*args): return _tst.IntegerTST___setitem__(*args)
    def debug(*args): return _tst.IntegerTST_debug(*args)
    def get_maximum_key_length(*args): return _tst.IntegerTST_get_maximum_key_length(*args)
    def bytes_allocated(*args): return _tst.IntegerTST_bytes_allocated(*args)

class IntegerTSTPtr(IntegerTST):
    def __init__(self, this):
        _swig_setattr(self, IntegerTST, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, IntegerTST, 'thisown', 0)
        _swig_setattr(self, IntegerTST,self.__class__,IntegerTST)
_tst.IntegerTST_swigregister(IntegerTSTPtr)

class IntegerAction(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, IntegerAction, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, IntegerAction, name)
    def __repr__(self):
        return "<C action<(int)> instance at %s>" % (self.this,)
    def __init__(self, *args):
        if self.__class__ == IntegerAction:
            args = (None,) + args
        else:
            args = (self,) + args
        _swig_setattr(self, IntegerAction, 'this', _tst.new_IntegerAction(*args))
        _swig_setattr(self, IntegerAction, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_IntegerAction):
        try:
            if self.thisown: destroy(self)
        except: pass
    def perform(*args): return _tst.IntegerAction_perform(*args)
    def __disown__(self):
        self.thisown = 0
        _tst.disown_IntegerAction(self)
        return weakref_proxy(self)

class IntegerActionPtr(IntegerAction):
    def __init__(self, this):
        _swig_setattr(self, IntegerAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, IntegerAction, 'thisown', 0)
        _swig_setattr(self, IntegerAction,self.__class__,IntegerAction)
_tst.IntegerAction_swigregister(IntegerActionPtr)

class IntegerFilter(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, IntegerFilter, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, IntegerFilter, name)
    def __repr__(self):
        return "<C filter<(int)> instance at %s>" % (self.this,)
    def __init__(self, *args):
        if self.__class__ == IntegerFilter:
            args = (None,) + args
        else:
            args = (self,) + args
        _swig_setattr(self, IntegerFilter, 'this', _tst.new_IntegerFilter(*args))
        _swig_setattr(self, IntegerFilter, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_IntegerFilter):
        try:
            if self.thisown: destroy(self)
        except: pass
    def perform(*args): return _tst.IntegerFilter_perform(*args)
    def __disown__(self):
        self.thisown = 0
        _tst.disown_IntegerFilter(self)
        return weakref_proxy(self)

class IntegerFilterPtr(IntegerFilter):
    def __init__(self, this):
        _swig_setattr(self, IntegerFilter, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, IntegerFilter, 'thisown', 0)
        _swig_setattr(self, IntegerFilter,self.__class__,IntegerFilter)
_tst.IntegerFilter_swigregister(IntegerFilterPtr)

class _object_tst(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, _object_tst, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, _object_tst, name)
    def __repr__(self):
        return "<C tst<(p.PyObject)> instance at %s>" % (self.this,)
    def __init__(self, *args):
        _swig_setattr(self, _object_tst, 'this', _tst.new__object_tst(*args))
        _swig_setattr(self, _object_tst, 'thisown', 1)
    def __del__(self, destroy=_tst.delete__object_tst):
        try:
            if self.thisown: destroy(self)
        except: pass
    def adjust(*args): return _tst._object_tst_adjust(*args)
    def walk(*args): return _tst._object_tst_walk(*args)
    def almost(*args): return _tst._object_tst_almost(*args)
    def common_prefix(*args): return _tst._object_tst_common_prefix(*args)
    def get(*args): return _tst._object_tst_get(*args)
    def __getitem__(*args): return _tst._object_tst___getitem__(*args)
    def put(*args): return _tst._object_tst_put(*args)
    def __setitem__(*args): return _tst._object_tst___setitem__(*args)
    def debug(*args): return _tst._object_tst_debug(*args)
    def get_maximum_key_length(*args): return _tst._object_tst_get_maximum_key_length(*args)
    def bytes_allocated(*args): return _tst._object_tst_bytes_allocated(*args)

class _object_tstPtr(_object_tst):
    def __init__(self, this):
        _swig_setattr(self, _object_tst, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, _object_tst, 'thisown', 0)
        _swig_setattr(self, _object_tst,self.__class__,_object_tst)
_tst._object_tst_swigregister(_object_tstPtr)

class Action(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Action, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Action, name)
    def __repr__(self):
        return "<C action<(p.PyObject)> instance at %s>" % (self.this,)
    def __init__(self, *args):
        if self.__class__ == Action:
            args = (None,) + args
        else:
            args = (self,) + args
        _swig_setattr(self, Action, 'this', _tst.new_Action(*args))
        _swig_setattr(self, Action, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_Action):
        try:
            if self.thisown: destroy(self)
        except: pass
    def perform(*args): return _tst.Action_perform(*args)
    def __disown__(self):
        self.thisown = 0
        _tst.disown_Action(self)
        return weakref_proxy(self)

class ActionPtr(Action):
    def __init__(self, this):
        _swig_setattr(self, Action, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Action, 'thisown', 0)
        _swig_setattr(self, Action,self.__class__,Action)
_tst.Action_swigregister(ActionPtr)

class Filter(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Filter, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Filter, name)
    def __repr__(self):
        return "<C filter<(p.PyObject)> instance at %s>" % (self.this,)
    def __init__(self, *args):
        if self.__class__ == Filter:
            args = (None,) + args
        else:
            args = (self,) + args
        _swig_setattr(self, Filter, 'this', _tst.new_Filter(*args))
        _swig_setattr(self, Filter, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_Filter):
        try:
            if self.thisown: destroy(self)
        except: pass
    def perform(*args): return _tst.Filter_perform(*args)
    def __disown__(self):
        self.thisown = 0
        _tst.disown_Filter(self)
        return weakref_proxy(self)

class FilterPtr(Filter):
    def __init__(self, this):
        _swig_setattr(self, Filter, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Filter, 'thisown', 0)
        _swig_setattr(self, Filter,self.__class__,Filter)
_tst.Filter_swigregister(FilterPtr)

class CallableAction(Action):
    __swig_setmethods__ = {}
    for _s in [Action]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, CallableAction, name, value)
    __swig_getmethods__ = {}
    for _s in [Action]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, CallableAction, name)
    def __repr__(self):
        return "<C CallableAction instance at %s>" % (self.this,)
    def __init__(self, *args):
        _swig_setattr(self, CallableAction, 'this', _tst.new_CallableAction(*args))
        _swig_setattr(self, CallableAction, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_CallableAction):
        try:
            if self.thisown: destroy(self)
        except: pass
    def perform(*args): return _tst.CallableAction_perform(*args)

class CallableActionPtr(CallableAction):
    def __init__(self, this):
        _swig_setattr(self, CallableAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, CallableAction, 'thisown', 0)
        _swig_setattr(self, CallableAction,self.__class__,CallableAction)
_tst.CallableAction_swigregister(CallableActionPtr)

class CallableFilter(Filter):
    __swig_setmethods__ = {}
    for _s in [Filter]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, CallableFilter, name, value)
    __swig_getmethods__ = {}
    for _s in [Filter]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, CallableFilter, name)
    def __repr__(self):
        return "<C CallableFilter instance at %s>" % (self.this,)
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

class DictAction(Action):
    __swig_setmethods__ = {}
    for _s in [Action]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, DictAction, name, value)
    __swig_getmethods__ = {}
    for _s in [Action]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, DictAction, name)
    def __repr__(self):
        return "<C DictAction instance at %s>" % (self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DictAction, 'this', _tst.new_DictAction(*args))
        _swig_setattr(self, DictAction, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_DictAction):
        try:
            if self.thisown: destroy(self)
        except: pass
    def perform(*args): return _tst.DictAction_perform(*args)
    def get_dict(*args): return _tst.DictAction_get_dict(*args)

class DictActionPtr(DictAction):
    def __init__(self, this):
        _swig_setattr(self, DictAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DictAction, 'thisown', 0)
        _swig_setattr(self, DictAction,self.__class__,DictAction)
_tst.DictAction_swigregister(DictActionPtr)

class ListAction(Action):
    __swig_setmethods__ = {}
    for _s in [Action]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ListAction, name, value)
    __swig_getmethods__ = {}
    for _s in [Action]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ListAction, name)
    def __repr__(self):
        return "<C ListAction instance at %s>" % (self.this,)
    def __init__(self, *args):
        _swig_setattr(self, ListAction, 'this', _tst.new_ListAction(*args))
        _swig_setattr(self, ListAction, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_ListAction):
        try:
            if self.thisown: destroy(self)
        except: pass
    def perform(*args): return _tst.ListAction_perform(*args)
    def get_list(*args): return _tst.ListAction_get_list(*args)

class ListActionPtr(ListAction):
    def __init__(self, this):
        _swig_setattr(self, ListAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, ListAction, 'thisown', 0)
        _swig_setattr(self, ListAction,self.__class__,ListAction)
_tst.ListAction_swigregister(ListActionPtr)

class TST(_object_tst):
    __swig_setmethods__ = {}
    for _s in [_object_tst]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, TST, name, value)
    __swig_getmethods__ = {}
    for _s in [_object_tst]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, TST, name)
    def __repr__(self):
        return "<C TST instance at %s>" % (self.this,)
    def __init__(self, *args):
        _swig_setattr(self, TST, 'this', _tst.new_TST(*args))
        _swig_setattr(self, TST, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_TST):
        try:
            if self.thisown: destroy(self)
        except: pass
    def get(*args): return _tst.TST_get(*args)
    def __getitem__(*args): return _tst.TST___getitem__(*args)
    def put(*args): return _tst.TST_put(*args)
    def __setitem__(*args): return _tst.TST___setitem__(*args)

class TSTPtr(TST):
    def __init__(self, this):
        _swig_setattr(self, TST, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, TST, 'thisown', 0)
        _swig_setattr(self, TST,self.__class__,TST)
_tst.TST_swigregister(TSTPtr)


