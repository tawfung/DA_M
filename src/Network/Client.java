package Network;

/**
 * Created by tungv on 5/12/2017.
 */
import java.io.DataInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;
import java.net.UnknownHostException;


public class Client {
    public static void  main(String [] args) {

        Socket socket;
        try {
            socket = new Socket("Localhost",8188);
            DataInputStream inFromServer = new DataInputStream(socket.getInputStream());

            FileOutputStream output= new FileOutputStream("D://output.txt");
            DataInputStream input = new DataInputStream(socket.getInputStream());
            int is= input.available();
            byte[] data= new byte[is];
            input.read(data);
            output.write(data, 0, is);

        } catch (UnknownHostException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }





    }


}