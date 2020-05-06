# -*- coding: utf-8 -*-
"""
Splib library
-------------


.. autosummary::
    :toctree: _autosummary

    splib.animation


"""
import Sofa
import Sofa.Core
import inspect
import functools
import inspect
__all__=["animation"]

def pyType2sofaType(v):
    if isinstance(v, str):
        return "string"
    if isinstance(v, int):
        return "int"
    if isinstance(v, float):
        return "double"
    return None

def FunctionToPrefab(f):
        frameinfo = inspect.getframeinfo(inspect.currentframe().f_back)
        definedloc = (frameinfo.filename, frameinfo.lineno)

        def SofaPrefabF(*args, **kwargs):
            class NodeHook(object):
                    def __init__(self, node):
                        self.node = node

                    def addChild(self, name):
                        return selfnode

                    def __getattr__(self, name):
                        return getattr(self.node, name)

            class InnerSofaPrefab(Sofa.Core.Prefab):
                def __init__(self, name):
                    Sofa.Core.Prefab.__init__(self, name=name)

                def doReInit(self):
                    argnames = inspect.getfullargspec(f).args

                    kkwargs = {}
                    kkwargs[argnames[0]] = self
                    for name in argnames[1:]:
                        kkwargs[name] = self.__data__[name].value
                    f(**kkwargs)

            selfnode = InnerSofaPrefab(name="InnerSofaP")
            selfnode.setDefinitionSourceFileName(definedloc[0])
            selfnode.setDefinitionSourceFilePos(definedloc[1])

            ## retrieve meta data from decorated class:
            selfnode.addData(name="prefabname", value=f.__code__.co_name,
                         type="string", help="The prefab's name", group="Infos")
            selfnode.addData(name="docstring", value=f.__doc__,
                         type="string", help="This prefab's docstring", group="Infos")

            ## Now we retrieve all params passed to the prefab and add them as datafields:
            argnames = inspect.getfullargspec(f).args
            defaults = inspect.getfullargspec(f).defaults

            i = len(argnames) - len(defaults)
            for n in range(0, len(defaults)):
                if argnames[i+n] not in selfnode.__data__:
                    selfnode.addPrefabParameter(name=argnames[i+n], value=defaults[n], type=pyType2sofaType(defaults[n]), help="Undefined")

            selfnode.init()
            return selfnode
        return SofaPrefabF

class TypeConversionEngine(Sofa.Core.DataEngine):
    def __init__(self, *args, **kwargs):
        Sofa.Core.DataEngine(self, *args, **kwargs)
        self.f = kwargs["lambda"]
        self.addInput(self.src)
        self.addData(name="dst", type=kwargs["dataType"])
        self.addOuptut(self.dst)
        self.mode = kwargs["mode"]


    def aggregateToContainer(self):
        # reset dest
        self.dst = np.zeros(shape=self.dst.shape)
        if self.mode == "append": # guarantee the destination is large enough to accomodate inputs
            self.dst.resize(len(self.inputs))
        
        with self.dst.writeable() as arr:
            for i in range(0,len(self.inputs)):
                if self.mode == "append":
                    arr[i] = self.f(self.inputs[i])
                elif self.mode == "overwrite":
                    arr[:] = self.f(self.src)
                # basic operators are applied on numpy arrays. operations are thus element-wise:
                elif self.mode == "add":
                    arr[:] += self.f(self.src)
                elif self.mode == "subtract":
                    arr[:] -= self.f(self.src)
                elif self.mode == "multiply":
                    arr[:] *= self.f(self.src)
                elif self.mode == "divide":
                    arr[:] /= self.f(self.src)


    def aggregateToScalar(self):
        # reset dest
        self.dst = 0
        for i in range(0,len(self.inputs)):
            if self.mode == "overwrite":
                self.dst = self.f(self.src)
            elif self.mode == "add":
                self.dst = self.dst.value + self.f(self.src)
            elif self.mode == "subtract":
                self.dst = self.dst.value - self.f(self.src)
            elif self.mode == "multiply":
                self.dst = self.dst.value * self.f(self.src)
            elif self.mode == "divide":
                self.dst = self.dst.value / self.f(self.src)


    def update(self):
        if type(self.dst) is Sofa.Core.DataContainer:
            self.aggregateToContainer()
        elif type(self.dst.value) is str and type(self.dst) not Sofa.Core.DataString:
            # dest types that do not have a proper AbstractTypeInfo implementation
            # (and thus default to strings) cannot handle basic operators (ex: BoundingBox).
            # Therefore, if more than 1 input is passed, we systematically all inputs but the last:
            self.dst = self.f(self.inputs[-1])
        else:
            self.aggregateToScalar()

