import Sofa
import Sofa.Core
import numpy as np

#class DataContainerRestShapeSpringsForcefield(Sofa.Core.ForceField):
#    def __init__(self, *args, **kwargs):
#        Sofa.Core.ForceField.__init__(self, *args, **kwargs)
#        self.addData(name="stiffness", value=kwargs.get("stiffness"), type="double",
#                     help="scalar value representing the stiffness between"
#                          "the actual position and the rest shape position")
#        self.addData(name="rest_pos", type="[Vec3]", value=kwargs.get("rest_pos"), default=[])
#        self.addData(name="indices", type="[int]", value=kwargs.get("indices"), default=[])

#    def init(self):
#        if not self.rest_pos.isSet():
#            print("ERROR: rest_pos required")
#        if not self.indices.isSet():
#            self.indices = list(range(0, len(self.rest_pos.value)))
#            forces[index[0]] -= (pos[index[0]] - self.rest_pos.value[index[0]]) * k

#    def addForce(self, m, forces, pos, vel):
#        k = self.stiffness.value
#        for index in self.indices.value:
#            forces[index[0]] -= (pos[index[0]] - self.rest_pos.value[index[0]]) * k

#    def addDForce(self, m, dforce, dx):
#        if self.rest_pos.hasChanged():
#            self.init()
#        # kFactorIncludingRayleighDamping -> assuming rayleighStiffness of 0.0
#        # kF = mparams['kFactor'] + mparams['bFactor'] * self.rayleighStiffness.value
#        k = self.stiffness.value * m['kFactor']
#        for index in self.indices.value:
#            dforce[index[0]] -= dx[index[0]] * k

#    def addKToMatrix(self, mparams, nNodes, nDofs):
#        K = []

#        # kFactorIncludingRayleighDamping => rayleighStiffness = 0.0
#        kF = mparams['kFactor'] + mparams['bFactor'] * 0.0

#        for index in self.indices.value:
#            for n in range(0, nDofs):
#                K.append([nDofs * index[0] + n, nDofs * index[0] +
#                          n, -kF * self.stiffness.value])
#        return np.asarray(K)


#class NumpyRestShapeSpringsForcefield(Sofa.Core.ForceField):
#    def __init__(self, *args, **kwargs):
#        Sofa.Core.ForceField.__init__(self, *args, **kwargs)
#        self.addData(name="stiffness", value=kwargs.get("stiffness"), type="double",
#                     help="scalar value representing the stiffness between"
#                          "the actual position and the rest shape position")
#        self.addData(name="rest_pos", type="[Vec3]", value=kwargs.get("rest_pos"), default=[])
#        self.addData(name="indices", type="[int]", value=kwargs.get("indices"), default=[])

#    def init(self):
#        if not self.rest_pos.isSet():
#            print("ERROR: rest_pos required")
#        if not self.indices.isSet():
#            self.indices = list(range(0, len(self.rest_pos.value)))

#    def addForce(self, m, forces, pos, vel):
#        k = self.stiffness.value
#        for index in self.indices.value:
#            forces[index[0]] -= (pos[index[0]] - self.rest_pos.value[index[0]]) * k

#    def addDForce(self, m, dforce, dx):
#        if self.rest_pos.hasChanged():
#            self.init()
#        # kFactorIncludingRayleighDamping -> assuming rayleighStiffness of 0.0
#        # kF = mparams['kFactor'] + mparams['bFactor'] * self.rayleighStiffness.value
#        k = self.stiffness.value * m['kFactor']
#        for index in self.indices.value:
#            dforce[index[0]] -= dx[index[0]] * k

#    def _addKToMatrix_selectivePoints(self, mparams, nNodes, nDofs):
#        K = []

#        # kFactorIncludingRayleighDamping => rayleighStiffness = 0.0
#        kF = mparams['kFactor'] + mparams['bFactor'] * 0.0

#        for index in self.indices.value:
#            for n in range(0, nDofs):
#                K.append([nDofs * index[0] + n, nDofs * index[0] +
#                          n, -kF * self.stiffness.value])
#        return np.asarray(K)

#    def _addKToMatrix_plainMatrix(self, mparams, nNodes, nDofs):
#        K = np.zeros((nNodes * nDofs, nNodes * nDofs, 1), dtype=float)
#        # kFactorIncludingRayleighDamping => rayleighStiffness = 0.0
#        kF = mparams['kFactor'] + mparams['bFactor'] * 0.0

#        for idx in self.indices.value:
#            for n in range(0, nDofs):
#                K[nDofs * idx[0] + n, nDofs * idx[0] + n] = -kF * self.stiffness.value
#        return K

#    def addKToMatrix(self, mparams, nNodes, nDofs):
#        if self.rest_pos.hasChanged():
#            self.init()
#        print("addKToMatrix")
#        # self.K = self._addKToMatrix_selectivePoints(mparams, nNodes, nDofs)
#        return self._addKToMatrix_plainMatrix(mparams, nNodes, nDofs)


#class VectorizedRestShapeSpringsForcefield(Sofa.Core.ForceField):
#    def __init__(self, *args, **kwargs):
#        Sofa.Core.ForceField.__init__(self, *args, **kwargs)
#        self.addData(name="stiffness", value=kwargs.get("stiffness"), type="double",
#                     help="scalar value representing the stiffness between"
#                          "the actual position and the rest shape position")
#        self.addData(name="rest_pos", type="[Vec3]", value=kwargs.get("rest_pos"), default=[])
#        self.addData(name="indices", type="[int]", value=kwargs.get("indices"), default=[])

#    def init(self):
#        if not self.rest_pos.isSet():
#            print("ERROR: rest_pos required")
#        if not self.indices.isSet():
#            self.indices = list(range(0, len(self.rest_pos.value)))

