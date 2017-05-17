package Network;

/**
 * Created by tungv on 5/12/2017.
 */

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {

    public static void main(String [] args) {


        ServerSocket server;
        try {
            server = new ServerSocket(8188);
            System.out.print("Dang cho ket noi");
            Socket socket=server.accept();

            FileInputStream in = new FileInputStream("D://input.txt");
            int ibyte= in.available();
            byte[] buffer= new byte[ibyte];
            in.read(buffer,0,ibyte);
            DataOutputStream output = new DataOutputStream(socket.getOutputStream());
            output.write(buffer, 0, ibyte);
            output.close();


        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }


    }


}
