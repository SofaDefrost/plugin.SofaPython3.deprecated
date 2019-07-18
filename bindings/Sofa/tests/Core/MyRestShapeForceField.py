import Sofa
import Sofa.Core
import numpy as np


class MyRestShapeSpringsForcefield(Sofa.Core.ForceField):
    def __init__(self, *args, **kwargs):
        Sofa.Core.ForceField.__init__(self, *args, **kwargs)

        print("stiffness")
        self.addData(name="stiffness", value=kwargs.get("stiffness"), type="double",
                     help="scalar value representing the stiffness between"
                          "the actual position and the rest shape position")
        print("rest_pos")
        self.addData(name="rest_pos", type="[Vec3]", value=kwargs.get("rest_pos"), default=[])
        print("indices")
        self.addData(name="indices", type="[int]", value=kwargs.get("indices"), default=[])
        print("great")

    def init(self):
        if not self.rest_pos.isSet():
            print("ERROR: rest_pos required")
        if not self.indices.isSet():
            print ("init rest_pos: "  + str(self.rest_pos.value))
            self.indices = list(range(0, len(self.rest_pos.value)))
            print ("init indices: "  + str(self.indices.value))
            print ("range: "  + str(list(range(0, len(self.rest_pos.value)))))
            print (self.indices.typeName())

    def addForce(self, m, forces, pos, vel):
        print("addForce")
        print ("rest_pos: "  + str(self.rest_pos.value))
        print ("indices: "  + str(self.indices.value))
        k = self.stiffness.value
        for index in self.indices.value:
            forces[index[0]] -= (pos[index[0]] - self.rest_pos.value[index[0]]) * k

    def addDForce(self, m, dforce, dx):
        if self.rest_pos.hasChanged():
            self.init()
        print("addDForce")
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
        # self.K = self._addKToMatrix_selectivePoints(mparams, nNodes, nDofs)
        return self._addKToMatrix_plainMatrix(mparams, nNodes, nDofs)
