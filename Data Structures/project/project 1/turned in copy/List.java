package project1;

//Finn Raae
//5/31/19
//COP3530
//linked list class
public class List {
    //link list
	public ListNode head;
	//methods
	void insertItem(String name)
    {//This method will insert a String item to the end of the linked list.
    	ListNode temp = head;		//temp node
    	if (head == null)
    	{// if this is the first insert
    		head = new ListNode(name);
    	}//end if
    	else
    	{//if not first insert
	    	while (temp.next != null)
	    	{//loops till .next is null
	    		temp = temp.next;
	    	}//end while
			temp.next = new ListNode(name);
    	}//end else
    }//end void insertItem(String name)
    
    void insertItem(String name, int pos)
    {//This method will insert a String item to the given position in the linked
    //list. You can assume that a position of 0 means the front of the list. (if
    //position is out of bounds, do not insert, but output out of bounds)
    	if (pos > size())
    	{//validates the input place
    		System.out.println("out of bounds");
    	}
    	else
    	{
	    	ListNode temp = head;			//temp node
	    	if (pos == 0)
	    	{//insert at front
	    		ListNode newLink = new ListNode(name);
	    		newLink.next = head;
	    		head = newLink;
	    	}//end if
	    	else
	    	{//
	    		for (int i = 0;i < pos-1; i++)
	    		{//loops pos amount of time
		    		temp = temp.next;
		    		i++;
		    	}//end while
		    	ListNode newLink = new ListNode(name);
		    	newLink.next = temp.next;
		    	temp.next = newLink;
	    	}//end else
    	}//end else	
    	
    }//end void insertItem(String name, int pos)
    
    boolean removeItem(String aname)
    {
	//This method will find the String with the same value as aname and
    //remove the first occurrence of that string from the list. The return of this
    //method is either true (success) or false if the string does not exist in the
    //list. Use the .equals method when comparing strings.
    	ListNode temp = head;
		
		if(head != null)
		{//if head not empty
			if(temp.head.equals(aname))
			{//remove first if its aname
				head = head.next;
				return true;
			}
			else 
			{
				while(temp.next != null)
				{//loop through list
					if(temp.next.head.equals(aname))
					{//if their equal
						if (temp.next == null)
						{//remove last element
							temp = null;
						}//end else if 
						else
						{//remove the other elements
							temp.next = temp.next.next;
						}//end else
						return true;
					}//end if
					else
					{
						temp = temp.next;
					}//end else
				}//end while
				return false;
			}//end else
		}//end if
		else
		{
			System.out.println("empty list");
			return false;
		}//end else
		
    }//end boolean removeItem(String aname)
    
    void removeItem(int position)
    {//Remove the node at position (if position is out of bounds, do not
    //remove, but output out of bounds)
    	if (position > size())
    	{//validates the input place
    		System.out.println("out of bounds");
    	}
    	else
    	{	
	    							//counter var
	    	ListNode temp = head;			//temp node
	    	if (position == 0)
	    	{//remove at front
	    		head = head.next;
	    	}//end if
	    	else
	    	{//
	    		for (int i = 0;i < position-1; i++)
	    		{//loops position amount of time
		    		temp = temp.next;
		    		i++;
		    	}//end while
	    		if (position != size())
	    		{//if post
	    			temp.next = temp.next.next;
	    		}
	    		else
	    		{
	    			temp.next = null;
	    		}
	    	}//end else
    	}
    }//end void removeItem(int position)
    
    boolean contains(String name)
    {//Return true if the linked list contains the string
    	ListNode temp = head;
		
		if(head != null)
		{
			while(temp.head != name)
			{
				if(temp.next == null)
				{
					return false;
				}//end if
				else
				{
					temp = temp.next;
				}//end else
			}//end while
			return true;
		}//end if
		else
		{
			return false;
		}//end else
		
    }//end boolean contains(String name)
    
    void clear()
    {//Remove all of the elements from the linked list
    	this.head = null;
    }//end void clear()
    
    String get(int index)
    {//Return the element at the specified position in the list.
    	//0 is the front of the list
    	if (index > size() || index < 0)
    	{// if out of bounds
    		return "out of bounds";
    	}
    	else
    	{
    		int i = 0;
        	ListNode temp = head;
        	while (i < index)
    		{//loops index amount of time
        		temp = temp.next;
        		i++;
    		}
        	return temp.head;	
    	}
    	
    }//end String get(int index)
    
    int size()
    {//Returns the number of elements in this list.
    	ListNode temp = head;
    	int i = 0;
    	if (head == null)
    	{
    		return 0;
    	}
    	else
    	{
	    	while (temp.next != null)
	    	{
	    		temp = temp.next;
	    		i++;
	    	}
	    	return i+1;
    	}
    }//end size()
    
    public String toString()
    {//Override the toString method to print out the names of all the songs in the list
    	ListNode theLink = head;
    	String temp ="";
		while(theLink != null)
		{
			temp = (temp + theLink.head + "\n"); 
			theLink = theLink.next;
		}
		return temp;
    }//end String toString() 
    
    String toHTMLString()
    {
	//Return a String that starts with < html > ends with < /html > and uses the
    //line breaks, < br/ >, in replacement of new line characters and prints out
    //all the names of all the songs in the list. See the current implementation for details.
    
    	ListNode theLink = head;
    	String temp ="<html> ";
		while(theLink != null)
		{
			temp = (temp + theLink.head + "<br/> "); 
			theLink = theLink.next;
		}
		temp = (temp + "</html>");
		return temp;
    	
    }//end String toHTMLString()
    

    //listNodes classes
    public class ListNode 
    {
    	//link nodes
    	public String head;
    	public ListNode next;
    
    	//Constructors
    	public ListNode()
    	{//constructor with no parameters, songName should be an empty string 
    		
    	}//end public ListNode()
    	
    	public ListNode(String name)
    	{//constructor with no parameters, songName should be an empty string 
    		this.head = name;
    	}//end public ListNode(String name)
    	
    	public ListNode(String name, ListNode next)
    	{//constructor with 2 parameters, name of the song and the next node in the list
    		this.head = name;
    		this.next = next;
    	}//end public ListNode(String name, ListNode next)

    }//end public class ListNode 

}//end prog