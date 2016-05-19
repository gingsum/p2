public class example_data{
	private native String[] data();
	public static void main(String[]args){
		System.loadLibrary("example_data");
		example_data ed = new example_data();
		Object[] edArr = ed.data();

		for(Object s : edArr){
			System.out.println((String)s);
		}
	}
}