import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.*;
import java.lang.Long;
import java.util.ArrayList;

public class p2gui extends JFrame {
    // public native int intMethod(int n);
    public native int[] date(int index);
    public native long size(int index);
    public native String name(int index);
    public native boolean type(int index);
    public native void resetData();
    public native int setCurrDir(String currDir);

    private static String current_directory = "c:\\";
    private static String[] columnNames = {"Name", "Date modified", "Type", "Size"};

    // GUI stuff
    private static JPanel panel;
    private static JTable table;
    private static JScrollPane scrollPane;

    public void init() {
        //JTable
        setTitle("p2_IO");
        setSize(800, 600);

        //frame = new JFrame();
        panel = new JPanel();
        panel.setLayout(new BorderLayout());
        getContentPane().add(panel);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        setTable(current_directory);
    }

    private void setTable(String directory) {
        panel.removeAll();

        Object[][] data = getDirectoryInformation(directory);
        TableModel model = new DefaultTableModel(data, columnNames) {
            @Override
            public Class getColumnClass(int col) {
                if (col == 3)
                    return Long.class;
                else
                    return String.class;
            }
        };

        if (data.length > 0 ) {
            System.out.println("Data: " + data[0][0]);
        }

        table = new JTable(model);
        table.setAutoCreateRowSorter(true); // sorter

        DefaultRowSorter sorter = ((DefaultRowSorter)table.getRowSorter());
        ArrayList list = new ArrayList();
        list.add( new RowSorter.SortKey(2, SortOrder.DESCENDING) );     // sort folder
        sorter.setSortKeys(list);
        sorter.sort();

        table.getSelectionModel().addListSelectionListener(new ListSelectionListener(){
            public void valueChanged(ListSelectionEvent event) {
                if (!event.getValueIsAdjusting()) {
                    String folderName = directory + "\\" +
                            table.getValueAt(table.getSelectedRow(), 0).toString();

                    String fileType = table.getValueAt(table.getSelectedRow(), 2).toString();

                    if (fileType.equals("folder")) {
                        setTable(folderName);
                    }
                }
            }
        });

        scrollPane = new JScrollPane(table);
        panel.add(scrollPane, BorderLayout.CENTER);
        setVisible(true);
    }

    private Object[][] getDirectoryInformation(String path) {
        int count = setCurrDir(path);
        String[] date = new String[count];
        String[] size = new String[count];
        String[] name = new String[count];
        String[] type = new String[count];

        for (int i = 0; i < count; i++) {
            size[i] = String.format("%d", size(i));
            name[i] = name(i);
            if (type(i))
                type[i] = "folder";
            else
                type[i] = "file";
            if (date(i)[3] > 12)
                date[i] = String.format("%2d/%2d/%2d  %2d:%2d PM", date(i)[0], date(i)[1],
                        date(i)[2], date(i)[3] - 12, date(i)[4]);
            else
                date[i] = String.format("%2d/%2d/%2d  %2d:%2d AM", date(i)[0], date(i)[1],
                        date(i)[2], date(i)[3], date(i)[4]);
        }

        Object dataValues[][] = new Object[count][4];
        for (int i = 0; i < count; i++) {
            dataValues[i][0] = name[i];
            dataValues[i][1] = date[i];
            dataValues[i][2] = type[i];
            dataValues[i][3] = new Long(size[i]);
        }
        return dataValues;
    }

    public static void main(String[] args) {
        System.loadLibrary("p2_IO");
        p2gui p2 = new p2gui();
        p2.init();
    }
}