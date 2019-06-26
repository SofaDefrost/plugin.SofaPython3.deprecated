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


static const char *__doc_sofa_simulation_Simulation =
R"doc(Main controller of the scene. Defines how the scene is inited at the
beginning, and updated at each time step. Derives from Base in order
to use smart pointers and model the parameters as Datas, which makes
their edition easy in the GUI.)doc";

static const char *__doc_sofa_simulation_Simulation_GetClass = R"doc()doc";

static const char *__doc_sofa_simulation_Simulation_HeaderFileLocation = R"doc()doc";

static const char *__doc_sofa_simulation_Simulation_Simulation = R"doc()doc";

static const char *__doc_sofa_simulation_Simulation_Simulation_2 = R"doc()doc";

static const char *__doc_sofa_simulation_Simulation_animate =
R"doc(Execute one timestep. If dt is 0, the dt parameter in the graph will
be used)doc";

static const char *__doc_sofa_simulation_Simulation_computeBBox =
R"doc(Compute the bounding box of the scene. If init is set to "true", then
minBBox and maxBBox will be initialised to a default value @warning
MechanicalObjects with showObject member set to false are ignored @sa
computeTotalBBox(Node* root, SReal* minBBox, SReal* maxBBox))doc";

static const char *__doc_sofa_simulation_Simulation_computeTotalBBox =
R"doc(Compute the bounding box of the scene. Includes all objects, may they
be displayed or not. @sa computeBBox(Node* root, SReal* minBBox,
SReal* maxBBox, bool init=true) @deprecated)doc";

static const char *__doc_sofa_simulation_Simulation_createNewGraph = R"doc(create a new graph(or tree) and return its root node.)doc";

static const char *__doc_sofa_simulation_Simulation_createNewNode = R"doc(creates and returns a new node.)doc";

static const char *__doc_sofa_simulation_Simulation_draw = R"doc(Render the scene)doc";

static const char *__doc_sofa_simulation_Simulation_dumpState = R"doc(Dump the current state in the given stream)doc";

static const char *__doc_sofa_simulation_Simulation_exportGraph =
R"doc(Print all objects in the graph in the given file (format is given by
the filename extension))doc";

static const char *__doc_sofa_simulation_Simulation_exportOBJ = R"doc(Export a scene to an OBJ 3D Scene)doc";

static const char *__doc_sofa_simulation_Simulation_exportXML = R"doc(Print all object in the graph in XML format)doc";

static const char *__doc_sofa_simulation_Simulation_getClass = R"doc()doc";

static const char *__doc_sofa_simulation_Simulation_getHeaderFileLocation = R"doc()doc";

static const char *__doc_sofa_simulation_Simulation_init = R"doc(Initialize the objects)doc";

static const char *__doc_sofa_simulation_Simulation_initData = R"doc()doc";

static const char *__doc_sofa_simulation_Simulation_initData_2 = R"doc()doc";

static const char *__doc_sofa_simulation_Simulation_initData_3 = R"doc()doc";

static const char *__doc_sofa_simulation_Simulation_initLink = R"doc()doc";

static const char *__doc_sofa_simulation_Simulation_initNode = R"doc(Init a node without changing the context of the simulation.)doc";

static const char *__doc_sofa_simulation_Simulation_initTextures = R"doc(Initialize the textures)doc";

static const char *__doc_sofa_simulation_Simulation_isDirectedAcyclicGraph = R"doc(Can the simulation handle a directed acyclic graph?)doc";

static const char *__doc_sofa_simulation_Simulation_load = R"doc(Load a scene from a file)doc";

static const char *__doc_sofa_simulation_Simulation_operator_assign = R"doc()doc";

static const char *__doc_sofa_simulation_Simulation_print = R"doc(Print all object in the graph)doc";

static const char *__doc_sofa_simulation_Simulation_reset = R"doc(Reset to initial state)doc";

static const char *__doc_sofa_simulation_Simulation_unload = R"doc(Unload a scene from a Node.)doc";

static const char *__doc_sofa_simulation_Simulation_updateContext =
R"doc(Update contexts. Required before drawing the scene if root flags are
modified.)doc";

static const char *__doc_sofa_simulation_Simulation_updateVisual = R"doc(Update the Visual Models: triggers the Mappings)doc";

static const char *__doc_sofa_simulation_Simulation_updateVisualContext =
R"doc(Update contexts. Required before drawing the scene if root flags are
modified.)doc";

static const char *__doc_sofa_simulation_getSimulation =
R"doc(Get the (unique) simulation which controls the scene. Automatically
creates one if no Simulation has been set.)doc";

static const char *__doc_sofa_simulation_setSimulation = R"doc(Set the (unique) simulation which controls the scene)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

