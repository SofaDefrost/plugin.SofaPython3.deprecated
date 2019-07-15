# coding: utf8

import unittest
import Sofa
import Sofa.Core
import numpy as np
import SofaRuntime


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

    def addKToMatrix(self, nNodes, nDofs, mparams):
        print("addKToMatrix")
        self.K = np.zeros(nDofs * len(self.indices))

        # kFactorIncludingRayleighDamping
        kF = mparams['kFactor'] + mparams['bFactor'] * self.stiffness.value

        for Ki, index in zip(self.K, self.indices):
            for n in range(0, nDofs):
                Ki += (nDofs * index + n, nDofs * index +
                       n, -kF * self.stiffness.value)

        return self.K


def createIntegrationScheme(node, use_implicit_scheme):
    if use_implicit_scheme is True:
        node.addObject('EulerImplicitSolver', name='odeImplicitSolver',
                       rayleighStiffness='0.1', rayleighMass='0.1')
    else:
        node.addObject('EulerExplicitSolver', name='odeExplicitSolver')


def createSolver(node, use_iterative_solver):
    if use_iterative_solver == True:
        node.addObject('CGLinearSolver', name='linearSolver',
                       iterations=30, tolerance=1.e-9, threshold=1.e-9)
    else:
        node.addObject('SparseLDLSolver', name='ldlSolver')


def createDragon(node, node_name, use_implicit_scheme, use_iterative_solver):
    dragon = node.addChild(node_name)
    createIntegrationScheme(dragon, use_implicit_scheme)
    createSolver(dragon, use_iterative_solver)
    dragon.addObject('SparseGridTopology', n=[
                     10, 5, 10], fileTopology="mesh/dragon.obj")
    dofs = dragon.addObject(
        'MechanicalObject', name="DOFs")
    dragon.addObject('UniformMass', totalMass=1)

    myRSSFF = MyRestShapeSpringsForcefield(name="Springs",
                                           stiffness=50,
                                           mstate=dofs, rest_pos=dofs.rest_position)
    dragon.addObject(myRSSFF)

    visu = dragon.addChild("Visu")
    vm = visu.addObject('OglModel', fileMesh="mesh/dragon.obj",
                        color=[1.0, 0.5, 1.0, 1.0])
    visu.addObject('BarycentricMapping',
                   input=dofs.getLink(), output=vm.getLink())

    collision = dragon.addChild("Collis")
    collision.addObject('MeshObjLoader', name="loader",
                        filename="mesh/dragon.obj")
    collision.addObject('Mesh', src="@loader")
    collision.addObject('MechanicalObject', src="@loader")
    collision.addObject('TriangleCollisionModel', group="1")
    collision.addObject('LineCollisionModel', group="1")
    collision.addObject('PointCollisionModel', group="1")
    collision.addObject('BarycentricMapping', input="@..", output="@.")


def createCube(node, node_name, use_implicit_scheme, use_iterative_solver):
    cube = node.addChild(node_name)
    createIntegrationScheme(cube, use_implicit_scheme)
    createSolver(cube, use_iterative_solver)
    cube.addObject('SparseGridTopology', n=[
                   10, 5, 10], fileTopology="mesh/smCube27.obj")
    dofs = cube.addObject('MechanicalObject', name="DOFs", dy=20)
    cube.addObject('UniformMass', totalMass=1.0)

    myRSSFF = MyRestShapeSpringsForcefield(name="Springs",
                                           stiffness=50,
                                           mstate=dofs, rest_pos=dofs.rest_position)
    cube.addObject(myRSSFF)

    visu = cube.addChild("Visu")
    vm = visu.addObject(
        'OglModel', fileMesh="mesh/smCube27.obj", color=[0.5, 1.0, 0.5, 1.0])
    visu.addObject('BarycentricMapping',
                   input=dofs.getLink(), output=vm.getLink())

    collision = cube.addChild("Collis")
    collision.addObject('MeshObjLoader', name="loader",
                        filename="mesh/smCube27.obj", triangulate=True)
    collision.addObject('Mesh', src="@loader")
    collision.addObject('MechanicalObject', src="@loader")
    collision.addObject('TriangleCollisionModel', group="1")
    collision.addObject('LineCollisionModel', group="1")
    collision.addObject('PointCollisionModel', group="1")
    collision.addObject('BarycentricMapping', input="@..", output="@.")


def rssffScene(use_implicit_scheme=True, use_iterative_solver=True):
    SofaRuntime.importPlugin("SofaAllCommonComponents")
    SofaRuntime.importPlugin("SofaSparseSolver")
    node = Sofa.Core.Node("root")
    node.gravity = [0, -10, 0]
    createDragon(node, "Dragon", use_implicit_scheme, use_iterative_solver)
    createCube(node, "Cube", use_implicit_scheme, use_iterative_solver)
    return node


class Test(unittest.TestCase):

    def test_0_explicit(self):
        rssffScene(use_implicit_scheme=False, use_iterative_solver=False)

        # do some steps here
        return

    def test_1_implicit_iterative(self):
        rssffScene(use_implicit_scheme=True, use_iterative_solver=True)

        # do some steps here
        return

    def test_2_implicit_direct(self):
        rssffScene(use_implicit_scheme=True, use_iterative_solver=False)

        # do some steps here
        return


def getTestsName():
    suite = unittest.TestLoader().loadTestsFromTestCase(Test)
    return [test.id().split(".")[2] for test in suite]


def runTests():
    import sys
    suite = None
    if(len(sys.argv) == 1):
        suite = unittest.TestLoader().loadTestsFromTestCase(Test)
    else:
        suite = unittest.TestSuite()
        suite.addTest(Test(sys.argv[1]))
    return unittest.TextTestRunner(verbosity=1).run(suite).wasSuccessful()


def createScene(rootNode):
    rootNode.addChild(Test().test_animation())
