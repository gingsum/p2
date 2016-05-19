import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.*;
import java.lang.Long;

 public class p2gui extends JFrame{
   // public native int intMethod(int n);
    public native int[] date(int index);
    public native long size(int index);
    public native String name(int index);
    public native boolean type(int index);

	public native void resetData();
	public native int setCurrDir(String currDir);
	public native void goUpOneDir();
	public native void sort(int index);

 	private static p2gui p2 = new p2gui();
	private static String current_directory = "c:\\";	
	private static String[] columnNames = {"Name", "Date modified", "Type","Size"};
	
	// GUI stuff
	private static JPanel	panel;
	private static JTable	table;
	private static JScrollPane	scrollPane;

	private Object[][] setTable(String currDir) {
     	int count = p2.setCurrDir(current_directory);
    	String[] date = new String[count];
    	String[] size = new String[count];
    	String[] name = new String[count];
    	String[] type = new String[count];

		for(int i = 0; i < count; i++){
			size[i] = String.format("%d",p2.size(i));
			name[i] = p2.name(i);
			if(p2.type(i))
				type[i] = "folder";
			else
				type[i] = "file";
			if(p2.date(i)[3] > 12)
				date[i] = String.format("%2d/%2d/%2d  %2d:%2d PM",p2.date(i)[0],p2.date(i)[1],
								p2.date(i)[2],p2.date(i)[3]-12,p2.date(i)[4]);
			else
				date[i] = String.format("%2d/%2d/%2d  %2d:%2d AM",p2.date(i)[0],p2.date(i)[1],
								p2.date(i)[2],p2.date(i)[3],p2.date(i)[4]);
			
		//	System.out.println(date[i] + " " +  type[i] + " " + name[i] + " " +  size[i]);
    	}

    	Object dataValues[][] = new Object[count][4];
    	for(int i = 0; i < count; i++){
    		dataValues[i][0] = name[i];
    		dataValues[i][1] = date[i];
    		dataValues[i][2] = type[i];
    		dataValues[i][3] = new Long(size[i]);
    	}
    	return dataValues;
	}

	private void deployTable(Object[][] data){
    	//JTable
    	setTitle("p2_IO");
    	setSize(800,600);

    	//frame = new JFrame();
		panel = new JPanel();
    	panel.setLayout(new BorderLayout());
    	getContentPane().add(panel);

    	TableModel model = new DefaultTableModel(data,columnNames){
    		@Override
    		public Class getColumnClass(int col){
    			if(col == 3)
    				return Long.class;
    			else
    				return String.class;
    		}
    	};

    	table = new JTable(model);
    	table.setAutoCreateRowSorter(true); // sorter
    	scrollPane = new JScrollPane(table);
    	panel.add(scrollPane, BorderLayout.CENTER);
    	//panel.getContentPane().add(table.getTableHeader());
    	p2.setVisible(true);
    	setDefaultCloseOperation(EXIT_ON_CLOSE);
	}

    public static void main(String[] args){
    	System.loadLibrary("p2_IO");
     	Object[][] newTable = p2.setTable(current_directory);
     	p2.deployTable(newTable);
     	table.getTableHeader().addMouseListener(new MouseAdapter() {
     		@Override
     		public void mouseClicked(MouseEvent e){
     			int col = table.columnAtPoint(e.getPoint());
     			int row = table.rowAtPoint (e.getPoint());

     			String name = (String) table.getValueAt(row,0);
     			//System.out.println(name);
     			//String col_name = table.getColumnName(col);
     			//String row_name = table.getRowName(row);
     	//		p2.sort(col);
     		//	DefaultTableModel model = (DefaultTableModel) table.getModel();
     	//		model.setRowCount(0);
     //			String[][] tempTable = p2.setTable(current_directory);
     	//		p2.deployTable(tempTable);

     			//System.out.println("Column index selected " + col + " " + name);
     		}
     	});
	}
}