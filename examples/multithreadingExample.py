import threading

import Sofa
import SofaRuntime


import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation






## Register all the common component in the factory. 
SofaRuntime.importPlugin("SofaAllCommonComponents")
               
def createScene(root):
	
	print("coucou")
	# time.sleep(1)
	print(root.gravity.value)

	# root.addObject("CGLinearSolver")
	# root.addObject('LCPConstraintSolver')
	# root.addObject("FreeMotionAnimationLoop")
	# root.addObject('EulerImplicitSolver', name='odesolver', firstOrder=0, rayleighMass=0.1, rayleighStiffness=0.1)


	# Cube = root.addChild("Cube")

	# Cube.addObject("MeshSTLLoader", name= "loader", filename=path+"/mesh/cube.stl")
	# print("loaded :", Cube.loader.filename.value)

	# Cube.addObject("MechanicalObject", name="CubeDOFs", template='Vec3d', position=Cube.loader.position.toList(), showObject=True, showObjectScale=5)
	# Cube.addObject("UniformMass", vertexMass=1)

def update_line(num, data, line):
    line.set_data(data[..., :num])
    return line,

        
class Simulator:
	def __init__(self, rootNode):
		self.rootNode = Sofa.Node(rootNode)

	def run(self):
		print("simulation ", self.rootNode.name.value, " has started")
		createScene(self.rootNode)
		# print("createscene")
		Sofa.Simulation.init(self.rootNode)
		# print("init")
		# Sofa.Simulation.print(root)

		for i in range(0, 10):
			# print("step: ", i)
			Sofa.Simulation.animate(self.rootNode, 0.1)
			# print("Cube position :", Cube.CubeDOFs.position.array()[0])

		print("simulation ", self.rootNode.name.value, " has ended")
		return

# sims = ["delaBath", "Bramart", "Flantier"]

p =  []


for i in range(3):#len(sims)):
		simulation = Simulator(str(i) )# sims[i])
		print("creating new simulation ")
		SimThread = threading.Thread(target=simulation.run, args=())
		SimThread.start()
		p.append(SimThread)



# fig1 = plt.figure()

# data = np.random.rand(2, 25)
# l, = plt.plot([], [], 'r-')
# plt.xlim(0, 1)
# plt.ylim(0, 1)
# plt.xlabel('x')
# plt.title('test')
# line_ani = animation.FuncAnimation(fig1, update_line, 25, fargs=(data, l))

# for i in p:
# 		i.join()


# if __name__ == '__main__':
# 	root = Sofa.Node("myroot")
# 	createScene(root)