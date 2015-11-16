import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;


public class Main {
	public static void main(String[] args) throws Exception {
		int clientNumber = 0;
		ServerSocket listener = new ServerSocket(50007);
		try {
            while (true) {
                new RoboServer(listener.accept(), clientNumber++).start();
            }
        } finally {
            listener.close();
        }
	}
}