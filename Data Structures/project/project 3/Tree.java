//Finn Raae
//6/19/19
//COP3530
//tree 
public class Tree
{
	//root node
	Node root;
	
	Tree ( ) 
	{//constructor
	//Sets root to null
		root = null;
	}

	public Node getRoot( ) 
	{//getter
	//Returns root
		return root;
	}
	
	public void setRoot(Node newRoot ) 
	{//Sets root to newRoot
		root = newRoot;
	}

	public boolean empty( ) 
	{//Returns true if the tree is empty and false otherwise
		return root == null;
	}

	public int count( ) 
	{//Returns the number of nodes in the tree.
	//Uses function countNodes().
		return countNodes(root);
	}
	
	public int countNodes(Node N) 
	{//Recursive function which returns the number of nodes
	//in the subtree rooted at N.
		if (N == null)
			return 0;
		else
			return (countNodes(N.left) + countNodes(N.right) + 1);//one plus cause itself
	}

	public boolean equal(Tree T) 
	{//Returns true if our tree equals tree T. Returns false otherwise.
	//Uses function equalNodes().
		return equalNodes(root, T.root);
	}

	public boolean equalNodes(Node N, Node M) 
	{//Recursive function which returns true if the subtrees rooted
	//at N and M are equal. Returns false otherwise.
		if(N == null && M == null)	//both empty
			return true;
		if(N == null && M != null || N != null && M == null)	//one or other empty
			return false;
		if(N.data != M.data)	//data does not match
			return false;
		if(!equalNodes(N.left, M.left) || (!equalNodes(N.right, M.right)))	//recursive left/right compare
				return false;
		return true;
	}
	
	public boolean search(int element) 
	{//Returns true if element belongs in the tree. Returns false otherwise.
	//Uses function searchNodes().
	return searchNodes(root, element);
	}

	public boolean searchNodes(Node N, int element) 
	{//Recursive function which returns true if element belongs to the
	//subtree rooted at N. Returns false otherwise.
		if(N != null)
		{//if empty
			if(N.data == element)
				return true;//if found
			else//recursive left or right
				return searchNodes(N.left, element) || searchNodes(N.right, element);
		}
		else
			return false;
	}//end searchNodes

	public void printLDR() 
	{//Prints the elements of the tree in in-order (LDR).
	//Uses function printLDRNodes().
		printLDRNodes(root);
	}
	
	public void printLDRNodes(Node N) 
	{//Recursive function which prints the elements of the subtree
	//rooted at N in in-order (LDR).
		if(N == null)
			return;
		printLDRNodes(N.left);//first recur on left subtree
		System.out.print(N.data + " ");//here dealing with the root
		printLDRNodes(N.right);//then recur on right subtrees
	}
	public void printLRD() 
	{//Prints the elements of the tree in post-order (LRD).
	//Uses function printLRDNodes().
		printLRDNodes(root);
	}
	public void printLRDNodes(Node N) 
	{//Recursive function which prints the elements of the subtree
	//rooted at N in post-order (LRD).
		if(N == null)
			return;
		printLRDNodes(N.left);//then recur on left subtree
		printLRDNodes(N.right);//then recur on right subtree
		System.out.print(N.data + " ");//here dealing with the root
	}
	public void printDLR() 
	{//Prints the elements of the tree in pre-order (DLR).
	//Uses function printDLRNodes().
		printDLRNodes(root);
	}
	public void printDLRNodes(Node N) 
	{//Recursive function which prints the elements of the subtree
	//rooted at N in pre-order (DLR).
		if(N == null)
			return;
		System.out.print(N.data + " ");//here dealing with the root
		printDLRNodes(N.left);//then recur on left subtree
		printDLRNodes(N.right);//then recur on right subtree
	}
	public Tree copy() 
	{//Returns a copy of our tree.
	//Uses function copyNodes().
		Tree cpTree = new Tree();
		Node cpNode = copyNodes(root);
		cpTree.setRoot(cpNode);
		return cpTree;
	}
	 
	public Node copyNodes(Node N) 
	{//Recursive function which returns a copy of the subtree rooted at N.
//		if(N != null)
//		{
//			Node temp = new Node();
//			temp.setData(N.data);
//			temp.setLeft(N.left);
//			temp.setRight(N.right);
//			
//			return temp;
//		}
		return N;
	}
	
	public void leaves( ) 
	{//Prints the leaves of our tree. The root is not a leave.
	//Uses function leavesNodes().
		 leavesNodes(root);
	}
	
	public void leavesNodes(Node N) 
	{//Recursive function which prints the leaves of the subtree
	 //rooted at N.
		if (N.left == null || N.right == null)
		{
			System.out.print(N.data + " ");
		}//end if
		else
		{
			leavesNodes(N.left);
			leavesNodes(N.right);
		}//end else
 	}

	public void internal() 
	{//Prints the internal nodes of our tree.
	//The root is not an internal node.
	//Uses function internalNodes().
		internalNodes(root);
	}
	
	//fix so doesnt show root
	public void internalNodes(Node N) 
	{//Recursive function which prints the internal nodes of the
	 //subtree rooted at N.
		if (N.left == null || N.right == null)
			return;
		else
		{
			System.out.print(N.data + " ");
			internalNodes(N.left);
			internalNodes(N.right);
		}
 	}
 	public void path(int element) 
 	{//Prints the path from root to element if element exists in the tree.
	 //Uses function pathNodes().
 		pathNodes(element, root);
 	}
 	
 	public void pathNodes(int element, Node N) 
 	{//Recursive function which prints the path from N to element.
	 //Assumes element belongs in the subtree rooted at N.
 		if(searchNodes(N, element))
 		{
 			System.out.print(N.data + " ");
 			if(N.data == element)
 				return;
 			pathNodes(element, N.left);
 			pathNodes(element, N.right);
 		}
 	}
 	
 	public int height() 
 	{//Returns the height of the tree.
	 //Uses function heightNodes().
 		return heightNodes(root);
 	}
 	public int heightNodes(Node N) 
 	{//Recursive function which returns the height of the subtree
	 //rooted at N.
 		if(N ==  null)
 			return 0;
 		else
 		{
 			return 1 + Math.max(heightNodes(N.left), heightNodes(N.right));// takes high + root 
 		}
 	}
 	public void descendents(int element) 
 	{//Prints all the descendents of element if element exists in the tree.
	//Uses function descendentsNodes().
 		descendentsNodes(root, element);
	}
	public void descendentsNodes(Node N, int element) 
	{//Recursive function which prints all the descendents of element in
	//the subtree rooted at N.
	//Assumes element belongs in the subtree rooted at N.
		if(N.left == null)
			return;
		if(element == N.data)
		{
			System.out.print(N.left.data + " " + N.right.data + " ");	//here dealing with the root
			descendentsNodes(N.left, N.left.data);	//then recur on left subtree
			descendentsNodes(N.right, N.right.data);	//then recur on right subtree
		}
		descendentsNodes(N.left, element);	//then recur on left subtree
		descendentsNodes(N.right, element);	//then recur on right subtree
	}

}//end public class Tree
