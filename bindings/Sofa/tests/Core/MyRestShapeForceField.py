import Sofa
import Sofa.Core
import numpy as np


class MyRestShapeSpringsForcefield(Sofa.Core.ForceField):
    def __init__(self, *args, **kwargs):
        Sofa.Core.ForceField.__init__(self, *args, **kwargs)

        if kwargs.get("stiffness") is not None:
            self.addData(name="stiffness", value=kwargs.get("stiffness"), type="double",
                         help="scalar value representing the stiffness between"
                              "the actual position and the rest shape position")
        self.addData(name="rest_pos", value=kwargs.get("rest_pos"))

    def init(self):
        try:
            hasattr(self, "indices")
        except:
            self.indices = range(0, len(self.rest_pos.value))

    def addForce(self, m, forces, pos, vel):
        print("addForce")
        k = self.stiffness.value
        for index in self.indices:
            forces[index] -= (pos[index] - self.rest_pos.value[index]) * k

    def addDForce(self, m, dforce, dx):
        print("addDForce")
        # kFactorIncludingRayleighDamping -> assuming rayleighStiffness of 0.0
        # kF = mparams['kFactor'] + mparams['bFactor'] * self.rayleighStiffness.value
        k = self.stiffness.value * m['kFactor']
        for index in self.indices:
            dforce[index] -= dx[index] * k

    def _addKToMatrix_selectivePoints(self, mparams, nNodes, nDofs):
        K = []

        # kFactorIncludingRayleighDamping => rayleighStiffness = 0.0
        kF = mparams['kFactor'] + mparams['bFactor'] * 0.0

        for index in self.indices:
            for n in range(0, nDofs):
                K.append([nDofs * index + n, nDofs * index +
                          n, -kF * self.stiffness.value])
        return np.asarray(K)

    def _addKToMatrix_plainMatrix(self, mparams, nNodes, nDofs):
        K = np.zeros((nNodes * nDofs, nNodes * nDofs, 1), dtype=float)
        # kFactorIncludingRayleighDamping => rayleighStiffness = 0.0
        kF = mparams['kFactor'] + mparams['bFactor'] * 0.0

        for idx in self.indices:
            for n in range(0, nDofs):
                K[nDofs * idx + n, nDofs * idx + n] = -kF * self.stiffness.value
        return K

    def addKToMatrix(self, mparams, nNodes, nDofs):
        print("addKToMatrix")
        # self.K = self._addKToMatrix_selectivePoints(mparams, nNodes, nDofs)
        return self._addKToMatrix_plainMatrix(mparams, nNodes, nDofs)
