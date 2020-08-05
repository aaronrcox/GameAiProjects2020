#pragma once

#include <vector>
#include <list>
#include <functional>

template<class TNodeData, class TEdgeData>
class Graph
{
public:

	struct Node;
	struct Edge;

	struct Node
	{
		TNodeData data;
		std::vector<Edge> connections;
	};

	struct Edge
	{
		Node* to;
		TEdgeData data; // COST
	};

	struct PFNode
	{
		Node* gNode;
		PFNode* parent = nullptr;
		float gScore; // parents gScore + cost to trave from parent to this node.
		// float hScore; // huristic estimate to goalNode (AStar)
		// float fScore; // gScore + hScore
	};

public:

	// ========================================================================
	// Constructor
	// ========================================================================
	Graph()
	{

	}

	// ========================================================================
	// Destructor
	// ========================================================================
	virtual ~Graph()
	{

	}

	// ========================================================================
	// Add Node
	// ========================================================================
	Node* AddNode(const TNodeData& data)
	{
		Node* node = new Node();
		node->data = data;
		m_nodes.push_back(node);
		return node;
	}

	// ========================================================================
	// AddEdge
	// ========================================================================
	void AddEdge(Node* nodeA, Node* nodeB, const TEdgeData& data)
	{
		nodeA->connections.push_back({ nodeB, data });		
	}

	// ========================================================================
	// GetNodes
	// ========================================================================
	const std::vector<Node*>& GetNodes()
	{
		return m_nodes;
	}

	// ========================================================================
	// ForEachBFS - iterates through the graph using Breth First Search
	// startNode: the node that the BFS algorithm will start from
	//            if null, the startNode will be the first node in the graph
	// predicate: method that returns true if the provided node has been found.
	// ========================================================================
	Node* ForEachBFS(Node* startNode, std::function<bool(Node* n)> process)
	{
		if (m_nodes.empty())
			return nullptr;

		std::vector<Node*> visited;
		std::list<Node*> queue;

		if (startNode == nullptr)
			startNode = m_nodes[0];

		queue.push_back(startNode);

		while (queue.empty() == false)
		{
			// get node at front of stack, and then remove the node from the stack.
			Node* node = queue.front();
			queue.pop_front();

			// add the node to the visited
			visited.push_back(node);

			// if the predicate returns true, we can stop the search
			if (process(node)) {
				break;
			}

			// add children to the stack if they have not been visited
			for (Edge& connection : node->connections)
			{
				// does the node exist in the visited list? or,
				// is it already in the queue?
				if (std::find(visited.begin(), visited.end(), connection.to) == visited.end() &&
					std::find(queue.begin(), queue.end(), connection.to) == queue.end())
				{
					queue.push_back(connection.to);
				}
			}
		}
	}

	// ========================================================================
	// ForEachBFS - iterates through the graph using Breth First Search
	// startNode: the node that the BFS algorithm will start from
	//            if null, the startNode will be the first node in the graph
	// predicate: method that returns true if the provided node has been found.
	// ========================================================================
	Node* ForEachDFS(Node* startNode, std::function<bool(Node* n)> process)
	{
		if (m_nodes.empty())
			return nullptr;

		std::vector<Node*> visited;
		std::vector<Node*> stack;

		if (startNode == nullptr)
			startNode = m_nodes[0];

		stack.push_back(startNode);

		while (stack.empty() == false)
		{
			// get node at end of stack, and then remove the node from the stack.
			Node* node = stack[stack.size() - 1];
			stack.pop_back();

			// add the node to the visited
			visited.push_back(node);

			// if the predicate returns true, we can stop the search
			if (process(node)) {
				break;
			}

			// add children to the stack if they have not been visited
			for (Edge& connection : node->connections)
			{
				// does the node exist in the visited list? or,
				// is it already in the stack?
				if (std::find(visited.begin(), visited.end(), connection.to) == visited.end() &&
					std::find(stack.begin(), stack.end(), connection.to) == stack.end())
				{
					stack.push_back(connection.to);
				}
			}
		}
	}

	// =======================================================================
	// Find Path
	// =======================================================================
	bool FindPath(Node* startNode, std::function<bool(Node* n)> isGoalNode, std::list<Node*>& out_path)
	{

		

		if (m_nodes.empty())
			return nullptr;

		std::vector<PFNode* > visited;
		std::list<PFNode* > stack;

		auto GetNodeInLists = [&](Node *nodeToFind) -> PFNode* {
			for (auto& n : stack)
				if (n->gNode == nodeToFind)
					return n;

			for (auto& n : visited)
				if (n->gNode == nodeToFind)
					return n;

			return nullptr;
		};


		// 
		PFNode* pfNode = new PFNode();
		pfNode->gNode = startNode;
		pfNode->parent = nullptr;
		pfNode->gScore = 0;

		stack.push_back(pfNode);

		while (stack.empty() == false)
		{
			// get node at end of stack, and then remove the node from the stack.
			PFNode* node = stack.back();
			stack.pop_back();

			// add the node to the visited
			visited.push_back(node);

			// if the isGoalNode returns true, we can stop the search
			if (isGoalNode(node->gNode)) {
				// Calculate the path
				auto current = node;
				while (current != nullptr)
				{
					out_path.push_front(current->gNode);
					current = current->parent;
				}
				return true;
			}

			// add children to the stack if they have not been visited
			for (Edge& connection : node->gNode->connections)
			{

				float gScore = node->gScore + connection.data; 

				// does the node exist in the visited list? or,
				// is it already in the stack?
				auto childPfNode = GetNodeInLists(connection.to);
				if (childPfNode == nullptr)
				{
					childPfNode = new PFNode();
					childPfNode->parent = node;
					childPfNode->gNode = connection.to;
					childPfNode->gScore = gScore;
					stack.push_back(childPfNode);
				}
				else
				{
					// lower scores are better
					if (gScore < childPfNode->gScore )
					{
						childPfNode->gScore = gScore;
						childPfNode->parent = node;
					}
				}
			}

			stack.sort([](PFNode* a, PFNode* b) {
				return a->gScore > b->gScore;
			});

		}

		return false;
	}















protected:

	std::vector<Node*> m_nodes;

private:
};