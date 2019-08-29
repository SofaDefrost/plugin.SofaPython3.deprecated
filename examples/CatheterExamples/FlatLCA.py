# -*- coding: utf-8 -*-
"""
Created on Tue Mar 19 14:35:00 2019

@author: PSC
"""

# __name__ = '.'.join(__name__.split('/'))
# __package__ = '.'.join('.'.join(__name__.split('/')).split('.')[:-1])

# print('name : ', __name__)
# print('package : ', __package__)


import Sofa

# from beamadapter.parts import createGuide, createInstrumentsCombined, createGeometry


def createScene(rootNode):

    rootNode.addObject('RequiredPlugin', pluginName='BeamAdapter')  
    
    rootNode.addObject('VisualStyle', displayFlags='showVisualModels showBehaviorModels showCollisionModels hideMappings hideForceFields')
    rootNode.addObject('FreeMotionAnimationLoop')
    rootNode.addObject('LCPConstraintSolver', mu=0.1, tolerance=1e-5, maxIt=1000, build_lcp=False)
    rootNode.addObject('CollisionPipeline', draw=False, depth=6, verbose=False)
    rootNode.addObject('BruteForceDetection', name='N2')
    rootNode.addObject('LocalMinDistance', contactDistance=0.1, alarmDistance=0.3, name='localmindistance', angleCone=0.02)
    rootNode.addObject('CollisionResponse', name='Response', response='FrictionContact')
    rootNode.addObject('CollisionGroup', name='Group')
    
    # topoLines_guide = createGuide(rootNode, 'guide', straightLength=980.0, length=1000.0, 
    #             youngModulus=20000, numEdges=200, spireDiameter=25, 
    #             numEdgesCollis=[50,10], spireHeight=0.0, densityOfBeams=[30,5], 
    #             youngModulusExtremity=1000)
    topoLines_guide = rootNode.addChild('topoLines_guide')
    topoLines_guide.addObject('WireRestShape', name='guideRestShape', 
                             straightLength=980.0, length=1000.0, 
                             numEdges=200, youngModulus=20000, 
                             spireDiameter=25, numEdgesCollis=[50, 10], 
                             printLog=True, template='Rigid3d', spireHeight=0.0, 
                             densityOfBeams=[30, 5], youngModulusExtremity=1000)
    topoLines_guide.addObject('MechanicalObject', name='dofTopo2', template='Rigid3d')
    topoLines_guide.addObject('EdgeSetTopologyContainer', name='meshLinesGuide')
    topoLines_guide.addObject('EdgeSetTopologyModifier', name='Modifier')
    topoLines_guide.addObject('EdgeSetTopologyAlgorithms', name='TopoAlgo', template='Vec3d')
    topoLines_guide.addObject('EdgeSetGeometryAlgorithms', name='GeomAlgo', template='Rigid3d')

    # instrumentsCombined = createInstrumentsCombined(rootNode)
    InstrumentCombined = rootNode.addChild('InstrumentCombined')
    InstrumentCombined.addObject('EulerImplicit', rayleighStiffness=0.2, printLog=False, rayleighMass=0.1)
    InstrumentCombined.addObject('BTDLinearSolver', verification=False, subpartSolve=False, verbose=False)
    InstrumentCombined.addObject('RegularGrid', name='meshLinesCombined', zmax=1, zmin=1, nx=60, ny=1, nz=1, 
                                    xmax=1.0, xmin=0.0, ymin=0, ymax=0)
    InstrumentCombined.addObject('MechanicalObject', showIndices=False, name='DOFs', template='Rigid3d', ry=-90)
    InstrumentCombined.addObject('WireBeamInterpolation', WireRestShape='@../topoLines_guide/guideRestShape', 
                                    radius=0.15, printLog=True, name='Interpolguide')
    InstrumentCombined.addObject('AdaptiveBeamForceFieldAndMass', massDensity=0.00000155, 
                                    name='guideForceField', interpolation='@Interpolguide')

    InstrumentCombined.addObject('InterventionalRadiologyController', xtip=[1, 0, 0], name='m_ircontroller', 
                                    instruments=['Interpolguide'], step=0.5, printLog=True, 
                                    listening=True, template='Rigid3d', startingPos=[0, 0, 0, 1, 0, 0, 0], 
                                    rotationInstrument=[0, 0, 0], speed=0, controlledInstrument=0)
    InstrumentCombined.addObject('LinearSolverConstraintCorrection', wire_optimization='true', printLog=False)
    InstrumentCombined.addObject('FixedConstraint', indices=0, name='FixedConstraint')
    InstrumentCombined.addObject('RestShapeSpringsForceField', points='@m_ircontroller.indexFirstNode', 
                                    angularStiffness=1e8, stiffness=1e8)

    # Collision model
    Collis = InstrumentCombined.addChild('Collis')
    # Collis.activated = True
    Collis.addObject('EdgeSetTopologyContainer', name='collisEdgeSet')
    Collis.addObject('EdgeSetTopologyModifier', name='colliseEdgeModifier')
    Collis.addObject('MechanicalObject', name='CollisionDOFs')
    Collis.addObject('MultiAdaptiveBeamMapping', controller='../m_ircontroller', 
                        useCurvAbs=True, printLog=False, name='collisMap')
    Collis.addObject('Line', proximity=0.0, group=1)
    Collis.addObject('Point', proximity=0.0, group=1)

    # Visualization Guide
    VisuGuide = InstrumentCombined.addChild('VisuGuide')
    # VisuGuide.activated = 'true'
    VisuGuide.addObject('MechanicalObject', name='Quads')
    VisuGuide.addObject('QuadSetTopologyContainer', name='ContainerGuide')
    VisuGuide.addObject('QuadSetTopologyModifier', name='Modifier')
    VisuGuide.addObject('QuadSetTopologyAlgorithms', name='TopoAlgo', template='Vec3d')
    VisuGuide.addObject('QuadSetGeometryAlgorithms', name='GeomAlgo', template='Vec3d')
    VisuGuide.addObject('Edge2QuadTopologicalMapping', radius='1', listening='true', 
                           input='@../../topoLines_guide/meshLinesGuide', 
                           nbPointsOnEachCircle='10', flipNormals='true', output='@ContainerGuide')
    VisuGuide.addObject('AdaptiveBeamMapping', interpolation='@../InterpolGuide', 
                           name='visuMapGuide', output='@Quads', isMechanical=False, 
                           input='@../DOFs', useCurvAbs=True, printLog=True)

    # Ogl model
    VisuOgl = VisuGuide.addChild('VisuOgl')
    VisuOgl.addObject('OglModel', color=[0.2, 0.2, 0.8], quads='@../ContainerGuide.quads', 
                         material='texture Ambient 1 0.2 0.2 0.2 0.0 Diffuse 1 1.0 1.0 1.0 1.0 Specular 1 1.0 1.0 1.0 1.0 Emissive 0 0.15 0.05 0.05 0.0 Shininess 1 20', name='Visual')
    VisuOgl.addObject('IdentityMapping', input='@../Quads', output='@Visual')
    
    # vessels = createGeometry(rootNode, 'mesh/FlatLCA1_5.stl', scale=5, rotation=[8.0, 5.0, 0.0], VISUAL = False)
    Geometry = rootNode.addChild('Vessels')
    Geometry.addObject('MeshSTLLoader', filename='mesh/FlatLCA1_5.stl', flipNormals=True, triangulate=True, name='meshLoader', scale=5, rotation=[8.0, 5.0, 0.0])
    Geometry.addObject('Mesh', position='@meshLoader.position', triangles='@meshLoader.triangles')
    Geometry.addObject('MechanicalObject', name='DOFs1', scale=1, rotation=[8.0, 5.0, 0.0])
    Geometry.addObject('Triangle', moving=False, simulated=False)
    Geometry.addObject('Line', moving=False, simulated=False)
    Geometry.addObject('Point', moving=False, simulated=False)
    
