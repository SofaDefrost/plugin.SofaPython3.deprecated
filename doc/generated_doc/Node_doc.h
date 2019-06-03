/*
  This file contains docstrings for the Python bindings.
  Do not edit! These were automatically extracted by mkdoc.py
 */

#define __EXPAND(x)                                      x
#define __COUNT(_1, _2, _3, _4, _5, _6, _7, COUNT, ...)  COUNT
#define __VA_SIZE(...)                                   __EXPAND(__COUNT(__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1))
#define __CAT1(a, b)                                     a ## b
#define __CAT2(a, b)                                     __CAT1(a, b)
#define __DOC1(n1)                                       __doc_##n1
#define __DOC2(n1, n2)                                   __doc_##n1##_##n2
#define __DOC3(n1, n2, n3)                               __doc_##n1##_##n2##_##n3
#define __DOC4(n1, n2, n3, n4)                           __doc_##n1##_##n2##_##n3##_##n4
#define __DOC5(n1, n2, n3, n4, n5)                       __doc_##n1##_##n2##_##n3##_##n4##_##n5
#define __DOC6(n1, n2, n3, n4, n5, n6)                   __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6
#define __DOC7(n1, n2, n3, n4, n5, n6, n7)               __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7
#define DOC(...)                                         __EXPAND(__EXPAND(__CAT2(__DOC, __VA_SIZE(__VA_ARGS__)))(__VA_ARGS__))

#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif


static const char *__doc_sofa_core_visual_VisualParams = R"doc()doc";

static const char *__doc_sofa_simulation_Node =
R"doc(Implements the object (component) management of the core::Context.
Contains objects in lists and provides accessors. The other nodes are
not visible (unknown scene graph).

@author The SOFA team </www.sofa-framework.org>)doc";

static const char *__doc_sofa_simulation_Node_GetClass = R"doc()doc";

static const char *__doc_sofa_simulation_Node_HeaderFileLocation = R"doc()doc";

static const char *__doc_sofa_simulation_Node_Node = R"doc()doc";

static const char *__doc_sofa_simulation_Node_Sequence =
R"doc(Sequence class to hold a list of objects. Public access is only
readonly using an interface similar to std::vector
(size/[]/begin/end). UPDATE: it is now an alias for the Link pointer
container)doc";

static const char *__doc_sofa_simulation_Node_Sequence_Sequence = R"doc()doc";

static const char *__doc_sofa_simulation_Node_Sequence_operator_array = R"doc()doc";

static const char *__doc_sofa_simulation_Node_Sequence_swap =
R"doc(Swap two values in the list. Uses a const_cast to violate the read-
only iterators.)doc";

static const char *__doc_sofa_simulation_Node_Single =
R"doc(Class to hold 0-or-1 object. Public access is only readonly using an
interface similar to std::vector (size/[]/begin/end), plus an
automatic convertion to one pointer. UPDATE: it is now an alias for
the Link pointer container)doc";

static const char *__doc_sofa_simulation_Node_Single_Single = R"doc()doc";

static const char *__doc_sofa_simulation_Node_Single_operator_T0 = R"doc()doc";

static const char *__doc_sofa_simulation_Node_Single_operator_mul = R"doc()doc";

static const char *__doc_sofa_simulation_Node_Single_operator_sub = R"doc()doc";

static const char *__doc_sofa_simulation_Node_actionStack = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addAnimationLoop = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addBehaviorModel = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addChild = R"doc(Pure Virtual method from BaseNode Add a child node)doc";

static const char *__doc_sofa_simulation_Node_addCollisionModel = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addCollisionPipeline = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addConfigurationSetting = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addConstraintSet = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addConstraintSolver = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addContextObject = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addForceField = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addInteractionForceField = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addLinearSolver = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addListener = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addMapping = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addMass = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addMechanicalMapping = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addMechanicalState = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addMeshTopology = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addObject =
R"doc(Add an object and return this. Detect the implemented interfaces and
add the object to the corresponding lists.)doc";

