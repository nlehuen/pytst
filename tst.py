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
    def get(*args): return _tst.IntegerTST_get(*args)
    def __getitem__(*args): return _tst.IntegerTST___getitem__(*args)
    def put(*args): return _tst.IntegerTST_put(*args)
    def __setitem__(*args): return _tst.IntegerTST___setitem__(*args)
    def debug(*args): return _tst.IntegerTST_debug(*args)
    def bytes_allocated(*args): return _tst.IntegerTST_bytes_allocated(*args)

class IntegerTSTPtr(IntegerTST):
    def __init__(self, this):
        _swig_setattr(self, IntegerTST, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, IntegerTST, 'thisown', 0)
        _swig_setattr(self, IntegerTST,self.__class__,IntegerTST)
_tst.IntegerTST_swigregister(IntegerTSTPtr)

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
    def get(*args): return _tst.StringTST_get(*args)
    def __getitem__(*args): return _tst.StringTST___getitem__(*args)
    def put(*args): return _tst.StringTST_put(*args)
    def __setitem__(*args): return _tst.StringTST___setitem__(*args)
    def debug(*args): return _tst.StringTST_debug(*args)
    def bytes_allocated(*args): return _tst.StringTST_bytes_allocated(*args)

class StringTSTPtr(StringTST):
    def __init__(self, this):
        _swig_setattr(self, StringTST, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, StringTST, 'thisown', 0)
        _swig_setattr(self, StringTST,self.__class__,StringTST)
_tst.StringTST_swigregister(StringTSTPtr)

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
    def get(*args): return _tst._object_tst_get(*args)
    def __getitem__(*args): return _tst._object_tst___getitem__(*args)
    def put(*args): return _tst._object_tst_put(*args)
    def __setitem__(*args): return _tst._object_tst___setitem__(*args)
    def debug(*args): return _tst._object_tst_debug(*args)
    def bytes_allocated(*args): return _tst._object_tst_bytes_allocated(*args)

class _object_tstPtr(_object_tst):
    def __init__(self, this):
        _swig_setattr(self, _object_tst, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, _object_tst, 'thisown', 0)
        _swig_setattr(self, _object_tst,self.__class__,_object_tst)
_tst._object_tst_swigregister(_object_tstPtr)

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
    def get(*args): return _tst.TST_get(*args)
    def __getitem__(*args): return _tst.TST___getitem__(*args)
    def put(*args): return _tst.TST_put(*args)
    def __setitem__(*args): return _tst.TST___setitem__(*args)
    def __del__(self, destroy=_tst.delete_TST):
        try:
            if self.thisown: destroy(self)
        except: pass

class TSTPtr(TST):
    def __init__(self, this):
        _swig_setattr(self, TST, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, TST, 'thisown', 0)
        _swig_setattr(self, TST,self.__class__,TST)
_tst.TST_swigregister(TSTPtr)


