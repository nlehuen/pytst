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


class int_tst(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, int_tst, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, int_tst, name)
    def __repr__(self):
        return "<C tst<(int)> instance at %s>" % (self.this,)
    def __init__(self, *args):
        _swig_setattr(self, int_tst, 'this', _tst.new_int_tst(*args))
        _swig_setattr(self, int_tst, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_int_tst):
        try:
            if self.thisown: destroy(self)
        except: pass
    def adjust(*args): return _tst.int_tst_adjust(*args)
    def get(*args): return _tst.int_tst_get(*args)
    def put(*args): return _tst.int_tst_put(*args)
    def debug(*args): return _tst.int_tst_debug(*args)
    def bytes_allocated(*args): return _tst.int_tst_bytes_allocated(*args)

class int_tstPtr(int_tst):
    def __init__(self, this):
        _swig_setattr(self, int_tst, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, int_tst, 'thisown', 0)
        _swig_setattr(self, int_tst,self.__class__,int_tst)
_tst.int_tst_swigregister(int_tstPtr)

class string_tst(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, string_tst, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, string_tst, name)
    def __repr__(self):
        return "<C tst<(p.char)> instance at %s>" % (self.this,)
    def __init__(self, *args):
        _swig_setattr(self, string_tst, 'this', _tst.new_string_tst(*args))
        _swig_setattr(self, string_tst, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_string_tst):
        try:
            if self.thisown: destroy(self)
        except: pass
    def adjust(*args): return _tst.string_tst_adjust(*args)
    def get(*args): return _tst.string_tst_get(*args)
    def put(*args): return _tst.string_tst_put(*args)
    def debug(*args): return _tst.string_tst_debug(*args)
    def bytes_allocated(*args): return _tst.string_tst_bytes_allocated(*args)

class string_tstPtr(string_tst):
    def __init__(self, this):
        _swig_setattr(self, string_tst, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, string_tst, 'thisown', 0)
        _swig_setattr(self, string_tst,self.__class__,string_tst)
_tst.string_tst_swigregister(string_tstPtr)

class object_tst(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, object_tst, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, object_tst, name)
    def __repr__(self):
        return "<C tst<(p.PyObject)> instance at %s>" % (self.this,)
    def __init__(self, *args):
        _swig_setattr(self, object_tst, 'this', _tst.new_object_tst(*args))
        _swig_setattr(self, object_tst, 'thisown', 1)
    def __del__(self, destroy=_tst.delete_object_tst):
        try:
            if self.thisown: destroy(self)
        except: pass
    def adjust(*args): return _tst.object_tst_adjust(*args)
    def get(*args): return _tst.object_tst_get(*args)
    def put(*args): return _tst.object_tst_put(*args)
    def debug(*args): return _tst.object_tst_debug(*args)
    def bytes_allocated(*args): return _tst.object_tst_bytes_allocated(*args)

class object_tstPtr(object_tst):
    def __init__(self, this):
        _swig_setattr(self, object_tst, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, object_tst, 'thisown', 0)
        _swig_setattr(self, object_tst,self.__class__,object_tst)
_tst.object_tst_swigregister(object_tstPtr)