static const char *__doc_sofa_simulation_Node_addOdeSolver = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addProjectiveConstraintSet = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addShader = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addState = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addTopology = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addTopologyObject = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addVisualLoop = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addVisualManager = R"doc()doc";

static const char *__doc_sofa_simulation_Node_addVisualModel = R"doc()doc";

static const char *__doc_sofa_simulation_Node_animationManager = R"doc()doc";

static const char *__doc_sofa_simulation_Node_behaviorModel = R"doc()doc";

static const char *__doc_sofa_simulation_Node_bwdInit = R"doc()doc";

static const char *__doc_sofa_simulation_Node_child = R"doc()doc";

static const char *__doc_sofa_simulation_Node_collisionModel = R"doc()doc";

static const char *__doc_sofa_simulation_Node_collisionPipeline = R"doc()doc";

static const char *__doc_sofa_simulation_Node_configurationSetting = R"doc()doc";

static const char *__doc_sofa_simulation_Node_constraintSet = R"doc()doc";

static const char *__doc_sofa_simulation_Node_constraintSolver = R"doc()doc";

static const char *__doc_sofa_simulation_Node_context = R"doc()doc";

static const char *__doc_sofa_simulation_Node_contextObject = R"doc()doc";

static const char *__doc_sofa_simulation_Node_create = R"doc()doc";

static const char *__doc_sofa_simulation_Node_create_2 = R"doc()doc";

static const char *__doc_sofa_simulation_Node_createChild = R"doc(Create, add, then return the new child of this Node)doc";

static const char *__doc_sofa_simulation_Node_debug = R"doc()doc";

static const char *__doc_sofa_simulation_Node_depend =
R"doc(Pairs representing component dependencies. First must be initialized
before second.)doc";

static const char *__doc_sofa_simulation_Node_doAddChild = R"doc(Delegate methods overridden in child classes Add a child node)doc";

static const char *__doc_sofa_simulation_Node_doAddObject = R"doc()doc";

static const char *__doc_sofa_simulation_Node_doExecuteVisitor = R"doc(Execute a recursive action starting from this node.)doc";

static const char *__doc_sofa_simulation_Node_doMoveChild = R"doc(Move a node from another node)doc";

static const char *__doc_sofa_simulation_Node_doMoveObject = R"doc()doc";

static const char *__doc_sofa_simulation_Node_doRemoveChild = R"doc(Remove a child node)doc";

static const char *__doc_sofa_simulation_Node_doRemoveObject = R"doc()doc";

static const char *__doc_sofa_simulation_Node_draw = R"doc(Draw the objects (using visual visitors))doc";

static const char *__doc_sofa_simulation_Node_execute = R"doc(Execute a recursive action starting from this node)doc";

static const char *__doc_sofa_simulation_Node_execute_2 = R"doc(Execute a recursive action starting from this node)doc";

static const char *__doc_sofa_simulation_Node_execute_3 = R"doc(Execute a recursive action starting from this node)doc";

static const char *__doc_sofa_simulation_Node_execute_4 = R"doc(Execute a recursive action starting from this node)doc";

static const char *__doc_sofa_simulation_Node_executeVisitor = R"doc(Execute a recursive action starting from this node)doc";

static const char *__doc_sofa_simulation_Node_findCommonParent =
R"doc(return the smallest common parent between this and node2 (returns NULL
if separated sub-graphes))doc";

static const char *__doc_sofa_simulation_Node_findLinkDestClass = R"doc()doc";

static const char *__doc_sofa_simulation_Node_forceField = R"doc()doc";

static const char *__doc_sofa_simulation_Node_getAnimationLoop = R"doc(@name Solvers and main algorithms @{)doc";

static const char *__doc_sofa_simulation_Node_getChild = R"doc(Find a child node given its name)doc";

static const char *__doc_sofa_simulation_Node_getChildren = R"doc(Get children nodes)doc";

static const char *__doc_sofa_simulation_Node_getClass = R"doc()doc";

