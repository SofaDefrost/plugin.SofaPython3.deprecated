# encoding: utf-8
#!/usr/bin/python3
import sys
import os

path = os.path.dirname(os.path.realpath(__file__))

if "SOFA_ROOT" not in os.environ:
        print("WARNING: missing SOFA_ROOT in you environment variable. ") 
        sys.exit(-1)

sys.path.append(os.path.abspath("./bindings/Sofa/package"))
sys.path.append(os.path.abspath("./bindings/SofaRuntime/package"))
sys.path.append(os.path.abspath("./bindings/SofaTypes/package"))

import Sofa
import SofaRuntime

## Register all the common component in the factory. 
SofaRuntime.importPlugin("SofaAllCommonComponents")
               
def createScene(root):
	
	# print(root.gravity.value)

	root.addObject("CGLinearSolver")
	root.addObject('LCPConstraintSolver')
	root.addObject("FreeMotionAnimationLoop")
	root.addObject('EulerImplicitSolver', name='odesolver', firstOrder=0, rayleighMass=0.1, rayleighStiffness=0.1)


	Cube = root.addChild("Cube")

	Cube.addObject("MeshSTLLoader", name= "loader", filename=path+"/mesh/cube.stl")
	print("loaded :", Cube.loader.filename.value)

	Cube.addObject("MechanicalObject", name="CubeDOFs", template='Vec3d', position=Cube.loader.position.toList(), showObject=True, showObjectScale=5)
	Cube.addObject("UniformMass", vertexMass=1)

	Sofa.Simulation.init(root)
	Sofa.Simulation.print(root)


	for i in range(0, 10):
	        print("step: ", i)
	        Sofa.Simulation.animate(root, 0.1)
	        print("Cube position :", Cube.CubeDOFs.position.array()[0])
        
if __name__ == '__main__':
	root = Sofa.Node("myroot")
	createScene(root)

