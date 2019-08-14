# This Python file uses the following encoding: utf-8

import Sofa.Core
import Sofa.Simulation
import unittest

def DumpNode(node):
    print("+ " + str(node.name.value))
    for o in node.objects:
        print("  - " + str(o.name.value))
    return True


class MyVisitor(Sofa.Core.Visitor):
    def __init__(self):
        Sofa.Core.Visitor.__init__(self)

    def processNodeTopDown(self, node):
        DumpNode(node)
        return True

    def processNodeBottomUp(self, node):
        pass

    def getCategoryName(self):
        return "plop"

class Test(unittest.TestCase):
    def test_visitor(self):
        node = Sofa.Core.Node("root")
        node.addObject("MechanicalObject" , name="AnObject1")
        node.addObject("MechanicalObject" , name="AnObject2")
        node.addObject("MechanicalObject" , name="AnObject3")
        node.addObject("MechanicalObject" , name="AnObject4")

        n = node.addChild('ANode1')
        n.addObject("MechanicalObject" , name="AnObject1")
        n.addObject("MechanicalObject" , name="AnObject2")
        n.addObject("MechanicalObject" , name="AnObject3")

        n = node.addChild('ANode2')
        n.addObject("MechanicalObject" , name="AnObject1")
        n.addObject("MechanicalObject" , name="AnObject2")
        n.addObject("MechanicalObject" , name="AnObject3")

        n = n.addChild('ANode')
        n.addObject("MechanicalObject" , name="AnObject1")
        n.addObject("MechanicalObject" , name="AnObject2")
        n.addObject("MechanicalObject" , name="AnObject3")

        Sofa.Simulation.init(node)

        # A good hack to create visitors without having to
        # create python classes (only supports processNodeTopDown)
        v = Sofa.Core.ExecuteFunctionVisitor(DumpNode)
        node.execute(v)

        # Works
        v2 = MyVisitor()

        # Works
        self.assertEqual(v2.getClassName(), "Sofa.Core.Visitor")
        self.assertEqual(v2.getCategoryName(), "plop")

        # Works from c++ too, trampoline does its job
        self.assertEqual(Sofa.Core._test_getCategoryName_test_(v2), "plop")


        v2.execute(node, False) # Does not work. WHYYYY?
        node.execute(v2) # Does not work. WHYYYY?