static const char *__doc_sofa_simulation_Node_getCollisionPipeline = R"doc()doc";

static const char *__doc_sofa_simulation_Node_getContext = R"doc()doc";

static const char *__doc_sofa_simulation_Node_getContext_2 = R"doc()doc";

static const char *__doc_sofa_simulation_Node_getDebug = R"doc()doc";

static const char *__doc_sofa_simulation_Node_getHeaderFileLocation = R"doc()doc";

static const char *__doc_sofa_simulation_Node_getLocalMeshTopology =
R"doc(Mesh Topology that is local to this context (i.e. not within parent
contexts))doc";

static const char *__doc_sofa_simulation_Node_getMechanicalState = R"doc(Mechanical Degrees-of-Freedom)doc";

static const char *__doc_sofa_simulation_Node_getMeshTopology =
R"doc(Mesh Topology (unified interface for both static and dynamic
topologies))doc";

static const char *__doc_sofa_simulation_Node_getNodeInGraph = R"doc()doc";

static const char *__doc_sofa_simulation_Node_getNodeObject =
R"doc(Return an object of this node deriving from a given class, or NULL if
not found. Note that only the first object is returned.)doc";

static const char *__doc_sofa_simulation_Node_getNodeObject_2 = R"doc()doc";

static const char *__doc_sofa_simulation_Node_getNodeObjects = R"doc(List all objects of this node deriving from a given class)doc";

static const char *__doc_sofa_simulation_Node_getNodeObjects_2 = R"doc(Returns a list of object of type passed as a parameter.)doc";

static const char *__doc_sofa_simulation_Node_getNodeObjects_3 = R"doc(Returns a list of object of type passed as a parameter)doc";

static const char *__doc_sofa_simulation_Node_getNodeObjects_4 =
R"doc(Returns a list of object of type passed as a parameter. This function
is return object by copy but should be compatible with Return Value
Optimization so the copy should be removed by the compiler. Eg: for(
BaseObject* o : node->getNodeObjects() ) { ... } for( VisualModel* v :
node->getNodeObjects<VisualModel>() ) { ... })doc";

static const char *__doc_sofa_simulation_Node_getObject = R"doc(Find an object given its name)doc";

static const char *__doc_sofa_simulation_Node_getObject_2 =
R"doc(Generic object access, given a set of required tags, possibly
searching up or down from the current context

Note that the template wrapper method should generally be used to have
the correct return type,)doc";

static const char *__doc_sofa_simulation_Node_getObject_3 =
R"doc(Generic object access, possibly searching up or down from the current
context

Note that the template wrapper method should generally be used to have
the correct return type,)doc";

static const char *__doc_sofa_simulation_Node_getObject_4 =
R"doc(Generic object access, given a path from the current context

Note that the template wrapper method should generally be used to have
the correct return type,)doc";

static const char *__doc_sofa_simulation_Node_getObjects =
R"doc(Generic list of objects access, given a set of required tags, possibly
searching up or down from the current context

Note that the template wrapper method should generally be used to have
the correct return type,)doc";

static const char *__doc_sofa_simulation_Node_getObjects_2 =
R"doc(Generic list of objects access, possibly searching up or down from the
current context

Note that the template wrapper method should generally be used to have
the correct return type,)doc";

static const char *__doc_sofa_simulation_Node_getOdeSolver = R"doc()doc";

static const char *__doc_sofa_simulation_Node_getRootContext = R"doc()doc";

static const char *__doc_sofa_simulation_Node_getShader = R"doc(Shader)doc";

static const char *__doc_sofa_simulation_Node_getShader_2 = R"doc()doc";

static const char *__doc_sofa_simulation_Node_getState = R"doc(Degrees-of-Freedom)doc";

static const char *__doc_sofa_simulation_Node_getTopology = R"doc(Topology)doc";

static const char *__doc_sofa_simulation_Node_getTreeNode = R"doc(Get a descendant node given its name)doc";

