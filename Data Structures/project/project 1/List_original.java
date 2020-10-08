public class List {
    ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////
    ////// Replace this arraylist implementation/ ///////
    ////// with a Linked List implementation ///////////
    ///////////////////////////////////////////////////
    //////////////////////////////////////////////////
    String[] alist; // String alist[];
    int ind; // holding the last element in my list
    
    public List() { // constructors always have the same name as the class
        alist = new String[2];
        ind = -1; // nothing in my list
    }
    
    public void insertItem(String aname) {
        if(ind+1 == alist.length) {//about to go out of bounds
            String[]newlist = new String[alist.length*2]; //doubling the array size
            for(int i=0;i<alist.length;i++) {
                newlist[i] = alist[i];
            }
            alist = newlist;
        }
        alist[ind+1] = aname;
        ind++;
    }
    
    public void insertItem(String aname, int pos) {
        if(ind+1 == alist.length) {//about to go out of bounds
            String[] newlist = new String[alist.length*2]; // doubling the array
            for(int i=0;i<alist.length;i++) {
                newlist[i] = alist[i];
            }
            alist = newlist;
        }
        if(pos == ind+1) {
            alist[pos] = aname;
            ind++;
        }
        else if(pos < 0 || pos > ind+1) {
            System.out.println("Not a valid position");
        }
        else if(pos < ind+1) {
            for(int i = ind+1; i > pos; i--) {
                alist[i] = alist[i-1];
            }
            alist[pos] = aname;
            ind++;
        }
    }
    
    public void removeItem(int pos) {
        if(pos == ind) {
            alist[pos] = null;
            ind--;
        }
        else if(pos < 0 || pos > ind) {
            System.out.println("Not a valid position");
        }
        else if(pos < ind) {
            for(int i = pos; i<ind; i++) {
                alist[i] = alist[i+1];
            }
            alist[ind] = null;
            ind--;
        }
        
    }
    
    public boolean removeItem(String aname) {
        for(int i=0;i<=ind;i++) {
            if(alist[i].equals(aname)) {
                removeItem(i);
                return true;
            }
        }
        return false;
    }
    
    public boolean contains(String aname) {
        boolean found = false;
        for(int i=0;i<=ind;i++) {
            if(alist[i].equals(aname)) {
                found = true;
            }
        }
        return found;
    }
    
    public void clear() {
        for(int i=0;i<=ind;i++) {
            alist[i] = null;
        }
        ind = -1;
    }
    
    public String get(int index) {
        return alist[index];
    }
    
    public int size() {
        return (ind + 1);
    }
    public String toHTMLString() {
        String temp = "<html>PlayList<br/>";
        for(int i=0;i<=ind; i++) {
            temp = temp+alist[i]+"<br/>";
        }
        temp = temp+"</html>";
        return temp;
    }
    
    
    @Override
    public String toString() {
        String temp = "";
        for(int i=0;i<=ind; i++) {
            temp = temp+alist[i]+"\n";
        }
        return temp;
    }
    
}