#    def addForce(self, m, forces, pos, vel):
#        k = self.stiffness.value
#        for index in self.indices.value:
#            forces[index[0]] -= (pos[index[0]] - self.rest_pos.value[index[0]]) * k

#    def addDForce(self, m, dforce, dx):
#        if self.rest_pos.hasChanged():
#            self.init()
#        # kFactorIncludingRayleighDamping -> assuming rayleighStiffness of 0.0
#        # kF = mparams['kFactor'] + mparams['bFactor'] * self.rayleighStiffness.value
#        k = self.stiffness.value * m['kFactor']
#        for index in self.indices.value:
#            dforce[index[0]] -= dx[index[0]] * k

#    def _addKToMatrix_selectivePoints(self, mparams, nNodes, nDofs):
#        K = []

#        # kFactorIncludingRayleighDamping => rayleighStiffness = 0.0
#        kF = mparams['kFactor'] + mparams['bFactor'] * 0.0

#        for index in self.indices.value:
#            for n in range(0, nDofs):
#                K.append([nDofs * index[0] + n, nDofs * index[0] +
#                          n, -kF * self.stiffness.value])
#        return np.asarray(K)

#    def _addKToMatrix_plainMatrix(self, mparams, nNodes, nDofs):
#        K = np.zeros((nNodes * nDofs, nNodes * nDofs, 1), dtype=float)
#        # kFactorIncludingRayleighDamping => rayleighStiffness = 0.0
#        kF = mparams['kFactor'] + mparams['bFactor'] * 0.0

#        for idx in self.indices.value:
#            for n in range(0, nDofs):
#                K[nDofs * idx[0] + n, nDofs * idx[0] + n] = -kF * self.stiffness.value
#        return K

#    def addKToMatrix(self, mparams, nNodes, nDofs):
#        if self.rest_pos.hasChanged():
#            self.init()
#        print("addKToMatrix")
#        # self.K = self._addKToMatrix_selectivePoints(mparams, nNodes, nDofs)
#        return self._addKToMatrix_plainMatrix(mparams, nNodes, nDofs)


class NaiveRestShapeSpringsForcefield(Sofa.Core.ForceField):
    def __init__(self, *args, **kwargs):
        Sofa.Core.ForceField.__init__(self, *args, **kwargs)
        self.addData(name="stiffness", value=kwargs.get("stiffness"), type="double",
                     help="scalar value representing the stiffness between"
                          "the actual position and the rest shape position")
        self.addData(name="rest_pos", type="[Vec3]", value=kwargs.get("rest_pos"), default=[])
        self.addData(name="indices", type="[int]", value=kwargs.get("indices"), default=[])

    def init(self):
        if not self.rest_pos.isSet():
            print("ERROR: rest_pos required")
        if not self.indices.isSet():
            print ("Indices not set.")
            indices = [ [i] for i in list(range(len(self.rest_pos.value)))]
            self.indices = [ [i] for i in list(range(len(self.rest_pos.value)))]
            print (        [ [i] for i in list(range(len(self.rest_pos.value)))])
            print ("setting to " + str(self.indices.value))

    def addForce(self, m, forces, pos, vel):
        if self.rest_pos.hasChanged():
            self.init()
        print('addForce')
        k = self.stiffness.value
        for index in self.indices.value:
            forces[index[0]] -= (pos[index[0]] - self.rest_pos.value[index[0]]) * k


    def addDForce(self, m, dforce, dx):
        print('addDForce')
        # kFactorIncludingRayleighDamping -> assuming rayleighStiffness of 0.0
        # kF = mparams['kFactor'] + mparams['bFactor'] * self.rayleighStiffness.value
        k = self.stiffness.value * m['kFactor']
        for index in self.indices.value:
            dforce[index[0]] -= dx[index[0]] * k

    def _addKToMatrix_selectivePoints(self, mparams, nNodes, nDofs):
        K = []

        # kFactorIncludingRayleighDamping => rayleighStiffness = 0.0
        kF = mparams['kFactor'] + mparams['bFactor'] * 0.0

        for index in self.indices.value:
            for n in range(0, nDofs):
                K.append([nDofs * index[0] + n, nDofs * index[0] +
                          n, -kF * self.stiffness.value])
        return np.asarray(K)

    def _addKToMatrix_plainMatrix(self, mparams, nNodes, nDofs):
        K = np.zeros((nNodes * nDofs, nNodes * nDofs, 1), dtype=float)
        # kFactorIncludingRayleighDamping => rayleighStiffness = 0.0
        kF = mparams['kFactor'] + mparams['bFactor'] * 0.0

        for idx in self.indices.value:
            for n in range(0, nDofs):
                K[nDofs * idx[0] + n, nDofs * idx[0] + n] = -kF * self.stiffness.value
        return K

    def addKToMatrix(self, mparams, nNodes, nDofs):
        if self.rest_pos.hasChanged():
            self.init()
        print("addKToMatrix")
        return self._addKToMatrix_selectivePoints(mparams, nNodes, nDofs)
        #return self._addKToMatrix_plainMatrix(mparams, nNodes, nDofs)




def MyRestShapeSpringsForcefield(*args, **kwargs):
    for key, value in kwargs.items():
        if key == "implementation":
            if value == "naive":
                return NaiveRestShapeSpringsForcefield(args, kwargs)
            if value == "vectorized":
                return VectorizedRestShapeSpringsForcefield(args, kwargs)
            if value == "numpy":
                return NumpyRestShapeSpringsForcefield(args, kwargs)
            if value == "DataContainer":
                return DataContainerRestShapeSpringsForcefield(args, kwargs)