static const char *__doc_sofa_simulation_Node_getTreeObject =
R"doc(Return an object of this node and sub-nodes deriving from a given
class, or NULL if not found. Note that only the first object is
returned.)doc";

static const char *__doc_sofa_simulation_Node_getTreeObject_2 = R"doc()doc";

static const char *__doc_sofa_simulation_Node_getTreeObjects =
R"doc(List all objects of this node and sub-nodes deriving from a given
class)doc";

static const char *__doc_sofa_simulation_Node_getTreeObjects_2 =
R"doc(List all objects of this node and sub-nodes deriving from a given
class)doc";

static const char *__doc_sofa_simulation_Node_getTreeObjects_3 =
R"doc(List all objects of this node and sub-nodes deriving from a given
class)doc";

static const char *__doc_sofa_simulation_Node_getTreeObjects_4 =
R"doc(List all objects of this node and sub-nodes deriving from a given
class This function is return a std::vector by copy but should be
compatible with Return Value Optimization so the copy should be
removed by the compiler. Eg: for( BaseObject* o :
node->getTreeObjects() ) { ... } for( VisualModel* v :
node->getTreeObjects<VisualModel>() ) { ... })doc";

static const char *__doc_sofa_simulation_Node_getVisualLoop = R"doc()doc";

static const char *__doc_sofa_simulation_Node_init = R"doc(Initialize the components)doc";

static const char *__doc_sofa_simulation_Node_initData = R"doc()doc";

static const char *__doc_sofa_simulation_Node_initData_2 = R"doc()doc";

static const char *__doc_sofa_simulation_Node_initData_3 = R"doc()doc";

static const char *__doc_sofa_simulation_Node_initLink = R"doc()doc";

static const char *__doc_sofa_simulation_Node_initVisualContext =
R"doc(Called during initialization to corectly propagate the visual context
to the children)doc";

static const char *__doc_sofa_simulation_Node_initialize =
R"doc(Must be called after each graph modification. Do not call it directly,
apply an InitVisitor instead.)doc";

static const char *__doc_sofa_simulation_Node_initialized = R"doc()doc";

static const char *__doc_sofa_simulation_Node_interactionForceField = R"doc()doc";

static const char *__doc_sofa_simulation_Node_isInitialized = R"doc()doc";

static const char *__doc_sofa_simulation_Node_linearSolver = R"doc()doc";

static const char *__doc_sofa_simulation_Node_listener = R"doc()doc";

static const char *__doc_sofa_simulation_Node_mapping = R"doc()doc";

static const char *__doc_sofa_simulation_Node_mass = R"doc()doc";

static const char *__doc_sofa_simulation_Node_mechanicalMapping = R"doc()doc";

static const char *__doc_sofa_simulation_Node_mechanicalState = R"doc()doc";

static const char *__doc_sofa_simulation_Node_meshTopology = R"doc()doc";

static const char *__doc_sofa_simulation_Node_moveChild = R"doc(Move a node in this from another node)doc";

static const char *__doc_sofa_simulation_Node_moveChild_2 = R"doc(Move a node in this from another node)doc";

static const char *__doc_sofa_simulation_Node_moveObject = R"doc(Move an object from another node)doc";

static const char *__doc_sofa_simulation_Node_notifyBeginAddChild = R"doc()doc";

static const char *__doc_sofa_simulation_Node_notifyBeginAddObject = R"doc()doc";

static const char *__doc_sofa_simulation_Node_notifyBeginAddSlave = R"doc()doc";

static const char *__doc_sofa_simulation_Node_notifyBeginRemoveChild = R"doc()doc";

static const char *__doc_sofa_simulation_Node_notifyBeginRemoveObject = R"doc()doc";

static const char *__doc_sofa_simulation_Node_notifyBeginRemoveSlave = R"doc()doc";

static const char *__doc_sofa_simulation_Node_notifyEndAddChild = R"doc()doc";

static const char *__doc_sofa_simulation_Node_notifyEndAddObject = R"doc()doc";

static const char *__doc_sofa_simulation_Node_notifyEndAddSlave = R"doc()doc";

