 public class p2_IO
  {
    public native int intMethod(int n);
    public native boolean booleanMethod(boolean bool);
    public native String stringMethod(String text);
    public native int intArrayMethod(int[] intArray);

    public native int []intArray();

    //public native String [] stringArrayMethod();

 
   public static void main(String[] args)
    {
     System.loadLibrary("p2_IO");
     p2_IO sample = new p2_IO();
     int     square = sample.intMethod(5);
     boolean bool   = sample.booleanMethod(true);
     String  text   = sample.stringMethod("JAVA");
     int     sum    = sample.intArrayMethod(
                         new int[]{1,1,2,3,5,8,13} );

     int[] intArr = sample.intArray();

     for(int i : intArr){
        if (i != 0)
            System.out.println("intArray: " + i);
     }


	System.out.println("intMethod: " + square);
	System.out.println("booleanMethod: " + bool);
	System.out.println("stringMethod: " + text);
	System.out.println("intArrayMethod: " + sum);
  }
}