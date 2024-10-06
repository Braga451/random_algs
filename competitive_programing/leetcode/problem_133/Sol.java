class Solution {
    public Node cloneGraph(Node node) {
        return dfs(node, new HashMap<Integer, Node>());       
    }

    private Node dfs(Node v, Map<Integer, Node> createdNodes) {
        if (v == null) {
            return null;
        }
        Node clonedV = nodeClone(v);
        createdNodes.put(v.val, clonedV); 

        if (v.neighbors != null) {
            for (Node w : v.neighbors.toArray(Node[]::new)) {
                Node clonedW = createdNodes.get(w.val);
                if (clonedW == null) {
                    clonedW = dfs(w, createdNodes);    
                }

                clonedV.neighbors.add(clonedW);
            }
        }

        return clonedV;
    }

    private Node nodeClone(Node n) {
        return n == null ? null : new Node(n.val);
    }
}
