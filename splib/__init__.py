# -*- coding: utf-8 -*-
"""
Splib library
-------------


.. autosummary::
    :toctree: _autosummary

    splib.animation


"""
import Sofa.Core
import inspect
import functools

__all__=["animation"]


class SofaPrefab(object):
    """This decorator is used for a seamless integration of the Sofa.Core.Node interface with the Python classes:
    Example of use:
    -----------------

    @SofaPrefab
    class MyPrefab(Sofa.Core.Node):
        def __init__(self, name, coucou=3, plop=42, kikoo=4):
            print (self.getName())
            self.addChild('plop')


    This decorator performs multiple things for the user:
        - It calls super() on the decorated class to initialize the Sofa.Core.Node base class
        - It retrieves meta data from the script (such as the prefab's source code, docstring, definition line etc.) and stores it as datafields
        - It stores the constructor's parameters (args & kwargs) as datafields in the node under the "Prefab" group
    """
    
    def __init__(self, prefab):
        self.o = prefab
        ## Reveal meta data from the decorated class to the decorator
        functools.update_wrapper(self, prefab)

    def __call__(self, *args, **kwargs):
        ## Instantiate decorated class without calling __init__
        prefab = self.o.__new__(self.o, *args, **kwargs)
        ## initialize Sofa.Core.Node on the decorated class
        Sofa.Core.Node.__init__(prefab, *args, **kwargs)
        ## Call the initializer of the decorated class
        prefab.__init__(*args, **kwargs)
        
        # ## retrieve meta data from decorated class:
        prefab.addData(name="modulename", value=inspect.getmodulename(self.o.__init__.__code__.co_filename),
                       type="string", help="The module containing this prefab", group="Infos")
        prefab.addData(name="prefabname", value=self.o.__init__.__code__.co_name,
                       type="string", help="The prefab's name", group="Infos")
        prefab.addData(name="modulepath", value=self.o.__init__.__code__.co_filename,
                       type="string", help="This prefab's module path", group="Infos")
        prefab.addData(name="lineno", value=self.o.__init__.__code__.co_firstlineno, type="int",
                       help="First line number for this prefab's source code", group="Infos")
        prefab.addData(name="sourcecode", value=inspect.getsource(self.o),
                       type="string", help="The source code of this prefab", group="Infos")
        prefab.addData(name="docstring", value=self.o.__doc__,
                       type="string", help="This prefab's docstring", group="Infos")

        ## Now we retrieve all params passed to the prefab and add them as datafields:
        argnames = inspect.getfullargspec(prefab.__init__).args
        defaults = inspect.getfullargspec(prefab.__init__).defaults
        for i in range(0, len(argnames) - len(defaults) - 1):
            defaults = ("",) + defaults

        i = 0
        for n in argnames:
            hasField = False
            if n == "self": continue
            for f in prefab.getDataFields():
                if n == f.getName():
                    hasField = True
                    break
            if hasField:
                i+=1
                continue
            print(n + " >>> " + str(args[i] if i < len(args) else defaults[i]))
            prefab.addData(name=n, value=str(args[i] if i < len(args) else defaults[i]), type="string", group="Prefab")
            i+=1

        ## TODO(@bmarques): Retrieve kwargs the same way & handle name conflicts, if any
            
        ## Return the constructed object:
        return prefab

