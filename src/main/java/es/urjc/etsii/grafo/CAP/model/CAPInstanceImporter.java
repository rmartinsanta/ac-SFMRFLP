package es.urjc.etsii.grafo.CAP.model;

import es.urjc.etsii.grafo.io.InstanceImporter;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Scanner;

public class CAPInstanceImporter extends InstanceImporter<CAPInstance> {

    private static final int N_FAKES = 0;

    @Override
    public CAPInstance importInstance(BufferedReader reader, String filename) throws IOException {

        // Loads the Problem dimensions
        var data = new CAPInstance(filename);
        var sc = new Scanner(reader);

        data.nN = sc.nextInt();

        // Includes fake facilities
        int F = N_FAKES; // Raul: refactor changed to 0
        data.nN += F;

        // Loads the Length vector
        data.L = new int[data.nN];
        for (int j = 0; j < data.nN - F; j++) {
            data.L[j] = sc.nextInt();
            data.L[j] = 4 * data.L[j];
        }
        for (int j = data.nN - F; j < data.nN; j++) data.L[j] = 2;

        // Loads the Costs matrix
        data.W = new int[data.nN][data.nN];
        for (int u = 0; u < data.nN - F; u++) {
            for (int v = 0; v < data.nN - F; v++) {
                data.W[u][v] = sc.nextInt();
                if (v < u) data.W[u][v] = data.W[v][u];
            }
        }

        return data;
    }
}
