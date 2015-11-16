import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;


public class RoboServer extends Thread {
    private Socket socket;
    private int clientNumber;

    public double gyro,distance,mLeft,mRight,penSize;

    public RoboServer(Socket _socket, int _clientNumber) {
        socket = _socket;
        clientNumber = _clientNumber;
    }

    public void run() {
        try {
            BufferedReader in = new BufferedReader(
                    new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            while (true) {
                String input = in.readLine();
                if (input == null || input.equals(".")) break;
                parseString(input);
                out.println(input.toUpperCase());
            }
        } catch (IOException e) {
            log("error");
        } finally {
            try {
                socket.close();
            } catch (IOException e) {
                log("we seem to have a bit of an issue");
            } log("connection broken");
        }
    }

    private void parseString(String input) {
        String[] valString = input.split(",");
        double[] vals = new double[valString.length];
        for (int i = 0; i < vals.length; i++)
            vals[i] = Double.parseDouble(valString[i]);
        gyro = vals[0]; distance = vals[1];
    }

    private String outString() {
        String outey = mLeft+","+mRight+","+penSize+"|";
        return outey;
    }

    private void log(String message) {
        System.out.println(message);
    }
}