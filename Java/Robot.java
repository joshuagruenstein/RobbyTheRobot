import java.io.*;
import java.net.*;

public class Robot {
    private double gyro,distance,mLeft,mRight,
                  penSize,penR,penG,penB;

    public boolean penIs = false;

    public RoboServer() {

    }

    public double getGyro() {
        return gyro;
    }

    public double getDistance() {
        return distance;
    }

    public void setPen(boolean penIs) {
        this.penIs = penIs;
    }

    public void setPen(double r, double g, double b) {
        penR = r;
        penG = g;
        penB = b;
    }

    public void setMotors(double mLeft, double mRight) {
        this.mLeft = mLeft;
        this.mRight = mRight;
    }

    private void parseString(String input) {
        String[] valString = input.split(",");
        double[] vals = new double[valString.length];
        for (int i = 0; i < vals.length; i++)
            vals[i] = Double.parseDouble(valString[i]);
        gyro = vals[0]; distance = vals[1];
    }

    private String outString() {
        String outey = mLeft+","+mRight+","+penSize
                       penR+","+penG+","+penB+"|";
        return outey;
    }
}