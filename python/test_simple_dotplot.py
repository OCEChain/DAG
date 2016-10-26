import pydot
'''Simple example to demonstrate producing a plot of a DAG via pydot (need to install) and python
'''


    
def plot_dag (graph, nodeids, nodeparents, nodelabels=None, nodecolors=None):
    #creates graphnodes and graph edges for the dot plot based on the nodes
    graphnodes = dict() 
    if nodecolors is None:
        nodecolors=["yellow"]*len(nodeids)
    if nodelabels is None:
        nodelabels=nodeids   
    for i in range(len(nodeids)): #add graph nodes
        nodeid = nodeids[i]
        if  graphnodes.has_key(nodeid)==False: #check if already exists
            graphnodes[nodeid] = pydot.Node(nodeid, style="filled", label=nodelabels[i], fillcolor=nodecolors[i])
            graph.add_node( graphnodes[nodeid]) 
    for i in range(len(nodeids)): #add graph edges
        nodeid = nodeids[i]
        for c in nodeparents[nodeid]:
            if len(graph.get_edge(graphnodes[c],graphnodes[nodeid]))==0:#check if already exists
                graph.add_edge(pydot.Edge(  graphnodes[c],graphnodes[nodeid])) 

if __name__ == '__main__':
    history = dict()
    nodeids = [1,2,3,4]
    nodelabels = ["one", "two", "three", "four"]
    nodecolors = ["red", "lightblue", "green","green"]
    nodeparents = dict()
    nodeparents[4] = [2,3]
    nodeparents[2] = [1]
    nodeparents[3] = [1]
    nodeparents[1] = []
    
    graph = pydot.Dot(graph_type='digraph')
    plot_dag(graph, nodeids, nodeparents, nodelabels, nodecolors)
    namestring='test_dag.png'
    graph.write_png(namestring)     