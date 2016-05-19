public class p2_GUI{
	public native String[] name();
	//public native int[] date();
	//public native boolean[] type();
//	public native long[] size();

	public static void main(String[] args){
		System.loadLibrary("p2_GUI");
		p2_GUI p2 = new p2_GUI();
		String[] nameArr = p2.name();
//		int[] dateArr = p2.date();
//		boolean[] typeArr = p2.type();
//		long[] sizeArr = p2.size();

		for(int i = 0; i < nameArr.length; i++){
			//if(name[i] != NULL)
				System.out.println(nameArr[i] /*+ " " + typeArr[i] + " "
					+ dateArr[i] + " " +  sizeArr[i]*/);
		}
	}
}