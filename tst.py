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
    def almost_perform(*args): return _tst.IntegerTST_almost_perform(*args)
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

class StringTST(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, StringTST, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, StringTST, name)
    def __repr__(self):
        return "<C tst<(p.char)> instance at %s>" % (self.this,)
    def __init__(self, *args):
        _swig_setattr(self, StringTST, 'this', _tst.new_StringTST(*args))
        _swig_setattr(self, StringTST, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_StringTST):
        try:
            if self.thisown: destroy(self)
        except: pass
    def adjust(*args): return _tst.StringTST_adjust(*args)
    def walk(*args): return _tst.StringTST_walk(*args)
    def almost_perform(*args): return _tst.StringTST_almost_perform(*args)
    def get(*args): return _tst.StringTST_get(*args)
    def __getitem__(*args): return _tst.StringTST___getitem__(*args)
    def put(*args): return _tst.StringTST_put(*args)
    def __setitem__(*args): return _tst.StringTST___setitem__(*args)
    def debug(*args): return _tst.StringTST_debug(*args)
    def get_maximum_key_length(*args): return _tst.StringTST_get_maximum_key_length(*args)
    def bytes_allocated(*args): return _tst.StringTST_bytes_allocated(*args)

class StringTSTPtr(StringTST):
    def __init__(self, this):
        _swig_setattr(self, StringTST, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, StringTST, 'thisown', 0)
        _swig_setattr(self, StringTST,self.__class__,StringTST)
_tst.StringTST_swigregister(StringTSTPtr)

class StringAction(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, StringAction, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, StringAction, name)
    def __repr__(self):
        return "<C action<(p.char)> instance at %s>" % (self.this,)
    def __init__(self, *args):
        if self.__class__ == StringAction:
            args = (None,) + args
        else:
            args = (self,) + args
        _swig_setattr(self, StringAction, 'this', _tst.new_StringAction(*args))
        _swig_setattr(self, StringAction, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_StringAction):
        try:
            if self.thisown: destroy(self)
        except: pass
    def perform(*args): return _tst.StringAction_perform(*args)
    def __disown__(self):
        self.thisown = 0
        _tst.disown_StringAction(self)
        return weakref_proxy(self)

class StringActionPtr(StringAction):
    def __init__(self, this):
        _swig_setattr(self, StringAction, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, StringAction, 'thisown', 0)
        _swig_setattr(self, StringAction,self.__class__,StringAction)
_tst.StringAction_swigregister(StringActionPtr)

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
    def almost_perform(*args): return _tst._object_tst_almost_perform(*args)
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
    def almost(*args): return _tst.TST_almost(*args)

class TSTPtr(TST):
    def __init__(self, this):
        _swig_setattr(self, TST, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, TST, 'thisown', 0)
        _swig_setattr(self, TST,self.__class__,TST)
_tst.TST_swigregister(TSTPtr)


