# encoding: utf-8
#!/usr/bin/python3
import sys
import os

if "SOFA_ROOT" not in os.environ:
        print("WARNING: missing SOFA_ROOT in you environment variable. ") 
        sys.exit(-1)

import Sofa.Core
import Sofa.Simulation
import SofaRuntime

## Register all the common component in the factory. 
SofaRuntime.importPlugin("SofaAllCommonComponents")

class MyController(Sofa.Core.Controller):
        def __init__(self, *args, **kwargs):
                Sofa.Core.Controller.__init__(self,*args, **kwargs)
                print("INITED")
                
        def onEvent(self, event):
                print("Event: "+event)
               
                
root = Sofa.Core.Node("myroot")
root.addChild("child1")
root.addObject(MyController(name="MyController"))
Sofa.Simulation.print(root)
Sofa.Simulation.init(root)
for i in range(0, 10):
        print("step: "+str(i))
        Sofa.Simulation.animate(root, 0.1)
        
        
