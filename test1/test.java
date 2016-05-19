 public class test
  {
    public native int intMethod(int n);

 
   public static void main(String[] args)
    {
     System.loadLibrary("test");
     test sample = new test();
     int     square = sample.intMethod(5);
  
	System.out.println("intMethod: " + square);
  }
}