static const char *__doc_sofa_simulation_Node_notifyEndRemoveChild = R"doc()doc";

static const char *__doc_sofa_simulation_Node_notifyEndRemoveObject = R"doc()doc";

static const char *__doc_sofa_simulation_Node_notifyEndRemoveSlave = R"doc()doc";

static const char *__doc_sofa_simulation_Node_notifySleepChanged = R"doc()doc";

static const char *__doc_sofa_simulation_Node_object = R"doc()doc";

static const char *__doc_sofa_simulation_Node_parse =
R"doc(Parse the given description to assign values to this object's fields
and potentially other parameters)doc";

static const char *__doc_sofa_simulation_Node_precomputeTraversalOrder =
R"doc(Possible optimization with traversal precomputation, not mandatory and
does nothing by default)doc";

static const char *__doc_sofa_simulation_Node_printComponents = R"doc()doc";

static const char *__doc_sofa_simulation_Node_projectiveConstraintSet = R"doc()doc";

static const char *__doc_sofa_simulation_Node_propagateEvent = R"doc(Propagate an event)doc";

static const char *__doc_sofa_simulation_Node_reinit = R"doc(Apply modifications to the components)doc";

static const char *__doc_sofa_simulation_Node_removeAnimationLoop = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeBehaviorModel = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeChild = R"doc(Remove a child node)doc";

static const char *__doc_sofa_simulation_Node_removeCollisionModel = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeCollisionPipeline = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeConfigurationSetting = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeConstraintSet = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeConstraintSolver = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeContextObject = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeControllers = R"doc(Remove odesolvers and mastercontroler)doc";

static const char *__doc_sofa_simulation_Node_removeForceField = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeInteractionForceField = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeLinearSolver = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeListener = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeMapping = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeMass = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeMechanicalMapping = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeMechanicalState = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeMeshTopology = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeObject = R"doc(Remove an object)doc";

static const char *__doc_sofa_simulation_Node_removeOdeSolver = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeProjectiveConstraintSet = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeShader = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeState = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeTopology = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeTopologyObject = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeVisualLoop = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeVisualManager = R"doc()doc";

static const char *__doc_sofa_simulation_Node_removeVisualModel = R"doc()doc";

static const char *__doc_sofa_simulation_Node_setDebug = R"doc()doc";

static const char *__doc_sofa_simulation_Node_setDefaultVisualContextValue =
R"doc(Called after initialization to set the default value of the visual
context.)doc";

static const char *__doc_sofa_simulation_Node_setSleeping = R"doc(override context setSleeping to add notification.)doc";

static const char *__doc_sofa_simulation_Node_shaders = R"doc()doc";

static const char *__doc_sofa_simulation_Node_solver = R"doc()doc";

static const char *__doc_sofa_simulation_Node_sortComponents =
R"doc(Sort the components according to the dependencies expressed in Data
depend.)doc";

static const char *__doc_sofa_simulation_Node_state = R"doc()doc";

static const char *__doc_sofa_simulation_Node_topology = R"doc()doc";

static const char *__doc_sofa_simulation_Node_topologyObject = R"doc()doc";

static const char *__doc_sofa_simulation_Node_unsorted = R"doc()doc";

static const char *__doc_sofa_simulation_Node_updateContext =
R"doc(Update the whole context values, based on parent and local
ContextObjects)doc";

static const char *__doc_sofa_simulation_Node_updateSimulationContext =
R"doc(Update the simulation context values(gravity, time...), based on
parent and local ContextObjects)doc";

static const char *__doc_sofa_simulation_Node_updateVisualContext =
R"doc(Update the visual context values, based on parent and local
ContextObjects)doc";

static const char *__doc_sofa_simulation_Node_visualLoop = R"doc()doc";

static const char *__doc_sofa_simulation_Node_visualManager = R"doc()doc";

static const char *__doc_sofa_simulation_Node_visualModel = R"doc()doc";

static const char *__doc_sofa_simulation_Visitor = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

